test:
    cargo test -- --nocapture

graph:
    cat tracing.folded | inferno-flamegraph > tracing-flamegraph.local.svg

chart:
    cat tracing.folded | inferno-flamegraph --flamechart > tracing-flamechart.local.svg
