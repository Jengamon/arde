use arde::parser::parser;
use nom::error::{convert_error, VerboseError};
use nom::Finish;
use similar::{ChangeTag, TextDiff};
use std::path::Path;
use tracing_subscriber::fmt;

#[derive(thiserror::Error, Debug)]
enum ParserTestError {
    #[error("missing directive")]
    MissingDirective,
    #[error("invalid directive {0}")]
    InvalidDirective(String),
    #[error("test failed")]
    Mismatch,
}

fn parser_test(path: &Path) -> datatest_stable::Result<()> {
    drop(
        fmt()
            .pretty()
            .with_ansi(std::env::var("NOCOLOR").is_err())
            .try_init(),
    );

    let test_contents = std::fs::read_to_string(path)?;
    let test_file = test_contents.lines();
    let directive = test_file.clone().next();
    if let Some(directive) = directive {
        let input = test_file
            .clone()
            .skip(1)
            .take_while(|p| *p != "----")
            .map(|l| format!("{}\n", l))
            .collect::<String>();
        let expected = test_file
            .skip_while(|p| *p != "----")
            .skip(1)
            .map(|l| format!("{}\n", l))
            .collect::<String>();
        match directive {
            "root" => {
                let (remaining, output) = match parser::<VerboseError<&str>>(&input).finish() {
                    Ok(data) => data,
                    Err(e) => Err(convert_error(input.as_str(), e))?,
                };
                assert_eq!(remaining, "");
                let actual = serde_json::to_string_pretty(&output)?;

                let diff = TextDiff::from_lines(expected.trim(), actual.trim());

                let mut changes = 0;
                for change in diff.iter_all_changes() {
                    let sign = match change.tag() {
                        ChangeTag::Delete => {
                            changes += 1;
                            "-"
                        }
                        ChangeTag::Insert => {
                            changes += 1;
                            "+"
                        }
                        ChangeTag::Equal => " ",
                    };
                    print!("{}{}", sign, change);
                }

                if changes > 0 {
                    Err(ParserTestError::Mismatch)?
                } else {
                    Ok(())
                }
            }
            d => Err(ParserTestError::InvalidDirective(d.to_string()))?,
        }
    } else {
        Err(ParserTestError::MissingDirective)?
    }
}

datatest_stable::harness!(parser_test, "tests/parser/", r"^.*.tdt");
