use std::{
    collections::{HashMap, HashSet},
    sync::RwLock,
};

use crate::{
    fixed_point_expand,
    parser::Predicate,
    runtime::{CompiledProgram, GroundedAtom, GroundedTerm},
};

// Note about internal mutability:
// Any storage that has been queried and said a fact was true
// MUST continue to say that fact is true in order to maintain a consistent world.
// The only real alternative would be to store all the used facts in fixed
// storage when expanding, and that seems kind inefficient.

pub type ThreadsafeStorageRef = Box<(dyn Storage + Send + Sync)>;

/// This allows for rule-like action by external things.
pub trait Storage {
    fn query(&self, name: &Predicate, terms: &[&GroundedTerm]) -> Option<bool> {
        if self.can_query(name, terms.len()) {
            Some(self._query(name, terms))
        } else {
            None
        }
    }

    fn _query(&self, name: &Predicate, terms: &[&GroundedTerm]) -> bool;
    fn can_query(&self, name: &Predicate, arity: usize) -> bool;

    fn as_fixed(&self) -> Option<&dyn FixedStorage> {
        None
    }
}

/// The trait that allows for things to create ground facts.
pub trait FixedStorage {
    fn get_facts(&self) -> HashSet<GroundedAtom>;
}

/// A (thread-safe) memoized store of facts.
pub struct Memoized {
    store: RwLock<HashMap<GroundedAtom, bool>>,
    storage: ThreadsafeStorageRef,
}

impl Storage for Memoized {
    fn _query(&self, name: &Predicate, terms: &[&GroundedTerm]) -> bool {
        if let Some(key) = self.store.read().ok().and_then(|s| {
            s.keys()
                .find(|ga| &ga.predicate == name && ga.terms.iter().collect::<Vec<_>>() == terms)
                .cloned()
        }) {
            *self.store.read().unwrap().get(&key).unwrap()
        } else {
            let result = self.storage._query(name, terms);

            if let Ok(mut write) = self.store.write() {
                write.insert(
                    GroundedAtom {
                        predicate: name.clone(),
                        terms: terms.iter().cloned().cloned().collect(),
                    },
                    result,
                );
            }
            result
        }
    }

    fn can_query(&self, name: &Predicate, arity: usize) -> bool {
        self.storage.can_query(name, arity)
    }

    fn as_fixed(&self) -> Option<&dyn FixedStorage> {
        Some(self)
    }
}

impl FixedStorage for Memoized {
    fn get_facts(&self) -> HashSet<GroundedAtom> {
        self.store
            .read()
            .ok()
            .into_iter()
            .flat_map(|m| {
                m.iter()
                    .filter_map(|(atom, is_true)| if *is_true { Some(atom.clone()) } else { None })
                    .collect::<Vec<_>>()
            })
            .collect()
    }
}

impl Memoized {
    pub fn new<S: Storage + Send + Sync + 'static>(storage: S) -> Self {
        Self {
            store: RwLock::new(HashMap::new()),
            storage: Box::new(storage),
        }
    }
}

/// A static store of facts.
#[derive(Debug)]
pub struct Fixed {
    pub(crate) facts: Vec<GroundedAtom>,
}

impl std::fmt::Display for Fixed {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        for fact in self.facts.iter() {
            write!(f, "{fact}.")?;
            if f.alternate() {
                writeln!(f)?;
            }
        }
        Ok(())
    }
}

impl FixedStorage for Fixed {
    fn get_facts(&self) -> HashSet<GroundedAtom> {
        self.facts.iter().cloned().collect()
    }
}

impl Storage for Fixed {
    fn _query(&self, name: &Predicate, terms: &[&GroundedTerm]) -> bool {
        let named_facts: Vec<_> = self.facts.iter().filter(|a| &a.predicate == name).collect();

        named_facts
            .into_iter()
            .any(|fact| fact.terms.iter().collect::<Vec<_>>() == terms)
    }

    fn can_query(&self, name: &Predicate, arity: usize) -> bool {
        self.facts
            .iter()
            .any(|a| &a.predicate == name && a.terms.len() == arity)
    }

    fn as_fixed(&self) -> Option<&dyn FixedStorage> {
        Some(self)
    }
}

impl Fixed {
    pub fn new(
        program: &CompiledProgram,
        other: &[ThreadsafeStorageRef],
    ) -> (Self, HashSet<GroundedTerm>) {
        let universe = program.universe();
        fixed_point_expand(&program.facts, &program.rules, &universe, other)
    }
}
