use sycamore::{futures::spawn_local_scoped, prelude::*};

use arde::{
    evaluate_program_async, evaluate_program_nonasync, CompiledProgram, Compiler, EvalOutput,
};

fn main() {
    console_error_panic_hook::set_once();
    tracing_wasm::set_as_global_default();

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
fn ProgramResults<'a, G: Html>(
    cx: Scope<'a>,
    program: &'a ReadSignal<Option<CompiledProgram>>,
) -> View<G> {
    let result = create_signal(cx, String::new());
    let sync_result = create_signal(cx, String::new());
    create_effect(
        cx,
        on([program], move || {
            spawn_local_scoped(cx, async move {
                let res_text = match program.get().as_ref() {
                    Some(prog) => print_program_output(evaluate_program_async(prog, vec![]).await),
                    None => String::new(),
                };
                result.set(res_text);
            });
            let sync_text = match program.get().as_ref() {
                Some(prog) => print_program_output(evaluate_program_nonasync(prog, &[])),
                None => String::new(),
            };
            sync_result.set(sync_text);
        }),
    );

    view! {cx,
        p { "ASYNC SOLVER: " (result.get()) }
        p { "SYNC SOLVER: " (sync_result.get()) }
    }
}

#[component(inline_props)]
fn ProgramResultsNoSync<'a, G: Html>(
    cx: Scope<'a>,
    program: &'a ReadSignal<Option<CompiledProgram>>,
) -> View<G> {
    let result = create_signal(cx, String::new());
    create_effect(
        cx,
        on([program], move || {
            spawn_local_scoped(cx, async move {
                let res_text = match program.get().as_ref() {
                    Some(prog) => print_program_output(evaluate_program_async(prog, vec![]).await),
                    None => String::new(),
                };
                result.set(res_text);
            });
        }),
    );

    view! {cx,
        p { "Solution: " (result.get()) }
    }
}

#[component]
fn ProgramEditor<G: Html>(cx: Scope) -> View<G> {
    let program = create_signal(cx, String::new());
    let with_sync = create_signal(cx, true);
    let compiled = create_memo(cx, || Compiler.compile(&program.get()));
    let compiled_display = create_memo(cx, || match compiled.get().as_ref() {
        Ok(prog) => prog.to_string(),
        Err(e) => format!("Error: {e}"),
    });
    let sync_label = create_memo(cx, || {
        if *with_sync.get() {
            "With Sync Solver"
        } else {
            "Only Async Solver"
        }
    });
    let program_view = create_signal(cx, view! { cx, });

    create_effect(
        cx,
        on([program, sync_label], move || {
            let program_opt = create_memo(cx, || match compiled.get().as_ref() {
                Ok(prog) => Some(prog.clone()),
                Err(_) => None,
            });

            let view = if *with_sync.get() {
                view! {
                    cx, ProgramResults(program=program_opt)
                }
            } else {
                view! {
                    cx, ProgramResultsNoSync(program=program_opt)
                }
            };
            program_view.set(view);
        }),
    );

    view! { cx,
        div {
            input(bind:checked = with_sync, type="checkbox", id="synccheck") {}
            label(for="synccheck") { (
                sync_label.get()
            ) }
        }

        textarea(bind:value = program) {}
        p { (compiled_display.get()) }
        (*program_view.get())
    }
}
