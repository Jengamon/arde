#![allow(deprecated)]
use sycamore::{futures::spawn_local_scoped, prelude::*};

use arde::{
    evaluate_program_async, evaluate_program_nonasync, library::StandardLibrary, CompiledProgram,
    Compiler, EvalOutput, ProgramError,
};
use tracing_subscriber::fmt::time::UtcTime;
use tracing_subscriber::prelude::*;
use tracing_subscriber::{filter::LevelFilter, fmt::format::Pretty};
use tracing_web::{performance_layer, MakeConsoleWriter};

fn main() {
    console_error_panic_hook::set_once();
    let fmt_layer = tracing_subscriber::fmt::layer()
        .with_ansi(false)
        .with_timer(UtcTime::rfc_3339())
        .with_writer(MakeConsoleWriter);
    let perf_layer = performance_layer().with_details_from_fields(Pretty::default());

    tracing_subscriber::registry()
        .with(fmt_layer.with_filter(LevelFilter::from_level(tracing::Level::DEBUG)))
        .with(perf_layer)
        .init();

    sycamore::render(|cx| {
        view! { cx,
            h1 { "ARDE Testbed" }
            ProgramEditor {}
        }
    });
}

fn print_program_output(output: EvalOutput) -> String {
    match output {
        EvalOutput::Proof(ref proof) => {
            if let Some(proof) = proof {
                proof
                    .iter()
                    .map(|i| i.to_string())
                    .collect::<Vec<_>>()
                    .join(" ← ")
            } else {
                "Proof failed".to_string()
            }
        }
        EvalOutput::Valid(ref vars) => format!("values: {:?}", vars),
        EvalOutput::Invalid => "Could not evaluate".to_string(),
    }
}

#[component(inline_props)]
fn ProgramResults<'a, G: Html>(cx: Scope<'a>, program: Option<CompiledProgram>) -> View<G> {
    let result = create_signal(cx, String::new());
    let sync_result = create_signal(cx, String::new());
    let program2 = program.clone();
    spawn_local_scoped(cx, async move {
        let res_text = match program2 {
            Some(prog) => print_program_output(
                evaluate_program_async(&prog, vec![Box::new(StandardLibrary)]).await,
            ),
            None => String::new(),
        };
        result.set(res_text);
    });
    let sync_text = match program {
        Some(prog) => print_program_output(evaluate_program_nonasync(
            &prog,
            &[Box::new(StandardLibrary)],
        )),
        None => String::new(),
    };
    sync_result.set(sync_text);

    view! {cx,
        p { "ASYNC SOLVER: " (result.get()) }
        p { "SYNC SOLVER: " (sync_result.get()) }
    }
}

#[component(inline_props)]
fn ProgramResultsNoSync<'a, G: Html>(cx: Scope<'a>, program: Option<CompiledProgram>) -> View<G> {
    let result = create_signal(cx, String::new());
    spawn_local_scoped(cx, async move {
        let res_text = match program {
            Some(prog) => print_program_output(
                evaluate_program_async(&prog, vec![Box::new(StandardLibrary)]).await,
            ),
            None => String::new(),
        };
        result.set(res_text);
    });

    view! {cx,
        p { "Solution: " (result.get()) }
    }
}

#[component(inline_props)]
fn CompiledDisplay<'a, G: Html>(
    cx: Scope<'a>,
    program: &'a ReadSignal<Result<CompiledProgram, ProgramError>>,
) -> View<G> {
    let progged = program.map(cx, move |prog| match prog {
        Ok(prog) => {
            let prog = prog.to_string();
            view! {
                cx, (prog)
            }
        }
        Err(e) => match e {
            arde::ProgramError::WinnowError(lines) => {
                let frag = View::new_fragment(
                    lines
                        .iter()
                        .map(|line| {
                            let line = line.clone();
                            view! {cx,
                                (line)
                                br {}
                            }
                        })
                        .collect(),
                );
                view! {
                    cx, pre {
                        code {
                            (frag)
                        }
                    }
                }
            }
            e => {
                let err = format!("Error: {e}");
                view! {
                    cx, (err)
                }
            }
        },
    });

    view! {
        cx,
        p { (progged.get()) }
    }
}

#[component]
fn ProgramEditor<G: Html>(cx: Scope) -> View<G> {
    let program = create_signal(cx, String::new());
    let with_sync = create_signal(cx, true);
    let compiled = create_memo(cx, || Compiler.compile(&program.get()));
    // let compiled_display = create_signal(cx, view! {cx, });

    let sync_label = create_memo(cx, || {
        if *with_sync.get() {
            "With Sync Solver"
        } else {
            "Only Async Solver"
        }
    });
    let program_view = create_signal(cx, view! { cx, });

    view! { cx,
        div {
            input(bind:checked = with_sync, type="checkbox", id="synccheck") {}
            label(for="synccheck") { (
                sync_label.get()
            ) }
        }

        textarea(bind:value = program) {}
        CompiledDisplay(program=compiled) {}
        (*program_view.get())
        div {
            button(on:click = move |_| {
                let program_opt = match compiled.get().as_ref() {
                    Ok(prog) => Some(prog.clone()),
                    Err(_) => None,
                };

                let view = if *with_sync.get() {
                    match program_opt {
                        Some(program) => view! {
                            cx, ProgramResults(program=program)
                        }, None => view! {
                            cx, ProgramResults()
                        }
                    }
                } else {
                    match program_opt {
                        Some(program) => view! {
                            cx, ProgramResultsNoSync(program=program)
                        }, None => view! {
                            cx, ProgramResultsNoSync()
                        }
                    }
                };
                program_view.set(view);
            }) {
                "Submit to Solvers"
            }
        }
    }
}
