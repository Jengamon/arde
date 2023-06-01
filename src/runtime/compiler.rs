use std::collections::{HashMap, HashSet};

use nom::{error::VerboseError, Finish};

use crate::parser::{parser, ParseTerm, Predicate, Visitor};

use super::{Atom, BodyAtom, CompiledProgram, Goal, GroundedTerm, Rule, Term};

pub enum CompilerContext {
    Term(GroundedTerm),
    Variable(String),
    Atom {
        predicate: Predicate,
        terms: Vec<CompilerContext>,
        is_negative: bool,
    },
    Rule {
        head_name: String,
        head_terms: Vec<Term>,
        body_atoms: Vec<BodyAtom>,
        mapping: Vec<String>,
        // Predicates this rule depends on, and whether they are negative or not.
        edges: Vec<(Predicate, bool)>,
    },
    Fact(String, Vec<GroundedTerm>),
    Goal {
        predicate: Predicate,
        terms: Vec<Term>,
        is_negative: bool,
        mapping: Vec<String>,
    },
}

#[derive(thiserror::Error, Debug)]
pub enum CompileError {
    // TODO implement display for crate::parser::Atom and BodyAtom?
    #[error("Ungrounded facts are not allowed: {0:?}")]
    UngroundedFact(crate::parser::Atom),
    #[error("Intrinsic facts are not allowed: {0:?}")]
    IntrinsicFact(crate::parser::Atom),
    #[error("Rule head is not allowed to be intrinsic: {0:?}")]
    IntrinsicRuleHead(crate::parser::Atom),
    #[error("Rule {0} :- {} is unsafe",
        .1.iter().map(|ba| ba.to_string()).collect::<Vec<_>>().join(", "),
    )]
    UnsafeRule(crate::parser::Atom, Vec<crate::parser::BodyAtom>),
}

#[derive(Debug)]
pub struct NegativeRuleCycle {
    cycle: Vec<Predicate>,
    negative_edges: Vec<(Predicate, Predicate)>,
}

impl std::fmt::Display for NegativeRuleCycle {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(
            f,
            "cycle {{{}}}, negative edges {}",
            self.cycle
                .iter()
                .map(|p| p.to_string())
                .collect::<Vec<_>>()
                .join(", "),
            self.negative_edges
                .iter()
                .map(|(f, t)| format!("{f} <-> {t}"))
                .collect::<Vec<_>>()
                .join(", ")
        )
    }
}

#[derive(thiserror::Error, Debug)]
pub enum ProgramError {
    #[error("Incomplete parse: {0}")]
    IncompleteParse(String),
    #[error("compile error at constraint {1}: {0}")]
    CompileError(#[source] CompileError, usize),
    #[error("nom error")]
    NomError {
        input: String,
        #[source]
        error: VerboseError<String>,
    },
    #[error("Negative rule cycle(s) found: {}",
        .0.iter().map(|nrc| format!("{nrc}")).collect::<Vec<_>>().join(", ")

    )]
    NegRuleCycle(Vec<NegativeRuleCycle>),
    #[error("Unbounded goal variable: {}",
        .0.iter().map(|ba| ba.to_string()).collect::<Vec<_>>().join(", ")
    )]
    IntrinsicGoalError(Vec<crate::parser::BodyAtom>),
}

impl From<(usize, CompileError)> for ProgramError {
    fn from(value: (usize, CompileError)) -> Self {
        Self::CompileError(value.1, value.0 + 1)
    }
}

#[derive(Debug)]
pub(crate) struct RuleCycleDetector {
    pub(crate) possible_rules: HashSet<Predicate>,
    pub(crate) edges: HashSet<(Predicate, Predicate, bool)>,
}

impl RuleCycleDetector {
    #[tracing::instrument(skip(self))]
    fn strongconnect<'a, 'b: 'a>(
        &'b self,
        v: &'a Predicate,
        metadata: &mut HashMap<&'a Predicate, (usize, usize)>,
        stack: &mut Vec<&'a Predicate>,
        index: &mut usize,
        sccs: &mut Vec<Vec<&'a Predicate>>,
    ) {
        metadata.insert(v, (*index, *index));
        *index += 1;
        stack.push(v);

        for w in self
            .edges
            .iter()
            .filter_map(|(f, t, _)| if f == v { Some(t) } else { None })
        {
            if metadata.get(w).is_none() {
                self.strongconnect(w, metadata, stack, index, sccs);
                let (vindex, vlowlink) = metadata.get(v).cloned().unwrap();
                let (_windex, wlowlink) = metadata.get(w).cloned().unwrap();
                metadata.insert(v, (vindex, std::cmp::min(vlowlink, wlowlink)));
            } else if stack.contains(&w) {
                let (vindex, vlowlink) = metadata.get(v).cloned().unwrap();
                let (windex, _wlowlink) = metadata.get(w).cloned().unwrap();
                metadata.insert(v, (vindex, std::cmp::min(vlowlink, windex)));
            }
        }

        let (vindex, vlowlink) = metadata.get(v).cloned().unwrap();
        if vindex == vlowlink {
            tracing::debug!("found scc!");
            let mut scc = vec![];
            loop {
                let w = stack.pop().expect("stack shouldn't be empty");
                scc.push(w);
                if v == w {
                    break;
                }
            }
            sccs.push(scc);
        }
    }

    pub(crate) fn sccs(&self) -> impl Iterator<Item = Vec<&Predicate>> {
        // First generate SCCs of the graph
        let mut metadata: HashMap<&Predicate, (usize, usize)> = HashMap::new();
        let mut index = 0;
        let mut stack = vec![];

        let mut sccs = vec![];

        for v in self.possible_rules.iter() {
            if metadata.get(v).is_none() {
                self.strongconnect(v, &mut metadata, &mut stack, &mut index, &mut sccs);
            }
        }

        sccs.into_iter()
    }

    fn detect_safety(&self) -> Result<(), ProgramError> {
        let mut neg_cycles = vec![];
        for scc in self.sccs() {
            tracing::debug!(
                "analyzing SCC: {}",
                scc.iter()
                    .map(|n| n.to_string())
                    .collect::<Vec<_>>()
                    .join(" <-> ")
            );
            let mut problem_edges = vec![];
            // Take advantage of the reverse topological sort:
            // for every edge uv, v comes before u in the scc
            for vindex in 0..scc.len() {
                let v = scc[vindex].clone();
                // u could be v (self-connected)
                for u in &scc[vindex..] {
                    let u = (*u).clone();
                    if self.edges.contains(&(u.clone(), v.clone(), true))
                        || self.edges.contains(&(v.clone(), u.clone(), true))
                    {
                        problem_edges.push((u, v.clone()));
                    }
                }
            }

            if !problem_edges.is_empty() {
                neg_cycles.push((scc.into_iter().cloned().collect::<Vec<_>>(), problem_edges))
            }
        }

        if neg_cycles.is_empty() {
            Ok(())
        } else {
            Err(ProgramError::NegRuleCycle(
                neg_cycles
                    .into_iter()
                    .map(|(cycle, prules)| NegativeRuleCycle {
                        cycle,
                        negative_edges: prules,
                    })
                    .collect(),
            ))
        }
    }
}

pub struct Compiler;

impl Compiler {
    fn extract_mapping(terms: Vec<CompilerContext>) -> (Vec<String>, Vec<Term>) {
        let mut mapping = vec![];
        let mut subbed_terms = vec![];

        for term in terms {
            match term {
                CompilerContext::Term(t) => subbed_terms.push(t.into()),
                CompilerContext::Variable(name) => {
                    if let Some(idx) = mapping.iter().position(|n: &String| n == &name) {
                        subbed_terms.push(Term::Variable(idx))
                    } else {
                        let idx = mapping.len();
                        mapping.push(name);
                        subbed_terms.push(Term::Variable(idx));
                    }
                }
                CompilerContext::Atom { .. }
                | CompilerContext::Rule { .. }
                | CompilerContext::Fact(_, _)
                | CompilerContext::Goal { .. } => {
                    unreachable!("Cannot extract a mapping from non-term level contexts")
                }
            }
        }

        (mapping, subbed_terms)
    }

    // Compiles programs (rejecting unsafe ones)
    pub fn compile(&self, input: &str) -> Result<CompiledProgram, ProgramError> {
        // Parse the data
        let (remaining, parsed) =
            parser(input)
                .finish()
                .map_err(|e: VerboseError<&str>| ProgramError::NomError {
                    input: input.to_string(),
                    error: VerboseError {
                        errors: e
                            .errors
                            .into_iter()
                            .map(|(s, e)| (s.to_string(), e))
                            .collect(),
                    },
                })?;

        if !remaining.is_empty() {
            return Err(ProgramError::IncompleteParse(remaining.to_string()));
        }

        let program = {
            let span = tracing::info_span!("compile");
            let mut rules = vec![];
            let mut facts = vec![];
            let mut goals = vec![];
            let mut goal_mapping = vec![];
            let mut goal_source = vec![];

            let mut rule_edges: HashSet<(Predicate, Predicate, bool)> = HashSet::new();
            let mut rules_vertices: HashSet<Predicate> = HashSet::new();

            for (idx, constraint) in parsed.into_iter().enumerate() {
                let _guard = span.enter();
                match self.visit((&constraint).into()).map_err(|e| (idx, e))? {
                    CompilerContext::Term(_)
                    | CompilerContext::Variable(_)
                    | CompilerContext::Atom { .. } => {
                        unreachable!("top-level must be a rule, fact, or goal (constraint)")
                    }
                    CompilerContext::Rule {
                        head_name,
                        head_terms,
                        body_atoms,
                        mapping,
                        edges,
                    } => {
                        for (to, neg) in edges.into_iter() {
                            let from = Predicate {
                                is_intrinsic: false,
                                name: head_name.clone(),
                            };
                            rule_edges.insert((from.clone(), to.clone(), neg));
                            rules_vertices.insert(from);
                            rules_vertices.insert(to.clone());
                        }

                        rules.push(Rule {
                            head: (head_name, head_terms),
                            body: body_atoms,
                            mapping,
                        });
                    }
                    CompilerContext::Fact(name, components) => facts.push((name, components)),
                    CompilerContext::Goal {
                        predicate,
                        terms,
                        is_negative,
                        mapping,
                    } => {
                        // Unify goal with all other existing goals
                        let mut remap = HashMap::new();
                        for (from, name) in mapping.iter().enumerate() {
                            if let Some(idx) = goal_mapping.iter().position(|s: &String| s == name)
                            {
                                remap.insert(from, idx);
                            } else {
                                let idx = goal_mapping.len();
                                goal_mapping.push(name.clone());
                                remap.insert(from, idx);
                            }
                        }

                        goal_source.push(if is_negative {
                            crate::parser::BodyAtom::Negative
                        } else {
                            crate::parser::BodyAtom::Positive
                        }(crate::parser::Atom {
                            predicate: predicate.clone(),
                            terms: terms
                                .iter()
                                .map(|t| match t {
                                    Term::Variable(v) => ParseTerm::Variable(mapping[*v].clone()),
                                    Term::Integer(v) => ParseTerm::Integer(*v),
                                    Term::String(v) => ParseTerm::String(v.clone()),
                                    Term::Uuid(v) => ParseTerm::Uuid(*v),
                                    Term::Boolean(v) => ParseTerm::Bool(*v),
                                })
                                .collect(),
                        }));

                        goals.push(if is_negative {
                            BodyAtom::Negative
                        } else {
                            BodyAtom::Positive
                        }(Atom {
                            predicate,
                            terms: terms
                                .into_iter()
                                .map(|t| match t {
                                    Term::Variable(id) => {
                                        Term::Variable(remap.get(&id).copied().unwrap_or_else(
                                            || panic!("ICE: remapping missing {id}"),
                                        ))
                                    }
                                    term => term,
                                })
                                .collect(),
                        }));
                    }
                }
            }

            // Rule safety analysis for the entire program
            let cycle_safety = RuleCycleDetector {
                possible_rules: rules_vertices,
                edges: rule_edges,
            };

            cycle_safety.detect_safety()?;

            let unbounded_intrinsics_goal_vars: HashSet<_> = (0..goal_mapping.len())
                .filter(|v| {
                    !goals
                        .iter()
                        .filter(|ba| !ba.atom().predicate.is_intrinsic)
                        .any(|ba| ba.atom().terms.contains(&Term::Variable(*v)))
                })
                .collect();

            // All goal inputs to intrinsics must be determinable by the program
            if !unbounded_intrinsics_goal_vars.is_empty() {
                Err(ProgramError::IntrinsicGoalError(goal_source))?
            }

            CompiledProgram {
                facts,
                rules,
                goal: Goal {
                    components: goals,
                    mapping: goal_mapping,
                },
            }
        };

        Ok(program)
    }
}

impl Visitor for Compiler {
    type Output = Result<CompilerContext, CompileError>;

    fn visit_parse_term(&self, term: &crate::parser::ParseTerm) -> Self::Output {
        tracing::trace!("compiling {:?}", term);
        match term {
            crate::parser::ParseTerm::Variable(name) => Ok(CompilerContext::Variable(name.clone())),
            crate::parser::ParseTerm::Bool(b) => {
                Ok(CompilerContext::Term(GroundedTerm::Boolean(*b)))
            }
            crate::parser::ParseTerm::Integer(i) => {
                Ok(CompilerContext::Term(GroundedTerm::Integer(*i)))
            }
            crate::parser::ParseTerm::String(s) => {
                Ok(CompilerContext::Term(GroundedTerm::String(s.clone())))
            }
            crate::parser::ParseTerm::Uuid(id) => {
                Ok(CompilerContext::Term(GroundedTerm::Uuid(*id)))
            }
        }
    }

    fn visit_atom(&self, atom: &crate::parser::Atom) -> Self::Output {
        tracing::trace!("compiling {:?}", atom);
        let predicate = atom.predicate.clone();

        let terms = atom
            .terms
            .iter()
            .map(|t| self.visit(t.into()))
            .collect::<Result<Vec<_>, _>>()?;

        Ok(CompilerContext::Atom {
            predicate,
            terms,
            is_negative: false,
        })
    }

    fn visit_body_atom(&self, body_atom: &crate::parser::BodyAtom) -> Self::Output {
        tracing::trace!("compiling {:?}", body_atom);
        let atom = match body_atom {
            crate::parser::BodyAtom::Positive(atom) => atom,
            crate::parser::BodyAtom::Negative(atom) => atom,
        };

        let (predicate, terms) = match self.visit(atom.into())? {
            CompilerContext::Atom {
                predicate, terms, ..
            } => (predicate, terms),
            _ => unreachable!("ICE: Atom visit didn't produce atom node"),
        };

        Ok(CompilerContext::Atom {
            predicate,
            terms,
            is_negative: matches!(body_atom, crate::parser::BodyAtom::Negative(_)),
        })
    }

    fn visit_constraint(&self, constraint: &crate::parser::Constraint) -> Self::Output {
        tracing::trace!("compiling {:?}", constraint);
        match constraint {
            crate::parser::Constraint::Fact(fact) => {
                let (predicate, terms) = match self.visit(fact.into())? {
                    CompilerContext::Atom {
                        predicate, terms, ..
                    } => (predicate, terms),
                    _ => unreachable!("ICE: Atom visit didn't produce atom node"),
                };

                let grounded_terms = terms
                    .into_iter()
                    .map(|t| match t {
                        CompilerContext::Term(t) => Some(t),
                        CompilerContext::Variable(_) => None,
                        CompilerContext::Atom { .. }
                        | CompilerContext::Rule { .. }
                        | CompilerContext::Fact(_, _)
                        | CompilerContext::Goal { .. } => {
                            unreachable!("terms of a fact cannot be atoms or constraints")
                        }
                    })
                    .collect::<Option<Vec<_>>>()
                    .ok_or(CompileError::UngroundedFact(fact.clone()))?;

                if predicate.is_intrinsic {
                    Err(CompileError::IntrinsicFact(fact.clone()))
                } else {
                    Ok(CompilerContext::Fact(predicate.name, grounded_terms))
                }
            }
            crate::parser::Constraint::Goal(goal) => {
                let (predicate, terms, is_negative) = match self.visit(goal.into())? {
                    CompilerContext::Atom {
                        predicate,
                        terms,
                        is_negative,
                    } => (predicate, terms, is_negative),
                    _ => unreachable!("ICE: Atom visit didn't produce atom node"),
                };

                let (mapping, terms) = Self::extract_mapping(terms);

                Ok(CompilerContext::Goal {
                    predicate,
                    terms,
                    is_negative,
                    mapping,
                })
            }
            crate::parser::Constraint::Rule { head, body } => {
                // make sure head is not intrinsic
                let (predicate, terms) = match self.visit(head.into())? {
                    CompilerContext::Atom {
                        predicate,
                        terms,
                        is_negative: false,
                    } => {
                        if !predicate.is_intrinsic {
                            (predicate, terms)
                        } else {
                            Err(CompileError::IntrinsicRuleHead(head.clone()))?
                        }
                    }
                    _ => unreachable!("ICE: Atom visit didn't produce valid head atom node"),
                };

                let mut mapping = vec![];
                let mut head_variables = HashSet::new();
                let mut body_variables = HashSet::new();
                let edges: Vec<_> = body
                    .iter()
                    .map(|ba| {
                        (
                            ba.atom().predicate.clone(),
                            matches!(ba, crate::parser::BodyAtom::Negative(_)),
                        )
                    })
                    .collect();

                let head_terms = terms
                    .into_iter()
                    .map(|ctx| match ctx {
                        CompilerContext::Term(t) => t.into(),
                        CompilerContext::Variable(name) => {
                            if let Some(pos) = mapping.iter().position(|n| n == &name) {
                                head_variables.insert(pos);
                                Term::Variable(pos)
                            } else {
                                let pos = mapping.len();
                                head_variables.insert(pos);
                                mapping.push(name);
                                Term::Variable(pos)
                            }
                        }
                        CompilerContext::Atom { .. }
                        | CompilerContext::Rule { .. }
                        | CompilerContext::Fact(_, _)
                        | CompilerContext::Goal { .. } => todo!(),
                    })
                    .collect();

                let body_atoms: Vec<_> = body
                    .iter()
                    .map(|ba| {
                        Ok((if matches!(ba, crate::parser::BodyAtom::Negative(_)) {
                            BodyAtom::Negative
                        } else {
                            BodyAtom::Positive
                        })(Atom {
                            predicate: ba.atom().predicate.clone(),
                            terms: ba
                                .atom()
                                .terms
                                .iter()
                                .map(|term| match self.visit(term.into())? {
                                    CompilerContext::Term(t) => Ok(t.into()),
                                    CompilerContext::Variable(name) => {
                                        if let Some(pos) = mapping.iter().position(|n| n == &name) {
                                            body_variables.insert((
                                                pos,
                                                matches!(ba, crate::parser::BodyAtom::Negative(_)),
                                                ba.atom().predicate.is_intrinsic,
                                            ));

                                            Ok(Term::Variable(pos))
                                        } else {
                                            let pos = mapping.len();

                                            body_variables.insert((
                                                pos,
                                                matches!(ba, crate::parser::BodyAtom::Negative(_)),
                                                ba.atom().predicate.is_intrinsic,
                                            ));

                                            mapping.push(name);
                                            Ok(Term::Variable(pos))
                                        }
                                    }
                                    CompilerContext::Atom { .. }
                                    | CompilerContext::Rule { .. }
                                    | CompilerContext::Fact(_, _)
                                    | CompilerContext::Goal { .. } => todo!(),
                                })
                                .collect::<Result<_, _>>()?,
                        }))
                    })
                    .collect::<Result<_, _>>()?;

                // Generate and sub in mapping

                // Safety checking here
                // All atoms in head are in body, and anything variable in a negative
                // body is also in a positive one
                let positive_body = body_variables
                    .iter()
                    .filter_map(|(v, neg, _)| if !neg { Some(*v) } else { None })
                    .collect();
                let negative_body: HashSet<_> = body_variables
                    .iter()
                    .filter_map(|(v, neg, _)| if *neg { Some(*v) } else { None })
                    .collect();
                let _intrinsic_body: HashSet<_> = body_variables
                    .iter()
                    .filter_map(|(v, _, i)| if *i { Some(*v) } else { None })
                    .collect();
                let _non_intrinsic_body: HashSet<_> = body_variables
                    .iter()
                    .filter_map(|(v, _, i)| if !*i { Some(*v) } else { None })
                    .collect();

                let head_in_positive_body = head_variables.difference(&positive_body).count() == 0;
                let negative_in_positive_body =
                    negative_body.difference(&positive_body).count() == 0;
                // A rule cannot be only intrinsics
                let unbounded_intrinsics_vars: HashSet<_> = body_variables
                    .iter()
                    .filter_map(|(v, _, i)| {
                        if *i
                            && !body_atoms
                                .iter()
                                .filter(|ba| !ba.atom().predicate.is_intrinsic)
                                .any(|ba| ba.atom().terms.contains(&Term::Variable(*v)))
                        {
                            Some(*v)
                        } else {
                            None
                        }
                    })
                    .collect();

                let _no_unbounded_intrinsics_vars = unbounded_intrinsics_vars
                    .intersection(&head_variables)
                    .count()
                    == 0;

                if head_in_positive_body && negative_in_positive_body
                // && no_unbounded_intrinsics_vars
                {
                    Ok(CompilerContext::Rule {
                        head_name: predicate.name,
                        head_terms,
                        body_atoms,
                        mapping,
                        edges,
                    })
                } else {
                    Err(CompileError::UnsafeRule(head.clone(), body.clone()))
                }
            }
        }
    }
}
