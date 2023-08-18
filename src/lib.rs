//! Our goal: be able to store selection queries in simple one-liners.
//!
//! We will model it after logic programming.

use std::collections::{HashMap, HashSet, VecDeque};

#[cfg(feature = "async")]
use std::sync::{Arc, Mutex};
#[cfg(feature = "web")]
use storage::js::JsStorage;
#[cfg(feature = "web")]
use wasm_bindgen::prelude::*;

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

// No async web, b/c JS values are !Send + !Sync

#[cfg_attr(feature = "web", wasm_bindgen)]
#[cfg(feature = "web")]
pub fn evaluate_program_nonasync_wasm(
    program: JsValue,
    storages: Box<[JsStorage]>,
) -> Result<JsValue, JsValue> {
    let program: CompiledProgram = serde_wasm_bindgen::from_value(program)?;
    Ok(serde_wasm_bindgen::to_value(&evaluate_program_nonasync(
        &program,
        storages.iter().map(|i| i.erase()),
    ))?)
}

#[cfg_attr(feature = "web", wasm_bindgen)]
#[cfg(feature = "web")]
pub fn compile_program_wasm(source: &str) -> Result<JsValue, JsError> {
    Ok(serde_wasm_bindgen::to_value(&Compiler.compile(source)?)?)
}

#[cfg(feature = "async")]
pub async fn evaluate_program_async<'a, I: IntoIterator<Item = ThreadsafeStorageRef<'a>>>(
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

pub fn evaluate_program_nonasync<'a, I: IntoIterator<Item = StorageRef<'a>>>(
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

// Returns the mapping to use and the current proof
#[cfg(feature = "async")]
#[tracing::instrument(skip(facts, ext_storages))]
fn provable_from_facts(
    current_mapping: &[GroundedTerm],
    facts: &[GroundedAtom],
    subject: &Atom,
    ext_storages: &[&(dyn Storage + Send + Sync)],
    memory: RuleMemoizeMap,
) -> Option<Vec<GroundedBodyAtom>> {
    // Can the head be grounded (instatiated) with the mapping given?
    if let Some(ga) = subject.ground(current_mapping) {
        if !ga.predicate.is_intrinsic && facts.contains(&ga) {
            tracing::info!("Proved {}", ga);
            let proof = vec![GroundedBodyAtom::Positive(ga.clone())];
            memory.lock().unwrap().insert(ga, (true, proof.clone()));
            Some(proof)
        } else if ga.predicate.is_intrinsic {
            let possible_storages: Vec<_> = ext_storages
                .iter()
                .filter_map(|s| s.query(&subject.predicate, &ga.terms.iter().collect::<Vec<_>>()))
                .collect();
            if possible_storages.is_empty() || possible_storages.into_iter().all(|q| !q) {
                tracing::info!("Proved not {}", ga);
                memory.lock().unwrap().insert(ga, (false, vec![]));
                None
            } else {
                tracing::info!("Proved {}", ga);
                let proof = vec![GroundedBodyAtom::Positive(ga.clone())];
                memory.lock().unwrap().insert(ga, (true, proof.clone()));
                Some(proof)
            }
        } else {
            tracing::info!("Could not prove {} from facts", ga);
            let memory = memory.lock().unwrap();
            // memory.lock().unwrap().insert(ga, (false, vec![]));
            if let Some((is_pos, proof)) = memory.get(&ga) {
                tracing::info!("Memoized {}! {is_pos} {}", ga, proof.iter().join(" <- "));
                if *is_pos {
                    return Some(proof.clone());
                } else {
                    None
                }
            } else {
                None
            }
        }
    } else {
        // Current mapping has some unbounded variables
        // We cannot prove something we do not know, crash, this is a programming error
        unreachable!("Failed to ground");
    }
}

#[cfg(feature = "async")]
fn transitive_rewrite(
    target: &Atom,
    trial_mapping: &[GroundedTerm],
    var_offset: usize,
) -> (Atom, usize) {
    let lowest_var = target
        .terms
        .iter()
        .filter_map(|t| match t {
            Term::Variable(v) => Some(*v),
            _ => None,
        })
        .min()
        .unwrap_or(trial_mapping.len());
    let rewrite_head = Atom {
        predicate: target.predicate.clone(),
        terms: target
            .terms
            .iter()
            .cloned()
            .map(|t| match t {
                Term::Variable(v) => {
                    if v < lowest_var {
                        //v < trial_mapping.len() {
                        trial_mapping[v].clone().into()
                    } else {
                        Term::Variable(v)
                    }
                }
                t => t,
            })
            .collect(),
    };

    tracing::warn!(
        "transitive -> {} {trial_mapping:?} {}",
        AtomDisplayWrapper(target),
        AtomDisplayWrapper(&rewrite_head),
    );

    (rewrite_head, lowest_var)
}

async fn merge_futures(
    futs: impl Iterator<Item = impl futures::Future<Output = Option<Vec<GroundedBodyAtom>>>>,
    memory: RuleMemoizeMap,
) -> Option<Vec<GroundedBodyAtom>> {
    let joined_futures = futures::future::join_all(futs);

    joined_futures
        .await
        .into_iter()
        .fold(Some(vec![]), |acc, it| match acc {
            Some(acc) => match it {
                Some(it) => {
                    memory
                        .lock()
                        .unwrap()
                        .insert(it[0].atom().clone(), (true, it.clone()));
                    Some(acc.into_iter().chain(it.into_iter()).collect())
                }
                None => None,
            },
            None => None,
        })
}

async fn select_futures(
    futs: impl Iterator<Item = impl futures::Future<Output = Option<Vec<GroundedBodyAtom>>>>,
) -> Vec<Vec<GroundedBodyAtom>> {
    let joined_futures = futures::future::join_all(futs);

    joined_futures.await.into_iter().flatten().collect()
}

type RuleMemoizeMap = Arc<Mutex<HashMap<GroundedAtom, (bool, Vec<GroundedBodyAtom>)>>>;
type TriedRules = Vec<(Rule, Vec<GroundedTerm>)>;

#[allow(clippy::too_many_arguments)]
#[cfg(feature = "async")]
#[async_recursion::async_recursion]
#[tracing::instrument(skip(universe, facts, rules, ext_storages, memory))]
async fn provable(
    universe: &[GroundedTerm],
    current_mapping: &[GroundedTerm],
    facts: &[GroundedAtom],
    rules: &[Rule],
    subject: &Atom,
    ext_storages: &[&(dyn Storage + Send + Sync)],
    memory: RuleMemoizeMap,
    breadcrumbs: TriedRules,
    var_offset: usize,
) -> Option<Vec<GroundedBodyAtom>> {
    if let Some(proof) = provable_from_facts(
        current_mapping,
        facts,
        subject,
        ext_storages,
        memory.clone(),
    ) {
        Some(proof)
    } else {
        let possible = rules
            .iter()
            .enumerate()
            .filter(|(_, rule)| {
                rule.head.0 == subject.predicate.to_string()
                    && rule.head.1.len() == subject.terms.len()
            })
            .filter(|(_, applicable)| {
                breadcrumbs.iter().all(|(rule, mapping)| {
                    rule.head != applicable.head
                        || rule.body != applicable.body
                        || mapping != current_mapping
                })
            })
            .map(|(idx, applicable)| {
                let omemory = memory.clone();
                let memory = memory.clone();
                let nonself_rules: Vec<_> = rules
                    .iter()
                    .enumerate()
                    .filter(|(ridx, _)| *ridx != idx)
                    .map(|(_, r)| r.clone())
                    .collect();

                let rule_head = Atom {
                    predicate: subject.predicate.clone(),
                    terms: applicable.head.1.clone(),
                };

                let vars: HashSet<_> = applicable
                    .body
                    .iter()
                    .flat_map(|ba| ba.atom().terms.iter())
                    .filter_map(|t| match t {
                        Term::Variable(v) => Some(*v),
                        _ => None,
                    })
                    .collect();

                let head_nvars: HashSet<_> = applicable
                    .head
                    .1
                    .iter()
                    .positions(|t| !matches!(t, Term::Variable(_)))
                    .collect();

                let head_vars = applicable.head.1.len() - head_nvars.len();

                let current_mapping: Vec<_> = current_mapping
                    .iter()
                    .take(head_vars + var_offset)
                    .skip(var_offset)
                    .cloned()
                    .collect();

                let variants: Vec<_> = (current_mapping.len()..vars.len())
                    .map(|_| universe.iter().cloned())
                    .multi_cartesian_product()
                    .collect();

                let breadcrumbs: Vec<_> = breadcrumbs
                    .iter()
                    .cloned()
                    .chain(std::iter::once((
                        applicable.clone(),
                        current_mapping.to_vec(),
                    )))
                    .collect();

                async move {
                    tracing::info!(
                        "Using rule {} (variants {}) (head nvars {:?})",
                        applicable,
                        variants.len(),
                        head_nvars
                    );

                    let grounded_proofs: Vec<_> =
                        if !variants.is_empty() {
                            let combined_future = variants.into_iter().map(|variant| {
                                let composite_mapping: Vec<_> = current_mapping
                                    .iter()
                                    .chain(variant.iter())
                                    .cloned()
                                    .collect();
                                let body_goals: Vec<_> = applicable
                                    .body
                                    .iter()
                                    .map(|body| match body {
                                        BodyAtom::Positive(atom) => {
                                            let (rewrite, var_offset) = transitive_rewrite(
                                                atom,
                                                &composite_mapping,
                                                var_offset,
                                            );
                                            (rewrite, false, var_offset)
                                        }
                                        BodyAtom::Negative(atom) => {
                                            let (rewrite, var_offset) = transitive_rewrite(
                                                atom,
                                                &composite_mapping,
                                                var_offset,
                                            );
                                            (rewrite, true, var_offset)
                                        }
                                    })
                                    .collect();
                                tracing::info!(
                                    "Attempting {:?} for {}",
                                    composite_mapping,
                                    body_goals
                                        .iter()
                                        .map(|(atom, is_neg, _)| {
                                            if *is_neg {
                                                format!("not {}", AtomDisplayWrapper(atom))
                                            } else {
                                                AtomDisplayWrapper(atom).to_string()
                                            }
                                        })
                                        .intersperse(" and ".to_string())
                                        .collect::<String>()
                                );
                                let memory = memory.clone();
                                let ovariant = current_mapping.clone();
                                let variant = composite_mapping.clone();

                                let rule_head = rule_head.clone();
                                let nonself_rules = nonself_rules.clone();
                                let omemory = memory.clone();
                                let breadcrumbs = breadcrumbs.clone();
                                let body_futures = body_goals.into_iter().map(
                                    move |(item, is_neg, var_offset)| {
                                        let variant = variant.clone();
                                        let memory = memory.clone();
                                        let nonself_rules = nonself_rules.clone();
                                        let breadcrumbs = breadcrumbs.clone();
                                        async move {
                                            if !is_neg {
                                                tracing::info!(
                                                    "Attempting to prove {} for {:?}",
                                                    AtomDisplayWrapper(&item),
                                                    variant
                                                );

                                                provable(
                                                    universe,
                                                    &variant,
                                                    facts,
                                                    rules,
                                                    &item,
                                                    ext_storages,
                                                    memory,
                                                    breadcrumbs,
                                                    var_offset,
                                                )
                                                .await
                                            } else {
                                                tracing::info!(
                                                    "Attempting to prove not {} for {:?}",
                                                    AtomDisplayWrapper(&item),
                                                    variant
                                                );

                                                provable(
                                                    universe,
                                                    &variant,
                                                    facts,
                                                    rules,
                                                    &item,
                                                    ext_storages,
                                                    memory,
                                                    breadcrumbs,
                                                    var_offset,
                                                )
                                                .await
                                                .xor(Some(vec![]))
                                                .and_then(|proof| {
                                                    if !matches!(
                                                        proof.first(),
                                                        Some(GroundedBodyAtom::Negative(_)) | None
                                                    ) {
                                                        None
                                                    } else {
                                                        Some(
                                                            std::iter::once(
                                                                GroundedBodyAtom::Negative(
                                                                    item.ground(&variant).unwrap(),
                                                                ),
                                                            )
                                                            .chain(proof.into_iter())
                                                            .collect(),
                                                        )
                                                    }
                                                })
                                            }
                                        }
                                    },
                                );

                                async move {
                                    merge_futures(body_futures, omemory).await.map(|proof| {
                                        std::iter::once(GroundedBodyAtom::Positive(
                                            rule_head.ground(&ovariant).unwrap(),
                                        ))
                                        .chain(proof.into_iter())
                                        .collect()
                                    })
                                }
                            });
                            select_futures(combined_future).await
                        } else {
                            let body_goals: Vec<_> = applicable
                                .body
                                .iter()
                                .map(|body| match body {
                                    BodyAtom::Positive(atom) => {
                                        let (rewrite, var_offset) =
                                            transitive_rewrite(atom, &current_mapping, var_offset);
                                        (rewrite, false, var_offset)
                                    }
                                    BodyAtom::Negative(atom) => {
                                        let (rewrite, var_offset) =
                                            transitive_rewrite(atom, &current_mapping, var_offset);
                                        (rewrite, true, var_offset)
                                    }
                                })
                                .collect();
                            let omemory = memory.clone();
                            let variant = current_mapping.clone();
                            let mvariant = variant.clone();
                            let breadcrumbs = breadcrumbs.clone();
                            let body_futures =
                                body_goals
                                    .into_iter()
                                    .map(move |(item, is_neg, var_offset)| {
                                        let variant = mvariant.clone();
                                        let memory = memory.clone();
                                        let nonself_rules = nonself_rules.clone();
                                        let breadcrumbs = breadcrumbs.clone();
                                        async move {
                                            if !is_neg {
                                                tracing::info!(
                                                    "Attempting to prove {} for {:?}",
                                                    AtomDisplayWrapper(&item),
                                                    variant
                                                );

                                                provable(
                                                    universe,
                                                    &variant,
                                                    facts,
                                                    &nonself_rules,
                                                    &item,
                                                    ext_storages,
                                                    memory,
                                                    breadcrumbs,
                                                    var_offset,
                                                )
                                                .await
                                            } else {
                                                tracing::info!(
                                                    "Attempting to prove not {} for {:?}",
                                                    AtomDisplayWrapper(&item),
                                                    variant
                                                );

                                                provable(
                                                    universe,
                                                    &variant,
                                                    facts,
                                                    &nonself_rules,
                                                    &item,
                                                    ext_storages,
                                                    memory,
                                                    breadcrumbs,
                                                    var_offset,
                                                )
                                                .await
                                                .xor(Some(vec![]))
                                                .and_then(|proof| {
                                                    if !matches!(
                                                        proof.first(),
                                                        Some(GroundedBodyAtom::Negative(_)) | None
                                                    ) {
                                                        None
                                                    } else {
                                                        Some(
                                                            std::iter::once(
                                                                GroundedBodyAtom::Negative(
                                                                    item.ground(&variant).unwrap(),
                                                                ),
                                                            )
                                                            .chain(proof.into_iter())
                                                            .collect(),
                                                        )
                                                    }
                                                })
                                            }
                                        }
                                    });

                            match merge_futures(body_futures, omemory).await {
                                Some(proof) => vec![std::iter::once(GroundedBodyAtom::Positive(
                                    rule_head.ground(&variant).unwrap(),
                                ))
                                .chain(proof.into_iter())
                                .collect()],
                                None => vec![],
                            }
                        };

                    if grounded_proofs.is_empty() {
                        tracing::error!(
                            "Failed to prove {} for {current_mapping:?}",
                            AtomDisplayWrapper(&rule_head)
                        );
                        // if let Some(rule_head) = rule_head.ground(current_mapping) {
                        //     omemory.lock().unwrap().insert(rule_head, (false, vec![]));
                        // }
                        None
                    } else {
                        grounded_proofs
                            .into_iter()
                            .filter(|proof| !proof.is_empty())
                            .min_by_key(|proof| proof.len())
                    }
                }
            });

        select_futures(possible)
            .await
            .into_iter()
            .filter(|proof| !proof.is_empty())
            .min_by_key(|proof| proof.len())
    }
}

#[cfg(feature = "async")]
async fn eval_proof<'a, I: IntoIterator<Item = ThreadsafeStorageRef<'a>>>(
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
                        &universe,
                        // &[],
                        &base_mapping,
                        &facts,
                        &rules,
                        &subject,
                        &ext_storages,
                        Arc::new(Mutex::new(HashMap::new())),
                        vec![],
                        0,
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

fn eval_grounded_fixed_point<'a, I: IntoIterator<Item = &'a dyn Storage>>(
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

fn eval_fixed_point<'a, I: IntoIterator<Item = &'a dyn Storage>>(
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

#[cfg(test)]
mod tests {
    use crate::{library::StandardLibrary, StorageRef, ThreadsafeStorageRef};

    use super::{evaluate_program_async, evaluate_program_nonasync, Compiler};
    use datadriven::walk;
    use tokio::runtime::Builder;

    // use std::{fs::File, io::BufWriter};
    use tracing_flame::FlameLayer;
    use tracing_subscriber::{fmt, prelude::*, registry::Registry};

    fn setup_global_subscriber() -> impl Drop {
        let fmt_layer = fmt::Layer::default();

        let (flame_layer, _guard) = FlameLayer::with_file("./tracing.folded").unwrap();

        let subscriber = Registry::default().with(fmt_layer).with(flame_layer);

        tracing::subscriber::set_global_default(subscriber).expect("Could not set global default");
        _guard
    }

    #[test]
    fn run() {
        let _guard = setup_global_subscriber();
        walk("tests/eval", |f| {
            f.run(|test| -> String {
                let test_storages = vec![StandardLibrary];
                match test.directive.as_str() {
                    "async" => {
                        let rt = Builder::new_multi_thread().build().unwrap();
                        match Compiler.compile(&test.input) {
                            Ok(program) => match rt.block_on(evaluate_program_async(
                                &program,
                                test_storages.iter().map(|s| s as ThreadsafeStorageRef),
                            )) {
                                crate::EvalOutput::Invalid => "INVALID".to_string(),
                                crate::EvalOutput::Proof(proof) => match proof {
                                    Some(proof) => proof
                                        .iter()
                                        .map(|i| i.to_string())
                                        .collect::<Vec<_>>()
                                        .join(" -> "),
                                    None => "NO PROOF".to_string(),
                                },
                                crate::EvalOutput::Valid(mapping) => mapping
                                    .into_iter()
                                    .map(|(k, vs)| {
                                        format!(
                                            "{k}: {}",
                                            vs.into_iter()
                                                .map(|i| i.to_string())
                                                .collect::<Vec<_>>()
                                                .join(", ")
                                        )
                                    })
                                    .collect::<Vec<_>>()
                                    .join("\n"),
                            },
                            Err(e) => format!("Error: {e}"),
                        }
                    }
                    "sync" => match Compiler.compile(&test.input) {
                        Ok(program) => {
                            match evaluate_program_nonasync(
                                &program,
                                test_storages.iter().map(|s| s as StorageRef),
                            ) {
                                crate::EvalOutput::Invalid => "INVALID".to_string(),
                                crate::EvalOutput::Proof(proof) => match proof {
                                    Some(proof) => proof
                                        .iter()
                                        .map(|i| i.to_string())
                                        .collect::<Vec<_>>()
                                        .join(" -> "),
                                    None => "NO PROOF".to_string(),
                                },
                                crate::EvalOutput::Valid(mapping) => mapping
                                    .into_iter()
                                    .map(|(k, vs)| {
                                        format!(
                                            "{k}: {}",
                                            vs.into_iter()
                                                .map(|i| i.to_string())
                                                .collect::<Vec<_>>()
                                                .join(", ")
                                        )
                                    })
                                    .collect::<Vec<_>>()
                                    .join("\n"),
                            }
                        }
                        Err(e) => format!("Error: {e}"),
                    },
                    _ => "Invalid directive".to_string(),
                }
            })
        });
    }
}
