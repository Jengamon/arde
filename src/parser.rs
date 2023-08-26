pub mod v1;
pub mod v2;

pub use v1::parser as parser_v1;
pub use v2::parser as parser_v2;

#[cfg_attr(
    feature = "serde_internal",
    derive(serde::Serialize, serde::Deserialize)
)]
#[derive(Debug, PartialEq, Eq, Clone)]
pub enum ParseTerm {
    Variable(String),
    Bool(bool),
    Integer(i64),
    String(String),
    Uuid(uuid::Uuid),
}

impl std::fmt::Display for ParseTerm {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            ParseTerm::Variable(v) => write!(f, "{v}"),
            ParseTerm::Bool(v) => write!(f, "{v}"),
            ParseTerm::Integer(v) => write!(f, "{v}"),
            ParseTerm::String(s) => {
                if s.chars().any(|c| c.is_whitespace()) {
                    write!(f, "\"{s}\"")
                } else {
                    write!(f, "{s}")
                }
            }
            ParseTerm::Uuid(id) => write!(f, "#{id}"),
        }
    }
}

#[cfg_attr(
    feature = "serde_internal",
    derive(serde::Serialize, serde::Deserialize)
)]
#[derive(Debug, PartialEq, Eq, Clone, Hash)]
pub struct Predicate {
    pub is_intrinsic: bool,
    pub name: String,
}

impl std::fmt::Display for Predicate {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        if self.is_intrinsic {
            write!(f, "@{}", self.name)
        } else {
            write!(f, "{}", self.name)
        }
    }
}

#[cfg_attr(
    feature = "serde_internal",
    derive(serde::Serialize, serde::Deserialize)
)]
#[derive(Debug, PartialEq, Eq, Clone)]
pub struct Atom {
    pub predicate: Predicate,
    pub terms: Vec<ParseTerm>,
}

impl std::fmt::Display for Atom {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "{}", self.predicate)?;
        write!(f, "(")?;
        if let Some(fr) = self.terms.first() {
            write!(f, "{}", fr)?;
        }
        for term in self.terms.iter().skip(1) {
            write!(f, ",")?;
            write!(f, "{}", term)?;
        }
        write!(f, ")")
    }
}

#[cfg_attr(
    feature = "serde_internal",
    derive(serde::Serialize, serde::Deserialize)
)]
#[derive(Debug, PartialEq, Eq, Clone)]
pub enum BodyAtom {
    Positive(Atom),
    Negative(Atom),
}

impl std::fmt::Display for BodyAtom {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            Self::Negative(atom) => write!(f, "not {atom}"),
            Self::Positive(atom) => write!(f, "{atom}"),
        }
    }
}

impl BodyAtom {
    pub fn atom(&self) -> &Atom {
        match self {
            Self::Positive(a) => a,
            Self::Negative(n) => n,
        }
    }
}

#[cfg_attr(
    feature = "serde_internal",
    derive(serde::Serialize, serde::Deserialize)
)]
#[derive(Debug, PartialEq, Eq)]
pub enum Constraint {
    Fact(Atom),
    Goal(BodyAtom),
    Rule { head: Atom, body: Vec<BodyAtom> },
}

#[derive(Debug, PartialEq, Eq)]
pub enum Ast<'a> {
    ParseTerm(&'a ParseTerm),
    Atom(&'a Atom),
    BodyAtom(&'a BodyAtom),
    Constraint(&'a Constraint),
}

impl<'a> From<&'a Constraint> for Ast<'a> {
    fn from(value: &'a Constraint) -> Self {
        Ast::Constraint(value)
    }
}

impl<'a> From<&'a BodyAtom> for Ast<'a> {
    fn from(value: &'a BodyAtom) -> Self {
        Ast::BodyAtom(value)
    }
}

impl<'a> From<&'a Atom> for Ast<'a> {
    fn from(value: &'a Atom) -> Self {
        Ast::Atom(value)
    }
}

impl<'a> From<&'a ParseTerm> for Ast<'a> {
    fn from(value: &'a ParseTerm) -> Self {
        Ast::ParseTerm(value)
    }
}

pub trait Visitor {
    type Output;

    fn visit_parse_term(&self, term: &ParseTerm) -> Self::Output;
    fn visit_atom(&self, atom: &Atom) -> Self::Output;
    fn visit_body_atom(&self, body_atom: &BodyAtom) -> Self::Output;
    fn visit_constraint(&self, constraint: &Constraint) -> Self::Output;

    fn visit(&self, ast: Ast) -> Self::Output {
        match ast {
            Ast::ParseTerm(r) => self.visit_parse_term(r),
            Ast::Atom(r) => self.visit_atom(r),
            Ast::BodyAtom(r) => self.visit_body_atom(r),
            Ast::Constraint(r) => self.visit_constraint(r),
        }
    }
}

pub trait VisitorMut {
    type Output;

    fn visit_parse_term(&mut self, term: &ParseTerm) -> Self::Output;
    fn visit_atom(&mut self, atom: &Atom) -> Self::Output;
    fn visit_body_atom(&mut self, body_atom: &BodyAtom) -> Self::Output;
    fn visit_constraint(&mut self, constraint: &Constraint) -> Self::Output;

    fn visit(&mut self, ast: Ast) -> Self::Output {
        match ast {
            Ast::ParseTerm(r) => self.visit_parse_term(r),
            Ast::Atom(r) => self.visit_atom(r),
            Ast::BodyAtom(r) => self.visit_body_atom(r),
            Ast::Constraint(r) => self.visit_constraint(r),
        }
    }
}

impl<T: Visitor> VisitorMut for T {
    type Output = <T as Visitor>::Output;

    fn visit_parse_term(&mut self, term: &ParseTerm) -> Self::Output {
        <T as Visitor>::visit_parse_term(self, term)
    }

    fn visit_atom(&mut self, atom: &Atom) -> Self::Output {
        <T as Visitor>::visit_atom(self, atom)
    }

    fn visit_body_atom(&mut self, body_atom: &BodyAtom) -> Self::Output {
        <T as Visitor>::visit_body_atom(self, body_atom)
    }

    fn visit_constraint(&mut self, constraint: &Constraint) -> Self::Output {
        <T as Visitor>::visit_constraint(self, constraint)
    }
}
