//! Standard modules (storages) for niceties
//! like being able to check if 2 different variables are actually the same value

use crate::{atom, FixedStorage, GroundedTerm, Storage};

pub struct StandardLibrary;

impl Storage for StandardLibrary {
    fn _query(&self, name: &crate::parser::Predicate, terms: &[&GroundedTerm]) -> bool {
        if &name.to_string() == "@is" {
            if terms.len() != 2 {
                return false;
            }
            terms[0] == terms[1]
        } else if &name.to_string() == "@exrange" {
            if terms.len() != 3 {
                return false;
            }
            let value = match terms[0] {
                GroundedTerm::Integer(i) => i,
                _ => return false,
            };
            match terms[1] {
                GroundedTerm::Integer(i) => match terms[2] {
                    GroundedTerm::Integer(j) => i <= value && j > value,
                    _ => false,
                },
                _ => false,
            }
        } else if &name.to_string() == "@incrange" {
            if terms.len() != 3 {
                return false;
            }
            let value = match terms[0] {
                GroundedTerm::Integer(i) => i,
                _ => return false,
            };
            match terms[1] {
                GroundedTerm::Integer(i) => match terms[2] {
                    GroundedTerm::Integer(j) => i <= value && j >= value,
                    _ => false,
                },
                _ => false,
            }
        } else if &name.to_string() == "@type" {
            if terms.len() != 2 {
                return false;
            }
            match terms[0] {
                GroundedTerm::Integer(_) => terms[1] == &GroundedTerm::String("integer".into()),
                GroundedTerm::String(_) => terms[1] == &GroundedTerm::String("string".into()),
                GroundedTerm::Uuid(_) => terms[1] == &GroundedTerm::String("uuid".into()),
                GroundedTerm::Boolean(_) => terms[1] == &GroundedTerm::String("boolean".into()),
            }
        } else if &name.to_string() == "@version_check" {
            if terms.len() != 1 {
                return false;
            }
            match terms[0] {
                GroundedTerm::String(s) => s == "0.0.1",
                GroundedTerm::Integer(i) => *i == 0,
                _ => false,
            }
        } else {
            false
        }
    }

    fn can_query(&self, name: &crate::parser::Predicate, arity: usize) -> bool {
        type QueryDefinition<'a> = (&'a str, fn(usize) -> bool);
        const HANDLED_QUERIES: &[QueryDefinition] = &[
            ("@is", |arity| arity == 2),
            ("@exrange", |arity| arity == 3),
            ("@incrange", |arity| arity == 3),
            ("@type", |arity| arity == 2),
            ("@version_check", |arity| arity == 1),
        ];

        HANDLED_QUERIES
            .iter()
            .filter(|(fc, _)| fc == &name.to_string())
            .any(|(_, f)| f(arity))
    }

    fn as_fixed(&self) -> Option<&dyn crate::FixedStorage> {
        Some(self)
    }
}

impl FixedStorage for StandardLibrary {
    fn get_facts(&self) -> std::collections::HashSet<crate::GroundedAtom> {
        vec![
            atom!(@stdlib_version (string "0.0.1".into())),
            atom!(@stdlib_version (integer 0)),
            atom!(@stdlib_version_prerelease (boolean true)),
            atom!(@possible_type (string "integer".into())),
            atom!(@possible_type (string "string".into())),
            atom!(@possible_type (string "uuid".into())),
            atom!(@possible_type (string "boolean".into())),
        ]
        .into_iter()
        .collect()
    }
}
