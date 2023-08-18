# Arde - Another Rust Datalog Engine

Just a Datalog thingy for Dataloggy stuff.

TODO Docs

## Version 0.2.0

This can be thought of as an alternate version of 0.1.8 that gets the async resolver (top-down) right.

It moves the interface to use all Send + Sync types, so if you want to run !Send or !Sync storages, use 0.1.8 nonasync for now. (For this reason, the web feature was removed)

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
