//! Our goal: be able to store selection queries in simple one-liners.
//!
//! We will model it after logic programming.

use std::collections::{HashMap, HashSet, VecDeque};

#[cfg(feature = "async")]
use std::sync::Arc;

use itertools::Itertools;
use runtime::compiler::RuleCycleDetector;

use crate::{parser::Predicate, runtime::AtomDisplayWrapper};

pub mod library;
pub mod parser;
pub mod runtime;
pub mod storage;

pub use runtime::{
    compiler::{Compiler, ProgramError},
    Atom, BodyAtom, CompiledProgram, GroundedAtom, GroundedBodyAtom, GroundedGoal, GroundedTerm,
    Rule, Term,
};
pub use storage::{Fixed, FixedStorage, Memoized, Storage, ThreadsafeStorageRef};

fn fixed_point_expand(
    facts: &[(String, Vec<GroundedTerm>)],
    rules: &[Rule],
    universe: &HashSet<GroundedTerm>,
    other: &[ThreadsafeStorageRef],
) -> (Fixed, HashSet<GroundedTerm>) {
    let mut total_facts = HashSet::new();

    // Try to do semi-naïve evaluation
    let mut iteration_facts: HashSet<_> = facts
        .iter()
        .map(|(name, terms)| GroundedAtom {
            predicate: parser::Predicate {
                is_intrinsic: false,
                name: name.to_string(),
            },
            terms: terms.clone(),
        })
        .chain(
            other
                .iter()
                .flat_map(|s| s.as_fixed())
                .flat_map(|fs| fs.get_facts()),
        )
        .collect();
    let mut counter = 0;

    // Get the actual universe (including terms from storage assertions)
    let universe: HashSet<_> = universe
        .union(
            &iteration_facts
                .iter()
                .flat_map(|atom| atom.terms.iter().cloned())
                .collect(),
        )
        .cloned()
        .collect();

    // Regenerate rule edges
    let rule_edges: HashSet<_> = rules
        .iter()
        .flat_map(|rule| {
            rule.body.iter().map(|from| {
                (
                    from.atom().predicate.clone(),
                    Predicate {
                        is_intrinsic: false,
                        name: rule.head.0.clone(),
                    },
                    from.negative().is_some(),
                )
            })
        })
        .collect();

    let rule_vertices: HashSet<_> = rules
        .iter()
        .flat_map(|rule| {
            rule.body
                .iter()
                .map(|from| from.atom().predicate.clone())
                .chain(std::iter::once(Predicate {
                    is_intrinsic: false,
                    name: rule.head.0.clone(),
                }))
        })
        .collect();

    let scc_detector = RuleCycleDetector {
        possible_rules: rule_vertices,
        edges: rule_edges,
    };

    // How we generate the canonical order to visit rules to generate facts
    let canonical_order: Vec<_> = scc_detector
        .sccs()
        .collect::<Vec<_>>()
        .into_iter()
        .rev()
        .collect();

    tracing::debug!(
        "Canonical order: {}",
        canonical_order
            .iter()
            .map(|nodes| nodes.iter().join(" <-> "))
            .join(", ")
    );

    while !iteration_facts.is_empty() {
        // Learn all the current iteration's facts
        tracing::debug!(
            "Iteration {counter}: {}",
            iteration_facts
                .iter()
                .map(|i: &GroundedAtom| i.to_string())
                .collect::<Vec<_>>()
                .join(", ")
        );
        counter += 1;
        total_facts.extend(iteration_facts.drain());

        for rule_cycle in canonical_order.iter() {
            // let mut analyzed: HashSet<_> = HashSet::new();
            // let mut executed_count = 0;

            // let mut done_expanding = HashSet::new();
            let mut rule_queue: VecDeque<_> = rules
                .iter()
                .filter(|rule| {
                    rule_cycle
                        .iter()
                        .any(|head| head.to_string() == rule.head.0)
                })
                .collect();

            while let Some(rule) = rule_queue.pop_front() {
                tracing::info!("Expanding {rule}");
                // All rule terms are groundable
                let pos: HashSet<_> = rule.body.iter().filter_map(BodyAtom::positive).collect();
                let neg: HashSet<_> = rule.body.iter().filter_map(BodyAtom::negative).collect();

                let rule_max = rule
                    .body
                    .iter()
                    .flat_map(|t| {
                        t.atom().terms.iter().filter_map(|t| match t {
                            Term::Variable(v) => Some(*v),
                            _ => None,
                        })
                    })
                    .max()
                    .unwrap_or(rule.mapping.len());

                let mut mapping = HashMap::new();

                for brule in rule.body.iter() {
                    let relevant: Vec<_> = total_facts
                        .iter()
                        // .chain(iteration_facts.iter())
                        .filter(|f| {
                            f.predicate == brule.atom().predicate
                                && f.terms.len() == brule.atom().terms.len()
                        })
                        .collect();
                    match brule {
                        // Negative atoms cannot tell us values a variable can take, but can restrict the universe
                        BodyAtom::Negative(neg) => {
                            for fact in relevant.iter() {
                                for (fterm, term) in fact.terms.iter().zip(neg.terms.iter()) {
                                    if let Term::Variable(v) = term {
                                        let deny = mapping.entry(*v).or_insert(HashSet::new());
                                        deny.insert(fterm.clone());
                                    }
                                }
                            }
                        }
                        BodyAtom::Positive(_pos) => {
                            // Dont check positive values, we don't need to as we test
                            // all combinations of the universe
                        }
                    }
                }

                let inferred_mapping = (0..std::cmp::max(rule_max, rule.mapping.len()))
                    .map(|i| {
                        mapping
                            .get(&i)
                            .cloned()
                            .map(|deny| {
                                let undenied: HashSet<_> =
                                    universe.difference(&deny).cloned().collect();

                                undenied
                            })
                            .unwrap_or(universe.iter().cloned().collect())
                            .into_iter()
                            .collect::<Vec<_>>()
                    })
                    .multi_cartesian_product()
                    .collect::<Vec<_>>();

                // If inferred_mapping is 0, the fact must be proven w/o input variables
                if inferred_mapping.is_empty() {
                    let valid = pos
                        .iter()
                        .map(|ba| (ba, false))
                        .chain(neg.iter().map(|ba| (ba, true)))
                        .all(|(dep_ba, is_neg)| {
                            let Some(atom) = dep_ba.as_grounded() else {
                                // Rule is not valid if it is ungroundable
                                return false;
                            };
                            if is_neg {
                                !total_facts.contains(&atom)
                                    && !iteration_facts.contains(&atom)
                                    && other
                                        .iter()
                                        .filter_map(|s| {
                                            s.query(
                                                &atom.predicate,
                                                &atom.terms.iter().collect::<Vec<_>>(),
                                            )
                                        })
                                        .all(|q| !q)
                            } else {
                                total_facts.contains(&atom)
                                    || iteration_facts.contains(&atom)
                                    || other
                                        .iter()
                                        .filter_map(|s| {
                                            s.query(
                                                &atom.predicate,
                                                &atom.terms.iter().collect::<Vec<_>>(),
                                            )
                                        })
                                        .any(|q| q)
                            }
                        });

                    if !valid {
                        continue;
                    }

                    let Some(fact) = rule
                        .head
                        .1
                        .iter()
                        .map(|t| t.as_grounded())
                        .collect::<Option<Vec<_>>>()
                        .map(|terms| GroundedAtom {
                            predicate: Predicate {
                                is_intrinsic: false,
                                name: rule.head.0.clone(),
                            },
                            terms,
                        }) else {
                            continue;
                        };

                    if !total_facts.contains(&fact) {
                        tracing::info!(
                            "Created static inference {}",
                            AtomDisplayWrapper(&Atom {
                                predicate: Predicate {
                                    is_intrinsic: false,
                                    name: rule.head.0.clone()
                                },
                                terms: rule.head.1.clone()
                            }),
                        );
                        iteration_facts.insert(fact.clone());
                    }
                    // continue;
                }

                // Now we are only exploring a fully body-groundable rule, where all body atoms are can be known

                for inference in inferred_mapping.into_iter() {
                    let valid = pos
                        .iter()
                        .map(|ba| (ba, false))
                        .chain(neg.iter().map(|ba| (ba, true)))
                        .all(|(dep_ba, is_neg)| {
                            let atom = dep_ba.ground(&inference).unwrap();
                            if is_neg {
                                !total_facts.contains(&atom)
                                    && !iteration_facts.contains(&atom)
                                    && other
                                        .iter()
                                        .filter_map(|s| {
                                            s.query(
                                                &atom.predicate,
                                                &atom.terms.iter().collect::<Vec<_>>(),
                                            )
                                        })
                                        .all(|q| !q)
                            } else {
                                total_facts.contains(&atom)
                                    || iteration_facts.contains(&atom)
                                    || other
                                        .iter()
                                        .filter_map(|s| {
                                            s.query(
                                                &atom.predicate,
                                                &atom.terms.iter().collect::<Vec<_>>(),
                                            )
                                        })
                                        .any(|q| q)
                            }
                        });

                    if !valid {
                        continue;
                    }

                    // mutated = true;

                    let fact = rule
                        .head
                        .1
                        .iter()
                        .map(|t| t.ground(&inference))
                        .collect::<Option<Vec<_>>>()
                        .map(|terms| GroundedAtom {
                            predicate: Predicate {
                                is_intrinsic: false,
                                name: rule.head.0.clone(),
                            },
                            terms,
                        })
                        .unwrap();

                    if !total_facts.contains(&fact) {
                        tracing::info!(
                            "Created inference {} for {}",
                            AtomDisplayWrapper(&Atom {
                                predicate: Predicate {
                                    is_intrinsic: false,
                                    name: rule.head.0.clone()
                                },
                                terms: rule.head.1.clone()
                            }),
                            inference.iter().join(", ")
                        );
                        iteration_facts.insert(fact.clone());
                    }
                }
            }
        }
    }

    (
        Fixed {
            facts: total_facts.into_iter().collect(),
        },
        universe,
    )
}

#[derive(Debug)]
#[cfg_attr(
    feature = "serde_internal",
    derive(serde::Serialize, serde::Deserialize)
)]
pub enum EvalOutput {
    /// Proof tree for the goal.
    /// Returned if the goal is grounded.
    /// None indicates ungrounded goals exist.
    Proof(Option<Vec<GroundedBodyAtom>>),
    /// Sets of valid values that a term can take to satisfy the program.
    Valid(HashMap<String, HashSet<GroundedTerm>>),
    /// A variable wasn't groundable.
    Invalid,
}

impl EvalOutput {
    pub fn goal_satisfied(&self) -> bool {
        match self {
            // A proof exists.
            Self::Proof(proof) => proof.is_some(),
            // All variables must have a value that they solve for
            Self::Valid(valid) => valid.iter().all(|(_, v)| !v.is_empty()),
            Self::Invalid => false,
        }
    }
}

#[cfg(feature = "async")]
pub async fn evaluate_program_async(
    program: &CompiledProgram,
    storages: Vec<ThreadsafeStorageRef>,
) -> EvalOutput {
    if let Some(goal) = program.goal.as_grounded() {
        // Proof (top-down) semantics
        eval_proof(program, goal, storages).await
    } else {
        let (_, variables) = eval_fixed_point(program, &storages);
        if variables.is_empty() {
            EvalOutput::Invalid
        } else {
            EvalOutput::Valid(variables)
        }
    }
}

#[deprecated(since = "0.2.0", note = "please use `evaluate_program_async` instead")]
pub fn evaluate_program_nonasync(
    program: &CompiledProgram,
    storages: &[ThreadsafeStorageRef],
) -> EvalOutput {
    if let Some(goal) = program.goal.as_grounded() {
        // Proof (top-down) semantics
        eval_grounded_fixed_point(goal, program, storages)
    } else {
        let (_, variables) = eval_fixed_point(program, storages);
        if variables.is_empty() {
            EvalOutput::Invalid
        } else {
            EvalOutput::Valid(variables)
        }
    }
}

// Returns the mapping to use and the current proof
#[cfg(feature = "async")]
#[tracing::instrument(skip(facts, ext_storages))]
fn provable_from_facts(
    current_mapping: &[GroundedTerm],
    facts: &[GroundedAtom],
    subject: &Atom,
    ext_storages: Arc<Vec<ThreadsafeStorageRef>>,
) -> Option<Vec<GroundedBodyAtom>> {
    // Can the head be grounded (instatiated) with the mapping given?
    if let Some(ga) = subject.ground(current_mapping) {
        if !ga.predicate.is_intrinsic && facts.contains(&ga) {
            tracing::info!("Proved {}", ga);
            let proof = vec![GroundedBodyAtom::Positive(ga.clone())];
            Some(proof)
        } else if ga.predicate.is_intrinsic {
            let possible_storages: Vec<_> = ext_storages
                .iter()
                .filter_map(|s| s.query(&subject.predicate, &ga.terms.iter().collect::<Vec<_>>()))
                .collect();
            if possible_storages.is_empty() || possible_storages.into_iter().all(|q| !q) {
                tracing::info!("Proved not {}", ga);
                let proof = vec![GroundedBodyAtom::Negative(ga.clone())];
                Some(proof)
            } else {
                tracing::info!("Proved {}", ga);
                let proof = vec![GroundedBodyAtom::Positive(ga.clone())];
                Some(proof)
            }
        } else {
            tracing::info!("Could not prove {} from facts", ga);
            None
        }
    } else {
        // Current mapping has some unbounded variables
        // We cannot prove something we do not know, crash, this is a programming error
        unreachable!("Failed to ground");
    }
}

#[cfg(feature = "async")]
fn transitive_rewrite(otarget: &BodyAtom, trial_mapping: &[GroundedTerm]) -> BodyAtom {
    let target = otarget.atom();
    let rewrite_head = GroundedAtom {
        predicate: target.predicate.clone(),
        terms: target
            .terms
            .iter()
            .cloned()
            .map(|t| match t {
                Term::Variable(v) => {
                    if v < trial_mapping.len() {
                        trial_mapping[v].clone()
                    } else {
                        unreachable!()
                    }
                }
                t => t.as_grounded().unwrap(),
            })
            .collect(),
    };

    tracing::warn!(
        "transitive -> {} {trial_mapping:?} {}",
        AtomDisplayWrapper(target),
        rewrite_head,
    );

    match otarget {
        BodyAtom::Positive(_) => BodyAtom::Positive(rewrite_head.into()),
        BodyAtom::Negative(_) => BodyAtom::Negative(rewrite_head.into()),
    }
}

#[cfg(feature = "async")]
#[tracing::instrument(skip(universe, facts, rules, ext_storages))]
async fn provable<'a>(
    universe: Vec<GroundedTerm>,
    current_mapping: Vec<GroundedTerm>,
    facts: Vec<GroundedAtom>,
    rules: Vec<Rule>,
    subject: Atom,
    ext_storages: Arc<Vec<ThreadsafeStorageRef>>,
) -> Option<Vec<GroundedBodyAtom>> {
    let (tx, agenda) = flume::unbounded();
    tx.send((
        vec![(
            current_mapping.clone(),
            GroundedBodyAtom::Positive(subject.ground(&current_mapping).unwrap()),
            vec![BodyAtom::Positive(subject.clone())],
            vec![],
            0,
        )],
        vec![],
    ))
    .unwrap();

    // Prove direct statements
    if provable_from_facts(&current_mapping, &facts, &subject, ext_storages.clone())
        .is_some_and(|p| matches!(p[0], GroundedBodyAtom::Positive(_)))
    {
        return Some(vec![GroundedBodyAtom::Positive(
            subject.ground(&current_mapping).unwrap(),
        )]);
    }

    // Atoms that we *know* are negative go here
    let mut proofs = vec![];
    let mut proof_reject = HashSet::new();

    while let Ok((mut targets, pproof)) = agenda.try_recv() {
        tracing::info!(
            "Scanning [{}] {}",
            targets
                .iter()
                .map(|(pmapping, goal, layer, rule_trace, negc)| format!(
                    "{:?} ({} :- {}) rules {{{}}} <{negc}>",
                    pmapping,
                    goal,
                    layer
                        .iter()
                        .map(|target| match target {
                            BodyAtom::Positive(a) => format!("{}", AtomDisplayWrapper(a)),
                            BodyAtom::Negative(a) => format!("not {}", AtomDisplayWrapper(a)),
                        })
                        .intersperse(", ".to_string())
                        .collect::<String>(),
                    rule_trace
                        .iter()
                        .map(|r| format!("rule{r}"))
                        .intersperse(",".to_string())
                        .collect::<String>()
                ))
                .intersperse(" ".to_string())
                .collect::<String>(),
            pproof.iter().join(" <- ")
        );
        let layer = targets.pop();

        if pproof.first().is_some_and(|proof_head: &GroundedBodyAtom| {
            proof_head.atom() == &subject.ground(&current_mapping).unwrap()
        }) {
            proofs.push(pproof);
            continue;
        }
        if let Some((pmapping, goal, mut layer, rule_trace, negc)) = layer {
            let otarget = layer.pop();
            if let Some(otarget) = otarget {
                let target = otarget.atom().clone();
                let possible = rules
                    .iter()
                    .enumerate()
                    .filter(|(_, rule)| {
                        rule.head.0 == target.predicate.to_string()
                            && rule.head.1.len() == target.terms.len()
                    })
                    .map(|(idx, r)| (idx, r.clone()))
                    .collect::<Vec<_>>();
                let proof = provable_from_facts(&pmapping, &facts, &target, ext_storages.clone());
                {
                    let pmapping = pmapping.clone();
                    let pproof = pproof.clone();

                    match otarget.clone() {
                        BodyAtom::Positive(_) => {
                            if let Some(proof) = proof {
                                tracing::info!("NEW PROOF {}", proof.iter().join(" !! "));
                                if matches!(proof[0], GroundedBodyAtom::Positive(_)) {
                                    tx.send((
                                        targets
                                            .iter()
                                            .cloned()
                                            .chain(std::iter::once((
                                                pmapping.clone(),
                                                goal.clone(),
                                                layer.clone(),
                                                rule_trace.clone(),
                                                negc,
                                            )))
                                            .collect(),
                                        proof.into_iter().chain(pproof.into_iter()).collect(),
                                    ))
                                    .unwrap();
                                }
                            } else if possible.is_empty()
                                && matches!(goal, GroundedBodyAtom::Negative(_))
                            {
                                tx.send((
                                    targets.clone(),
                                    std::iter::once(goal.clone()).chain(pproof).collect(),
                                ))
                                .unwrap();
                            }
                        }
                        BodyAtom::Negative(a) => {
                            let neg_atom = a.ground(&pmapping).unwrap();
                            tracing::info!("NEG PROOF of {}", neg_atom);

                            if let Some(proof) = proof {
                                tracing::info!(
                                    "NEW NEG PROOF {} {:?}",
                                    proof.iter().join(" !! "),
                                    otarget
                                );
                                if matches!(proof[0], GroundedBodyAtom::Negative(_)) {
                                    tx.send((
                                        targets
                                            .iter()
                                            .cloned()
                                            .chain(std::iter::once((
                                                pmapping.clone(),
                                                goal.clone(),
                                                // We have proven
                                                layer.clone(),
                                                rule_trace.clone(),
                                                negc,
                                            )))
                                            .collect(),
                                        proof.into_iter().chain(pproof.into_iter()).collect(),
                                    ))
                                    .unwrap();
                                } else if matches!(goal, GroundedBodyAtom::Negative(_)) {
                                    tracing::warn!(
                                        "Cutting upper at double negation {goal} {}",
                                        pproof.iter().join(" <- ")
                                    );
                                    tx.send((
                                        targets.clone(),
                                        std::iter::once(goal.clone())
                                            .chain(proof.into_iter())
                                            .chain(pproof.into_iter())
                                            .collect(),
                                    ))
                                    .unwrap();
                                }
                            } else if possible.is_empty() {
                                tx.send((
                                    targets
                                        .iter()
                                        .cloned()
                                        .chain(std::iter::once((
                                            pmapping.clone(),
                                            goal.clone(),
                                            layer.clone(),
                                            rule_trace.clone(),
                                            negc,
                                        )))
                                        .collect(),
                                    std::iter::once(GroundedBodyAtom::Negative(neg_atom))
                                        .chain(pproof)
                                        .collect(),
                                ))
                                .unwrap();
                            }
                        }
                    };
                }
                let tx = tx.clone();
                let otarget = otarget.clone();
                let possible = possible.into_iter().map(|(idx, applicable)| {
                    let rule_trace: Vec<_> = rule_trace
                        .iter()
                        .copied()
                        .chain(std::iter::once(idx))
                        .collect();

                    let rule_head = Atom {
                        predicate: target.predicate.clone(),
                        terms: applicable.head.1.clone(),
                    };

                    let head_vars = applicable
                        .head
                        .1
                        .iter()
                        .filter(|t| matches!(t, Term::Variable(_)))
                        .count();

                    let head_nvars: HashSet<_> = applicable
                        .head
                        .1
                        .iter()
                        .positions(|t| !matches!(t, Term::Variable(_)))
                        .collect();

                    let body_vars: HashSet<_> = applicable
                        .body
                        .iter()
                        .flat_map(|ba| ba.atom().terms.clone())
                        .filter_map(|t| match t {
                            Term::Variable(v) => Some(v),
                            _ => None,
                        })
                        .collect();
                    let body_vars = body_vars.len();

                    let target_terms: Option<Vec<_>> = target
                        .terms
                        .iter()
                        .map(|t| t.ground(&pmapping))
                        .enumerate()
                        .filter(|(i, _)| !head_nvars.contains(i))
                        .map(|(_, x)| x)
                        .collect();

                    let preserved: Vec<_> = pmapping.iter().take(head_vars).cloned().collect();
                    // let memo = memo.clone();
                    let universe = universe.clone();
                    let pproof = pproof.clone();
                    let targets = targets.clone();
                    let tx = tx.clone();
                    let pmapping = pmapping.clone();
                    let target = target.clone();
                    let goal = goal.clone();
                    let layer = layer.clone();
                    let otarget = otarget.clone();
                    async move {
                        tracing::info!(
                            "Using rule {} (preserving {:?}) to prove {}",
                            applicable,
                            preserved,
                            AtomDisplayWrapper(&target),
                        );

                        for i in &head_nvars {
                            if target.terms[*i] != applicable.head.1[*i]
                                && !matches!(target.terms[*i], Term::Variable(_))
                            {
                                tracing::warn!(
                                    "Breaking because {:?} != {:?}",
                                    target.terms[*i],
                                    applicable.head.1[*i]
                                );
                                return;
                            }
                        }

                        let body_variables = (head_vars..body_vars)
                            .map(|_| universe.clone())
                            .multi_cartesian_product();

                        let head = if let Some(target_terms) = target_terms.clone() {
                            target_terms
                        } else {
                            preserved
                        };

                        let rule_trace = rule_trace.clone();

                        if pmapping.len() >= body_vars {
                            let current_mapping: Vec<_> = head
                                .iter()
                                .chain(pmapping.iter().skip(head.len()))
                                .cloned()
                                .collect();

                            // Fully static rule
                            tracing::info!(
                                "Trying static mapping {:?} for body elements of {}",
                                current_mapping,
                                applicable
                            );

                            let new_goal = match otarget {
                                BodyAtom::Positive(_) => {
                                    GroundedBodyAtom::Positive(rule_head.ground(&head).unwrap())
                                }
                                BodyAtom::Negative(_) => {
                                    GroundedBodyAtom::Negative(rule_head.ground(&head).unwrap())
                                }
                            };

                            let body_elements: Vec<_> = applicable
                                .body
                                .iter()
                                .map(|ba| transitive_rewrite(ba, &current_mapping))
                                .collect();

                            if targets.iter().any(|(_, goal, _, _, _)| goal == &new_goal) {
                                tracing::warn!("Throwing out due to cycle",);
                                return;
                            }

                            tx.send((
                                targets
                                    .iter()
                                    .cloned()
                                    .chain(
                                        vec![
                                            (
                                                pmapping.clone(),
                                                goal.clone(),
                                                layer.clone(),
                                                rule_trace.clone(),
                                                negc,
                                            ),
                                            (
                                                current_mapping.clone(),
                                                new_goal,
                                                body_elements,
                                                rule_trace.clone(),
                                                negc,
                                            ),
                                        ]
                                        .into_iter(),
                                    )
                                    .collect(),
                                pproof.clone(),
                            ))
                            .unwrap();
                        }

                        for body_mapping in body_variables {
                            let full_mapping: Vec<_> =
                                head.iter().chain(body_mapping.iter()).cloned().collect();

                            tracing::info!(
                                "Trying full mapping {:?} for body elements of {}",
                                full_mapping,
                                applicable
                            );

                            let body_elements: Vec<_> = applicable
                                .body
                                .iter()
                                .map(|ba| transitive_rewrite(ba, &full_mapping))
                                .collect();

                            let new_goal = match otarget {
                                BodyAtom::Positive(_) => {
                                    GroundedBodyAtom::Positive(rule_head.ground(&head).unwrap())
                                }
                                BodyAtom::Negative(_) => {
                                    GroundedBodyAtom::Negative(rule_head.ground(&head).unwrap())
                                }
                            };

                            if targets.iter().any(|(_, goal, _, _, _)| goal == &new_goal) {
                                tracing::warn!("Throwing out due to cycle",);
                                return;
                            }

                            tx.send((
                                targets
                                    .iter()
                                    .cloned()
                                    .chain(
                                        vec![
                                            (
                                                pmapping.clone(),
                                                goal.clone(),
                                                layer.clone(),
                                                rule_trace.clone(),
                                                negc,
                                            ),
                                            (
                                                full_mapping.clone(),
                                                new_goal,
                                                body_elements,
                                                rule_trace.clone(),
                                                negc,
                                            ),
                                        ]
                                        .into_iter(),
                                    )
                                    .collect(),
                                pproof.clone(),
                            ))
                            .unwrap();
                        }
                    }
                });
                futures::future::join_all(possible).await.len();
            } else {
                // Transitive rule proving
                tracing::info!(
                    "GOAL ACHIEVED: {} {} {rule_trace:?} {pmapping:?} {negc}",
                    goal,
                    pproof.iter().join(" <- "),
                );

                if negc > 1 {
                    tracing::warn!("Double negation {goal} {}", pproof.iter().join(" <- "));
                }

                if matches!(goal, GroundedBodyAtom::Positive(_)) && !pproof.is_empty() {
                    tx.send((
                        targets,
                        std::iter::once(goal.clone())
                            .chain(pproof.into_iter())
                            .collect(),
                    ))
                    .unwrap();
                } else if matches!(goal, GroundedBodyAtom::Negative(_)) {
                    tracing::info!(
                        "Found negative proof of {goal} {} {negc}",
                        pproof.iter().join(" <- ")
                    );

                    let goald = targets.last().map(|(_, goal, _, _, _)| goal.atom().clone());
                    proof_reject.insert(goald.unwrap());
                    tx.send((targets.clone(), pproof)).unwrap();
                }
            }
        }
    }

    tracing::debug!(
        "Results: [{}] <<{}>>",
        proofs.iter().map(|p| p.iter().join(" <- ")).join(", "),
        proof_reject.iter().join(", "),
    );

    proofs
        .into_iter()
        .filter(|proof| {
            !proof
                .iter()
                .filter(|elem| matches!(elem, GroundedBodyAtom::Positive(_)))
                .any(|pelem| proof_reject.contains(pelem.atom()))
        })
        .max_by_key(|p| p.len())
}

#[cfg(feature = "async")]
async fn eval_proof(
    program: &CompiledProgram,
    goal: GroundedGoal,
    storages: Vec<ThreadsafeStorageRef>,
) -> EvalOutput {
    let ext_storages: Arc<Vec<_>> = Arc::new(storages);
    let universe: HashSet<_> = program.universe().into_iter().collect();
    let storage_universe: HashSet<_> = ext_storages
        .iter()
        .flat_map(|s| {
            s.as_fixed()
                .map(|f| f.get_facts().into_iter().flat_map(|a| a.terms).collect())
                .unwrap_or(vec![])
                .into_iter()
        })
        .collect();
    let total_universe: Vec<_> = universe.union(&storage_universe).cloned().collect();

    let handles: Vec<_> = goal
        .components
        .clone()
        .into_iter()
        .map(|comp| {
            let ext_storages = ext_storages.clone();
            let base_mapping = comp.atom().terms.clone();
            let facts = program
                .facts
                .iter()
                .map(|(name, terms)| GroundedAtom {
                    predicate: Predicate {
                        is_intrinsic: false,
                        name: name.clone(),
                    },
                    terms: terms.clone(),
                })
                .chain(
                    ext_storages
                        .iter()
                        .filter_map(|s| s.as_fixed())
                        .flat_map(|fs| fs.get_facts()),
                )
                .collect::<Vec<_>>();
            let is_neg = matches!(comp, GroundedBodyAtom::Negative(_));
            let subject = Atom {
                predicate: comp.atom().predicate.clone(),
                // terms: comp
                //     .atom()
                //     .terms
                //     .iter()
                //     .cloned()
                //     .map(|i| i.into())
                //     .collect(),
                terms: (0..comp.atom().terms.len()).map(Term::Variable).collect(),
            };
            let rules = program.rules.clone();
            let universe = total_universe.clone();
            async move {
                (
                    subject.clone(),
                    base_mapping.clone(),
                    provable(
                        universe,
                        // &[],
                        base_mapping,
                        facts,
                        rules,
                        subject,
                        ext_storages,
                    )
                    .await,
                    is_neg,
                )
            }
        })
        .collect();

    let handle_future = futures::future::join_all(handles);

    let subtrees = handle_future.await.into_iter().collect::<Vec<_>>();

    let overall_proof: Option<Vec<GroundedBodyAtom>> =
        subtrees.into_iter().try_fold(vec![], |otree, proof| {
            if let (_subj, _bm, Some(proof), false) = proof {
                tracing::warn!("Component proof: {}", proof.iter().join(" <- "));
                Some(otree.into_iter().chain(proof.into_iter()).collect())
            } else if let (subj, _bm, None, true) = proof {
                tracing::warn!("Negative component proof of {}", AtomDisplayWrapper(&subj));
                Some(otree.into_iter().collect())
            } else {
                None
            }
        });

    EvalOutput::Proof(overall_proof)
}

fn eval_grounded_fixed_point(
    goal: GroundedGoal,
    program: &CompiledProgram,
    ext_storages: &[ThreadsafeStorageRef],
) -> EvalOutput {
    // TODO Come up w/ faster way of proving (not rule(X) and other_rule(X))
    // TODO I might have an idea of how to do this, but I'd need some time to implement

    // Oof, I could ask fact(X), not fact2(Y), and it should be able to tell me
    // X and Y such that they are both true...
    // It should be even able to tell me what makes not fact2(Y) true by itself.
    // Where X and Y are real terms that could also be proven by an intrinsic...

    let mut proof = vec![];

    let (program_storage, _results) = eval_fixed_point(program, ext_storages);

    tracing::info!(
        "fixed-point storage: {}",
        program_storage
            .facts
            .iter()
            .map(|f| format!("{f}."))
            .join("")
    );

    // Not every variable was resolved.
    for component in goal.components {
        match &component {
            GroundedBodyAtom::Negative(neg) => {
                if program_storage.query(&neg.predicate, &neg.terms.iter().collect::<Vec<_>>())
                    == Some(true)
                    || ext_storages
                        .iter()
                        .filter_map(|s| {
                            s.query(&neg.predicate, &neg.terms.iter().collect::<Vec<_>>())
                        })
                        .any(|q| q)
                {
                    return EvalOutput::Invalid;
                } else {
                    proof.push(component.clone());
                }
            }
            GroundedBodyAtom::Positive(pos) => {
                if program_storage.query(&pos.predicate, &pos.terms.iter().collect::<Vec<_>>())
                    != Some(true)
                    && !ext_storages
                        .iter()
                        .filter_map(|s| {
                            s.query(&pos.predicate, &pos.terms.iter().collect::<Vec<_>>())
                        })
                        .any(|q| q)
                {
                    return EvalOutput::Invalid;
                } else {
                    proof.push(component.clone());
                }
            }
        }
    }
    EvalOutput::Proof(Some(proof))
}

fn eval_fixed_point(
    program: &CompiledProgram,
    storages: &[ThreadsafeStorageRef],
) -> (Fixed, HashMap<String, HashSet<GroundedTerm>>) {
    // Fixed-point semantics
    let mut satisfactory_values: HashMap<String, HashSet<GroundedTerm>> = HashMap::new();
    let universe = program.universe();

    // Ignore the output universe (which contains synthesized values)
    let (program_storage, universe) =
        fixed_point_expand(&program.facts, &program.rules, &universe, storages);

    {
        tracing::debug!("Program Proved:\n{program_storage}");

        'scan: for variable_set in [&universe]
            .into_iter()
            .map(|i| i.iter().cloned().collect::<Vec<_>>())
            .cycle()
            .take(program.goal.mapping.len())
            .multi_cartesian_product()
        {
            for goal_component in program.goal.components.iter() {
                let (atom, neg) = (
                    goal_component.atom(),
                    matches!(goal_component, BodyAtom::Negative(_)),
                );

                let gatom = atom.ground(&variable_set.to_vec()).unwrap();

                // Do we need to ask external storage?

                let proved = program_storage
                    .query(&gatom.predicate, &gatom.terms.iter().collect::<Vec<_>>())
                    .unwrap_or(false);

                let found = proved
                    || storages
                        .iter()
                        .filter_map(|s| {
                            s.query(&gatom.predicate, &gatom.terms.iter().collect::<Vec<_>>())
                        })
                        .any(|q| q);

                tracing::trace!("For vars {variable_set:?}: {gatom} {found} {neg}");

                if neg {
                    if found {
                        continue 'scan;
                    }
                } else if !found {
                    continue 'scan;
                }
            }

            for (idx, variable) in variable_set.into_iter().enumerate() {
                satisfactory_values
                    .entry(program.goal.mapping[idx].clone())
                    .or_insert(HashSet::new())
                    .insert(variable.clone());
            }
        }
    }

    (program_storage, satisfactory_values)
}
