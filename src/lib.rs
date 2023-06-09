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
pub use storage::{Fixed, FixedStorage, Memoized, Storage, StorageRef, ThreadsafeStorageRef};

fn fixed_point_expand(
    facts: &[(String, Vec<GroundedTerm>)],
    rules: &[Rule],
    universe: &HashSet<GroundedTerm>,
    other: &[&dyn Storage],
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
pub enum EvalOutput {
    /// Proof tree for the goal.
    /// Returned if the goal is grounded.
    /// None indicates ungrounded goals exist.
    Proof(Option<Vec<GroundedBodyAtom>>),
    /// Sets of valid values that a term can take to satisfy the program.
    Valid(HashMap<String, HashSet<GroundedTerm>>),
    /// No variables were groundable.
    Invalid,
}

impl EvalOutput {
    pub fn goal_satisfied(&self) -> bool {
        match self {
            // A proof exists.
            Self::Proof(proof) => proof.is_some(),
            // All variables must have a value that they solve for
            // (which we encode using the Result)
            Self::Valid(valid) => valid.iter().all(|(_, v)| !v.is_empty()),
            Self::Invalid => false,
        }
    }
}

#[cfg(feature = "async")]
pub async fn evaluate_program_async<I: IntoIterator<Item = ThreadsafeStorageRef<'static>>>(
    program: &CompiledProgram,
    storages: I,
) -> EvalOutput {
    if let Some(goal) = program.goal.as_grounded() {
        // Proof (top-down) semantics
        eval_proof(program, goal, storages).await
    } else {
        let storages: Vec<_> = storages.into_iter().map(|s| s as &dyn Storage).collect();
        let (_, variables) = eval_fixed_point(program, storages);
        if variables.is_empty() {
            EvalOutput::Invalid
        } else {
            EvalOutput::Valid(variables)
        }
    }
}

pub fn evaluate_program_nonasync<I: IntoIterator<Item = StorageRef<'static>>>(
    program: &CompiledProgram,
    storages: I,
) -> EvalOutput {
    if let Some(goal) = program.goal.as_grounded() {
        // Proof (top-down) semantics
        eval_grounded_fixed_point(goal, program, storages)
    } else {
        let storages: Vec<_> = storages.into_iter().map(|s| s as &dyn Storage).collect();
        let (_, variables) = eval_fixed_point(program, storages);
        if variables.is_empty() {
            EvalOutput::Invalid
        } else {
            EvalOutput::Valid(variables)
        }
    }
}

#[cfg(feature = "async")]
#[async_recursion::async_recursion]
async fn provable<'a>(
    universe: &[GroundedTerm],
    current_mapping: &[GroundedTerm],
    facts: &[GroundedAtom],
    rules: &[Rule],
    subject: &Atom,
    ext_storages: &[&(dyn Storage + Send + Sync)],
) -> Option<(Vec<GroundedTerm>, Vec<GroundedBodyAtom>)> {
    // If we have an unbound variable, search for in-program facts that match the shape
    // try to prove it.
    let possible: Vec<_> = rules
        .iter()
        .filter(|rule| {
            rule.head.0 == subject.predicate.to_string() && rule.head.1.len() == subject.terms.len()
        })
        .collect();

    if let Some(ga) = subject.ground(current_mapping) {
        if !ga.predicate.is_intrinsic && facts.contains(&ga) {
            tracing::info!("Proved {}", ga);
            return Some((
                current_mapping.to_vec(),
                vec![GroundedBodyAtom::Positive(ga)],
            ));
        } else if ga.predicate.is_intrinsic {
            let possible_storages: Vec<_> = ext_storages
                .iter()
                .filter_map(|s| s.query(&subject.predicate, &ga.terms.iter().collect::<Vec<_>>()))
                .collect();
            if possible_storages.is_empty() || possible_storages.into_iter().all(|q| !q) {
                tracing::info!("Proved !{}", ga);
                return Some((
                    current_mapping.to_vec(),
                    vec![GroundedBodyAtom::Negative(ga)],
                ));
            } else {
                tracing::info!("Proved {}", ga);
                return Some((
                    current_mapping.to_vec(),
                    vec![GroundedBodyAtom::Positive(ga)],
                ));
            }
        }
    } else if subject.predicate.is_intrinsic {
        let Some(ga) = subject.ground(current_mapping) else {
            return None;
        };
        // Unbound intrinsics are always unprovablely false
        let possible_storages: Vec<_> = ext_storages
            .iter()
            .filter_map(|s| s.query(&subject.predicate, &ga.terms.iter().collect::<Vec<_>>()))
            .collect();
        if possible_storages.is_empty() || possible_storages.into_iter().all(|q| !q) {
            return Some((
                current_mapping.to_vec(),
                vec![GroundedBodyAtom::Negative(ga)],
            ));
        } else {
            tracing::info!("Proved {}", ga);
            return Some((
                current_mapping.to_vec(),
                vec![GroundedBodyAtom::Positive(ga)],
            ));
        }
    }

    // Try to find a possible mapping for subrules
    'ruleexp: for rule in possible.iter() {
        tracing::trace!("Found relevant rule: {rule}");

        let indeterminate = rule
            .body
            .iter()
            .flat_map(|ba| ba.atom().terms.iter())
            .filter_map(|t| match t {
                Term::Variable(v) => {
                    if current_mapping.len() <= *v {
                        Some(*v)
                    } else {
                        None
                    }
                }
                _ => None,
            })
            .collect::<HashSet<_>>();

        let variance = indeterminate.len();

        let possible_mappings = (0..variance)
            .map(|_| universe.iter().cloned())
            .multi_cartesian_product();

        tracing::warn!("Detected {} unbounded vars: {indeterminate:?}", variance);

        // If the rule head is groundable, try to simply ground the body w/o exploration.
        let rule_head = Atom {
            predicate: subject.predicate.clone(),
            terms: rule.head.1.clone(),
        };

        'mapexp: for possible_mapping in possible_mappings {
            // refuted = false;
            let mapping: Vec<_> = current_mapping
                .iter()
                .cloned()
                .chain(possible_mapping.iter().cloned())
                .collect();
            tracing::warn!("Checking FSU: {}", mapping.iter().join(", "));

            let excluded_rules: Vec<_> = rules
                .iter()
                .cloned()
                .filter(|frule| !(frule.head == rule.head && frule.body == rule.body))
                .collect();
            let mut grounded_proof = vec![];
            // let mut refuted = false;
            for ba in rule.body.iter() {
                // Rewrite the atom in terms of the mapping
                let new_ba_atom = ba.atom();

                tracing::warn!(
                    "Rewrote {} to {}",
                    AtomDisplayWrapper(ba.atom()),
                    AtomDisplayWrapper(new_ba_atom)
                );

                let is_neg = matches!(ba, BodyAtom::Negative(_));

                tracing::info!(
                    "Searching for {} {}",
                    is_neg,
                    AtomDisplayWrapper(new_ba_atom)
                );

                if !is_neg {
                    if let Some((_mapping, proof)) = provable(
                        universe,
                        &mapping,
                        facts,
                        &excluded_rules,
                        new_ba_atom,
                        ext_storages,
                    )
                    .await
                    {
                        if mapping
                            .iter()
                            .skip(current_mapping.len())
                            .take(indeterminate.len())
                            .zip(_mapping.iter().skip(current_mapping.len()))
                            .any(|(o, t)| o != t)
                        {
                            tracing::error!(
                                "Axiom {} is unsatisfiable with {} from {}.",
                                AtomDisplayWrapper(new_ba_atom),
                                _mapping.iter().join(", "),
                                mapping.iter().join(", ")
                            );
                            return Some((
                                mapping,
                                vec![GroundedBodyAtom::Negative(
                                    subject.ground(&_mapping).unwrap(),
                                )]
                                .into_iter()
                                .chain(grounded_proof)
                                .chain(proof)
                                .collect(),
                            ));
                        };
                        // assert!(_mapping.len() == mapping.len());

                        let brule_head = new_ba_atom.ground(&_mapping).unwrap();

                        if proof.iter().any(|pa| {
                            matches!(pa, GroundedBodyAtom::Negative(_)) && &brule_head == pa.atom()
                        }) {
                            continue 'mapexp;
                        }

                        tracing::info!(
                            "PROVEN {} {} <- {}",
                            is_neg,
                            subject.ground(current_mapping).unwrap(),
                            proof.iter().join(" <- ")
                        );

                        if proof
                            .iter()
                            .any(|pa| matches!(pa, GroundedBodyAtom::Negative(_)))
                        {
                            grounded_proof.extend(
                                std::iter::once(GroundedBodyAtom::Negative(brule_head.clone()))
                                    .chain(proof.into_iter().filter(|pa| pa.atom() != &brule_head)),
                            );
                            return Some((mapping, grounded_proof));
                        }
                        grounded_proof.extend(proof);
                    } else {
                        grounded_proof.extend(std::iter::once(GroundedBodyAtom::Negative(
                            subject.ground(current_mapping).unwrap(),
                        )));
                        return Some((mapping.to_vec(), grounded_proof));
                    }
                } else {
                    let brule_head = new_ba_atom.ground(&mapping).unwrap();
                    if let Some((_, proof)) = provable(
                        universe,
                        &mapping,
                        facts,
                        &excluded_rules,
                        new_ba_atom,
                        ext_storages,
                    )
                    .await
                    {
                        tracing::error!("NEG PROOF {} {}", brule_head, proof.iter().join(" <- "));
                        if matches!(proof[0], GroundedBodyAtom::Positive(_))
                            && &brule_head == proof[0].atom()
                        {
                            grounded_proof.extend(
                                std::iter::once(GroundedBodyAtom::Negative(brule_head.clone()))
                                    .chain(proof.into_iter().filter(|pa| pa.atom() != &brule_head)),
                            );
                            return Some((mapping, grounded_proof));
                        } else if matches!(proof[0], GroundedBodyAtom::Negative(_))
                            && &brule_head == proof[0].atom()
                        {
                            // grounded_proof
                            // .extend(std::iter::once(GroundedBodyAtom::Negative(brule_head)));
                            grounded_proof.extend(proof);
                        } else {
                            grounded_proof.extend(
                                std::iter::once(GroundedBodyAtom::Negative(brule_head.clone()))
                                    .chain(proof),
                            );
                            return Some((mapping, grounded_proof));
                        }
                    } else {
                        return Some((
                            current_mapping.to_vec(),
                            vec![GroundedBodyAtom::Negative(
                                subject.ground(current_mapping).unwrap(),
                            )],
                        ));
                    }
                }
            }

            if grounded_proof.is_empty() {
                return Some((
                    mapping.clone(),
                    vec![GroundedBodyAtom::Positive(
                        rule_head.ground(&mapping).unwrap(),
                    )]
                    .into_iter()
                    .chain(grounded_proof.into_iter())
                    .collect(),
                ));
            }
        }

        let mut composite_proof = vec![];

        if variance == 0 {
            let excluded_rules: Vec<_> = rules
                .iter()
                .cloned()
                .filter(|frule| !(frule.head == rule.head && frule.body == rule.body))
                .collect();

            // Try to prove each body directly
            for ba in rule.body.iter() {
                let ungrounded = ba.atom();
                let is_neg = matches!(ba, BodyAtom::Negative(_));
                if let Some((_mapping, proof)) = provable(
                    universe,
                    current_mapping,
                    facts,
                    &excluded_rules,
                    ungrounded,
                    ext_storages,
                )
                .await
                {
                    let Some(mapped_subject) = subject.ground(current_mapping) else {
                        return Some((current_mapping.to_vec(), proof));
                    };

                    tracing::info!(
                        "PROOF {:?} {} {} {}",
                        subject.ground(current_mapping),
                        AtomDisplayWrapper(ba.atom()),
                        proof.iter().join(" <- "),
                        is_neg
                    );

                    // let grounded_subject = subject.ground(&current_mapping).unwrap();

                    // We are groundable or in the chain of logic

                    // Rewrite in terms of the subject, then confirm the proof follows

                    let Some(grounded_terms) = ba
                        .atom()
                        .terms
                        .iter()
                        .map(|t| match t {
                            Term::Variable(v) => {
                                if *v < mapped_subject.terms.len() {
                                    Some(mapped_subject.terms[*v].clone())
                                } else {
                                    None
                                }
                            }
                            t => t.as_grounded(),
                        })
                        .collect() else {
                            // A fact is trivially true
                            composite_proof
                                .extend(std::iter::once(GroundedBodyAtom::Positive(mapped_subject)));
                            continue;
                        };

                    let true_term = GroundedAtom {
                        predicate: ba.atom().predicate.clone(),
                        terms: grounded_terms,
                    };

                    tracing::info!("Rewrote {} -> {}", AtomDisplayWrapper(ba.atom()), true_term);

                    // let instanti = true_term.ground(&mapping).unwrap();

                    if proof.iter().any(|pa| {
                        matches!(pa, GroundedBodyAtom::Positive(_)) && pa.atom() == &true_term
                    }) || proof.iter().any(|pa| {
                        matches!(pa, GroundedBodyAtom::Negative(_)) && pa.atom() == &true_term
                    }) {
                        // if is_neg {
                        //     return None;
                        // }
                        tracing::info!(
                            "TRANSITIVE {} {} :- {}",
                            mapped_subject,
                            is_neg,
                            proof.iter().join(" <- ")
                        );
                        let refuted = !is_neg
                            && proof.iter().any(|pa| {
                                matches!(pa, GroundedBodyAtom::Negative(_))
                                    && pa.atom() == &mapped_subject
                            })
                            || is_neg
                                && proof
                                    .iter()
                                    .any(|pa| matches!(pa, GroundedBodyAtom::Positive(_)));
                        if refuted {
                            composite_proof.push(GroundedBodyAtom::Negative(mapped_subject));
                            // return Some((current_mapping.to_vec(), composite_proof));
                            // composite_proof.extend(proof);
                        } else {
                            let disproven = !is_neg
                                && proof.len() == 1
                                && matches!(proof[0], GroundedBodyAtom::Negative(_))
                                || is_neg
                                    && proof.len() == 1
                                    && matches!(proof[0], GroundedBodyAtom::Positive(_));

                            if disproven {
                                composite_proof.extend(std::iter::once(
                                    GroundedBodyAtom::Negative(mapped_subject.clone()),
                                ));
                            } else {
                                composite_proof.push(GroundedBodyAtom::Positive(mapped_subject))
                            }
                            composite_proof.extend(proof);
                        }
                        continue;
                    }

                    if !proof.iter().any(|pa| {
                        matches!(pa, GroundedBodyAtom::Negative(_)) && pa.atom() == &mapped_subject
                    }) {
                        tracing::info!(
                            "CHAINED {} <- {}",
                            mapped_subject,
                            proof.iter().join(" <- ")
                        );

                        if is_neg
                            && proof
                                .iter()
                                .any(|pa| matches!(pa, GroundedBodyAtom::Positive(_)))
                            || !is_neg
                                && proof
                                    .iter()
                                    .any(|pa| matches!(pa, GroundedBodyAtom::Negative(_)))
                        {
                            return Some((
                                current_mapping.to_vec(),
                                std::iter::once(GroundedBodyAtom::Negative(mapped_subject))
                                    .chain(proof)
                                    .collect(),
                            ));
                        } else {
                            // if proof
                            //     .iter()
                            //     .all(|pa| matches!(pa, GroundedBodyAtom::Positive(_)))
                        }
                        // composite_proof
                        //     .extend(std::iter::once(GroundedBodyAtom::Positive(mapped_subject)));
                        composite_proof.extend(proof);
                    } else {
                        continue 'ruleexp;
                    }
                } else if is_neg {
                    composite_proof.extend(std::iter::once(GroundedBodyAtom::Negative(
                        ba.atom().ground(current_mapping).unwrap(),
                    )));
                } else {
                    composite_proof.extend(std::iter::once(GroundedBodyAtom::Positive(
                        ba.atom().ground(current_mapping).unwrap(),
                    )));
                }
            }

            if composite_proof.is_empty() {
                return Some((current_mapping.to_vec(), composite_proof));
            }
        }
    }

    tracing::info!(
        "Failed to prove subject {} for {}",
        AtomDisplayWrapper(subject),
        current_mapping.iter().join(", ")
    );

    subject.ground(current_mapping).map(|mapped_subject| {
        (
            current_mapping.to_vec(),
            vec![GroundedBodyAtom::Negative(mapped_subject)],
        )
    })
}

#[cfg(feature = "async")]
async fn eval_proof<I: IntoIterator<Item = ThreadsafeStorageRef<'static>>>(
    program: &CompiledProgram,
    goal: GroundedGoal,
    storages: I,
) -> EvalOutput {
    let ext_storages: Arc<Vec<_>> = Arc::new(storages.into_iter().collect());
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
                terms: (0..comp.atom().terms.len()).map(Term::Variable).collect(),
            };
            let rules = program.rules.clone();
            let universe = total_universe.clone();
            async move {
                (
                    subject.clone(),
                    provable(
                        &universe,
                        &base_mapping,
                        &facts,
                        &rules,
                        &subject,
                        &ext_storages,
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
            if let (subj, Some((_mapping, proof)), false) = proof {
                tracing::warn!("Component proof: {}", proof.iter().join(" <- "));
                if matches!(proof[0], GroundedBodyAtom::Positive(_))
                    && proof.iter().any(|pa| {
                        pa.atom().predicate == subj.predicate
                            && matches!(pa, GroundedBodyAtom::Negative(_))
                    })
                    || matches!(proof[0], GroundedBodyAtom::Negative(_))
                        && !proof.iter().any(|pa| {
                            pa.atom().predicate == subj.predicate
                                && matches!(pa, GroundedBodyAtom::Positive(_))
                        })
                {
                    None
                } else {
                    Some(otree.into_iter().chain(proof.into_iter()).collect())
                }
            } else if let (subj, Some((_mapping, proof)), true) = proof {
                tracing::warn!("Negative component proof: {}", proof.iter().join(" <- "));
                if proof.is_empty() {
                    Some(otree)
                } else if (matches!(proof[0], GroundedBodyAtom::Positive(_))
                    && !proof.iter().any(|pa| {
                        pa.atom().predicate == subj.predicate
                            && matches!(pa, GroundedBodyAtom::Negative(_))
                    }))
                {
                    None
                } else {
                    Some(otree.into_iter().chain(proof.into_iter()).collect())
                }
            } else if let (_, None, true) = proof {
                Some(otree)
            } else {
                None
            }
        });

    EvalOutput::Proof(overall_proof)
}

fn eval_grounded_fixed_point<I: IntoIterator<Item = &'static dyn Storage>>(
    goal: GroundedGoal,
    program: &CompiledProgram,
    ext_storages: I,
) -> EvalOutput {
    // TODO Come up w/ faster way of proving (not rule(X) and other_rule(X))
    // TODO I might have an idea of how to do this, but I'd need some time to implement

    // Oof, I could ask fact(X), not fact2(Y), and it should be able to tell me
    // X and Y such that they are both true...
    // It should be even able to tell me what makes not fact2(Y) true by itself.
    // Where X and Y are real terms that could also be proven by an intrinsic...

    let mut proof = vec![];

    let ext_storages: Vec<_> = ext_storages.into_iter().collect();
    let (program_storage, _results) = eval_fixed_point(program, ext_storages.iter().copied());

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

fn eval_fixed_point<I: IntoIterator<Item = &'static dyn Storage>>(
    program: &CompiledProgram,
    storages: I,
) -> (Fixed, HashMap<String, HashSet<GroundedTerm>>) {
    // Fixed-point semantics
    let mut satisfactory_values: HashMap<String, HashSet<GroundedTerm>> = HashMap::new();
    let ext_storages: Vec<_> = storages.into_iter().collect();
    let universe = program.universe();

    // Ignore the output universe (which contains synthesized values)
    let (program_storage, universe) =
        fixed_point_expand(&program.facts, &program.rules, &universe, &ext_storages);

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
                    || ext_storages
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
