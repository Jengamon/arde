# Arde - Another Rust Datalog Engine

Just a Datalog thingy for Dataloggy stuff.

TODO Docs

## Version 0.2.0

This can be thought of as an alternate version of 0.1.8 that gets the async resolver (top-down) right.

It moves the interface to use all Send + Sync types, so if you want to run !Send or !Sync storages, use 0.1.8 nonasync for now. (For this reason, the web feature was removed)

Because of this switch of focus, I won't be updating the sync solver unless very necessary. The sync solver doesn't do well with ~~sole~~ factless negation. It cannot solve:

```prolog
c :- not d.
c?
```

however, the async solver can.

Both can solve

```prolog
b.
c :- not d.
c?
```

## Note about tests

As they are, they aren't perfect, because the tests are sensitive to ordering
and proof branching (while programs don't actually care), so actually *read* what the tests are saying, because both:

```
expected:
A: 30, 4
actual:
A: 4, 30
```

and

```
expected:
b("s") -> a("s").
actual:
NO PROOF
```

are equally marked as errors.

## TRACING

Be *incredibly* careful about enabling tracing within this crate.
The traces right now are noisy at the info level, which should be changed.
And will take a worst-case logic bomb `damn2_async.tdt` from taking around
10s on a M1 Macbook, to over a minute.

Basically, until the tracing is denoised, always use an env-filter and
don't use arde at the info level.