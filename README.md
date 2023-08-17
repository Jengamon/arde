# Arde - Another Rust Datalog Engine

Just a Datalog thingy for Dataloggy stuff.

TODO Docs

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
