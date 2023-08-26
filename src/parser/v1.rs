use super::{Atom, BodyAtom, Constraint, ParseTerm, Predicate};
use nom::branch::alt;
use nom::bytes::complete::{tag, take_until, take_while, take_while1, take_while_m_n};
use nom::character::complete::{i64, multispace1};
use nom::character::is_hex_digit;
use nom::combinator::{cut, map, map_res, opt, value};
use nom::error::{context, ContextError, FromExternalError, ParseError};
use nom::multi::{many0, separated_list0, separated_list1};
use nom::sequence::{delimited, preceded, separated_pair, terminated, tuple};
use nom::IResult;

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
        delimited(
            parse_trivia,
            many0(terminated(parse_constraint, parse_trivia)),
            parse_trivia,
        ),
    )(input)
}
