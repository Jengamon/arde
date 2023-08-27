module.exports = grammar({
  name: 'datalog_arde',
  extras: $ => [$._whitespace, $.comment],

  rules: {
    source_file: $ => repeat(seq($._constraint)),

    _constraint: $ => choice(
      $.rule_definition,
      $.fact_definition,
      $.goal_definition,
    ),

    _whitespace: $ => /\s+/,
    comment: $ => /%[^\r\n]*\r?\n/,

    rule_definition: $ => prec(2, seq(
      field("head", $.atom),
      ':-',
      $.body_atom,
      repeat(seq(',', $.body_atom)),
      '.'
    )),

    fact_definition: $ => seq(
      $.atom,
      '.'
    ),

    goal_definition: $ => seq(
      $.body_atom,
      '?'
    ),

    body_atom: $ => choice(
      seq('not',  $.atom),
      $.atom
    ),

    atom: $ => seq(
      $.predicate,
      optional(seq(
        '(',
        optional(seq(
          $.term,
          repeat(
            seq(',', $.term),
          ),
        )),
        ')',
      ))
    ),

    predicate: $ => choice(
      token.immediate(seq('@', /[_!~+\-*/&|\p{Alpha}][_!~+\-*/&|\p{Alpha}\p{Nd}\p{No}\p{Nl}]*/u)),
      /[_!~+\-*/&|\p{Alpha}][_!~+\-*/&|\p{Alpha}\p{Nd}\p{No}\p{Nl}]*/u
    ),

    term: $ => choice(
      $.variable,
      $.boolean,
      $.integer,
      $.atomic_string,
      $.string,
      $.uuid,
    ),

    variable: $ => /[\p{Upper}][_!~+\-*/&|\p{Alpha}\p{Nd}\p{Nl}\p{No}]*/u,
    boolean: $ => choice('true', 'false'),
    integer: $ => /\d+/,
    atomic_string: $ => /[_!~+\-*/&|\p{Lower}][_!~+\-*/&|\p{Alpha}\p{Nd}\p{No}\p{Nl}]*/u,
    string: $ => /"[^"]*"/,
    uuid: $ => /#\d{8}-?\d{4}-?\d{4}-?\d{4}-?\d{12}/,
  }
});
