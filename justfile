test:
    cargo test -- --nocapture

nextest:
    cargo nextest r --no-fail-fast

graph:
    cat tracing.folded | inferno-flamegraph > tracing-flamegraph.local.svg

chart:
    cat tracing.folded | inferno-flamegraph --flamechart > tracing-flamechart.local.svg
