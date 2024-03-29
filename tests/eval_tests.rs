#![allow(deprecated)]
use arde::{
    evaluate_program_async, evaluate_program_nonasync, library::StandardLibrary, Compiler,
    EvalOutput,
};
use similar::{ChangeTag, TextDiff};
use std::path::Path;
use tokio::runtime::Builder;
use tracing_subscriber::{fmt, EnvFilter};

#[derive(thiserror::Error, Debug)]
enum EvalTestError {
    #[error("missing directive")]
    MissingDirective,
    #[error("invalid directive {0}")]
    InvalidDirective(String),
    #[error("test failure")]
    Mismatch,
}

fn eval_test(path: &Path) -> datatest_stable::Result<()> {
    drop(
        fmt()
            .pretty()
            .with_ansi(std::env::var("NOCOLOR").is_err())
            .with_env_filter(EnvFilter::from_default_env())
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
            "async" => {
                let rt = Builder::new_multi_thread().build().unwrap();
                let program = Compiler.compile(&input)?;
                let actual = match rt.block_on(evaluate_program_async(
                    &program,
                    vec![Box::new(StandardLibrary)],
                )) {
                    EvalOutput::Invalid => "INVALID".to_string(),
                    EvalOutput::Proof(proof) => match proof {
                        Some(proof) => proof
                            .iter()
                            .map(|i| i.to_string())
                            .collect::<Vec<_>>()
                            .join(" -> "),
                        None => "NO PROOF".to_string(),
                    },
                    EvalOutput::Valid(mapping) => mapping
                        .into_iter()
                        .map(|(k, vs)| {
                            format!(
                                "{k}: {}",
                                vs.into_iter()
                                    .map(|i| i.to_string())
                                    .collect::<Vec<_>>()
                                    .join(", ")
                            )
                        })
                        .collect::<Vec<_>>()
                        .join("\n"),
                };

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
                    Err(EvalTestError::Mismatch)?
                } else {
                    Ok(())
                }
            }
            "sync" => {
                let program = Compiler.compile(&input)?;
                let actual = match evaluate_program_nonasync(&program, &[Box::new(StandardLibrary)])
                {
                    crate::EvalOutput::Invalid => "INVALID".to_string(),
                    crate::EvalOutput::Proof(proof) => match proof {
                        Some(proof) => proof
                            .iter()
                            .map(|i| i.to_string())
                            .collect::<Vec<_>>()
                            .join(" -> "),
                        None => "NO PROOF".to_string(),
                    },
                    crate::EvalOutput::Valid(mapping) => mapping
                        .into_iter()
                        .map(|(k, vs)| {
                            format!(
                                "{k}: {}",
                                vs.into_iter()
                                    .map(|i| i.to_string())
                                    .collect::<Vec<_>>()
                                    .join(", ")
                            )
                        })
                        .collect::<Vec<_>>()
                        .join("\n"),
                };

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
                    Err(EvalTestError::Mismatch)?
                } else {
                    Ok(())
                }
            }
            d => Err(EvalTestError::InvalidDirective(d.to_string()))?,
        }
    } else {
        Err(EvalTestError::MissingDirective)?
    }
}

datatest_stable::harness!(eval_test, "tests/eval/", r"^.*.tdt");
