use std::path::Path;

fn parser_test(_path: &Path) -> datatest_stable::Result<()> {
    todo!("replace datadriven with datatest-stable...")
}

datatest_stable::harness!(parser_test, "tests/parser/", r"^.*.tdt");
