; highlights.scm

(atom (predicate) @function.method.builtin
  (#match? @function.method.builtin "^@"))
(goal_definition (body_atom (atom (predicate) @function.method)))
(rule_definition head: (atom (predicate) @function))
"not" @keyword
(integer) @number
(atomic_string) @string
(string) @string
(boolean) @constant.builtin
(variable) @variable.parameter
(uuid) @constant
[
  "."
  "?"
] @punctuation.delimiter
(comment) @comment
":-" @operator
[
  "("
  ")"
] @punctuation.bracket