use winnow::ascii::{alpha0, digit1, hex_digit1, multispace1};
use winnow::combinator::{
    alt, cut_err, delimited, dispatch, fail, opt, preceded, repeat, separated0, separated1,
    separated_pair, success, terminated,
};
use winnow::error::{ContextError, ParseError, ParserError, StrContext};
use winnow::token::{any, one_of, take_till0, take_till1};
use winnow::PResult;
use winnow::Parser;

use super::{Atom, BodyAtom, Constraint, ParseTerm, Predicate};

fn parse_bool(input: &mut &str) -> PResult<bool> {
    dispatch! {any;
        't' => preceded("rue", success(true)),
        'f' => preceded("alse", success(false)),
        _ => fail::<_, bool, _>
    }
    .parse_next(input)
}

fn parse_integer(input: &mut &str) -> PResult<i64> {
    digit1.parse_to().parse_next(input)
}

fn parse_variable(input: &mut &str) -> PResult<String> {
    (one_of('A'..='Z'), cut_err(alpha0))
        .recognize()
        .map(ToString::to_string)
        .parse_next(input)
}

fn parse_atomic_string(input: &mut &str) -> PResult<String> {
    parse_identifier.parse_next(input)
}

// TODO Add escape processing
fn parse_string(input: &mut &str) -> PResult<String> {
    preceded('"', cut_err(terminated(take_till0(['"']), '"')))
        .map(ToString::to_string)
        .parse_next(input)
}

fn parse_uuid(input: &mut &str) -> PResult<uuid::Uuid> {
    preceded(
        '#',
        (
            terminated(hex_digit1.verify(|i: &str| i.len() == 8), opt('-')),
            terminated(hex_digit1.verify(|i: &str| i.len() == 4), opt('-')),
            terminated(hex_digit1.verify(|i: &str| i.len() == 4), opt('-')),
            terminated(hex_digit1.verify(|i: &str| i.len() == 4), opt('-')),
            hex_digit1.verify(|i: &str| i.len() == 12),
        )
            .recognize(),
    )
    .parse_to()
    .parse_next(input)
}

fn parse_term(input: &mut &str) -> PResult<ParseTerm> {
    alt((
        parse_variable
            .map(ParseTerm::Variable)
            .context(StrContext::Label("variable")),
        parse_bool
            .map(ParseTerm::Bool)
            .context(StrContext::Label("boolean")),
        parse_atomic_string
            .map(ParseTerm::String)
            .context(StrContext::Label("atomic-string")),
        parse_string
            .map(ParseTerm::String)
            .context(StrContext::Label("string")),
        parse_uuid
            .map(ParseTerm::Uuid)
            .context(StrContext::Label("Uuid")),
        // No longer cuts, so should be last attempt
        parse_integer
            .map(ParseTerm::Integer)
            .context(StrContext::Label("integer")),
    ))
    .parse_next(input)
}

impl std::str::FromStr for ParseTerm {
    type Err = String;

    fn from_str(s: &str) -> Result<Self, Self::Err> {
        parse_term.parse(s).map_err(|e| e.to_string())
    }
}

fn parse_identifier(input: &mut &str) -> PResult<String> {
    let allowed_nondigit = |c: char| c.is_alphabetic() || "_!~+-*/&|".contains(c);
    (
        one_of(allowed_nondigit),
        cut_err(repeat(
            0..,
            one_of(move |c: char| allowed_nondigit(c) || c.is_numeric()),
        )),
    )
        .map(|(p, s): (char, String)| format!("{p}{s}"))
        .verify(|s| !["not"].contains(&s))
        .parse_next(input)
}

fn parse_predicate(input: &mut &str) -> PResult<Predicate> {
    alt((
        preceded('@', cut_err(parse_identifier))
            .map(|n| Predicate {
                is_intrinsic: true,
                name: n,
            })
            .context(StrContext::Label("intrinsic-predicate")),
        parse_identifier
            .map(|n| Predicate {
                is_intrinsic: false,
                name: n,
            })
            .context(StrContext::Label("regular-predicate")),
    ))
    .parse_next(input)
}

impl std::str::FromStr for Predicate {
    type Err = String;
    fn from_str(s: &str) -> Result<Self, Self::Err> {
        parse_predicate.parse(s).map_err(|e| e.to_string())
    }
}

fn parse_atom(input: &mut &str) -> PResult<Atom> {
    (
        parse_predicate,
        opt(delimited(
            delimited(opt(parse_trivia), '(', opt(parse_trivia)),
            separated0(
                parse_term,
                delimited(opt(parse_trivia), ',', opt(parse_trivia)),
            ),
            delimited(opt(parse_trivia), ')', opt(parse_trivia)),
        )),
    )
        .map(|(predicate, terms_opt)| Atom {
            predicate,
            terms: terms_opt.unwrap_or(vec![]),
        })
        .parse_next(input)
}

impl std::str::FromStr for Atom {
    type Err = String;
    fn from_str(s: &str) -> Result<Self, Self::Err> {
        parse_atom.parse(s).map_err(|e| e.to_string())
    }
}

fn parse_body_atom(input: &mut &str) -> PResult<BodyAtom> {
    alt((
        (terminated("not", opt(parse_trivia)), cut_err(parse_atom))
            .map(|(_, atom)| BodyAtom::Negative(atom))
            .context(StrContext::Label("negative-body-atom")),
        parse_atom
            .map(BodyAtom::Positive)
            .context(StrContext::Label("positive-body-atom")),
    ))
    .parse_next(input)
}

impl std::str::FromStr for BodyAtom {
    type Err = String;
    fn from_str(s: &str) -> Result<Self, Self::Err> {
        parse_body_atom.parse(s).map_err(|e| e.to_string())
    }
}

fn parse_constraint(input: &mut &str) -> PResult<Constraint> {
    alt((
        terminated(
            separated_pair(
                parse_atom,
                delimited(opt(parse_trivia), ":-", opt(parse_trivia)),
                separated1(
                    parse_body_atom,
                    delimited(opt(parse_trivia), ',', opt(parse_trivia)),
                ),
            ),
            preceded(opt(parse_trivia), '.'),
        )
        .map(|(head, body)| Constraint::Rule { head, body })
        .context(StrContext::Label("rule")),
        terminated(parse_atom, preceded(opt(parse_trivia), '.'))
            .map(Constraint::Fact)
            .context(StrContext::Label("fact")),
        terminated(parse_body_atom, preceded(opt(parse_trivia), '?'))
            .map(Constraint::Goal)
            .context(StrContext::Label("goal")),
    ))
    .parse_next(input)
}

impl std::str::FromStr for Constraint {
    type Err = String;
    fn from_str(s: &str) -> Result<Self, Self::Err> {
        parse_constraint.parse(s).map_err(|e| e.to_string())
    }
}

fn parse_comment<'a, E: ParserError<&'a str>>(input: &mut &'a str) -> PResult<&'a str, E> {
    preceded('%', take_till1(['\n', '\r'])).parse_next(input)
}

fn parse_trivia<'a, E: ParserError<&'a str>>(input: &mut &'a str) -> PResult<(), E> {
    repeat::<_, _, (), _, _>(1.., alt((multispace1, parse_comment)))
        .void()
        .parse_next(input)
}

pub fn parser<'a>(
    input: &mut &'a str,
) -> Result<Vec<Constraint>, ParseError<&'a str, ContextError>> {
    preceded(
        opt(parse_trivia),
        repeat(0.., terminated(parse_constraint, opt(parse_trivia))),
    )
    .parse(input)
}
