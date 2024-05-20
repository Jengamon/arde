use std::{collections::HashSet, sync::Arc};

use crate::{
    Atom, Fixed, GroundedAtom, GroundedBodyAtom, GroundedTerm, Rule, ThreadsafeStorageRef,
};

pub(crate) fn fixed_point_expand(
    facts: &[(String, Vec<GroundedTerm>)],
    rules: &[Rule],
    universe: &HashSet<GroundedTerm>,
    other: &[ThreadsafeStorageRef],
) -> (Fixed, HashSet<GroundedTerm>) {
    todo!()
}

#[cfg(feature = "async")]
#[tracing::instrument(skip(universe, facts, rules, ext_storages))]
pub(crate) async fn provable<'a>(
    universe: Vec<GroundedTerm>,
    current_mapping: Vec<GroundedTerm>,
    facts: Vec<GroundedAtom>,
    rules: Vec<Rule>,
    subject: Atom,
    ext_storages: Arc<Vec<ThreadsafeStorageRef>>,
) -> Option<Vec<GroundedBodyAtom>> {
    todo!()
}
