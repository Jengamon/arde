use std::path::Path;

fn parser_test(path: &Path) -> datatest_stable::Result<()> {
    todo!()
}

datatest_stable::harness!(parser_test, "tests/parser/", r"^.*.tdt");
