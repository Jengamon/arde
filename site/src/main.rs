use sycamore::{futures::spawn_local_scoped, prelude::*};

use arde::{evaluate_program_async, CompiledProgram, Compiler};

fn main() {
    console_error_panic_hook::set_once();
    tracing_wasm::set_as_global_default();

    sycamore::render(|cx| {
        view! { cx,
            p { "Hello, World!" }
            ProgramEditor {}
        }
    });
}

#[component(inline_props)]
async fn ProgramResults<'a, G: Html>(
    cx: Scope<'a>,
    program: &'a ReadSignal<Option<CompiledProgram>>,
) -> View<G> {
    let result = create_signal(cx, String::new());
    create_effect(
        cx,
        on([program], move || {
            spawn_local_scoped(cx, async move {
                program.track();
                let res_text = match program.get().as_ref() {
                    Some(prog) => match evaluate_program_async(prog, vec![]).await {
                        arde::EvalOutput::Proof(ref proof) => {
                            if let Some(proof) = proof {
                                format!(
                                    "Proof: {}",
                                    proof
                                        .into_iter()
                                        .map(|i| i.to_string())
                                        .collect::<Vec<_>>()
                                        .join(" <- ")
                                )
                            } else {
                                format!("Proof failed")
                            }
                        }
                        arde::EvalOutput::Valid(ref vars) => format!("Proven vars: {:?}", vars),
                        arde::EvalOutput::Invalid => format!("Could not evaluate"),
                    },
                    None => String::new(),
                };
                result.set(res_text);
            })
        }),
    );

    view! {cx,
        p { (result.get()) }
    }
}

#[component]
fn ProgramEditor<'a, G: Html>(cx: Scope<'a>) -> View<G> {
    let program = create_signal(cx, String::new());
    let compiled = create_memo(cx, || Compiler.compile(&program.get()));
    let compiled_display = create_memo(cx, || match compiled.get().as_ref() {
        Ok(prog) => prog.to_string(),
        Err(e) => format!("Error: {e}"),
    });
    let program_opt = create_memo(cx, || match compiled.get().as_ref() {
        Ok(prog) => Some(prog.clone()),
        Err(_) => None,
    });

    view! { cx,
        textarea(bind:value = program) {}
        p { (compiled_display.get()) }
        ProgramResults(program=program_opt) {}
    }
}
