use std::collections::HashSet;

use crate::parser::Predicate;

pub mod compiler;

#[macro_export]
macro_rules! atom {
    ($name:ident ($($sname:ident $val:expr),*)) => {
        $crate::GroundedAtom {
            predicate: $crate::Predicate {
                is_intrinsic: false,
                name: stringify!($name).to_string(),
            },
            terms: vec![
                $(atom!($sname $val)),*
            ]
        }
    };

    (@$name:ident ($($sname:ident $val:expr),*)) => {
        $crate::GroundedAtom {
            predicate: $crate::Predicate {
                is_intrinsic: true,
                name: stringify!($name).to_string(),
            },
            terms: vec![
                $(atom!($sname $val)),*
            ]
        }
    };

    (boolean $val:expr) => {
        $crate::GroundedTerm::Boolean($val)
    };

    (integer $val:expr) => {
        $crate::GroundedTerm::Integer($val)
    };

    (uuid $val:expr) => {
        $crate::GroundedTerm::Uuid($val)
    };

    (string $val:expr) => {
        $crate::GroundedTerm::String($val)
    };

    (term $val:expr) => {
        $val.to_owned()
    }
}

#[derive(Debug, PartialEq, Eq, Clone, Hash)]
#[cfg_attr(
    feature = "serde_internal",
    derive(serde::Serialize, serde::Deserialize)
)]
pub enum GroundedTerm {
    Integer(i64),
    String(String),
    Uuid(uuid::Uuid),
    Boolean(bool),
}

impl GroundedTerm {
    pub fn as_integer(&self) -> Option<i64> {
        match self {
            GroundedTerm::Integer(i) => Some(*i),
            _ => None,
        }
    }

    pub fn as_string(&self) -> Option<&str> {
        match self {
            GroundedTerm::String(s) => Some(s),
            _ => None,
        }
    }

    pub fn as_uuid(&self) -> Option<uuid::Uuid> {
        match self {
            GroundedTerm::Uuid(id) => Some(*id),
            _ => None,
        }
    }

    pub fn as_boolean(&self) -> Option<bool> {
        match self {
            GroundedTerm::Boolean(b) => Some(*b),
            _ => None,
        }
    }
}

impl std::fmt::Display for GroundedTerm {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            GroundedTerm::Integer(i) => write!(f, "{}", i),
            GroundedTerm::String(s) => write!(f, "\"{}\"", s),
            GroundedTerm::Uuid(id) => write!(f, "#{}", id),
            GroundedTerm::Boolean(b) => write!(f, "{}", b),
        }
    }
}

#[derive(Debug, PartialEq, Eq, Clone, Hash)]
#[cfg_attr(
    feature = "serde_internal",
    derive(serde::Serialize, serde::Deserialize)
)]
pub enum Term {
    Variable(usize),
    Integer(i64),
    String(String),
    Uuid(uuid::Uuid),
    Boolean(bool),
}

impl From<GroundedTerm> for Term {
    fn from(value: GroundedTerm) -> Self {
        match value {
            GroundedTerm::Integer(i) => Term::Integer(i),
            GroundedTerm::String(s) => Term::String(s),
            GroundedTerm::Uuid(id) => Term::Uuid(id),
            GroundedTerm::Boolean(b) => Term::Boolean(b),
        }
    }
}

impl Term {
    pub fn as_grounded(&self) -> Option<GroundedTerm> {
        match self {
            Term::Variable(_) => None,
            Term::Integer(i) => Some(GroundedTerm::Integer(*i)),
            Term::String(s) => Some(GroundedTerm::String(s.clone())),
            Term::Uuid(id) => Some(GroundedTerm::Uuid(*id)),
            Term::Boolean(b) => Some(GroundedTerm::Boolean(*b)),
        }
    }

    // If a variable specfied doesn't exist in the given terms, returns None
    pub fn ground(&self, terms: &[GroundedTerm]) -> Option<GroundedTerm> {
        match self {
            Term::Variable(v) => terms.get(*v).cloned(),
            Term::Integer(i) => Some(GroundedTerm::Integer(*i)),
            Term::String(s) => Some(GroundedTerm::String(s.clone())),
            Term::Uuid(id) => Some(GroundedTerm::Uuid(*id)),
            Term::Boolean(b) => Some(GroundedTerm::Boolean(*b)),
        }
    }

    // pub fn maybe_ground(&self, terms: &[Option<GroundedTerm>]) -> Option<GroundedTerm> {
    //     match self {
    //         Term::Variable(v) => terms.get(*v).cloned()?,
    //         Term::Integer(i) => Some(GroundedTerm::Integer(*i)),
    //         Term::String(s) => Some(GroundedTerm::String(s.clone())),
    //         Term::Uuid(id) => Some(GroundedTerm::Uuid(*id)),
    //         Term::Boolean(b) => Some(GroundedTerm::Boolean(*b)),
    //     }
    // }

    fn display(&self, f: &mut std::fmt::Formatter<'_>, mapping: &[String]) -> std::fmt::Result {
        match self.as_grounded() {
            Some(g) => write!(f, "{}", g),
            None => match self {
                Term::Variable(idx) => {
                    write!(
                        f,
                        "{}",
                        mapping.get(*idx).map(|s| s.as_str()).unwrap_or("$ERROR")
                    )
                }
                _ => unreachable!("only ungrounded term is a variable"),
            },
        }
    }
}

pub(crate) struct AtomDisplayWrapper<'a>(pub &'a Atom);

impl<'a> std::fmt::Display for AtomDisplayWrapper<'a> {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        self.0.display(
            f,
            &(0..=self
                .0
                .terms
                .iter()
                .filter_map(|t| match t {
                    Term::Variable(v) => Some(*v),
                    _ => None,
                })
                .max()
                .unwrap_or(0))
                .map(|n| format!("v{n}"))
                .collect::<Vec<_>>(),
        )
    }
}

#[derive(Debug, Clone, PartialEq, Eq, Hash)]
#[cfg_attr(
    feature = "serde_internal",
    derive(serde::Serialize, serde::Deserialize)
)]
pub struct GroundedAtom {
    pub predicate: Predicate,
    pub terms: Vec<GroundedTerm>,
}

impl std::fmt::Display for GroundedAtom {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "{}", self.predicate)?;
        write!(f, "(")?;
        if let Some(first) = self.terms.first() {
            write!(f, "{}", first)?;
        }
        for item in self.terms.iter().skip(1) {
            write!(f, ", {}", item)?;
        }
        write!(f, ")")
    }
}

#[derive(Debug, PartialEq, Eq, Clone, Hash)]
#[cfg_attr(
    feature = "serde_internal",
    derive(serde::Serialize, serde::Deserialize)
)]
pub struct Atom {
    pub(crate) predicate: Predicate,
    pub(crate) terms: Vec<Term>,
}

impl From<GroundedAtom> for Atom {
    fn from(value: GroundedAtom) -> Self {
        Self {
            predicate: value.predicate,
            terms: value.terms.into_iter().map(Into::<Term>::into).collect(),
        }
    }
}

impl Atom {
    pub fn as_grounded(&self) -> Option<GroundedAtom> {
        Some(GroundedAtom {
            predicate: self.predicate.clone(),
            terms: self
                .terms
                .iter()
                .map(|t| t.as_grounded())
                .collect::<Option<Vec<_>>>()?,
        })
    }

    // If a variable specfied doesn't exist in the given terms, returns None
    pub fn ground(&self, terms: &[GroundedTerm]) -> Option<GroundedAtom> {
        Some(GroundedAtom {
            predicate: self.predicate.clone(),
            terms: self
                .terms
                .iter()
                .map(|t| match t.as_grounded() {
                    Some(term) => Some(term),
                    None => match t {
                        Term::Variable(i) => terms.get(*i).map(|t| (*t).clone()),
                        _ => None,
                    },
                })
                .collect::<Option<Vec<_>>>()?,
        })
    }

    // If a variable specfied doesn't exist in the given terms, returns None
    pub fn maybe_ground(&self, terms: &[Option<GroundedTerm>]) -> Option<GroundedAtom> {
        Some(GroundedAtom {
            predicate: self.predicate.clone(),
            terms: self
                .terms
                .iter()
                .map(|t| match t.as_grounded() {
                    Some(term) => Some(term),
                    None => match t {
                        Term::Variable(i) => terms.get(*i).map(|t| (*t).clone())?,
                        _ => None,
                    },
                })
                .collect::<Option<Vec<_>>>()?,
        })
    }

    fn display(&self, f: &mut std::fmt::Formatter<'_>, mapping: &[String]) -> std::fmt::Result {
        write!(f, "{}", self.predicate)?;
        if !self.terms.is_empty() {
            write!(f, "(")?;
            self.terms.first().unwrap().display(f, mapping)?;
            for term in self.terms.iter().skip(1) {
                write!(f, ",")?;
                term.display(f, mapping)?;
            }
            write!(f, ")")?;
        }
        Ok(())
    }
}

#[derive(Debug, Clone, PartialEq, Eq)]
#[cfg_attr(
    feature = "serde_internal",
    derive(serde::Serialize, serde::Deserialize)
)]
pub enum BodyAtom {
    Positive(Atom),
    Negative(Atom),
}

impl From<GroundedBodyAtom> for BodyAtom {
    fn from(value: GroundedBodyAtom) -> Self {
        match value {
            GroundedBodyAtom::Positive(atom) => BodyAtom::Positive(atom.into()),
            GroundedBodyAtom::Negative(atom) => BodyAtom::Negative(atom.into()),
        }
    }
}

impl BodyAtom {
    pub fn atom(&self) -> &Atom {
        match self {
            BodyAtom::Negative(neg) => neg,
            BodyAtom::Positive(pos) => pos,
        }
    }

    pub fn positive(&self) -> Option<&Atom> {
        match self {
            BodyAtom::Negative(_) => None,
            BodyAtom::Positive(pos) => Some(pos),
        }
    }

    pub fn negative(&self) -> Option<&Atom> {
        match self {
            BodyAtom::Negative(neg) => Some(neg),
            BodyAtom::Positive(_) => None,
        }
    }

    pub fn as_grounded(&self) -> Option<GroundedBodyAtom> {
        let atom = match self {
            BodyAtom::Negative(atom) => atom,
            BodyAtom::Positive(atom) => atom,
        };

        atom.as_grounded().map(match self {
            BodyAtom::Negative(_) => GroundedBodyAtom::Negative,
            BodyAtom::Positive(_) => GroundedBodyAtom::Positive,
        })
    }

    fn display(&self, f: &mut std::fmt::Formatter<'_>, mapping: &[String]) -> std::fmt::Result {
        match self {
            BodyAtom::Negative(atom) => {
                write!(f, "not ")?;
                atom.display(f, mapping)
            }
            BodyAtom::Positive(atom) => atom.display(f, mapping),
        }
    }
}

#[derive(Debug, Clone)]
#[cfg_attr(
    feature = "serde_internal",
    derive(serde::Serialize, serde::Deserialize)
)]
pub enum GroundedBodyAtom {
    Positive(GroundedAtom),
    Negative(GroundedAtom),
}

impl GroundedBodyAtom {
    pub fn atom(&self) -> &GroundedAtom {
        match self {
            GroundedBodyAtom::Negative(neg) => neg,
            GroundedBodyAtom::Positive(pos) => pos,
        }
    }
}

impl std::fmt::Display for GroundedBodyAtom {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            GroundedBodyAtom::Positive(at) => write!(f, "{at}"),
            GroundedBodyAtom::Negative(at) => write!(f, "not {at}"),
        }
    }
}

#[derive(Debug, Clone)]
#[cfg_attr(
    feature = "serde_internal",
    derive(serde::Serialize, serde::Deserialize)
)]
pub struct Rule {
    // rule heads are not allowed to be intrinsic.
    pub(crate) head: (String, Vec<Term>),
    /// Should have at least one atom.
    /// We can impicitly convert to a fact if the head is grounded while the body is empty.
    /// All variables used in the head must appear in the body in at least 1 positive
    /// body atom.
    pub(crate) body: Vec<BodyAtom>,
    /// Maps variable indicies to variable names for debugging
    pub(crate) mapping: Vec<String>,
}

impl Rule {
    pub fn name(&self) -> &str {
        &self.head.0
    }

    pub fn arity(&self) -> usize {
        self.head.1.len()
    }
}

impl std::fmt::Display for Rule {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "{}", &self.head.0)?;
        if !self.head.1.is_empty() {
            write!(f, "(")?;
            self.head.1.first().unwrap().display(f, &self.mapping)?;
            for term in self.head.1.iter().skip(1) {
                write!(f, ",")?;
                term.display(f, &self.mapping)?;
            }
            write!(f, ")")?;
        }
        if !self.body.is_empty() {
            write!(f, ":-")?;
            self.body.first().unwrap().display(f, &self.mapping)?;
            for bt in self.body.iter().skip(1) {
                write!(f, ",")?;
                bt.display(f, &self.mapping)?;
            }
        }
        write!(f, ".")
    }
}

#[derive(Debug)]
#[cfg_attr(
    feature = "serde_internal",
    derive(serde::Serialize, serde::Deserialize)
)]
pub struct Goal {
    pub(crate) components: Vec<BodyAtom>,
    pub(crate) mapping: Vec<String>,
}

impl Goal {
    pub fn as_grounded(&self) -> Option<GroundedGoal> {
        let components: Option<Vec<_>> =
            self.components.iter().map(BodyAtom::as_grounded).collect();

        components.map(|components| GroundedGoal { components })
    }
}

#[derive(Debug)]
pub struct GroundedGoal {
    pub(crate) components: Vec<GroundedBodyAtom>,
}

#[derive(Debug)]
#[cfg_attr(
    feature = "serde_internal",
    derive(serde::Serialize, serde::Deserialize)
)]
pub struct CompiledProgram {
    pub facts: Vec<(String, Vec<GroundedTerm>)>,
    pub rules: Vec<Rule>, // Ungrounded facts go here.
    pub goal: Goal,
}

impl CompiledProgram {
    pub fn universe(&self) -> HashSet<GroundedTerm> {
        self.facts
            .iter()
            .flat_map(|fact| fact.1.iter().cloned())
            .chain(self.rules.iter().flat_map(|rule| {
                rule.head
                    .1
                    .iter()
                    .filter_map(|term| term.as_grounded())
                    .chain(
                        rule.body
                            .iter()
                            .flat_map(|ba| ba.atom().terms.iter().filter_map(|t| t.as_grounded())),
                    )
            }))
            .chain(
                self.goal
                    .components
                    .iter()
                    .flat_map(|comp| comp.atom().terms.iter().filter_map(|g| g.as_grounded())),
            )
            .collect()
    }
}

impl std::fmt::Display for CompiledProgram {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        for fact in self.facts.iter() {
            write!(
                f,
                "{}.",
                GroundedAtom {
                    predicate: Predicate {
                        is_intrinsic: false,
                        name: fact.0.clone()
                    },
                    terms: fact.1.clone()
                }
            )?;
            if f.alternate() {
                writeln!(f)?;
            }
        }

        if !self.rules.is_empty() && f.alternate() {
            writeln!(f)?;
        }

        for rule in self.rules.iter() {
            write!(f, "{}", rule)?;
            if f.alternate() {
                writeln!(f)?;
            }
        }

        if !self.goal.components.is_empty() && f.alternate() {
            writeln!(f)?;
        }

        for comp in self.goal.components.iter() {
            comp.display(f, &self.goal.mapping)?;
            write!(f, "?")?;
            if f.alternate() {
                writeln!(f)?;
            }
        }

        Ok(())
    }
}
