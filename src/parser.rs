use nom::branch::alt;
use nom::bytes::complete::{tag, take_until, take_while, take_while1, take_while_m_n};
use nom::character::complete::{i64, multispace1};
use nom::character::is_hex_digit;
use nom::combinator::{cut, map, map_res, opt, value};
use nom::error::{context, ContextError, FromExternalError, ParseError};
use nom::multi::{many0, separated_list0, separated_list1};
use nom::sequence::{delimited, preceded, separated_pair, terminated, tuple};
use nom::IResult;

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

fn parse_bool<'input, E: ParseError<&'input str> + ContextError<&'input str>>(
    input: &'input str,
) -> IResult<&str, bool, E> {
    context(
        "bool",
        alt((value(true, tag("true")), value(false, tag("false")))),
    )(input)
}

fn is_ident_char(c: char) -> bool {
    "_!~+-*/&|".contains(c)
}

fn identifier<'input, E: ParseError<&'input str>>(input: &'input str) -> IResult<&str, String, E> {
    map(
        tuple((
            take_while1(|s: char| s.is_alphabetic() || is_ident_char(s)),
            take_while(|s: char| s.is_alphanumeric() || is_ident_char(s)),
        )),
        |(s, t): (&str, &str)| format!("{s}{t}"),
    )(input)
}

fn cap_identifier<'input, E: ParseError<&'input str>>(
    input: &'input str,
) -> IResult<&str, String, E> {
    map(
        tuple((
            take_while1(|s: char| s.is_uppercase() && s.is_alphabetic()),
            take_while(|s: char| s.is_alphanumeric() || is_ident_char(s)),
        )),
        |(s, t): (&str, &str)| format!("{s}{t}"),
    )(input)
}

#[derive(thiserror::Error, Debug)]
pub enum TermError {
    #[error("uuid error: {0}")]
    Uuid(#[source] uuid::Error),
    #[error("predicate cannot be used")]
    PredicateNotError,
}

impl From<uuid::Error> for TermError {
    fn from(value: uuid::Error) -> Self {
        Self::Uuid(value)
    }
}

fn parse_term<
    'input,
    E: ParseError<&'input str> + ContextError<&'input str> + FromExternalError<&'input str, TermError>,
>(
    input: &'input str,
) -> IResult<&str, ParseTerm, E> {
    alt((
        map(parse_bool, ParseTerm::Bool),
        map(context("integer", i64), ParseTerm::Integer),
        map(context("variable", cap_identifier), ParseTerm::Variable),
        map_res(context("atomic-string", identifier), |s: String| {
            forbidden_predicates(&s).map(|_| ParseTerm::String(s))
        }),
        map(
            context(
                "string",
                preceded(tag("\""), cut(terminated(take_until("\""), tag("\"")))),
            ),
            |s: &str| ParseTerm::String(s.to_string()),
        ),
        context(
            "uuid",
            preceded(
                tag("#"),
                cut(alt((
                    map_res(
                        take_while_m_n(32, 32, |c| is_hex_digit(c as u8)),
                        |s: &str| Ok(ParseTerm::Uuid(uuid::Uuid::parse_str(s)?)),
                    ),
                    map_res(
                        tuple((
                            take_while_m_n(8, 8, |c| is_hex_digit(c as u8)),
                            tag("-"),
                            take_while_m_n(4, 4, |c| is_hex_digit(c as u8)),
                            tag("-"),
                            take_while_m_n(4, 4, |c| is_hex_digit(c as u8)),
                            tag("-"),
                            take_while_m_n(4, 4, |c| is_hex_digit(c as u8)),
                            tag("-"),
                            take_while_m_n(12, 12, |c| is_hex_digit(c as u8)),
                        )),
                        |(a, _, b, _, c, _, d, _, e)| {
                            Ok(ParseTerm::Uuid(uuid::Uuid::parse_str(&format!(
                                "{a}-{b}-{c}-{d}-{e}"
                            ))?))
                        },
                    ),
                ))),
            ),
        ),
    ))(input)
}

fn forbidden_predicates(s: &str) -> Result<(), TermError> {
    if ["not"].contains(&s) {
        Err(TermError::PredicateNotError)
    } else {
        Ok(())
    }
}

fn parse_predicate<
    'input,
    E: ParseError<&'input str> + ContextError<&'input str> + FromExternalError<&'input str, TermError>,
>(
    input: &'input str,
) -> IResult<&str, Predicate, E> {
    context(
        "predicate",
        alt((
            map_res(preceded(tag("@"), identifier), |name: String| {
                forbidden_predicates(&name).map(|_| Predicate {
                    is_intrinsic: true,
                    name,
                })
            }),
            map_res(identifier, |name: String| {
                forbidden_predicates(&name).map(|_| Predicate {
                    is_intrinsic: false,
                    name,
                })
            }),
        )),
    )(input)
}

fn parse_comment<'input, E: ParseError<&'input str>>(input: &'input str) -> IResult<&str, &str, E> {
    delimited(tag("%"), take_until("\n"), tag("\n"))(input)
}

fn parse_trivia<'input, E: ParseError<&'input str>>(
    input: &'input str,
) -> IResult<&str, Vec<&str>, E> {
    many0(alt((multispace1, parse_comment)))(input)
}

fn parse_atom<
    'input,
    E: ParseError<&'input str>
        + ContextError<&'input str>
        + FromExternalError<&'input str, TermError>
        + FromExternalError<&'input str, uuid::Error>,
>(
    input: &'input str,
) -> IResult<&str, Atom, E> {
    let (input, predicate) = context("atom_predicate", parse_predicate)(input)?;
    let (input, terms) = context(
        "atom_terms",
        opt(delimited(
            tuple((parse_trivia, tag("("), parse_trivia)),
            separated_list0(tuple((parse_trivia, tag(","), parse_trivia)), parse_term),
            tuple((parse_trivia, tag(")"), parse_trivia)),
        )),
    )(input)?;
    Ok((
        input,
        Atom {
            predicate,
            terms: terms.unwrap_or(vec![]),
        },
    ))
}

fn parse_body_atom<
    'input,
    E: ParseError<&'input str>
        + ContextError<&'input str>
        + FromExternalError<&'input str, TermError>
        + FromExternalError<&'input str, uuid::Error>,
>(
    input: &'input str,
) -> IResult<&str, BodyAtom, E> {
    context(
        "body_atom",
        alt((
            map(
                preceded(
                    tuple((tag("not"), tuple((multispace1, parse_trivia)))),
                    parse_atom,
                ),
                BodyAtom::Negative,
            ),
            map(parse_atom, BodyAtom::Positive),
        )),
    )(input)
}

fn parse_constraint<
    'input,
    E: ParseError<&'input str>
        + ContextError<&'input str>
        + FromExternalError<&'input str, TermError>
        + FromExternalError<&'input str, uuid::Error>,
>(
    input: &'input str,
) -> IResult<&str, Constraint, E> {
    context(
        "constraint",
        alt((
            map(
                terminated(
                    separated_pair(
                        parse_atom,
                        tuple((parse_trivia, tag(":-"), parse_trivia)),
                        separated_list1(
                            tuple((parse_trivia, tag(","), parse_trivia)),
                            parse_body_atom,
                        ),
                    ),
                    preceded(parse_trivia, tag(".")),
                ),
                |(atom, body_atoms): (Atom, Vec<BodyAtom>)| Constraint::Rule {
                    head: atom,
                    body: body_atoms,
                },
            ),
            map(
                terminated(parse_atom, preceded(parse_trivia, tag("."))),
                Constraint::Fact,
            ),
            map(
                terminated(parse_body_atom, preceded(parse_trivia, tag("?"))),
                Constraint::Goal,
            ),
        )),
    )(input)
}

pub fn parser<
    'input,
    E: ParseError<&'input str>
        + ContextError<&'input str>
        + FromExternalError<&'input str, TermError>
        + FromExternalError<&'input str, uuid::Error>,
>(
    input: &'input str,
) -> IResult<&str, Vec<Constraint>, E> {
    context(
        "program",
        preceded(
            parse_trivia,
            many0(terminated(parse_constraint, parse_trivia)),
        ),
    )(input)
}
