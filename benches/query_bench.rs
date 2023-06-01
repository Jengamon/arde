extern crate deity_query;

use criterion::{black_box, criterion_group, criterion_main, Criterion};
use deity_query::{
    evaluate_program_async, evaluate_program_nonasync, library::StandardLibrary, CompiledProgram,
    Compiler, StorageRef, ThreadsafeStorageRef,
};
use tokio::runtime::Runtime;

const SOURCE_DATA: &'static str = include_str!("bench_sel.sel");

fn bench_execute_empty(c: &mut Criterion) {
    let program = Compiler.compile("").unwrap();
    let runtime = Runtime::new().unwrap();

    c.bench_function("execute_empty nonasync", |b| {
        b.iter(|| evaluate_program_nonasync(black_box(&program), []))
    });

    c.bench_function("execute_empty async", |b| {
        b.to_async(&runtime)
            .iter(|| evaluate_program_async(black_box(&program), []))
    });
}

fn bench_execute_no_storage(c: &mut Criterion) {
    let program = Compiler.compile(SOURCE_DATA).unwrap();
    let runtime = Runtime::new().unwrap();

    c.bench_function("execute_no_storage nonasync", |b| {
        b.iter(|| evaluate_program_nonasync(black_box(&program), []))
    });

    c.bench_function("execute_no_storage async", |b| {
        b.to_async(&runtime)
            .iter(|| evaluate_program_async(black_box(&program), []))
    });
}

fn bench_execute_std_storage(c: &mut Criterion) {
    let program = Compiler.compile(SOURCE_DATA).unwrap();
    let runtime = Runtime::new().unwrap();

    c.bench_function("execute_std_storage nonasync", |b| {
        b.iter(|| evaluate_program_nonasync(black_box(&program), [&StandardLibrary as StorageRef]))
    });

    c.bench_function("execute_std_storage async", |b| {
        b.to_async(&runtime).iter(|| {
            evaluate_program_async(
                black_box(&program),
                [&StandardLibrary as ThreadsafeStorageRef],
            )
        })
    });
}

fn bench_execute_std_storage_top_down(c: &mut Criterion) {
    let program = Compiler.compile(SOURCE_DATA).unwrap();
    let goal = Compiler.compile("ultifact(a, b, c)?").unwrap();
    let runtime = Runtime::new().unwrap();

    let combined_program = CompiledProgram {
        facts: program.facts.clone(),
        rules: program.rules.clone(),
        goal: goal.goal,
    };

    c.bench_function(
        "execute_std_storage_top_down unprovable fact nonasync",
        |b| {
            b.iter(|| {
                evaluate_program_nonasync(
                    black_box(&combined_program),
                    [&StandardLibrary as StorageRef],
                )
            })
        },
    );

    c.bench_function("execute_std_storage_top_down unprovable fact async", |b| {
        b.to_async(&runtime).iter(|| {
            evaluate_program_async(
                black_box(&combined_program),
                [&StandardLibrary as ThreadsafeStorageRef],
            )
        })
    });

    let goal = Compiler.compile("ultifact(0, 1, 2)?").unwrap();

    let combined_program = CompiledProgram {
        facts: program.facts,
        rules: program.rules,
        goal: goal.goal,
    };

    c.bench_function("execute_std_storage_top_down provable fact nonasync", |b| {
        b.iter(|| {
            evaluate_program_nonasync(
                black_box(&combined_program),
                [&StandardLibrary as StorageRef],
            )
        })
    });

    c.bench_function("execute_std_storage_top_down provable fact async", |b| {
        b.to_async(&runtime).iter(|| {
            evaluate_program_async(
                black_box(&combined_program),
                [&StandardLibrary as ThreadsafeStorageRef],
            )
        })
    });
}

criterion_group!(
    benches,
    bench_execute_empty,
    bench_execute_no_storage,
    bench_execute_std_storage,
    bench_execute_std_storage_top_down
);
criterion_main!(benches);
