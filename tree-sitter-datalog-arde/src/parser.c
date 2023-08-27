#include <tree_sitter/parser.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 34
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 33
#define ALIAS_COUNT 0
#define TOKEN_COUNT 19
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 1
#define MAX_ALIAS_SEQUENCE_LENGTH 5
#define PRODUCTION_ID_COUNT 2

enum {
  sym__whitespace = 1,
  sym_comment = 2,
  anon_sym_COLON_DASH = 3,
  anon_sym_COMMA = 4,
  anon_sym_DOT = 5,
  anon_sym_QMARK = 6,
  anon_sym_not = 7,
  anon_sym_LPAREN = 8,
  anon_sym_RPAREN = 9,
  aux_sym_predicate_token1 = 10,
  aux_sym_predicate_token2 = 11,
  sym_identifier = 12,
  sym_variable = 13,
  anon_sym_true = 14,
  anon_sym_false = 15,
  sym_integer = 16,
  sym_string = 17,
  sym_uuid = 18,
  sym_source_file = 19,
  sym__constraint = 20,
  sym_rule_definition = 21,
  sym_fact_definition = 22,
  sym_goal_definition = 23,
  sym_body_atom = 24,
  sym_atom = 25,
  sym_predicate = 26,
  sym_term = 27,
  sym_boolean = 28,
  sym_atomic_string = 29,
  aux_sym_source_file_repeat1 = 30,
  aux_sym_rule_definition_repeat1 = 31,
  aux_sym_atom_repeat1 = 32,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [sym__whitespace] = "_whitespace",
  [sym_comment] = "comment",
  [anon_sym_COLON_DASH] = ":-",
  [anon_sym_COMMA] = ",",
  [anon_sym_DOT] = ".",
  [anon_sym_QMARK] = "\?",
  [anon_sym_not] = "not",
  [anon_sym_LPAREN] = "(",
  [anon_sym_RPAREN] = ")",
  [aux_sym_predicate_token1] = "predicate_token1",
  [aux_sym_predicate_token2] = "predicate_token2",
  [sym_identifier] = "atomic_string",
  [sym_variable] = "variable",
  [anon_sym_true] = "true",
  [anon_sym_false] = "false",
  [sym_integer] = "integer",
  [sym_string] = "string",
  [sym_uuid] = "uuid",
  [sym_source_file] = "source_file",
  [sym__constraint] = "_constraint",
  [sym_rule_definition] = "rule_definition",
  [sym_fact_definition] = "fact_definition",
  [sym_goal_definition] = "goal_definition",
  [sym_body_atom] = "body_atom",
  [sym_atom] = "atom",
  [sym_predicate] = "predicate",
  [sym_term] = "term",
  [sym_boolean] = "boolean",
  [sym_atomic_string] = "atomic_string",
  [aux_sym_source_file_repeat1] = "source_file_repeat1",
  [aux_sym_rule_definition_repeat1] = "rule_definition_repeat1",
  [aux_sym_atom_repeat1] = "atom_repeat1",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [sym__whitespace] = sym__whitespace,
  [sym_comment] = sym_comment,
  [anon_sym_COLON_DASH] = anon_sym_COLON_DASH,
  [anon_sym_COMMA] = anon_sym_COMMA,
  [anon_sym_DOT] = anon_sym_DOT,
  [anon_sym_QMARK] = anon_sym_QMARK,
  [anon_sym_not] = anon_sym_not,
  [anon_sym_LPAREN] = anon_sym_LPAREN,
  [anon_sym_RPAREN] = anon_sym_RPAREN,
  [aux_sym_predicate_token1] = aux_sym_predicate_token1,
  [aux_sym_predicate_token2] = aux_sym_predicate_token2,
  [sym_identifier] = sym_identifier,
  [sym_variable] = sym_variable,
  [anon_sym_true] = anon_sym_true,
  [anon_sym_false] = anon_sym_false,
  [sym_integer] = sym_integer,
  [sym_string] = sym_string,
  [sym_uuid] = sym_uuid,
  [sym_source_file] = sym_source_file,
  [sym__constraint] = sym__constraint,
  [sym_rule_definition] = sym_rule_definition,
  [sym_fact_definition] = sym_fact_definition,
  [sym_goal_definition] = sym_goal_definition,
  [sym_body_atom] = sym_body_atom,
  [sym_atom] = sym_atom,
  [sym_predicate] = sym_predicate,
  [sym_term] = sym_term,
  [sym_boolean] = sym_boolean,
  [sym_atomic_string] = sym_atomic_string,
  [aux_sym_source_file_repeat1] = aux_sym_source_file_repeat1,
  [aux_sym_rule_definition_repeat1] = aux_sym_rule_definition_repeat1,
  [aux_sym_atom_repeat1] = aux_sym_atom_repeat1,
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [sym__whitespace] = {
    .visible = false,
    .named = true,
  },
  [sym_comment] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_COLON_DASH] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_COMMA] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DOT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_QMARK] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_not] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LPAREN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RPAREN] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_predicate_token1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_predicate_token2] = {
    .visible = false,
    .named = false,
  },
  [sym_identifier] = {
    .visible = true,
    .named = false,
  },
  [sym_variable] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_true] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_false] = {
    .visible = true,
    .named = false,
  },
  [sym_integer] = {
    .visible = true,
    .named = true,
  },
  [sym_string] = {
    .visible = true,
    .named = true,
  },
  [sym_uuid] = {
    .visible = true,
    .named = true,
  },
  [sym_source_file] = {
    .visible = true,
    .named = true,
  },
  [sym__constraint] = {
    .visible = false,
    .named = true,
  },
  [sym_rule_definition] = {
    .visible = true,
    .named = true,
  },
  [sym_fact_definition] = {
    .visible = true,
    .named = true,
  },
  [sym_goal_definition] = {
    .visible = true,
    .named = true,
  },
  [sym_body_atom] = {
    .visible = true,
    .named = true,
  },
  [sym_atom] = {
    .visible = true,
    .named = true,
  },
  [sym_predicate] = {
    .visible = true,
    .named = true,
  },
  [sym_term] = {
    .visible = true,
    .named = true,
  },
  [sym_boolean] = {
    .visible = true,
    .named = true,
  },
  [sym_atomic_string] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_source_file_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_rule_definition_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_atom_repeat1] = {
    .visible = false,
    .named = false,
  },
};

enum {
  field_head = 1,
};

static const char * const ts_field_names[] = {
  [0] = NULL,
  [field_head] = "head",
};

static const TSFieldMapSlice ts_field_map_slices[PRODUCTION_ID_COUNT] = {
  [1] = {.index = 0, .length = 1},
};

static const TSFieldMapEntry ts_field_map_entries[] = {
  [0] =
    {field_head, 0},
};

static const TSSymbol ts_alias_sequences[PRODUCTION_ID_COUNT][MAX_ALIAS_SEQUENCE_LENGTH] = {
  [0] = {0},
};

static const uint16_t ts_non_terminal_alias_map[] = {
  0,
};

static const TSStateId ts_primary_state_ids[STATE_COUNT] = {
  [0] = 0,
  [1] = 1,
  [2] = 2,
  [3] = 3,
  [4] = 4,
  [5] = 5,
  [6] = 6,
  [7] = 7,
  [8] = 8,
  [9] = 9,
  [10] = 10,
  [11] = 11,
  [12] = 12,
  [13] = 13,
  [14] = 14,
  [15] = 15,
  [16] = 16,
  [17] = 17,
  [18] = 18,
  [19] = 19,
  [20] = 20,
  [21] = 21,
  [22] = 22,
  [23] = 23,
  [24] = 24,
  [25] = 25,
  [26] = 26,
  [27] = 27,
  [28] = 28,
  [29] = 29,
  [30] = 30,
  [31] = 31,
  [32] = 32,
  [33] = 33,
};

static inline bool aux_sym_predicate_token2_character_set_1(int32_t c) {
  return (c < 7774
    ? (c < 996
      ? (c < 437
        ? (c < 332
          ? (c < 290
            ? (c < 270
              ? (c < 260
                ? (c < 216
                  ? (c < 192
                    ? (c >= 'A' && c <= 'Z')
                    : c <= 214)
                  : (c <= 222 || (c < 258
                    ? c == 256
                    : c <= 258)))
                : (c <= 260 || (c < 266
                  ? (c < 264
                    ? c == 262
                    : c <= 264)
                  : (c <= 266 || c == 268))))
              : (c <= 270 || (c < 280
                ? (c < 276
                  ? (c < 274
                    ? c == 272
                    : c <= 274)
                  : (c <= 276 || c == 278))
                : (c <= 280 || (c < 286
                  ? (c < 284
                    ? c == 282
                    : c <= 284)
                  : (c <= 286 || c == 288))))))
            : (c <= 290 || (c < 310
              ? (c < 300
                ? (c < 296
                  ? (c < 294
                    ? c == 292
                    : c <= 294)
                  : (c <= 296 || c == 298))
                : (c <= 300 || (c < 306
                  ? (c < 304
                    ? c == 302
                    : c <= 304)
                  : (c <= 306 || c == 308))))
              : (c <= 310 || (c < 321
                ? (c < 317
                  ? (c < 315
                    ? c == 313
                    : c <= 315)
                  : (c <= 317 || c == 319))
                : (c <= 321 || (c < 327
                  ? (c < 325
                    ? c == 323
                    : c <= 325)
                  : (c <= 327 || c == 330))))))))
          : (c <= 332 || (c < 374
            ? (c < 354
              ? (c < 344
                ? (c < 338
                  ? (c < 336
                    ? c == 334
                    : c <= 336)
                  : (c <= 338 || (c < 342
                    ? c == 340
                    : c <= 342)))
                : (c <= 344 || (c < 350
                  ? (c < 348
                    ? c == 346
                    : c <= 348)
                  : (c <= 350 || c == 352))))
              : (c <= 354 || (c < 364
                ? (c < 360
                  ? (c < 358
                    ? c == 356
                    : c <= 358)
                  : (c <= 360 || c == 362))
                : (c <= 364 || (c < 370
                  ? (c < 368
                    ? c == 366
                    : c <= 368)
                  : (c <= 370 || c == 372))))))
            : (c <= 374 || (c < 406
              ? (c < 388
                ? (c < 381
                  ? (c < 379
                    ? (c >= 376 && c <= 377)
                    : c <= 379)
                  : (c <= 381 || (c >= 385 && c <= 386)))
                : (c <= 388 || (c < 398
                  ? (c < 393
                    ? (c >= 390 && c <= 391)
                    : c <= 395)
                  : (c <= 401 || (c >= 403 && c <= 404)))))
              : (c <= 408 || (c < 422
                ? (c < 418
                  ? (c < 415
                    ? (c >= 412 && c <= 413)
                    : c <= 416)
                  : (c <= 418 || c == 420))
                : (c <= 423 || (c < 430
                  ? (c < 428
                    ? c == 425
                    : c <= 428)
                  : (c <= 431 || (c >= 433 && c <= 435)))))))))))
        : (c <= 437 || (c < 536
          ? (c < 492
            ? (c < 471
              ? (c < 461
                ? (c < 452
                  ? (c < 444
                    ? (c >= 439 && c <= 440)
                    : c <= 444)
                  : (c <= 452 || (c < 458
                    ? c == 455
                    : c <= 458)))
                : (c <= 461 || (c < 467
                  ? (c < 465
                    ? c == 463
                    : c <= 465)
                  : (c <= 467 || c == 469))))
              : (c <= 471 || (c < 482
                ? (c < 478
                  ? (c < 475
                    ? c == 473
                    : c <= 475)
                  : (c <= 478 || c == 480))
                : (c <= 482 || (c < 488
                  ? (c < 486
                    ? c == 484
                    : c <= 486)
                  : (c <= 488 || c == 490))))))
            : (c <= 492 || (c < 516
              ? (c < 506
                ? (c < 500
                  ? (c < 497
                    ? c == 494
                    : c <= 497)
                  : (c <= 500 || (c >= 502 && c <= 504)))
                : (c <= 506 || (c < 512
                  ? (c < 510
                    ? c == 508
                    : c <= 510)
                  : (c <= 512 || c == 514))))
              : (c <= 516 || (c < 526
                ? (c < 522
                  ? (c < 520
                    ? c == 518
                    : c <= 520)
                  : (c <= 522 || c == 524))
                : (c <= 526 || (c < 532
                  ? (c < 530
                    ? c == 528
                    : c <= 530)
                  : (c <= 532 || c == 534))))))))
          : (c <= 536 || (c < 588
            ? (c < 556
              ? (c < 546
                ? (c < 542
                  ? (c < 540
                    ? c == 538
                    : c <= 540)
                  : (c <= 542 || c == 544))
                : (c <= 546 || (c < 552
                  ? (c < 550
                    ? c == 548
                    : c <= 550)
                  : (c <= 552 || c == 554))))
              : (c <= 556 || (c < 573
                ? (c < 562
                  ? (c < 560
                    ? c == 558
                    : c <= 560)
                  : (c <= 562 || (c >= 570 && c <= 571)))
                : (c <= 574 || (c < 584
                  ? (c < 579
                    ? c == 577
                    : c <= 582)
                  : (c <= 584 || c == 586))))))
            : (c <= 588 || (c < 913
              ? (c < 895
                ? (c < 882
                  ? (c < 880
                    ? c == 590
                    : c <= 880)
                  : (c <= 882 || c == 886))
                : (c <= 895 || (c < 908
                  ? (c < 904
                    ? c == 902
                    : c <= 906)
                  : (c <= 908 || (c >= 910 && c <= 911)))))
              : (c <= 929 || (c < 986
                ? (c < 978
                  ? (c < 975
                    ? (c >= 931 && c <= 939)
                    : c <= 975)
                  : (c <= 980 || c == 984))
                : (c <= 986 || (c < 992
                  ? (c < 990
                    ? c == 988
                    : c <= 990)
                  : (c <= 992 || c == 994))))))))))))
      : (c <= 996 || (c < 1274
        ? (c < 1190
          ? (c < 1142
            ? (c < 1122
              ? (c < 1012
                ? (c < 1002
                  ? (c < 1000
                    ? c == 998
                    : c <= 1000)
                  : (c <= 1002 || (c < 1006
                    ? c == 1004
                    : c <= 1006)))
                : (c <= 1012 || (c < 1021
                  ? (c < 1017
                    ? c == 1015
                    : c <= 1018)
                  : (c <= 1071 || c == 1120))))
              : (c <= 1122 || (c < 1132
                ? (c < 1128
                  ? (c < 1126
                    ? c == 1124
                    : c <= 1126)
                  : (c <= 1128 || c == 1130))
                : (c <= 1132 || (c < 1138
                  ? (c < 1136
                    ? c == 1134
                    : c <= 1136)
                  : (c <= 1138 || c == 1140))))))
            : (c <= 1142 || (c < 1170
              ? (c < 1152
                ? (c < 1148
                  ? (c < 1146
                    ? c == 1144
                    : c <= 1146)
                  : (c <= 1148 || c == 1150))
                : (c <= 1152 || (c < 1166
                  ? (c < 1164
                    ? c == 1162
                    : c <= 1164)
                  : (c <= 1166 || c == 1168))))
              : (c <= 1170 || (c < 1180
                ? (c < 1176
                  ? (c < 1174
                    ? c == 1172
                    : c <= 1174)
                  : (c <= 1176 || c == 1178))
                : (c <= 1180 || (c < 1186
                  ? (c < 1184
                    ? c == 1182
                    : c <= 1184)
                  : (c <= 1186 || c == 1188))))))))
          : (c <= 1190 || (c < 1234
            ? (c < 1212
              ? (c < 1202
                ? (c < 1196
                  ? (c < 1194
                    ? c == 1192
                    : c <= 1194)
                  : (c <= 1196 || (c < 1200
                    ? c == 1198
                    : c <= 1200)))
                : (c <= 1202 || (c < 1208
                  ? (c < 1206
                    ? c == 1204
                    : c <= 1206)
                  : (c <= 1208 || c == 1210))))
              : (c <= 1212 || (c < 1223
                ? (c < 1219
                  ? (c < 1216
                    ? c == 1214
                    : c <= 1217)
                  : (c <= 1219 || c == 1221))
                : (c <= 1223 || (c < 1229
                  ? (c < 1227
                    ? c == 1225
                    : c <= 1227)
                  : (c <= 1229 || c == 1232))))))
            : (c <= 1234 || (c < 1254
              ? (c < 1244
                ? (c < 1240
                  ? (c < 1238
                    ? c == 1236
                    : c <= 1238)
                  : (c <= 1240 || c == 1242))
                : (c <= 1244 || (c < 1250
                  ? (c < 1248
                    ? c == 1246
                    : c <= 1248)
                  : (c <= 1250 || c == 1252))))
              : (c <= 1254 || (c < 1264
                ? (c < 1260
                  ? (c < 1258
                    ? c == 1256
                    : c <= 1258)
                  : (c <= 1260 || c == 1262))
                : (c <= 1264 || (c < 1270
                  ? (c < 1268
                    ? c == 1266
                    : c <= 1268)
                  : (c <= 1270 || c == 1272))))))))))
        : (c <= 1274 || (c < 7694
          ? (c < 1316
            ? (c < 1296
              ? (c < 1286
                ? (c < 1280
                  ? (c < 1278
                    ? c == 1276
                    : c <= 1278)
                  : (c <= 1280 || (c < 1284
                    ? c == 1282
                    : c <= 1284)))
                : (c <= 1286 || (c < 1292
                  ? (c < 1290
                    ? c == 1288
                    : c <= 1290)
                  : (c <= 1292 || c == 1294))))
              : (c <= 1296 || (c < 1306
                ? (c < 1302
                  ? (c < 1300
                    ? c == 1298
                    : c <= 1300)
                  : (c <= 1302 || c == 1304))
                : (c <= 1306 || (c < 1312
                  ? (c < 1310
                    ? c == 1308
                    : c <= 1310)
                  : (c <= 1312 || c == 1314))))))
            : (c <= 1316 || (c < 5024
              ? (c < 1326
                ? (c < 1322
                  ? (c < 1320
                    ? c == 1318
                    : c <= 1320)
                  : (c <= 1322 || c == 1324))
                : (c <= 1326 || (c < 4295
                  ? (c < 4256
                    ? (c >= 1329 && c <= 1366)
                    : c <= 4293)
                  : (c <= 4295 || c == 4301))))
              : (c <= 5109 || (c < 7684
                ? (c < 7680
                  ? (c < 7357
                    ? (c >= 7312 && c <= 7354)
                    : c <= 7359)
                  : (c <= 7680 || c == 7682))
                : (c <= 7684 || (c < 7690
                  ? (c < 7688
                    ? c == 7686
                    : c <= 7688)
                  : (c <= 7690 || c == 7692))))))))
          : (c <= 7694 || (c < 7734
            ? (c < 7714
              ? (c < 7704
                ? (c < 7700
                  ? (c < 7698
                    ? c == 7696
                    : c <= 7698)
                  : (c <= 7700 || c == 7702))
                : (c <= 7704 || (c < 7710
                  ? (c < 7708
                    ? c == 7706
                    : c <= 7708)
                  : (c <= 7710 || c == 7712))))
              : (c <= 7714 || (c < 7724
                ? (c < 7720
                  ? (c < 7718
                    ? c == 7716
                    : c <= 7718)
                  : (c <= 7720 || c == 7722))
                : (c <= 7724 || (c < 7730
                  ? (c < 7728
                    ? c == 7726
                    : c <= 7728)
                  : (c <= 7730 || c == 7732))))))
            : (c <= 7734 || (c < 7754
              ? (c < 7744
                ? (c < 7740
                  ? (c < 7738
                    ? c == 7736
                    : c <= 7738)
                  : (c <= 7740 || c == 7742))
                : (c <= 7744 || (c < 7750
                  ? (c < 7748
                    ? c == 7746
                    : c <= 7748)
                  : (c <= 7750 || c == 7752))))
              : (c <= 7754 || (c < 7764
                ? (c < 7760
                  ? (c < 7758
                    ? c == 7756
                    : c <= 7758)
                  : (c <= 7760 || c == 7762))
                : (c <= 7764 || (c < 7770
                  ? (c < 7768
                    ? c == 7766
                    : c <= 7768)
                  : (c <= 7770 || c == 7772))))))))))))))
    : (c <= 7774 || (c < 11484
      ? (c < 8025
        ? (c < 7864
          ? (c < 7816
            ? (c < 7796
              ? (c < 7786
                ? (c < 7780
                  ? (c < 7778
                    ? c == 7776
                    : c <= 7778)
                  : (c <= 7780 || (c < 7784
                    ? c == 7782
                    : c <= 7784)))
                : (c <= 7786 || (c < 7792
                  ? (c < 7790
                    ? c == 7788
                    : c <= 7790)
                  : (c <= 7792 || c == 7794))))
              : (c <= 7796 || (c < 7806
                ? (c < 7802
                  ? (c < 7800
                    ? c == 7798
                    : c <= 7800)
                  : (c <= 7802 || c == 7804))
                : (c <= 7806 || (c < 7812
                  ? (c < 7810
                    ? c == 7808
                    : c <= 7810)
                  : (c <= 7812 || c == 7814))))))
            : (c <= 7816 || (c < 7844
              ? (c < 7826
                ? (c < 7822
                  ? (c < 7820
                    ? c == 7818
                    : c <= 7820)
                  : (c <= 7822 || c == 7824))
                : (c <= 7826 || (c < 7840
                  ? (c < 7838
                    ? c == 7828
                    : c <= 7838)
                  : (c <= 7840 || c == 7842))))
              : (c <= 7844 || (c < 7854
                ? (c < 7850
                  ? (c < 7848
                    ? c == 7846
                    : c <= 7848)
                  : (c <= 7850 || c == 7852))
                : (c <= 7854 || (c < 7860
                  ? (c < 7858
                    ? c == 7856
                    : c <= 7858)
                  : (c <= 7860 || c == 7862))))))))
          : (c <= 7864 || (c < 7906
            ? (c < 7886
              ? (c < 7876
                ? (c < 7870
                  ? (c < 7868
                    ? c == 7866
                    : c <= 7868)
                  : (c <= 7870 || (c < 7874
                    ? c == 7872
                    : c <= 7874)))
                : (c <= 7876 || (c < 7882
                  ? (c < 7880
                    ? c == 7878
                    : c <= 7880)
                  : (c <= 7882 || c == 7884))))
              : (c <= 7886 || (c < 7896
                ? (c < 7892
                  ? (c < 7890
                    ? c == 7888
                    : c <= 7890)
                  : (c <= 7892 || c == 7894))
                : (c <= 7896 || (c < 7902
                  ? (c < 7900
                    ? c == 7898
                    : c <= 7900)
                  : (c <= 7902 || c == 7904))))))
            : (c <= 7906 || (c < 7926
              ? (c < 7916
                ? (c < 7912
                  ? (c < 7910
                    ? c == 7908
                    : c <= 7910)
                  : (c <= 7912 || c == 7914))
                : (c <= 7916 || (c < 7922
                  ? (c < 7920
                    ? c == 7918
                    : c <= 7920)
                  : (c <= 7922 || c == 7924))))
              : (c <= 7926 || (c < 7944
                ? (c < 7932
                  ? (c < 7930
                    ? c == 7928
                    : c <= 7930)
                  : (c <= 7932 || c == 7934))
                : (c <= 7951 || (c < 7992
                  ? (c < 7976
                    ? (c >= 7960 && c <= 7965)
                    : c <= 7983)
                  : (c <= 7999 || (c >= 8008 && c <= 8013)))))))))))
        : (c <= 8025 || (c < 11404
          ? (c < 8510
            ? (c < 8455
              ? (c < 8136
                ? (c < 8031
                  ? (c < 8029
                    ? c == 8027
                    : c <= 8029)
                  : (c <= 8031 || (c < 8120
                    ? (c >= 8040 && c <= 8047)
                    : c <= 8123)))
                : (c <= 8139 || (c < 8184
                  ? (c < 8168
                    ? (c >= 8152 && c <= 8155)
                    : c <= 8172)
                  : (c <= 8187 || c == 8450))))
              : (c <= 8455 || (c < 8484
                ? (c < 8469
                  ? (c < 8464
                    ? (c >= 8459 && c <= 8461)
                    : c <= 8466)
                  : (c <= 8469 || (c >= 8473 && c <= 8477)))
                : (c <= 8484 || (c < 8490
                  ? (c < 8488
                    ? c == 8486
                    : c <= 8488)
                  : (c <= 8493 || (c >= 8496 && c <= 8499)))))))
            : (c <= 8511 || (c < 11371
              ? (c < 11264
                ? (c < 8579
                  ? (c < 8544
                    ? c == 8517
                    : c <= 8559)
                  : (c <= 8579 || (c >= 9398 && c <= 9423)))
                : (c <= 11311 || (c < 11367
                  ? (c < 11362
                    ? c == 11360
                    : c <= 11364)
                  : (c <= 11367 || c == 11369))))
              : (c <= 11371 || (c < 11394
                ? (c < 11381
                  ? (c < 11378
                    ? (c >= 11373 && c <= 11376)
                    : c <= 11378)
                  : (c <= 11381 || (c >= 11390 && c <= 11392)))
                : (c <= 11394 || (c < 11400
                  ? (c < 11398
                    ? c == 11396
                    : c <= 11398)
                  : (c <= 11400 || c == 11402))))))))
          : (c <= 11404 || (c < 11444
            ? (c < 11424
              ? (c < 11414
                ? (c < 11410
                  ? (c < 11408
                    ? c == 11406
                    : c <= 11408)
                  : (c <= 11410 || c == 11412))
                : (c <= 11414 || (c < 11420
                  ? (c < 11418
                    ? c == 11416
                    : c <= 11418)
                  : (c <= 11420 || c == 11422))))
              : (c <= 11424 || (c < 11434
                ? (c < 11430
                  ? (c < 11428
                    ? c == 11426
                    : c <= 11428)
                  : (c <= 11430 || c == 11432))
                : (c <= 11434 || (c < 11440
                  ? (c < 11438
                    ? c == 11436
                    : c <= 11438)
                  : (c <= 11440 || c == 11442))))))
            : (c <= 11444 || (c < 11464
              ? (c < 11454
                ? (c < 11450
                  ? (c < 11448
                    ? c == 11446
                    : c <= 11448)
                  : (c <= 11450 || c == 11452))
                : (c <= 11454 || (c < 11460
                  ? (c < 11458
                    ? c == 11456
                    : c <= 11458)
                  : (c <= 11460 || c == 11462))))
              : (c <= 11464 || (c < 11474
                ? (c < 11470
                  ? (c < 11468
                    ? c == 11466
                    : c <= 11468)
                  : (c <= 11470 || c == 11472))
                : (c <= 11474 || (c < 11480
                  ? (c < 11478
                    ? c == 11476
                    : c <= 11478)
                  : (c <= 11480 || c == 11482))))))))))))
      : (c <= 11484 || (c < 42873
        ? (c < 42646
          ? (c < 42588
            ? (c < 42568
              ? (c < 11506
                ? (c < 11490
                  ? (c < 11488
                    ? c == 11486
                    : c <= 11488)
                  : (c <= 11490 || (c < 11501
                    ? c == 11499
                    : c <= 11501)))
                : (c <= 11506 || (c < 42564
                  ? (c < 42562
                    ? c == 42560
                    : c <= 42562)
                  : (c <= 42564 || c == 42566))))
              : (c <= 42568 || (c < 42578
                ? (c < 42574
                  ? (c < 42572
                    ? c == 42570
                    : c <= 42572)
                  : (c <= 42574 || c == 42576))
                : (c <= 42578 || (c < 42584
                  ? (c < 42582
                    ? c == 42580
                    : c <= 42582)
                  : (c <= 42584 || c == 42586))))))
            : (c <= 42588 || (c < 42626
              ? (c < 42598
                ? (c < 42594
                  ? (c < 42592
                    ? c == 42590
                    : c <= 42592)
                  : (c <= 42594 || c == 42596))
                : (c <= 42598 || (c < 42604
                  ? (c < 42602
                    ? c == 42600
                    : c <= 42602)
                  : (c <= 42604 || c == 42624))))
              : (c <= 42626 || (c < 42636
                ? (c < 42632
                  ? (c < 42630
                    ? c == 42628
                    : c <= 42630)
                  : (c <= 42632 || c == 42634))
                : (c <= 42636 || (c < 42642
                  ? (c < 42640
                    ? c == 42638
                    : c <= 42640)
                  : (c <= 42642 || c == 42644))))))))
          : (c <= 42646 || (c < 42824
            ? (c < 42804
              ? (c < 42792
                ? (c < 42786
                  ? (c < 42650
                    ? c == 42648
                    : c <= 42650)
                  : (c <= 42786 || (c < 42790
                    ? c == 42788
                    : c <= 42790)))
                : (c <= 42792 || (c < 42798
                  ? (c < 42796
                    ? c == 42794
                    : c <= 42796)
                  : (c <= 42798 || c == 42802))))
              : (c <= 42804 || (c < 42814
                ? (c < 42810
                  ? (c < 42808
                    ? c == 42806
                    : c <= 42808)
                  : (c <= 42810 || c == 42812))
                : (c <= 42814 || (c < 42820
                  ? (c < 42818
                    ? c == 42816
                    : c <= 42818)
                  : (c <= 42820 || c == 42822))))))
            : (c <= 42824 || (c < 42844
              ? (c < 42834
                ? (c < 42830
                  ? (c < 42828
                    ? c == 42826
                    : c <= 42828)
                  : (c <= 42830 || c == 42832))
                : (c <= 42834 || (c < 42840
                  ? (c < 42838
                    ? c == 42836
                    : c <= 42838)
                  : (c <= 42840 || c == 42842))))
              : (c <= 42844 || (c < 42854
                ? (c < 42850
                  ? (c < 42848
                    ? c == 42846
                    : c <= 42848)
                  : (c <= 42850 || c == 42852))
                : (c <= 42854 || (c < 42860
                  ? (c < 42858
                    ? c == 42856
                    : c <= 42858)
                  : (c <= 42860 || c == 42862))))))))))
        : (c <= 42873 || (c < 66956
          ? (c < 42922
            ? (c < 42902
              ? (c < 42886
                ? (c < 42880
                  ? (c < 42877
                    ? c == 42875
                    : c <= 42878)
                  : (c <= 42880 || (c < 42884
                    ? c == 42882
                    : c <= 42884)))
                : (c <= 42886 || (c < 42896
                  ? (c < 42893
                    ? c == 42891
                    : c <= 42893)
                  : (c <= 42896 || c == 42898))))
              : (c <= 42902 || (c < 42912
                ? (c < 42908
                  ? (c < 42906
                    ? c == 42904
                    : c <= 42906)
                  : (c <= 42908 || c == 42910))
                : (c <= 42912 || (c < 42918
                  ? (c < 42916
                    ? c == 42914
                    : c <= 42916)
                  : (c <= 42918 || c == 42920))))))
            : (c <= 42926 || (c < 42953
              ? (c < 42940
                ? (c < 42936
                  ? (c < 42934
                    ? (c >= 42928 && c <= 42932)
                    : c <= 42934)
                  : (c <= 42936 || c == 42938))
                : (c <= 42940 || (c < 42946
                  ? (c < 42944
                    ? c == 42942
                    : c <= 42944)
                  : (c <= 42946 || (c >= 42948 && c <= 42951)))))
              : (c <= 42953 || (c < 65313
                ? (c < 42968
                  ? (c < 42966
                    ? c == 42960
                    : c <= 42966)
                  : (c <= 42968 || c == 42997))
                : (c <= 65338 || (c < 66928
                  ? (c < 66736
                    ? (c >= 66560 && c <= 66599)
                    : c <= 66771)
                  : (c <= 66938 || (c >= 66940 && c <= 66954)))))))))
          : (c <= 66962 || (c < 120123
            ? (c < 119970
              ? (c < 119808
                ? (c < 71840
                  ? (c < 68736
                    ? (c >= 66964 && c <= 66965)
                    : c <= 68786)
                  : (c <= 71871 || (c >= 93760 && c <= 93791)))
                : (c <= 119833 || (c < 119964
                  ? (c < 119912
                    ? (c >= 119860 && c <= 119885)
                    : c <= 119937)
                  : (c <= 119964 || (c >= 119966 && c <= 119967)))))
              : (c <= 119970 || (c < 120068
                ? (c < 119982
                  ? (c < 119977
                    ? (c >= 119973 && c <= 119974)
                    : c <= 119980)
                  : (c <= 119989 || (c >= 120016 && c <= 120041)))
                : (c <= 120069 || (c < 120086
                  ? (c < 120077
                    ? (c >= 120071 && c <= 120074)
                    : c <= 120084)
                  : (c <= 120092 || (c >= 120120 && c <= 120121)))))))
            : (c <= 120126 || (c < 120488
              ? (c < 120224
                ? (c < 120138
                  ? (c < 120134
                    ? (c >= 120128 && c <= 120132)
                    : c <= 120134)
                  : (c <= 120144 || (c >= 120172 && c <= 120197)))
                : (c <= 120249 || (c < 120380
                  ? (c < 120328
                    ? (c >= 120276 && c <= 120301)
                    : c <= 120353)
                  : (c <= 120405 || (c >= 120432 && c <= 120457)))))
              : (c <= 120512 || (c < 120778
                ? (c < 120662
                  ? (c < 120604
                    ? (c >= 120546 && c <= 120570)
                    : c <= 120628)
                  : (c <= 120686 || (c >= 120720 && c <= 120744)))
                : (c <= 120778 || (c < 127312
                  ? (c < 127280
                    ? (c >= 125184 && c <= 125217)
                    : c <= 127305)
                  : (c <= 127337 || (c >= 127344 && c <= 127369)))))))))))))))));
}

static inline bool aux_sym_predicate_token2_character_set_2(int32_t c) {
  return (c < 42994
    ? (c < 3482
      ? (c < 2631
        ? (c < 1808
          ? (c < 940
            ? (c < 223
              ? (c < '|'
                ? (c < '*'
                  ? (c < '&'
                    ? c == '!'
                    : c <= '&')
                  : (c <= '/' || (c < 'a'
                    ? c == '_'
                    : c <= 'z')))
                : (c <= '|' || (c < 181
                  ? (c < 170
                    ? c == '~'
                    : c <= 170)
                  : (c <= 181 || c == 186))))
              : (c <= 246 || (c < 837
                ? (c < 736
                  ? (c < 710
                    ? (c >= 248 && c <= 705)
                    : c <= 721)
                  : (c <= 740 || (c < 750
                    ? c == 748
                    : c <= 750)))
                : (c <= 837 || (c < 890
                  ? (c < 887
                    ? (c >= 881 && c <= 884)
                    : c <= 887)
                  : (c <= 893 || c == 912))))))
            : (c <= 1013 || (c < 1519
              ? (c < 1471
                ? (c < 1369
                  ? (c < 1163
                    ? (c >= 1016 && c <= 1153)
                    : c <= 1327)
                  : (c <= 1369 || (c < 1456
                    ? (c >= 1376 && c <= 1416)
                    : c <= 1469)))
                : (c <= 1471 || (c < 1479
                  ? (c < 1476
                    ? (c >= 1473 && c <= 1474)
                    : c <= 1477)
                  : (c <= 1479 || (c >= 1488 && c <= 1514)))))
              : (c <= 1522 || (c < 1749
                ? (c < 1625
                  ? (c < 1568
                    ? (c >= 1552 && c <= 1562)
                    : c <= 1623)
                  : (c <= 1631 || (c >= 1646 && c <= 1747)))
                : (c <= 1756 || (c < 1786
                  ? (c < 1773
                    ? (c >= 1761 && c <= 1768)
                    : c <= 1775)
                  : (c <= 1788 || c == 1791))))))))
          : (c <= 1855 || (c < 2474
            ? (c < 2208
              ? (c < 2074
                ? (c < 2036
                  ? (c < 1994
                    ? (c >= 1869 && c <= 1969)
                    : c <= 2026)
                  : (c <= 2037 || (c < 2048
                    ? c == 2042
                    : c <= 2071)))
                : (c <= 2092 || (c < 2160
                  ? (c < 2144
                    ? (c >= 2112 && c <= 2136)
                    : c <= 2154)
                  : (c <= 2183 || (c >= 2185 && c <= 2190)))))
              : (c <= 2249 || (c < 2389
                ? (c < 2288
                  ? (c < 2275
                    ? (c >= 2260 && c <= 2271)
                    : c <= 2281)
                  : (c <= 2363 || (c < 2382
                    ? (c >= 2365 && c <= 2380)
                    : c <= 2384)))
                : (c <= 2403 || (c < 2447
                  ? (c < 2437
                    ? (c >= 2417 && c <= 2435)
                    : c <= 2444)
                  : (c <= 2448 || (c >= 2451 && c <= 2472)))))))
            : (c <= 2480 || (c < 2556
              ? (c < 2510
                ? (c < 2493
                  ? (c < 2486
                    ? c == 2482
                    : c <= 2489)
                  : (c <= 2500 || (c < 2507
                    ? (c >= 2503 && c <= 2504)
                    : c <= 2508)))
                : (c <= 2510 || (c < 2527
                  ? (c < 2524
                    ? c == 2519
                    : c <= 2525)
                  : (c <= 2531 || (c >= 2544 && c <= 2545)))))
              : (c <= 2556 || (c < 2602
                ? (c < 2575
                  ? (c < 2565
                    ? (c >= 2561 && c <= 2563)
                    : c <= 2570)
                  : (c <= 2576 || (c >= 2579 && c <= 2600)))
                : (c <= 2608 || (c < 2616
                  ? (c < 2613
                    ? (c >= 2610 && c <= 2611)
                    : c <= 2614)
                  : (c <= 2617 || (c >= 2622 && c <= 2626)))))))))))
        : (c <= 2632 || (c < 3006
          ? (c < 2835
            ? (c < 2738
              ? (c < 2689
                ? (c < 2649
                  ? (c < 2641
                    ? (c >= 2635 && c <= 2636)
                    : c <= 2641)
                  : (c <= 2652 || (c < 2672
                    ? c == 2654
                    : c <= 2677)))
                : (c <= 2691 || (c < 2707
                  ? (c < 2703
                    ? (c >= 2693 && c <= 2701)
                    : c <= 2705)
                  : (c <= 2728 || (c >= 2730 && c <= 2736)))))
              : (c <= 2739 || (c < 2784
                ? (c < 2759
                  ? (c < 2749
                    ? (c >= 2741 && c <= 2745)
                    : c <= 2757)
                  : (c <= 2761 || (c < 2768
                    ? (c >= 2763 && c <= 2764)
                    : c <= 2768)))
                : (c <= 2787 || (c < 2821
                  ? (c < 2817
                    ? (c >= 2809 && c <= 2812)
                    : c <= 2819)
                  : (c <= 2828 || (c >= 2831 && c <= 2832)))))))
            : (c <= 2856 || (c < 2946
              ? (c < 2891
                ? (c < 2869
                  ? (c < 2866
                    ? (c >= 2858 && c <= 2864)
                    : c <= 2867)
                  : (c <= 2873 || (c < 2887
                    ? (c >= 2877 && c <= 2884)
                    : c <= 2888)))
                : (c <= 2892 || (c < 2911
                  ? (c < 2908
                    ? (c >= 2902 && c <= 2903)
                    : c <= 2909)
                  : (c <= 2915 || c == 2929))))
              : (c <= 2947 || (c < 2972
                ? (c < 2962
                  ? (c < 2958
                    ? (c >= 2949 && c <= 2954)
                    : c <= 2960)
                  : (c <= 2965 || (c >= 2969 && c <= 2970)))
                : (c <= 2972 || (c < 2984
                  ? (c < 2979
                    ? (c >= 2974 && c <= 2975)
                    : c <= 2980)
                  : (c <= 2986 || (c >= 2990 && c <= 3001)))))))))
          : (c <= 3010 || (c < 3242
            ? (c < 3142
              ? (c < 3077
                ? (c < 3024
                  ? (c < 3018
                    ? (c >= 3014 && c <= 3016)
                    : c <= 3020)
                  : (c <= 3024 || (c < 3072
                    ? c == 3031
                    : c <= 3075)))
                : (c <= 3084 || (c < 3114
                  ? (c < 3090
                    ? (c >= 3086 && c <= 3088)
                    : c <= 3112)
                  : (c <= 3129 || (c >= 3133 && c <= 3140)))))
              : (c <= 3144 || (c < 3168
                ? (c < 3160
                  ? (c < 3157
                    ? (c >= 3146 && c <= 3148)
                    : c <= 3158)
                  : (c <= 3162 || c == 3165))
                : (c <= 3171 || (c < 3214
                  ? (c < 3205
                    ? (c >= 3200 && c <= 3203)
                    : c <= 3212)
                  : (c <= 3216 || (c >= 3218 && c <= 3240)))))))
            : (c <= 3251 || (c < 3346
              ? (c < 3293
                ? (c < 3270
                  ? (c < 3261
                    ? (c >= 3253 && c <= 3257)
                    : c <= 3268)
                  : (c <= 3272 || (c < 3285
                    ? (c >= 3274 && c <= 3276)
                    : c <= 3286)))
                : (c <= 3294 || (c < 3328
                  ? (c < 3313
                    ? (c >= 3296 && c <= 3299)
                    : c <= 3314)
                  : (c <= 3340 || (c >= 3342 && c <= 3344)))))
              : (c <= 3386 || (c < 3412
                ? (c < 3402
                  ? (c < 3398
                    ? (c >= 3389 && c <= 3396)
                    : c <= 3400)
                  : (c <= 3404 || c == 3406))
                : (c <= 3415 || (c < 3457
                  ? (c < 3450
                    ? (c >= 3423 && c <= 3427)
                    : c <= 3455)
                  : (c <= 3459 || (c >= 3461 && c <= 3478)))))))))))))
      : (c <= 3505 || (c < 6981
        ? (c < 4792
          ? (c < 3840
            ? (c < 3713
              ? (c < 3544
                ? (c < 3520
                  ? (c < 3517
                    ? (c >= 3507 && c <= 3515)
                    : c <= 3517)
                  : (c <= 3526 || (c < 3542
                    ? (c >= 3535 && c <= 3540)
                    : c <= 3542)))
                : (c <= 3551 || (c < 3648
                  ? (c < 3585
                    ? (c >= 3570 && c <= 3571)
                    : c <= 3642)
                  : (c <= 3654 || c == 3661))))
              : (c <= 3714 || (c < 3771
                ? (c < 3724
                  ? (c < 3718
                    ? c == 3716
                    : c <= 3722)
                  : (c <= 3747 || (c < 3751
                    ? c == 3749
                    : c <= 3769)))
                : (c <= 3773 || (c < 3789
                  ? (c < 3782
                    ? (c >= 3776 && c <= 3780)
                    : c <= 3782)
                  : (c <= 3789 || (c >= 3804 && c <= 3807)))))))
            : (c <= 3840 || (c < 4304
              ? (c < 4096
                ? (c < 3953
                  ? (c < 3913
                    ? (c >= 3904 && c <= 3911)
                    : c <= 3948)
                  : (c <= 3969 || (c < 3993
                    ? (c >= 3976 && c <= 3991)
                    : c <= 4028)))
                : (c <= 4150 || (c < 4176
                  ? (c < 4155
                    ? c == 4152
                    : c <= 4159)
                  : (c <= 4239 || (c >= 4250 && c <= 4253)))))
              : (c <= 4346 || (c < 4698
                ? (c < 4688
                  ? (c < 4682
                    ? (c >= 4348 && c <= 4680)
                    : c <= 4685)
                  : (c <= 4694 || c == 4696))
                : (c <= 4701 || (c < 4752
                  ? (c < 4746
                    ? (c >= 4704 && c <= 4744)
                    : c <= 4749)
                  : (c <= 4784 || (c >= 4786 && c <= 4789)))))))))
          : (c <= 4798 || (c < 6070
            ? (c < 5761
              ? (c < 4888
                ? (c < 4808
                  ? (c < 4802
                    ? c == 4800
                    : c <= 4805)
                  : (c <= 4822 || (c < 4882
                    ? (c >= 4824 && c <= 4880)
                    : c <= 4885)))
                : (c <= 4954 || (c < 5121
                  ? (c < 5112
                    ? (c >= 4992 && c <= 5007)
                    : c <= 5117)
                  : (c <= 5740 || (c >= 5743 && c <= 5759)))))
              : (c <= 5786 || (c < 5952
                ? (c < 5888
                  ? (c < 5870
                    ? (c >= 5792 && c <= 5866)
                    : c <= 5880)
                  : (c <= 5907 || (c >= 5919 && c <= 5939)))
                : (c <= 5971 || (c < 6002
                  ? (c < 5998
                    ? (c >= 5984 && c <= 5996)
                    : c <= 6000)
                  : (c <= 6003 || (c >= 6016 && c <= 6067)))))))
            : (c <= 6088 || (c < 6528
              ? (c < 6400
                ? (c < 6176
                  ? (c < 6108
                    ? c == 6103
                    : c <= 6108)
                  : (c <= 6264 || (c < 6320
                    ? (c >= 6272 && c <= 6314)
                    : c <= 6389)))
                : (c <= 6430 || (c < 6480
                  ? (c < 6448
                    ? (c >= 6432 && c <= 6443)
                    : c <= 6456)
                  : (c <= 6509 || (c >= 6512 && c <= 6516)))))
              : (c <= 6571 || (c < 6823
                ? (c < 6688
                  ? (c < 6656
                    ? (c >= 6576 && c <= 6601)
                    : c <= 6683)
                  : (c <= 6750 || (c >= 6753 && c <= 6772)))
                : (c <= 6823 || (c < 6912
                  ? (c < 6860
                    ? (c >= 6847 && c <= 6848)
                    : c <= 6862)
                  : (c <= 6963 || (c >= 6965 && c <= 6979)))))))))))
        : (c <= 6988 || (c < 11559
          ? (c < 8130
            ? (c < 7413
              ? (c < 7245
                ? (c < 7098
                  ? (c < 7084
                    ? (c >= 7040 && c <= 7081)
                    : c <= 7087)
                  : (c <= 7141 || (c < 7168
                    ? (c >= 7143 && c <= 7153)
                    : c <= 7222)))
                : (c <= 7247 || (c < 7401
                  ? (c < 7296
                    ? (c >= 7258 && c <= 7293)
                    : c <= 7304)
                  : (c <= 7404 || (c >= 7406 && c <= 7411)))))
              : (c <= 7414 || (c < 8016
                ? (c < 7655
                  ? (c < 7424
                    ? c == 7418
                    : c <= 7615)
                  : (c <= 7668 || (c < 7968
                    ? (c >= 7681 && c <= 7957)
                    : c <= 8005)))
                : (c <= 8023 || (c < 8118
                  ? (c < 8064
                    ? (c >= 8032 && c <= 8061)
                    : c <= 8116)
                  : (c <= 8124 || c == 8126))))))
            : (c <= 8132 || (c < 8495
              ? (c < 8182
                ? (c < 8150
                  ? (c < 8144
                    ? (c >= 8134 && c <= 8140)
                    : c <= 8147)
                  : (c <= 8151 || (c < 8178
                    ? (c >= 8160 && c <= 8167)
                    : c <= 8180)))
                : (c <= 8188 || (c < 8336
                  ? (c < 8319
                    ? c == 8305
                    : c <= 8319)
                  : (c <= 8348 || (c >= 8458 && c <= 8467)))))
              : (c <= 8505 || (c < 9424
                ? (c < 8526
                  ? (c < 8518
                    ? (c >= 8508 && c <= 8509)
                    : c <= 8521)
                  : (c <= 8526 || (c >= 8560 && c <= 8584)))
                : (c <= 9449 || (c < 11507
                  ? (c < 11500
                    ? (c >= 11312 && c <= 11492)
                    : c <= 11502)
                  : (c <= 11507 || (c >= 11520 && c <= 11557)))))))))
          : (c <= 11559 || (c < 12449
            ? (c < 11728
              ? (c < 11688
                ? (c < 11631
                  ? (c < 11568
                    ? c == 11565
                    : c <= 11623)
                  : (c <= 11631 || (c < 11680
                    ? (c >= 11648 && c <= 11670)
                    : c <= 11686)))
                : (c <= 11694 || (c < 11712
                  ? (c < 11704
                    ? (c >= 11696 && c <= 11702)
                    : c <= 11710)
                  : (c <= 11718 || (c >= 11720 && c <= 11726)))))
              : (c <= 11734 || (c < 12321
                ? (c < 11823
                  ? (c < 11744
                    ? (c >= 11736 && c <= 11742)
                    : c <= 11775)
                  : (c <= 11823 || (c >= 12293 && c <= 12295)))
                : (c <= 12329 || (c < 12353
                  ? (c < 12344
                    ? (c >= 12337 && c <= 12341)
                    : c <= 12348)
                  : (c <= 12438 || (c >= 12445 && c <= 12447)))))))
            : (c <= 12538 || (c < 42538
              ? (c < 13312
                ? (c < 12593
                  ? (c < 12549
                    ? (c >= 12540 && c <= 12543)
                    : c <= 12591)
                  : (c <= 12686 || (c < 12784
                    ? (c >= 12704 && c <= 12735)
                    : c <= 12799)))
                : (c <= 19903 || (c < 42240
                  ? (c < 42192
                    ? (c >= 19968 && c <= 42124)
                    : c <= 42237)
                  : (c <= 42508 || (c >= 42512 && c <= 42527)))))
              : (c <= 42539 || (c < 42787
                ? (c < 42623
                  ? (c < 42612
                    ? (c >= 42561 && c <= 42606)
                    : c <= 42619)
                  : (c <= 42735 || (c >= 42775 && c <= 42783)))
                : (c <= 42888 || (c < 42963
                  ? (c < 42961
                    ? (c >= 42892 && c <= 42954)
                    : c <= 42961)
                  : (c <= 42963 || (c >= 42965 && c <= 42969)))))))))))))))
    : (c <= 43013 || (c < 70784
      ? (c < 67392
        ? (c < 64318
          ? (c < 43739
            ? (c < 43392
              ? (c < 43259
                ? (c < 43136
                  ? (c < 43072
                    ? (c >= 43015 && c <= 43047)
                    : c <= 43123)
                  : (c <= 43203 || (c < 43250
                    ? c == 43205
                    : c <= 43255)))
                : (c <= 43259 || (c < 43312
                  ? (c < 43274
                    ? (c >= 43261 && c <= 43263)
                    : c <= 43306)
                  : (c <= 43346 || (c >= 43360 && c <= 43388)))))
              : (c <= 43442 || (c < 43584
                ? (c < 43488
                  ? (c < 43471
                    ? (c >= 43444 && c <= 43455)
                    : c <= 43471)
                  : (c <= 43503 || (c < 43520
                    ? (c >= 43514 && c <= 43518)
                    : c <= 43574)))
                : (c <= 43597 || (c < 43712
                  ? (c < 43642
                    ? (c >= 43616 && c <= 43638)
                    : c <= 43710)
                  : (c <= 43712 || c == 43714))))))
            : (c <= 43741 || (c < 44032
              ? (c < 43808
                ? (c < 43777
                  ? (c < 43762
                    ? (c >= 43744 && c <= 43759)
                    : c <= 43765)
                  : (c <= 43782 || (c < 43793
                    ? (c >= 43785 && c <= 43790)
                    : c <= 43798)))
                : (c <= 43814 || (c < 43868
                  ? (c < 43824
                    ? (c >= 43816 && c <= 43822)
                    : c <= 43866)
                  : (c <= 43881 || (c >= 43888 && c <= 44010)))))
              : (c <= 55203 || (c < 64256
                ? (c < 63744
                  ? (c < 55243
                    ? (c >= 55216 && c <= 55238)
                    : c <= 55291)
                  : (c <= 64109 || (c >= 64112 && c <= 64217)))
                : (c <= 64262 || (c < 64298
                  ? (c < 64285
                    ? (c >= 64275 && c <= 64279)
                    : c <= 64296)
                  : (c <= 64310 || (c >= 64312 && c <= 64316)))))))))
          : (c <= 64318 || (c < 65616
            ? (c < 65382
              ? (c < 64914
                ? (c < 64326
                  ? (c < 64323
                    ? (c >= 64320 && c <= 64321)
                    : c <= 64324)
                  : (c <= 64433 || (c < 64848
                    ? (c >= 64467 && c <= 64829)
                    : c <= 64911)))
                : (c <= 64967 || (c < 65142
                  ? (c < 65136
                    ? (c >= 65008 && c <= 65019)
                    : c <= 65140)
                  : (c <= 65276 || (c >= 65345 && c <= 65370)))))
              : (c <= 65470 || (c < 65536
                ? (c < 65490
                  ? (c < 65482
                    ? (c >= 65474 && c <= 65479)
                    : c <= 65487)
                  : (c <= 65495 || (c >= 65498 && c <= 65500)))
                : (c <= 65547 || (c < 65596
                  ? (c < 65576
                    ? (c >= 65549 && c <= 65574)
                    : c <= 65594)
                  : (c <= 65597 || (c >= 65599 && c <= 65613)))))))
            : (c <= 65629 || (c < 66513
              ? (c < 66349
                ? (c < 66176
                  ? (c < 65856
                    ? (c >= 65664 && c <= 65786)
                    : c <= 65908)
                  : (c <= 66204 || (c < 66304
                    ? (c >= 66208 && c <= 66256)
                    : c <= 66335)))
                : (c <= 66378 || (c < 66464
                  ? (c < 66432
                    ? (c >= 66384 && c <= 66426)
                    : c <= 66461)
                  : (c <= 66499 || (c >= 66504 && c <= 66511)))))
              : (c <= 66517 || (c < 66967
                ? (c < 66816
                  ? (c < 66776
                    ? (c >= 66600 && c <= 66717)
                    : c <= 66811)
                  : (c <= 66855 || (c >= 66864 && c <= 66915)))
                : (c <= 66977 || (c < 67003
                  ? (c < 66995
                    ? (c >= 66979 && c <= 66993)
                    : c <= 67001)
                  : (c <= 67004 || (c >= 67072 && c <= 67382)))))))))))
        : (c <= 67413 || (c < 69600
          ? (c < 68117
            ? (c < 67680
              ? (c < 67592
                ? (c < 67463
                  ? (c < 67456
                    ? (c >= 67424 && c <= 67431)
                    : c <= 67461)
                  : (c <= 67504 || (c < 67584
                    ? (c >= 67506 && c <= 67514)
                    : c <= 67589)))
                : (c <= 67592 || (c < 67644
                  ? (c < 67639
                    ? (c >= 67594 && c <= 67637)
                    : c <= 67640)
                  : (c <= 67644 || (c >= 67647 && c <= 67669)))))
              : (c <= 67702 || (c < 67968
                ? (c < 67828
                  ? (c < 67808
                    ? (c >= 67712 && c <= 67742)
                    : c <= 67826)
                  : (c <= 67829 || (c < 67872
                    ? (c >= 67840 && c <= 67861)
                    : c <= 67897)))
                : (c <= 68023 || (c < 68101
                  ? (c < 68096
                    ? (c >= 68030 && c <= 68031)
                    : c <= 68099)
                  : (c <= 68102 || (c >= 68108 && c <= 68115)))))))
            : (c <= 68119 || (c < 68800
              ? (c < 68352
                ? (c < 68224
                  ? (c < 68192
                    ? (c >= 68121 && c <= 68149)
                    : c <= 68220)
                  : (c <= 68252 || (c < 68297
                    ? (c >= 68288 && c <= 68295)
                    : c <= 68324)))
                : (c <= 68405 || (c < 68480
                  ? (c < 68448
                    ? (c >= 68416 && c <= 68437)
                    : c <= 68466)
                  : (c <= 68497 || (c >= 68608 && c <= 68680)))))
              : (c <= 68850 || (c < 69376
                ? (c < 69291
                  ? (c < 69248
                    ? (c >= 68864 && c <= 68903)
                    : c <= 69289)
                  : (c <= 69292 || (c >= 69296 && c <= 69297)))
                : (c <= 69404 || (c < 69488
                  ? (c < 69424
                    ? c == 69415
                    : c <= 69445)
                  : (c <= 69505 || (c >= 69552 && c <= 69572)))))))))
          : (c <= 69622 || (c < 70282
            ? (c < 70081
              ? (c < 69888
                ? (c < 69762
                  ? (c < 69745
                    ? (c >= 69632 && c <= 69701)
                    : c <= 69749)
                  : (c <= 69816 || (c < 69840
                    ? c == 69826
                    : c <= 69864)))
                : (c <= 69938 || (c < 70006
                  ? (c < 69968
                    ? (c >= 69956 && c <= 69959)
                    : c <= 70002)
                  : (c <= 70006 || (c >= 70016 && c <= 70079)))))
              : (c <= 70084 || (c < 70163
                ? (c < 70108
                  ? (c < 70106
                    ? (c >= 70094 && c <= 70095)
                    : c <= 70106)
                  : (c <= 70108 || (c >= 70144 && c <= 70161)))
                : (c <= 70196 || (c < 70272
                  ? (c < 70206
                    ? c == 70199
                    : c <= 70206)
                  : (c <= 70278 || c == 70280))))))
            : (c <= 70285 || (c < 70461
              ? (c < 70415
                ? (c < 70320
                  ? (c < 70303
                    ? (c >= 70287 && c <= 70301)
                    : c <= 70312)
                  : (c <= 70376 || (c < 70405
                    ? (c >= 70400 && c <= 70403)
                    : c <= 70412)))
                : (c <= 70416 || (c < 70450
                  ? (c < 70442
                    ? (c >= 70419 && c <= 70440)
                    : c <= 70448)
                  : (c <= 70451 || (c >= 70453 && c <= 70457)))))
              : (c <= 70468 || (c < 70493
                ? (c < 70480
                  ? (c < 70475
                    ? (c >= 70471 && c <= 70472)
                    : c <= 70476)
                  : (c <= 70480 || c == 70487))
                : (c <= 70499 || (c < 70727
                  ? (c < 70723
                    ? (c >= 70656 && c <= 70721)
                    : c <= 70725)
                  : (c <= 70730 || (c >= 70751 && c <= 70753)))))))))))))
      : (c <= 70849 || (c < 110928
        ? (c < 72971
          ? (c < 71995
            ? (c < 71424
              ? (c < 71168
                ? (c < 71040
                  ? (c < 70855
                    ? (c >= 70852 && c <= 70853)
                    : c <= 70855)
                  : (c <= 71093 || (c < 71128
                    ? (c >= 71096 && c <= 71102)
                    : c <= 71133)))
                : (c <= 71230 || (c < 71296
                  ? (c < 71236
                    ? c == 71232
                    : c <= 71236)
                  : (c <= 71349 || c == 71352))))
              : (c <= 71450 || (c < 71945
                ? (c < 71680
                  ? (c < 71488
                    ? (c >= 71453 && c <= 71466)
                    : c <= 71494)
                  : (c <= 71736 || (c < 71935
                    ? (c >= 71872 && c <= 71903)
                    : c <= 71942)))
                : (c <= 71945 || (c < 71960
                  ? (c < 71957
                    ? (c >= 71948 && c <= 71955)
                    : c <= 71958)
                  : (c <= 71989 || (c >= 71991 && c <= 71992)))))))
            : (c <= 71996 || (c < 72368
              ? (c < 72163
                ? (c < 72106
                  ? (c < 72096
                    ? (c >= 71999 && c <= 72002)
                    : c <= 72103)
                  : (c <= 72151 || (c < 72161
                    ? (c >= 72154 && c <= 72159)
                    : c <= 72161)))
                : (c <= 72164 || (c < 72272
                  ? (c < 72245
                    ? (c >= 72192 && c <= 72242)
                    : c <= 72254)
                  : (c <= 72343 || c == 72349))))
              : (c <= 72440 || (c < 72818
                ? (c < 72760
                  ? (c < 72714
                    ? (c >= 72704 && c <= 72712)
                    : c <= 72758)
                  : (c <= 72766 || c == 72768))
                : (c <= 72847 || (c < 72960
                  ? (c < 72873
                    ? (c >= 72850 && c <= 72871)
                    : c <= 72886)
                  : (c <= 72966 || (c >= 72968 && c <= 72969)))))))))
          : (c <= 73014 || (c < 92736
            ? (c < 73112
              ? (c < 73056
                ? (c < 73023
                  ? (c < 73020
                    ? c == 73018
                    : c <= 73021)
                  : (c <= 73025 || (c < 73030
                    ? c == 73027
                    : c <= 73031)))
                : (c <= 73061 || (c < 73104
                  ? (c < 73066
                    ? (c >= 73063 && c <= 73064)
                    : c <= 73102)
                  : (c <= 73105 || (c >= 73107 && c <= 73110)))))
              : (c <= 73112 || (c < 74880
                ? (c < 73728
                  ? (c < 73648
                    ? (c >= 73440 && c <= 73462)
                    : c <= 73648)
                  : (c <= 74649 || (c >= 74752 && c <= 74862)))
                : (c <= 75075 || (c < 82944
                  ? (c < 77824
                    ? (c >= 77712 && c <= 77808)
                    : c <= 78894)
                  : (c <= 83526 || (c >= 92160 && c <= 92728)))))))
            : (c <= 92766 || (c < 94176
              ? (c < 93053
                ? (c < 92928
                  ? (c < 92880
                    ? (c >= 92784 && c <= 92862)
                    : c <= 92909)
                  : (c <= 92975 || (c < 93027
                    ? (c >= 92992 && c <= 92995)
                    : c <= 93047)))
                : (c <= 93071 || (c < 94031
                  ? (c < 93952
                    ? (c >= 93792 && c <= 93823)
                    : c <= 94026)
                  : (c <= 94087 || (c >= 94095 && c <= 94111)))))
              : (c <= 94177 || (c < 101632
                ? (c < 94208
                  ? (c < 94192
                    ? c == 94179
                    : c <= 94193)
                  : (c <= 100343 || (c >= 100352 && c <= 101589)))
                : (c <= 101640 || (c < 110589
                  ? (c < 110581
                    ? (c >= 110576 && c <= 110579)
                    : c <= 110587)
                  : (c <= 110590 || (c >= 110592 && c <= 110882)))))))))))
        : (c <= 110930 || (c < 125255
          ? (c < 120688
            ? (c < 119995
              ? (c < 113808
                ? (c < 113664
                  ? (c < 110960
                    ? (c >= 110948 && c <= 110951)
                    : c <= 111355)
                  : (c <= 113770 || (c < 113792
                    ? (c >= 113776 && c <= 113788)
                    : c <= 113800)))
                : (c <= 113817 || (c < 119894
                  ? (c < 119834
                    ? c == 113822
                    : c <= 119892)
                  : (c <= 119963 || (c >= 119990 && c <= 119993)))))
              : (c <= 119995 || (c < 120540
                ? (c < 120094
                  ? (c < 120005
                    ? (c >= 119997 && c <= 120003)
                    : c <= 120067)
                  : (c <= 120119 || (c < 120514
                    ? (c >= 120146 && c <= 120485)
                    : c <= 120538)))
                : (c <= 120545 || (c < 120630
                  ? (c < 120598
                    ? (c >= 120572 && c <= 120596)
                    : c <= 120603)
                  : (c <= 120654 || (c >= 120656 && c <= 120661)))))))
            : (c <= 120712 || (c < 123191
              ? (c < 122888
                ? (c < 120772
                  ? (c < 120746
                    ? (c >= 120714 && c <= 120719)
                    : c <= 120770)
                  : (c <= 120779 || (c < 122880
                    ? (c >= 122624 && c <= 122654)
                    : c <= 122886)))
                : (c <= 122904 || (c < 122918
                  ? (c < 122915
                    ? (c >= 122907 && c <= 122913)
                    : c <= 122916)
                  : (c <= 122922 || (c >= 123136 && c <= 123180)))))
              : (c <= 123197 || (c < 124904
                ? (c < 123584
                  ? (c < 123536
                    ? c == 123214
                    : c <= 123565)
                  : (c <= 123627 || (c >= 124896 && c <= 124902)))
                : (c <= 124907 || (c < 124928
                  ? (c < 124912
                    ? (c >= 124909 && c <= 124910)
                    : c <= 124926)
                  : (c <= 125124 || (c >= 125218 && c <= 125251)))))))))
          : (c <= 125255 || (c < 126557
            ? (c < 126530
              ? (c < 126503
                ? (c < 126469
                  ? (c < 126464
                    ? c == 125259
                    : c <= 126467)
                  : (c <= 126495 || (c < 126500
                    ? (c >= 126497 && c <= 126498)
                    : c <= 126500)))
                : (c <= 126503 || (c < 126521
                  ? (c < 126516
                    ? (c >= 126505 && c <= 126514)
                    : c <= 126519)
                  : (c <= 126521 || c == 126523))))
              : (c <= 126530 || (c < 126545
                ? (c < 126539
                  ? (c < 126537
                    ? c == 126535
                    : c <= 126537)
                  : (c <= 126539 || (c >= 126541 && c <= 126543)))
                : (c <= 126546 || (c < 126553
                  ? (c < 126551
                    ? c == 126548
                    : c <= 126551)
                  : (c <= 126553 || c == 126555))))))
            : (c <= 126557 || (c < 126625
              ? (c < 126580
                ? (c < 126564
                  ? (c < 126561
                    ? c == 126559
                    : c <= 126562)
                  : (c <= 126564 || (c < 126572
                    ? (c >= 126567 && c <= 126570)
                    : c <= 126578)))
                : (c <= 126583 || (c < 126592
                  ? (c < 126590
                    ? (c >= 126585 && c <= 126588)
                    : c <= 126590)
                  : (c <= 126601 || (c >= 126603 && c <= 126619)))))
              : (c <= 126627 || (c < 177984
                ? (c < 131072
                  ? (c < 126635
                    ? (c >= 126629 && c <= 126633)
                    : c <= 126651)
                  : (c <= 173791 || (c >= 173824 && c <= 177976)))
                : (c <= 178205 || (c < 194560
                  ? (c < 183984
                    ? (c >= 178208 && c <= 183969)
                    : c <= 191456)
                  : (c <= 195101 || (c >= 196608 && c <= 201546)))))))))))))))));
}

static inline bool aux_sym_predicate_token2_character_set_3(int32_t c) {
  return (c < 42960
    ? (c < 3520
      ? (c < 2613
        ? (c < 1646
          ? (c < 886
            ? (c < 181
              ? (c < 'A'
                ? (c < '*'
                  ? (c < '&'
                    ? c == '!'
                    : c <= '&')
                  : (c <= '+' || (c < '/'
                    ? c == '-'
                    : c <= '/')))
                : (c <= 'Z' || (c < '|'
                  ? (c < 'a'
                    ? c == '_'
                    : c <= 'z')
                  : (c <= '|' || (c < 170
                    ? c == '~'
                    : c <= 170)))))
              : (c <= 181 || (c < 736
                ? (c < 216
                  ? (c < 192
                    ? c == 186
                    : c <= 214)
                  : (c <= 246 || (c < 710
                    ? (c >= 248 && c <= 705)
                    : c <= 721)))
                : (c <= 740 || (c < 837
                  ? (c < 750
                    ? c == 748
                    : c <= 750)
                  : (c <= 837 || (c >= 880 && c <= 884)))))))
            : (c <= 887 || (c < 1376
              ? (c < 910
                ? (c < 902
                  ? (c < 895
                    ? (c >= 890 && c <= 893)
                    : c <= 895)
                  : (c <= 902 || (c < 908
                    ? (c >= 904 && c <= 906)
                    : c <= 908)))
                : (c <= 929 || (c < 1162
                  ? (c < 1015
                    ? (c >= 931 && c <= 1013)
                    : c <= 1153)
                  : (c <= 1327 || (c < 1369
                    ? (c >= 1329 && c <= 1366)
                    : c <= 1369)))))
              : (c <= 1416 || (c < 1488
                ? (c < 1473
                  ? (c < 1471
                    ? (c >= 1456 && c <= 1469)
                    : c <= 1471)
                  : (c <= 1474 || (c < 1479
                    ? (c >= 1476 && c <= 1477)
                    : c <= 1479)))
                : (c <= 1514 || (c < 1568
                  ? (c < 1552
                    ? (c >= 1519 && c <= 1522)
                    : c <= 1562)
                  : (c <= 1623 || (c >= 1625 && c <= 1631)))))))))
          : (c <= 1747 || (c < 2389
            ? (c < 2074
              ? (c < 1808
                ? (c < 1773
                  ? (c < 1761
                    ? (c >= 1749 && c <= 1756)
                    : c <= 1768)
                  : (c <= 1775 || (c < 1791
                    ? (c >= 1786 && c <= 1788)
                    : c <= 1791)))
                : (c <= 1855 || (c < 2036
                  ? (c < 1994
                    ? (c >= 1869 && c <= 1969)
                    : c <= 2026)
                  : (c <= 2037 || (c < 2048
                    ? c == 2042
                    : c <= 2071)))))
              : (c <= 2092 || (c < 2260
                ? (c < 2160
                  ? (c < 2144
                    ? (c >= 2112 && c <= 2136)
                    : c <= 2154)
                  : (c <= 2183 || (c < 2208
                    ? (c >= 2185 && c <= 2190)
                    : c <= 2249)))
                : (c <= 2271 || (c < 2365
                  ? (c < 2288
                    ? (c >= 2275 && c <= 2281)
                    : c <= 2363)
                  : (c <= 2380 || (c >= 2382 && c <= 2384)))))))
            : (c <= 2403 || (c < 2519
              ? (c < 2482
                ? (c < 2447
                  ? (c < 2437
                    ? (c >= 2417 && c <= 2435)
                    : c <= 2444)
                  : (c <= 2448 || (c < 2474
                    ? (c >= 2451 && c <= 2472)
                    : c <= 2480)))
                : (c <= 2482 || (c < 2503
                  ? (c < 2493
                    ? (c >= 2486 && c <= 2489)
                    : c <= 2500)
                  : (c <= 2504 || (c < 2510
                    ? (c >= 2507 && c <= 2508)
                    : c <= 2510)))))
              : (c <= 2519 || (c < 2565
                ? (c < 2544
                  ? (c < 2527
                    ? (c >= 2524 && c <= 2525)
                    : c <= 2531)
                  : (c <= 2545 || (c < 2561
                    ? c == 2556
                    : c <= 2563)))
                : (c <= 2570 || (c < 2602
                  ? (c < 2579
                    ? (c >= 2575 && c <= 2576)
                    : c <= 2600)
                  : (c <= 2608 || (c >= 2610 && c <= 2611)))))))))))
        : (c <= 2614 || (c < 3006
          ? (c < 2821
            ? (c < 2707
              ? (c < 2649
                ? (c < 2631
                  ? (c < 2622
                    ? (c >= 2616 && c <= 2617)
                    : c <= 2626)
                  : (c <= 2632 || (c < 2641
                    ? (c >= 2635 && c <= 2636)
                    : c <= 2641)))
                : (c <= 2652 || (c < 2689
                  ? (c < 2672
                    ? c == 2654
                    : c <= 2677)
                  : (c <= 2691 || (c < 2703
                    ? (c >= 2693 && c <= 2701)
                    : c <= 2705)))))
              : (c <= 2728 || (c < 2763
                ? (c < 2741
                  ? (c < 2738
                    ? (c >= 2730 && c <= 2736)
                    : c <= 2739)
                  : (c <= 2745 || (c < 2759
                    ? (c >= 2749 && c <= 2757)
                    : c <= 2761)))
                : (c <= 2764 || (c < 2809
                  ? (c < 2784
                    ? c == 2768
                    : c <= 2787)
                  : (c <= 2812 || (c >= 2817 && c <= 2819)))))))
            : (c <= 2828 || (c < 2929
              ? (c < 2877
                ? (c < 2858
                  ? (c < 2835
                    ? (c >= 2831 && c <= 2832)
                    : c <= 2856)
                  : (c <= 2864 || (c < 2869
                    ? (c >= 2866 && c <= 2867)
                    : c <= 2873)))
                : (c <= 2884 || (c < 2902
                  ? (c < 2891
                    ? (c >= 2887 && c <= 2888)
                    : c <= 2892)
                  : (c <= 2903 || (c < 2911
                    ? (c >= 2908 && c <= 2909)
                    : c <= 2915)))))
              : (c <= 2929 || (c < 2972
                ? (c < 2958
                  ? (c < 2949
                    ? (c >= 2946 && c <= 2947)
                    : c <= 2954)
                  : (c <= 2960 || (c < 2969
                    ? (c >= 2962 && c <= 2965)
                    : c <= 2970)))
                : (c <= 2972 || (c < 2984
                  ? (c < 2979
                    ? (c >= 2974 && c <= 2975)
                    : c <= 2980)
                  : (c <= 2986 || (c >= 2990 && c <= 3001)))))))))
          : (c <= 3010 || (c < 3261
            ? (c < 3146
              ? (c < 3077
                ? (c < 3024
                  ? (c < 3018
                    ? (c >= 3014 && c <= 3016)
                    : c <= 3020)
                  : (c <= 3024 || (c < 3072
                    ? c == 3031
                    : c <= 3075)))
                : (c <= 3084 || (c < 3114
                  ? (c < 3090
                    ? (c >= 3086 && c <= 3088)
                    : c <= 3112)
                  : (c <= 3129 || (c < 3142
                    ? (c >= 3133 && c <= 3140)
                    : c <= 3144)))))
              : (c <= 3148 || (c < 3205
                ? (c < 3165
                  ? (c < 3160
                    ? (c >= 3157 && c <= 3158)
                    : c <= 3162)
                  : (c <= 3165 || (c < 3200
                    ? (c >= 3168 && c <= 3171)
                    : c <= 3203)))
                : (c <= 3212 || (c < 3242
                  ? (c < 3218
                    ? (c >= 3214 && c <= 3216)
                    : c <= 3240)
                  : (c <= 3251 || (c >= 3253 && c <= 3257)))))))
            : (c <= 3268 || (c < 3398
              ? (c < 3313
                ? (c < 3285
                  ? (c < 3274
                    ? (c >= 3270 && c <= 3272)
                    : c <= 3276)
                  : (c <= 3286 || (c < 3296
                    ? (c >= 3293 && c <= 3294)
                    : c <= 3299)))
                : (c <= 3314 || (c < 3346
                  ? (c < 3342
                    ? (c >= 3328 && c <= 3340)
                    : c <= 3344)
                  : (c <= 3386 || (c >= 3389 && c <= 3396)))))
              : (c <= 3400 || (c < 3457
                ? (c < 3412
                  ? (c < 3406
                    ? (c >= 3402 && c <= 3404)
                    : c <= 3406)
                  : (c <= 3415 || (c < 3450
                    ? (c >= 3423 && c <= 3427)
                    : c <= 3455)))
                : (c <= 3459 || (c < 3507
                  ? (c < 3482
                    ? (c >= 3461 && c <= 3478)
                    : c <= 3505)
                  : (c <= 3515 || c == 3517))))))))))))
      : (c <= 3526 || (c < 7245
        ? (c < 4808
          ? (c < 3976
            ? (c < 3749
              ? (c < 3648
                ? (c < 3544
                  ? (c < 3542
                    ? (c >= 3535 && c <= 3540)
                    : c <= 3542)
                  : (c <= 3551 || (c < 3585
                    ? (c >= 3570 && c <= 3571)
                    : c <= 3642)))
                : (c <= 3654 || (c < 3716
                  ? (c < 3713
                    ? c == 3661
                    : c <= 3714)
                  : (c <= 3716 || (c < 3724
                    ? (c >= 3718 && c <= 3722)
                    : c <= 3747)))))
              : (c <= 3749 || (c < 3804
                ? (c < 3776
                  ? (c < 3771
                    ? (c >= 3751 && c <= 3769)
                    : c <= 3773)
                  : (c <= 3780 || (c < 3789
                    ? c == 3782
                    : c <= 3789)))
                : (c <= 3807 || (c < 3913
                  ? (c < 3904
                    ? c == 3840
                    : c <= 3911)
                  : (c <= 3948 || (c >= 3953 && c <= 3969)))))))
            : (c <= 3991 || (c < 4682
              ? (c < 4250
                ? (c < 4152
                  ? (c < 4096
                    ? (c >= 3993 && c <= 4028)
                    : c <= 4150)
                  : (c <= 4152 || (c < 4176
                    ? (c >= 4155 && c <= 4159)
                    : c <= 4239)))
                : (c <= 4253 || (c < 4301
                  ? (c < 4295
                    ? (c >= 4256 && c <= 4293)
                    : c <= 4295)
                  : (c <= 4301 || (c < 4348
                    ? (c >= 4304 && c <= 4346)
                    : c <= 4680)))))
              : (c <= 4685 || (c < 4752
                ? (c < 4698
                  ? (c < 4696
                    ? (c >= 4688 && c <= 4694)
                    : c <= 4696)
                  : (c <= 4701 || (c < 4746
                    ? (c >= 4704 && c <= 4744)
                    : c <= 4749)))
                : (c <= 4784 || (c < 4800
                  ? (c < 4792
                    ? (c >= 4786 && c <= 4789)
                    : c <= 4798)
                  : (c <= 4800 || (c >= 4802 && c <= 4805)))))))))
          : (c <= 4822 || (c < 6272
            ? (c < 5888
              ? (c < 5112
                ? (c < 4888
                  ? (c < 4882
                    ? (c >= 4824 && c <= 4880)
                    : c <= 4885)
                  : (c <= 4954 || (c < 5024
                    ? (c >= 4992 && c <= 5007)
                    : c <= 5109)))
                : (c <= 5117 || (c < 5761
                  ? (c < 5743
                    ? (c >= 5121 && c <= 5740)
                    : c <= 5759)
                  : (c <= 5786 || (c < 5870
                    ? (c >= 5792 && c <= 5866)
                    : c <= 5880)))))
              : (c <= 5907 || (c < 6016
                ? (c < 5984
                  ? (c < 5952
                    ? (c >= 5919 && c <= 5939)
                    : c <= 5971)
                  : (c <= 5996 || (c < 6002
                    ? (c >= 5998 && c <= 6000)
                    : c <= 6003)))
                : (c <= 6067 || (c < 6108
                  ? (c < 6103
                    ? (c >= 6070 && c <= 6088)
                    : c <= 6103)
                  : (c <= 6108 || (c >= 6176 && c <= 6264)))))))
            : (c <= 6314 || (c < 6823
              ? (c < 6512
                ? (c < 6432
                  ? (c < 6400
                    ? (c >= 6320 && c <= 6389)
                    : c <= 6430)
                  : (c <= 6443 || (c < 6480
                    ? (c >= 6448 && c <= 6456)
                    : c <= 6509)))
                : (c <= 6516 || (c < 6656
                  ? (c < 6576
                    ? (c >= 6528 && c <= 6571)
                    : c <= 6601)
                  : (c <= 6683 || (c < 6753
                    ? (c >= 6688 && c <= 6750)
                    : c <= 6772)))))
              : (c <= 6823 || (c < 7040
                ? (c < 6912
                  ? (c < 6860
                    ? (c >= 6847 && c <= 6848)
                    : c <= 6862)
                  : (c <= 6963 || (c < 6981
                    ? (c >= 6965 && c <= 6979)
                    : c <= 6988)))
                : (c <= 7081 || (c < 7143
                  ? (c < 7098
                    ? (c >= 7084 && c <= 7087)
                    : c <= 7141)
                  : (c <= 7153 || (c >= 7168 && c <= 7222)))))))))))
        : (c <= 7247 || (c < 8544
          ? (c < 8130
            ? (c < 7960
              ? (c < 7406
                ? (c < 7312
                  ? (c < 7296
                    ? (c >= 7258 && c <= 7293)
                    : c <= 7304)
                  : (c <= 7354 || (c < 7401
                    ? (c >= 7357 && c <= 7359)
                    : c <= 7404)))
                : (c <= 7411 || (c < 7424
                  ? (c < 7418
                    ? (c >= 7413 && c <= 7414)
                    : c <= 7418)
                  : (c <= 7615 || (c < 7680
                    ? (c >= 7655 && c <= 7668)
                    : c <= 7957)))))
              : (c <= 7965 || (c < 8029
                ? (c < 8016
                  ? (c < 8008
                    ? (c >= 7968 && c <= 8005)
                    : c <= 8013)
                  : (c <= 8023 || (c < 8027
                    ? c == 8025
                    : c <= 8027)))
                : (c <= 8029 || (c < 8118
                  ? (c < 8064
                    ? (c >= 8031 && c <= 8061)
                    : c <= 8116)
                  : (c <= 8124 || c == 8126))))))
            : (c <= 8132 || (c < 8458
              ? (c < 8182
                ? (c < 8150
                  ? (c < 8144
                    ? (c >= 8134 && c <= 8140)
                    : c <= 8147)
                  : (c <= 8155 || (c < 8178
                    ? (c >= 8160 && c <= 8172)
                    : c <= 8180)))
                : (c <= 8188 || (c < 8336
                  ? (c < 8319
                    ? c == 8305
                    : c <= 8319)
                  : (c <= 8348 || (c < 8455
                    ? c == 8450
                    : c <= 8455)))))
              : (c <= 8467 || (c < 8490
                ? (c < 8484
                  ? (c < 8473
                    ? c == 8469
                    : c <= 8477)
                  : (c <= 8484 || (c < 8488
                    ? c == 8486
                    : c <= 8488)))
                : (c <= 8493 || (c < 8517
                  ? (c < 8508
                    ? (c >= 8495 && c <= 8505)
                    : c <= 8511)
                  : (c <= 8521 || c == 8526))))))))
          : (c <= 8584 || (c < 12337
            ? (c < 11688
              ? (c < 11559
                ? (c < 11499
                  ? (c < 11264
                    ? (c >= 9398 && c <= 9449)
                    : c <= 11492)
                  : (c <= 11502 || (c < 11520
                    ? (c >= 11506 && c <= 11507)
                    : c <= 11557)))
                : (c <= 11559 || (c < 11631
                  ? (c < 11568
                    ? c == 11565
                    : c <= 11623)
                  : (c <= 11631 || (c < 11680
                    ? (c >= 11648 && c <= 11670)
                    : c <= 11686)))))
              : (c <= 11694 || (c < 11736
                ? (c < 11712
                  ? (c < 11704
                    ? (c >= 11696 && c <= 11702)
                    : c <= 11710)
                  : (c <= 11718 || (c < 11728
                    ? (c >= 11720 && c <= 11726)
                    : c <= 11734)))
                : (c <= 11742 || (c < 12293
                  ? (c < 11823
                    ? (c >= 11744 && c <= 11775)
                    : c <= 11823)
                  : (c <= 12295 || (c >= 12321 && c <= 12329)))))))
            : (c <= 12341 || (c < 19968
              ? (c < 12549
                ? (c < 12445
                  ? (c < 12353
                    ? (c >= 12344 && c <= 12348)
                    : c <= 12438)
                  : (c <= 12447 || (c < 12540
                    ? (c >= 12449 && c <= 12538)
                    : c <= 12543)))
                : (c <= 12591 || (c < 12784
                  ? (c < 12704
                    ? (c >= 12593 && c <= 12686)
                    : c <= 12735)
                  : (c <= 12799 || (c >= 13312 && c <= 19903)))))
              : (c <= 42124 || (c < 42612
                ? (c < 42512
                  ? (c < 42240
                    ? (c >= 42192 && c <= 42237)
                    : c <= 42508)
                  : (c <= 42527 || (c < 42560
                    ? (c >= 42538 && c <= 42539)
                    : c <= 42606)))
                : (c <= 42619 || (c < 42786
                  ? (c < 42775
                    ? (c >= 42623 && c <= 42735)
                    : c <= 42783)
                  : (c <= 42888 || (c >= 42891 && c <= 42954)))))))))))))))
    : (c <= 42961 || (c < 71040
      ? (c < 67003
        ? (c < 64318
          ? (c < 43712
            ? (c < 43312
              ? (c < 43136
                ? (c < 42994
                  ? (c < 42965
                    ? c == 42963
                    : c <= 42969)
                  : (c <= 43013 || (c < 43072
                    ? (c >= 43015 && c <= 43047)
                    : c <= 43123)))
                : (c <= 43203 || (c < 43259
                  ? (c < 43250
                    ? c == 43205
                    : c <= 43255)
                  : (c <= 43259 || (c < 43274
                    ? (c >= 43261 && c <= 43263)
                    : c <= 43306)))))
              : (c <= 43346 || (c < 43514
                ? (c < 43444
                  ? (c < 43392
                    ? (c >= 43360 && c <= 43388)
                    : c <= 43442)
                  : (c <= 43455 || (c < 43488
                    ? c == 43471
                    : c <= 43503)))
                : (c <= 43518 || (c < 43616
                  ? (c < 43584
                    ? (c >= 43520 && c <= 43574)
                    : c <= 43597)
                  : (c <= 43638 || (c >= 43642 && c <= 43710)))))))
            : (c <= 43712 || (c < 43888
              ? (c < 43785
                ? (c < 43744
                  ? (c < 43739
                    ? c == 43714
                    : c <= 43741)
                  : (c <= 43759 || (c < 43777
                    ? (c >= 43762 && c <= 43765)
                    : c <= 43782)))
                : (c <= 43790 || (c < 43816
                  ? (c < 43808
                    ? (c >= 43793 && c <= 43798)
                    : c <= 43814)
                  : (c <= 43822 || (c < 43868
                    ? (c >= 43824 && c <= 43866)
                    : c <= 43881)))))
              : (c <= 44010 || (c < 64256
                ? (c < 55243
                  ? (c < 55216
                    ? (c >= 44032 && c <= 55203)
                    : c <= 55238)
                  : (c <= 55291 || (c < 64112
                    ? (c >= 63744 && c <= 64109)
                    : c <= 64217)))
                : (c <= 64262 || (c < 64298
                  ? (c < 64285
                    ? (c >= 64275 && c <= 64279)
                    : c <= 64296)
                  : (c <= 64310 || (c >= 64312 && c <= 64316)))))))))
          : (c <= 64318 || (c < 65664
            ? (c < 65382
              ? (c < 64914
                ? (c < 64326
                  ? (c < 64323
                    ? (c >= 64320 && c <= 64321)
                    : c <= 64324)
                  : (c <= 64433 || (c < 64848
                    ? (c >= 64467 && c <= 64829)
                    : c <= 64911)))
                : (c <= 64967 || (c < 65142
                  ? (c < 65136
                    ? (c >= 65008 && c <= 65019)
                    : c <= 65140)
                  : (c <= 65276 || (c < 65345
                    ? (c >= 65313 && c <= 65338)
                    : c <= 65370)))))
              : (c <= 65470 || (c < 65549
                ? (c < 65490
                  ? (c < 65482
                    ? (c >= 65474 && c <= 65479)
                    : c <= 65487)
                  : (c <= 65495 || (c < 65536
                    ? (c >= 65498 && c <= 65500)
                    : c <= 65547)))
                : (c <= 65574 || (c < 65599
                  ? (c < 65596
                    ? (c >= 65576 && c <= 65594)
                    : c <= 65597)
                  : (c <= 65613 || (c >= 65616 && c <= 65629)))))))
            : (c <= 65786 || (c < 66736
              ? (c < 66384
                ? (c < 66208
                  ? (c < 66176
                    ? (c >= 65856 && c <= 65908)
                    : c <= 66204)
                  : (c <= 66256 || (c < 66349
                    ? (c >= 66304 && c <= 66335)
                    : c <= 66378)))
                : (c <= 66426 || (c < 66504
                  ? (c < 66464
                    ? (c >= 66432 && c <= 66461)
                    : c <= 66499)
                  : (c <= 66511 || (c < 66560
                    ? (c >= 66513 && c <= 66517)
                    : c <= 66717)))))
              : (c <= 66771 || (c < 66956
                ? (c < 66864
                  ? (c < 66816
                    ? (c >= 66776 && c <= 66811)
                    : c <= 66855)
                  : (c <= 66915 || (c < 66940
                    ? (c >= 66928 && c <= 66938)
                    : c <= 66954)))
                : (c <= 66962 || (c < 66979
                  ? (c < 66967
                    ? (c >= 66964 && c <= 66965)
                    : c <= 66977)
                  : (c <= 66993 || (c >= 66995 && c <= 67001)))))))))))
        : (c <= 67004 || (c < 69600
          ? (c < 68108
            ? (c < 67647
              ? (c < 67506
                ? (c < 67424
                  ? (c < 67392
                    ? (c >= 67072 && c <= 67382)
                    : c <= 67413)
                  : (c <= 67431 || (c < 67463
                    ? (c >= 67456 && c <= 67461)
                    : c <= 67504)))
                : (c <= 67514 || (c < 67594
                  ? (c < 67592
                    ? (c >= 67584 && c <= 67589)
                    : c <= 67592)
                  : (c <= 67637 || (c < 67644
                    ? (c >= 67639 && c <= 67640)
                    : c <= 67644)))))
              : (c <= 67669 || (c < 67872
                ? (c < 67808
                  ? (c < 67712
                    ? (c >= 67680 && c <= 67702)
                    : c <= 67742)
                  : (c <= 67826 || (c < 67840
                    ? (c >= 67828 && c <= 67829)
                    : c <= 67861)))
                : (c <= 67897 || (c < 68096
                  ? (c < 68030
                    ? (c >= 67968 && c <= 68023)
                    : c <= 68031)
                  : (c <= 68099 || (c >= 68101 && c <= 68102)))))))
            : (c <= 68115 || (c < 68736
              ? (c < 68297
                ? (c < 68192
                  ? (c < 68121
                    ? (c >= 68117 && c <= 68119)
                    : c <= 68149)
                  : (c <= 68220 || (c < 68288
                    ? (c >= 68224 && c <= 68252)
                    : c <= 68295)))
                : (c <= 68324 || (c < 68448
                  ? (c < 68416
                    ? (c >= 68352 && c <= 68405)
                    : c <= 68437)
                  : (c <= 68466 || (c < 68608
                    ? (c >= 68480 && c <= 68497)
                    : c <= 68680)))))
              : (c <= 68786 || (c < 69376
                ? (c < 69248
                  ? (c < 68864
                    ? (c >= 68800 && c <= 68850)
                    : c <= 68903)
                  : (c <= 69289 || (c < 69296
                    ? (c >= 69291 && c <= 69292)
                    : c <= 69297)))
                : (c <= 69404 || (c < 69488
                  ? (c < 69424
                    ? c == 69415
                    : c <= 69445)
                  : (c <= 69505 || (c >= 69552 && c <= 69572)))))))))
          : (c <= 69622 || (c < 70303
            ? (c < 70094
              ? (c < 69888
                ? (c < 69762
                  ? (c < 69745
                    ? (c >= 69632 && c <= 69701)
                    : c <= 69749)
                  : (c <= 69816 || (c < 69840
                    ? c == 69826
                    : c <= 69864)))
                : (c <= 69938 || (c < 70006
                  ? (c < 69968
                    ? (c >= 69956 && c <= 69959)
                    : c <= 70002)
                  : (c <= 70006 || (c < 70081
                    ? (c >= 70016 && c <= 70079)
                    : c <= 70084)))))
              : (c <= 70095 || (c < 70206
                ? (c < 70144
                  ? (c < 70108
                    ? c == 70106
                    : c <= 70108)
                  : (c <= 70161 || (c < 70199
                    ? (c >= 70163 && c <= 70196)
                    : c <= 70199)))
                : (c <= 70206 || (c < 70282
                  ? (c < 70280
                    ? (c >= 70272 && c <= 70278)
                    : c <= 70280)
                  : (c <= 70285 || (c >= 70287 && c <= 70301)))))))
            : (c <= 70312 || (c < 70475
              ? (c < 70442
                ? (c < 70405
                  ? (c < 70400
                    ? (c >= 70320 && c <= 70376)
                    : c <= 70403)
                  : (c <= 70412 || (c < 70419
                    ? (c >= 70415 && c <= 70416)
                    : c <= 70440)))
                : (c <= 70448 || (c < 70461
                  ? (c < 70453
                    ? (c >= 70450 && c <= 70451)
                    : c <= 70457)
                  : (c <= 70468 || (c >= 70471 && c <= 70472)))))
              : (c <= 70476 || (c < 70727
                ? (c < 70493
                  ? (c < 70487
                    ? c == 70480
                    : c <= 70487)
                  : (c <= 70499 || (c < 70723
                    ? (c >= 70656 && c <= 70721)
                    : c <= 70725)))
                : (c <= 70730 || (c < 70852
                  ? (c < 70784
                    ? (c >= 70751 && c <= 70753)
                    : c <= 70849)
                  : (c <= 70853 || c == 70855))))))))))))
      : (c <= 71093 || (c < 119894
        ? (c < 73056
          ? (c < 72154
            ? (c < 71840
              ? (c < 71296
                ? (c < 71168
                  ? (c < 71128
                    ? (c >= 71096 && c <= 71102)
                    : c <= 71133)
                  : (c <= 71230 || (c < 71236
                    ? c == 71232
                    : c <= 71236)))
                : (c <= 71349 || (c < 71453
                  ? (c < 71424
                    ? c == 71352
                    : c <= 71450)
                  : (c <= 71466 || (c < 71680
                    ? (c >= 71488 && c <= 71494)
                    : c <= 71736)))))
              : (c <= 71903 || (c < 71991
                ? (c < 71948
                  ? (c < 71945
                    ? (c >= 71935 && c <= 71942)
                    : c <= 71945)
                  : (c <= 71955 || (c < 71960
                    ? (c >= 71957 && c <= 71958)
                    : c <= 71989)))
                : (c <= 71992 || (c < 72096
                  ? (c < 71999
                    ? (c >= 71995 && c <= 71996)
                    : c <= 72002)
                  : (c <= 72103 || (c >= 72106 && c <= 72151)))))))
            : (c <= 72159 || (c < 72818
              ? (c < 72349
                ? (c < 72192
                  ? (c < 72163
                    ? c == 72161
                    : c <= 72164)
                  : (c <= 72242 || (c < 72272
                    ? (c >= 72245 && c <= 72254)
                    : c <= 72343)))
                : (c <= 72349 || (c < 72714
                  ? (c < 72704
                    ? (c >= 72368 && c <= 72440)
                    : c <= 72712)
                  : (c <= 72758 || (c < 72768
                    ? (c >= 72760 && c <= 72766)
                    : c <= 72768)))))
              : (c <= 72847 || (c < 73018
                ? (c < 72960
                  ? (c < 72873
                    ? (c >= 72850 && c <= 72871)
                    : c <= 72886)
                  : (c <= 72966 || (c < 72971
                    ? (c >= 72968 && c <= 72969)
                    : c <= 73014)))
                : (c <= 73018 || (c < 73027
                  ? (c < 73023
                    ? (c >= 73020 && c <= 73021)
                    : c <= 73025)
                  : (c <= 73027 || (c >= 73030 && c <= 73031)))))))))
          : (c <= 73061 || (c < 93952
            ? (c < 77824
              ? (c < 73440
                ? (c < 73104
                  ? (c < 73066
                    ? (c >= 73063 && c <= 73064)
                    : c <= 73102)
                  : (c <= 73105 || (c < 73112
                    ? (c >= 73107 && c <= 73110)
                    : c <= 73112)))
                : (c <= 73462 || (c < 74752
                  ? (c < 73728
                    ? c == 73648
                    : c <= 74649)
                  : (c <= 74862 || (c < 77712
                    ? (c >= 74880 && c <= 75075)
                    : c <= 77808)))))
              : (c <= 78894 || (c < 92928
                ? (c < 92736
                  ? (c < 92160
                    ? (c >= 82944 && c <= 83526)
                    : c <= 92728)
                  : (c <= 92766 || (c < 92880
                    ? (c >= 92784 && c <= 92862)
                    : c <= 92909)))
                : (c <= 92975 || (c < 93053
                  ? (c < 93027
                    ? (c >= 92992 && c <= 92995)
                    : c <= 93047)
                  : (c <= 93071 || (c >= 93760 && c <= 93823)))))))
            : (c <= 94026 || (c < 110589
              ? (c < 94208
                ? (c < 94176
                  ? (c < 94095
                    ? (c >= 94031 && c <= 94087)
                    : c <= 94111)
                  : (c <= 94177 || (c < 94192
                    ? c == 94179
                    : c <= 94193)))
                : (c <= 100343 || (c < 110576
                  ? (c < 101632
                    ? (c >= 100352 && c <= 101589)
                    : c <= 101640)
                  : (c <= 110579 || (c >= 110581 && c <= 110587)))))
              : (c <= 110590 || (c < 113776
                ? (c < 110948
                  ? (c < 110928
                    ? (c >= 110592 && c <= 110882)
                    : c <= 110930)
                  : (c <= 110951 || (c < 113664
                    ? (c >= 110960 && c <= 111355)
                    : c <= 113770)))
                : (c <= 113788 || (c < 113822
                  ? (c < 113808
                    ? (c >= 113792 && c <= 113800)
                    : c <= 113817)
                  : (c <= 113822 || (c >= 119808 && c <= 119892)))))))))))
        : (c <= 119964 || (c < 125255
          ? (c < 120630
            ? (c < 120094
              ? (c < 119995
                ? (c < 119973
                  ? (c < 119970
                    ? (c >= 119966 && c <= 119967)
                    : c <= 119970)
                  : (c <= 119974 || (c < 119982
                    ? (c >= 119977 && c <= 119980)
                    : c <= 119993)))
                : (c <= 119995 || (c < 120071
                  ? (c < 120005
                    ? (c >= 119997 && c <= 120003)
                    : c <= 120069)
                  : (c <= 120074 || (c < 120086
                    ? (c >= 120077 && c <= 120084)
                    : c <= 120092)))))
              : (c <= 120121 || (c < 120488
                ? (c < 120134
                  ? (c < 120128
                    ? (c >= 120123 && c <= 120126)
                    : c <= 120132)
                  : (c <= 120134 || (c < 120146
                    ? (c >= 120138 && c <= 120144)
                    : c <= 120485)))
                : (c <= 120512 || (c < 120572
                  ? (c < 120540
                    ? (c >= 120514 && c <= 120538)
                    : c <= 120570)
                  : (c <= 120596 || (c >= 120598 && c <= 120628)))))))
            : (c <= 120654 || (c < 123136
              ? (c < 122624
                ? (c < 120714
                  ? (c < 120688
                    ? (c >= 120656 && c <= 120686)
                    : c <= 120712)
                  : (c <= 120744 || (c < 120772
                    ? (c >= 120746 && c <= 120770)
                    : c <= 120779)))
                : (c <= 122654 || (c < 122907
                  ? (c < 122888
                    ? (c >= 122880 && c <= 122886)
                    : c <= 122904)
                  : (c <= 122913 || (c < 122918
                    ? (c >= 122915 && c <= 122916)
                    : c <= 122922)))))
              : (c <= 123180 || (c < 124904
                ? (c < 123536
                  ? (c < 123214
                    ? (c >= 123191 && c <= 123197)
                    : c <= 123214)
                  : (c <= 123565 || (c < 124896
                    ? (c >= 123584 && c <= 123627)
                    : c <= 124902)))
                : (c <= 124907 || (c < 124928
                  ? (c < 124912
                    ? (c >= 124909 && c <= 124910)
                    : c <= 124926)
                  : (c <= 125124 || (c >= 125184 && c <= 125251)))))))))
          : (c <= 125255 || (c < 126561
            ? (c < 126535
              ? (c < 126503
                ? (c < 126469
                  ? (c < 126464
                    ? c == 125259
                    : c <= 126467)
                  : (c <= 126495 || (c < 126500
                    ? (c >= 126497 && c <= 126498)
                    : c <= 126500)))
                : (c <= 126503 || (c < 126521
                  ? (c < 126516
                    ? (c >= 126505 && c <= 126514)
                    : c <= 126519)
                  : (c <= 126521 || (c < 126530
                    ? c == 126523
                    : c <= 126530)))))
              : (c <= 126535 || (c < 126551
                ? (c < 126541
                  ? (c < 126539
                    ? c == 126537
                    : c <= 126539)
                  : (c <= 126543 || (c < 126548
                    ? (c >= 126545 && c <= 126546)
                    : c <= 126548)))
                : (c <= 126551 || (c < 126557
                  ? (c < 126555
                    ? c == 126553
                    : c <= 126555)
                  : (c <= 126557 || c == 126559))))))
            : (c <= 126562 || (c < 126635
              ? (c < 126590
                ? (c < 126572
                  ? (c < 126567
                    ? c == 126564
                    : c <= 126570)
                  : (c <= 126578 || (c < 126585
                    ? (c >= 126580 && c <= 126583)
                    : c <= 126588)))
                : (c <= 126590 || (c < 126625
                  ? (c < 126603
                    ? (c >= 126592 && c <= 126601)
                    : c <= 126619)
                  : (c <= 126627 || (c >= 126629 && c <= 126633)))))
              : (c <= 126651 || (c < 177984
                ? (c < 127344
                  ? (c < 127312
                    ? (c >= 127280 && c <= 127305)
                    : c <= 127337)
                  : (c <= 127369 || (c < 173824
                    ? (c >= 131072 && c <= 173791)
                    : c <= 177976)))
                : (c <= 178205 || (c < 194560
                  ? (c < 183984
                    ? (c >= 178208 && c <= 183969)
                    : c <= 191456)
                  : (c <= 195101 || (c >= 196608 && c <= 201546)))))))))))))))));
}

static inline bool aux_sym_predicate_token2_character_set_4(int32_t c) {
  return (c < 19968
    ? (c < 3520
      ? (c < 2616
        ? (c < 1646
          ? (c < 880
            ? (c < 178
              ? (c < 'A'
                ? (c < '*'
                  ? (c < '&'
                    ? c == '!'
                    : c <= '&')
                  : (c <= '+' || (c < '/'
                    ? c == '-'
                    : c <= '9')))
                : (c <= 'Z' || (c < '|'
                  ? (c < 'a'
                    ? c == '_'
                    : c <= 'z')
                  : (c <= '|' || (c < 170
                    ? c == '~'
                    : c <= 170)))))
              : (c <= 179 || (c < 248
                ? (c < 188
                  ? (c < 185
                    ? c == 181
                    : c <= 186)
                  : (c <= 190 || (c < 216
                    ? (c >= 192 && c <= 214)
                    : c <= 246)))
                : (c <= 705 || (c < 748
                  ? (c < 736
                    ? (c >= 710 && c <= 721)
                    : c <= 740)
                  : (c <= 748 || (c < 837
                    ? c == 750
                    : c <= 837)))))))
            : (c <= 884 || (c < 1369
              ? (c < 908
                ? (c < 895
                  ? (c < 890
                    ? (c >= 886 && c <= 887)
                    : c <= 893)
                  : (c <= 895 || (c < 904
                    ? c == 902
                    : c <= 906)))
                : (c <= 908 || (c < 1015
                  ? (c < 931
                    ? (c >= 910 && c <= 929)
                    : c <= 1013)
                  : (c <= 1153 || (c < 1329
                    ? (c >= 1162 && c <= 1327)
                    : c <= 1366)))))
              : (c <= 1369 || (c < 1479
                ? (c < 1471
                  ? (c < 1456
                    ? (c >= 1376 && c <= 1416)
                    : c <= 1469)
                  : (c <= 1471 || (c < 1476
                    ? (c >= 1473 && c <= 1474)
                    : c <= 1477)))
                : (c <= 1479 || (c < 1552
                  ? (c < 1519
                    ? (c >= 1488 && c <= 1514)
                    : c <= 1522)
                  : (c <= 1562 || (c < 1625
                    ? (c >= 1568 && c <= 1623)
                    : c <= 1641)))))))))
          : (c <= 1747 || (c < 2417
            ? (c < 2112
              ? (c < 1869
                ? (c < 1773
                  ? (c < 1761
                    ? (c >= 1749 && c <= 1756)
                    : c <= 1768)
                  : (c <= 1788 || (c < 1808
                    ? c == 1791
                    : c <= 1855)))
                : (c <= 1969 || (c < 2042
                  ? (c < 2036
                    ? (c >= 1984 && c <= 2026)
                    : c <= 2037)
                  : (c <= 2042 || (c < 2074
                    ? (c >= 2048 && c <= 2071)
                    : c <= 2092)))))
              : (c <= 2136 || (c < 2275
                ? (c < 2185
                  ? (c < 2160
                    ? (c >= 2144 && c <= 2154)
                    : c <= 2183)
                  : (c <= 2190 || (c < 2260
                    ? (c >= 2208 && c <= 2249)
                    : c <= 2271)))
                : (c <= 2281 || (c < 2382
                  ? (c < 2365
                    ? (c >= 2288 && c <= 2363)
                    : c <= 2380)
                  : (c <= 2384 || (c < 2406
                    ? (c >= 2389 && c <= 2403)
                    : c <= 2415)))))))
            : (c <= 2435 || (c < 2524
              ? (c < 2486
                ? (c < 2451
                  ? (c < 2447
                    ? (c >= 2437 && c <= 2444)
                    : c <= 2448)
                  : (c <= 2472 || (c < 2482
                    ? (c >= 2474 && c <= 2480)
                    : c <= 2482)))
                : (c <= 2489 || (c < 2507
                  ? (c < 2503
                    ? (c >= 2493 && c <= 2500)
                    : c <= 2504)
                  : (c <= 2508 || (c < 2519
                    ? c == 2510
                    : c <= 2519)))))
              : (c <= 2525 || (c < 2565
                ? (c < 2548
                  ? (c < 2534
                    ? (c >= 2527 && c <= 2531)
                    : c <= 2545)
                  : (c <= 2553 || (c < 2561
                    ? c == 2556
                    : c <= 2563)))
                : (c <= 2570 || (c < 2602
                  ? (c < 2579
                    ? (c >= 2575 && c <= 2576)
                    : c <= 2600)
                  : (c <= 2608 || (c < 2613
                    ? (c >= 2610 && c <= 2611)
                    : c <= 2614)))))))))))
        : (c <= 2617 || (c < 3014
          ? (c < 2831
            ? (c < 2730
              ? (c < 2654
                ? (c < 2635
                  ? (c < 2631
                    ? (c >= 2622 && c <= 2626)
                    : c <= 2632)
                  : (c <= 2636 || (c < 2649
                    ? c == 2641
                    : c <= 2652)))
                : (c <= 2654 || (c < 2693
                  ? (c < 2689
                    ? (c >= 2662 && c <= 2677)
                    : c <= 2691)
                  : (c <= 2701 || (c < 2707
                    ? (c >= 2703 && c <= 2705)
                    : c <= 2728)))))
              : (c <= 2736 || (c < 2768
                ? (c < 2749
                  ? (c < 2741
                    ? (c >= 2738 && c <= 2739)
                    : c <= 2745)
                  : (c <= 2757 || (c < 2763
                    ? (c >= 2759 && c <= 2761)
                    : c <= 2764)))
                : (c <= 2768 || (c < 2809
                  ? (c < 2790
                    ? (c >= 2784 && c <= 2787)
                    : c <= 2799)
                  : (c <= 2812 || (c < 2821
                    ? (c >= 2817 && c <= 2819)
                    : c <= 2828)))))))
            : (c <= 2832 || (c < 2929
              ? (c < 2887
                ? (c < 2866
                  ? (c < 2858
                    ? (c >= 2835 && c <= 2856)
                    : c <= 2864)
                  : (c <= 2867 || (c < 2877
                    ? (c >= 2869 && c <= 2873)
                    : c <= 2884)))
                : (c <= 2888 || (c < 2908
                  ? (c < 2902
                    ? (c >= 2891 && c <= 2892)
                    : c <= 2903)
                  : (c <= 2909 || (c < 2918
                    ? (c >= 2911 && c <= 2915)
                    : c <= 2927)))))
              : (c <= 2935 || (c < 2972
                ? (c < 2958
                  ? (c < 2949
                    ? (c >= 2946 && c <= 2947)
                    : c <= 2954)
                  : (c <= 2960 || (c < 2969
                    ? (c >= 2962 && c <= 2965)
                    : c <= 2970)))
                : (c <= 2972 || (c < 2984
                  ? (c < 2979
                    ? (c >= 2974 && c <= 2975)
                    : c <= 2980)
                  : (c <= 2986 || (c < 3006
                    ? (c >= 2990 && c <= 3001)
                    : c <= 3010)))))))))
          : (c <= 3016 || (c < 3253
            ? (c < 3146
              ? (c < 3077
                ? (c < 3031
                  ? (c < 3024
                    ? (c >= 3018 && c <= 3020)
                    : c <= 3024)
                  : (c <= 3031 || (c < 3072
                    ? (c >= 3046 && c <= 3058)
                    : c <= 3075)))
                : (c <= 3084 || (c < 3114
                  ? (c < 3090
                    ? (c >= 3086 && c <= 3088)
                    : c <= 3112)
                  : (c <= 3129 || (c < 3142
                    ? (c >= 3133 && c <= 3140)
                    : c <= 3144)))))
              : (c <= 3148 || (c < 3192
                ? (c < 3165
                  ? (c < 3160
                    ? (c >= 3157 && c <= 3158)
                    : c <= 3162)
                  : (c <= 3165 || (c < 3174
                    ? (c >= 3168 && c <= 3171)
                    : c <= 3183)))
                : (c <= 3198 || (c < 3214
                  ? (c < 3205
                    ? (c >= 3200 && c <= 3203)
                    : c <= 3212)
                  : (c <= 3216 || (c < 3242
                    ? (c >= 3218 && c <= 3240)
                    : c <= 3251)))))))
            : (c <= 3257 || (c < 3389
              ? (c < 3296
                ? (c < 3274
                  ? (c < 3270
                    ? (c >= 3261 && c <= 3268)
                    : c <= 3272)
                  : (c <= 3276 || (c < 3293
                    ? (c >= 3285 && c <= 3286)
                    : c <= 3294)))
                : (c <= 3299 || (c < 3328
                  ? (c < 3313
                    ? (c >= 3302 && c <= 3311)
                    : c <= 3314)
                  : (c <= 3340 || (c < 3346
                    ? (c >= 3342 && c <= 3344)
                    : c <= 3386)))))
              : (c <= 3396 || (c < 3450
                ? (c < 3406
                  ? (c < 3402
                    ? (c >= 3398 && c <= 3400)
                    : c <= 3404)
                  : (c <= 3406 || (c < 3430
                    ? (c >= 3412 && c <= 3427)
                    : c <= 3448)))
                : (c <= 3455 || (c < 3482
                  ? (c < 3461
                    ? (c >= 3457 && c <= 3459)
                    : c <= 3478)
                  : (c <= 3505 || (c < 3517
                    ? (c >= 3507 && c <= 3515)
                    : c <= 3517)))))))))))))
      : (c <= 3526 || (c < 6981
        ? (c < 4802
          ? (c < 3904
            ? (c < 3718
              ? (c < 3585
                ? (c < 3544
                  ? (c < 3542
                    ? (c >= 3535 && c <= 3540)
                    : c <= 3542)
                  : (c <= 3551 || (c < 3570
                    ? (c >= 3558 && c <= 3567)
                    : c <= 3571)))
                : (c <= 3642 || (c < 3664
                  ? (c < 3661
                    ? (c >= 3648 && c <= 3654)
                    : c <= 3661)
                  : (c <= 3673 || (c < 3716
                    ? (c >= 3713 && c <= 3714)
                    : c <= 3716)))))
              : (c <= 3722 || (c < 3782
                ? (c < 3751
                  ? (c < 3749
                    ? (c >= 3724 && c <= 3747)
                    : c <= 3749)
                  : (c <= 3769 || (c < 3776
                    ? (c >= 3771 && c <= 3773)
                    : c <= 3780)))
                : (c <= 3782 || (c < 3804
                  ? (c < 3792
                    ? c == 3789
                    : c <= 3801)
                  : (c <= 3807 || (c < 3872
                    ? c == 3840
                    : c <= 3891)))))))
            : (c <= 3911 || (c < 4304
              ? (c < 4152
                ? (c < 3976
                  ? (c < 3953
                    ? (c >= 3913 && c <= 3948)
                    : c <= 3969)
                  : (c <= 3991 || (c < 4096
                    ? (c >= 3993 && c <= 4028)
                    : c <= 4150)))
                : (c <= 4152 || (c < 4256
                  ? (c < 4176
                    ? (c >= 4155 && c <= 4169)
                    : c <= 4253)
                  : (c <= 4293 || (c < 4301
                    ? c == 4295
                    : c <= 4301)))))
              : (c <= 4346 || (c < 4704
                ? (c < 4688
                  ? (c < 4682
                    ? (c >= 4348 && c <= 4680)
                    : c <= 4685)
                  : (c <= 4694 || (c < 4698
                    ? c == 4696
                    : c <= 4701)))
                : (c <= 4744 || (c < 4786
                  ? (c < 4752
                    ? (c >= 4746 && c <= 4749)
                    : c <= 4784)
                  : (c <= 4789 || (c < 4800
                    ? (c >= 4792 && c <= 4798)
                    : c <= 4800)))))))))
          : (c <= 4805 || (c < 6112
            ? (c < 5792
              ? (c < 4992
                ? (c < 4882
                  ? (c < 4824
                    ? (c >= 4808 && c <= 4822)
                    : c <= 4880)
                  : (c <= 4885 || (c < 4969
                    ? (c >= 4888 && c <= 4954)
                    : c <= 4988)))
                : (c <= 5007 || (c < 5121
                  ? (c < 5112
                    ? (c >= 5024 && c <= 5109)
                    : c <= 5117)
                  : (c <= 5740 || (c < 5761
                    ? (c >= 5743 && c <= 5759)
                    : c <= 5786)))))
              : (c <= 5866 || (c < 5998
                ? (c < 5919
                  ? (c < 5888
                    ? (c >= 5870 && c <= 5880)
                    : c <= 5907)
                  : (c <= 5939 || (c < 5984
                    ? (c >= 5952 && c <= 5971)
                    : c <= 5996)))
                : (c <= 6000 || (c < 6070
                  ? (c < 6016
                    ? (c >= 6002 && c <= 6003)
                    : c <= 6067)
                  : (c <= 6088 || (c < 6108
                    ? c == 6103
                    : c <= 6108)))))))
            : (c <= 6121 || (c < 6576
              ? (c < 6400
                ? (c < 6176
                  ? (c < 6160
                    ? (c >= 6128 && c <= 6137)
                    : c <= 6169)
                  : (c <= 6264 || (c < 6320
                    ? (c >= 6272 && c <= 6314)
                    : c <= 6389)))
                : (c <= 6430 || (c < 6470
                  ? (c < 6448
                    ? (c >= 6432 && c <= 6443)
                    : c <= 6456)
                  : (c <= 6509 || (c < 6528
                    ? (c >= 6512 && c <= 6516)
                    : c <= 6571)))))
              : (c <= 6601 || (c < 6800
                ? (c < 6688
                  ? (c < 6656
                    ? (c >= 6608 && c <= 6618)
                    : c <= 6683)
                  : (c <= 6750 || (c < 6784
                    ? (c >= 6753 && c <= 6772)
                    : c <= 6793)))
                : (c <= 6809 || (c < 6860
                  ? (c < 6847
                    ? c == 6823
                    : c <= 6848)
                  : (c <= 6862 || (c < 6965
                    ? (c >= 6912 && c <= 6963)
                    : c <= 6979)))))))))))
        : (c <= 6988 || (c < 8490
          ? (c < 8029
            ? (c < 7406
              ? (c < 7232
                ? (c < 7084
                  ? (c < 7040
                    ? (c >= 6992 && c <= 7001)
                    : c <= 7081)
                  : (c <= 7141 || (c < 7168
                    ? (c >= 7143 && c <= 7153)
                    : c <= 7222)))
                : (c <= 7241 || (c < 7312
                  ? (c < 7296
                    ? (c >= 7245 && c <= 7293)
                    : c <= 7304)
                  : (c <= 7354 || (c < 7401
                    ? (c >= 7357 && c <= 7359)
                    : c <= 7404)))))
              : (c <= 7411 || (c < 7960
                ? (c < 7424
                  ? (c < 7418
                    ? (c >= 7413 && c <= 7414)
                    : c <= 7418)
                  : (c <= 7615 || (c < 7680
                    ? (c >= 7655 && c <= 7668)
                    : c <= 7957)))
                : (c <= 7965 || (c < 8016
                  ? (c < 8008
                    ? (c >= 7968 && c <= 8005)
                    : c <= 8013)
                  : (c <= 8023 || (c < 8027
                    ? c == 8025
                    : c <= 8027)))))))
            : (c <= 8029 || (c < 8304
              ? (c < 8134
                ? (c < 8118
                  ? (c < 8064
                    ? (c >= 8031 && c <= 8061)
                    : c <= 8116)
                  : (c <= 8124 || (c < 8130
                    ? c == 8126
                    : c <= 8132)))
                : (c <= 8140 || (c < 8160
                  ? (c < 8150
                    ? (c >= 8144 && c <= 8147)
                    : c <= 8155)
                  : (c <= 8172 || (c < 8182
                    ? (c >= 8178 && c <= 8180)
                    : c <= 8188)))))
              : (c <= 8305 || (c < 8458
                ? (c < 8336
                  ? (c < 8319
                    ? (c >= 8308 && c <= 8313)
                    : c <= 8329)
                  : (c <= 8348 || (c < 8455
                    ? c == 8450
                    : c <= 8455)))
                : (c <= 8467 || (c < 8484
                  ? (c < 8473
                    ? c == 8469
                    : c <= 8477)
                  : (c <= 8484 || (c < 8488
                    ? c == 8486
                    : c <= 8488)))))))))
          : (c <= 8493 || (c < 11720
            ? (c < 11517
              ? (c < 9312
                ? (c < 8517
                  ? (c < 8508
                    ? (c >= 8495 && c <= 8505)
                    : c <= 8511)
                  : (c <= 8521 || (c < 8528
                    ? c == 8526
                    : c <= 8585)))
                : (c <= 9371 || (c < 11264
                  ? (c < 10102
                    ? (c >= 9398 && c <= 9471)
                    : c <= 10131)
                  : (c <= 11492 || (c < 11506
                    ? (c >= 11499 && c <= 11502)
                    : c <= 11507)))))
              : (c <= 11517 || (c < 11648
                ? (c < 11565
                  ? (c < 11559
                    ? (c >= 11520 && c <= 11557)
                    : c <= 11559)
                  : (c <= 11565 || (c < 11631
                    ? (c >= 11568 && c <= 11623)
                    : c <= 11631)))
                : (c <= 11670 || (c < 11696
                  ? (c < 11688
                    ? (c >= 11680 && c <= 11686)
                    : c <= 11694)
                  : (c <= 11702 || (c < 11712
                    ? (c >= 11704 && c <= 11710)
                    : c <= 11718)))))))
            : (c <= 11726 || (c < 12540
              ? (c < 12321
                ? (c < 11744
                  ? (c < 11736
                    ? (c >= 11728 && c <= 11734)
                    : c <= 11742)
                  : (c <= 11775 || (c < 12293
                    ? c == 11823
                    : c <= 12295)))
                : (c <= 12329 || (c < 12353
                  ? (c < 12344
                    ? (c >= 12337 && c <= 12341)
                    : c <= 12348)
                  : (c <= 12438 || (c < 12449
                    ? (c >= 12445 && c <= 12447)
                    : c <= 12538)))))
              : (c <= 12543 || (c < 12832
                ? (c < 12690
                  ? (c < 12593
                    ? (c >= 12549 && c <= 12591)
                    : c <= 12686)
                  : (c <= 12693 || (c < 12784
                    ? (c >= 12704 && c <= 12735)
                    : c <= 12799)))
                : (c <= 12841 || (c < 12928
                  ? (c < 12881
                    ? (c >= 12872 && c <= 12879)
                    : c <= 12895)
                  : (c <= 12937 || (c < 13312
                    ? (c >= 12977 && c <= 12991)
                    : c <= 19903)))))))))))))))
    : (c <= 42124 || (c < 70487
      ? (c < 66560
        ? (c < 44032
          ? (c < 43360
            ? (c < 42965
              ? (c < 42623
                ? (c < 42512
                  ? (c < 42240
                    ? (c >= 42192 && c <= 42237)
                    : c <= 42508)
                  : (c <= 42539 || (c < 42612
                    ? (c >= 42560 && c <= 42606)
                    : c <= 42619)))
                : (c <= 42735 || (c < 42891
                  ? (c < 42786
                    ? (c >= 42775 && c <= 42783)
                    : c <= 42888)
                  : (c <= 42954 || (c < 42963
                    ? (c >= 42960 && c <= 42961)
                    : c <= 42963)))))
              : (c <= 42969 || (c < 43205
                ? (c < 43056
                  ? (c < 43015
                    ? (c >= 42994 && c <= 43013)
                    : c <= 43047)
                  : (c <= 43061 || (c < 43136
                    ? (c >= 43072 && c <= 43123)
                    : c <= 43203)))
                : (c <= 43205 || (c < 43259
                  ? (c < 43250
                    ? (c >= 43216 && c <= 43225)
                    : c <= 43255)
                  : (c <= 43259 || (c < 43312
                    ? (c >= 43261 && c <= 43306)
                    : c <= 43346)))))))
            : (c <= 43388 || (c < 43739
              ? (c < 43584
                ? (c < 43471
                  ? (c < 43444
                    ? (c >= 43392 && c <= 43442)
                    : c <= 43455)
                  : (c <= 43481 || (c < 43520
                    ? (c >= 43488 && c <= 43518)
                    : c <= 43574)))
                : (c <= 43597 || (c < 43642
                  ? (c < 43616
                    ? (c >= 43600 && c <= 43609)
                    : c <= 43638)
                  : (c <= 43710 || (c < 43714
                    ? c == 43712
                    : c <= 43714)))))
              : (c <= 43741 || (c < 43808
                ? (c < 43777
                  ? (c < 43762
                    ? (c >= 43744 && c <= 43759)
                    : c <= 43765)
                  : (c <= 43782 || (c < 43793
                    ? (c >= 43785 && c <= 43790)
                    : c <= 43798)))
                : (c <= 43814 || (c < 43868
                  ? (c < 43824
                    ? (c >= 43816 && c <= 43822)
                    : c <= 43866)
                  : (c <= 43881 || (c < 44016
                    ? (c >= 43888 && c <= 44010)
                    : c <= 44025)))))))))
          : (c <= 55203 || (c < 65474
            ? (c < 64323
              ? (c < 64275
                ? (c < 63744
                  ? (c < 55243
                    ? (c >= 55216 && c <= 55238)
                    : c <= 55291)
                  : (c <= 64109 || (c < 64256
                    ? (c >= 64112 && c <= 64217)
                    : c <= 64262)))
                : (c <= 64279 || (c < 64312
                  ? (c < 64298
                    ? (c >= 64285 && c <= 64296)
                    : c <= 64310)
                  : (c <= 64316 || (c < 64320
                    ? c == 64318
                    : c <= 64321)))))
              : (c <= 64324 || (c < 65136
                ? (c < 64848
                  ? (c < 64467
                    ? (c >= 64326 && c <= 64433)
                    : c <= 64829)
                  : (c <= 64911 || (c < 65008
                    ? (c >= 64914 && c <= 64967)
                    : c <= 65019)))
                : (c <= 65140 || (c < 65313
                  ? (c < 65296
                    ? (c >= 65142 && c <= 65276)
                    : c <= 65305)
                  : (c <= 65338 || (c < 65382
                    ? (c >= 65345 && c <= 65370)
                    : c <= 65470)))))))
            : (c <= 65479 || (c < 65856
              ? (c < 65576
                ? (c < 65498
                  ? (c < 65490
                    ? (c >= 65482 && c <= 65487)
                    : c <= 65495)
                  : (c <= 65500 || (c < 65549
                    ? (c >= 65536 && c <= 65547)
                    : c <= 65574)))
                : (c <= 65594 || (c < 65616
                  ? (c < 65599
                    ? (c >= 65596 && c <= 65597)
                    : c <= 65613)
                  : (c <= 65629 || (c < 65799
                    ? (c >= 65664 && c <= 65786)
                    : c <= 65843)))))
              : (c <= 65912 || (c < 66349
                ? (c < 66208
                  ? (c < 66176
                    ? (c >= 65930 && c <= 65931)
                    : c <= 66204)
                  : (c <= 66256 || (c < 66304
                    ? (c >= 66273 && c <= 66299)
                    : c <= 66339)))
                : (c <= 66378 || (c < 66464
                  ? (c < 66432
                    ? (c >= 66384 && c <= 66426)
                    : c <= 66461)
                  : (c <= 66499 || (c < 66513
                    ? (c >= 66504 && c <= 66511)
                    : c <= 66517)))))))))))
        : (c <= 66717 || (c < 68608
          ? (c < 67644
            ? (c < 66995
              ? (c < 66928
                ? (c < 66776
                  ? (c < 66736
                    ? (c >= 66720 && c <= 66729)
                    : c <= 66771)
                  : (c <= 66811 || (c < 66864
                    ? (c >= 66816 && c <= 66855)
                    : c <= 66915)))
                : (c <= 66938 || (c < 66964
                  ? (c < 66956
                    ? (c >= 66940 && c <= 66954)
                    : c <= 66962)
                  : (c <= 66965 || (c < 66979
                    ? (c >= 66967 && c <= 66977)
                    : c <= 66993)))))
              : (c <= 67001 || (c < 67463
                ? (c < 67392
                  ? (c < 67072
                    ? (c >= 67003 && c <= 67004)
                    : c <= 67382)
                  : (c <= 67413 || (c < 67456
                    ? (c >= 67424 && c <= 67431)
                    : c <= 67461)))
                : (c <= 67504 || (c < 67592
                  ? (c < 67584
                    ? (c >= 67506 && c <= 67514)
                    : c <= 67589)
                  : (c <= 67592 || (c < 67639
                    ? (c >= 67594 && c <= 67637)
                    : c <= 67640)))))))
            : (c <= 67644 || (c < 68101
              ? (c < 67828
                ? (c < 67705
                  ? (c < 67672
                    ? (c >= 67647 && c <= 67669)
                    : c <= 67702)
                  : (c <= 67742 || (c < 67808
                    ? (c >= 67751 && c <= 67759)
                    : c <= 67826)))
                : (c <= 67829 || (c < 67968
                  ? (c < 67872
                    ? (c >= 67835 && c <= 67867)
                    : c <= 67897)
                  : (c <= 68023 || (c < 68096
                    ? (c >= 68030 && c <= 68031)
                    : c <= 68099)))))
              : (c <= 68102 || (c < 68288
                ? (c < 68121
                  ? (c < 68117
                    ? (c >= 68108 && c <= 68115)
                    : c <= 68119)
                  : (c <= 68149 || (c < 68224
                    ? (c >= 68192 && c <= 68220)
                    : c <= 68252)))
                : (c <= 68295 || (c < 68416
                  ? (c < 68352
                    ? (c >= 68297 && c <= 68324)
                    : c <= 68405)
                  : (c <= 68437 || (c < 68480
                    ? (c >= 68448 && c <= 68466)
                    : c <= 68497)))))))))
          : (c <= 68680 || (c < 70094
            ? (c < 69600
              ? (c < 69296
                ? (c < 68864
                  ? (c < 68800
                    ? (c >= 68736 && c <= 68786)
                    : c <= 68850)
                  : (c <= 68903 || (c < 69291
                    ? (c >= 69248 && c <= 69289)
                    : c <= 69292)))
                : (c <= 69297 || (c < 69424
                  ? (c < 69415
                    ? (c >= 69376 && c <= 69404)
                    : c <= 69415)
                  : (c <= 69445 || (c < 69552
                    ? (c >= 69488 && c <= 69505)
                    : c <= 69572)))))
              : (c <= 69622 || (c < 69888
                ? (c < 69762
                  ? (c < 69745
                    ? (c >= 69632 && c <= 69701)
                    : c <= 69749)
                  : (c <= 69816 || (c < 69840
                    ? c == 69826
                    : c <= 69864)))
                : (c <= 69938 || (c < 70006
                  ? (c < 69968
                    ? (c >= 69956 && c <= 69959)
                    : c <= 70002)
                  : (c <= 70006 || (c < 70081
                    ? (c >= 70016 && c <= 70079)
                    : c <= 70084)))))))
            : (c <= 70095 || (c < 70320
              ? (c < 70206
                ? (c < 70144
                  ? (c < 70108
                    ? c == 70106
                    : c <= 70108)
                  : (c <= 70161 || (c < 70199
                    ? (c >= 70163 && c <= 70196)
                    : c <= 70199)))
                : (c <= 70206 || (c < 70282
                  ? (c < 70280
                    ? (c >= 70272 && c <= 70278)
                    : c <= 70280)
                  : (c <= 70285 || (c < 70303
                    ? (c >= 70287 && c <= 70301)
                    : c <= 70312)))))
              : (c <= 70376 || (c < 70450
                ? (c < 70415
                  ? (c < 70405
                    ? (c >= 70400 && c <= 70403)
                    : c <= 70412)
                  : (c <= 70416 || (c < 70442
                    ? (c >= 70419 && c <= 70440)
                    : c <= 70448)))
                : (c <= 70451 || (c < 70471
                  ? (c < 70461
                    ? (c >= 70453 && c <= 70457)
                    : c <= 70468)
                  : (c <= 70472 || (c < 70480
                    ? (c >= 70475 && c <= 70476)
                    : c <= 70480)))))))))))))
      : (c <= 70487 || (c < 113792
        ? (c < 72968
          ? (c < 71948
            ? (c < 71168
              ? (c < 70784
                ? (c < 70723
                  ? (c < 70656
                    ? (c >= 70493 && c <= 70499)
                    : c <= 70721)
                  : (c <= 70725 || (c < 70751
                    ? (c >= 70727 && c <= 70730)
                    : c <= 70753)))
                : (c <= 70849 || (c < 71040
                  ? (c < 70855
                    ? (c >= 70852 && c <= 70853)
                    : c <= 70855)
                  : (c <= 71093 || (c < 71128
                    ? (c >= 71096 && c <= 71102)
                    : c <= 71133)))))
              : (c <= 71230 || (c < 71453
                ? (c < 71296
                  ? (c < 71236
                    ? c == 71232
                    : c <= 71236)
                  : (c <= 71349 || (c < 71424
                    ? c == 71352
                    : c <= 71450)))
                : (c <= 71466 || (c < 71840
                  ? (c < 71680
                    ? (c >= 71488 && c <= 71494)
                    : c <= 71736)
                  : (c <= 71903 || (c < 71945
                    ? (c >= 71935 && c <= 71942)
                    : c <= 71945)))))))
            : (c <= 71955 || (c < 72245
              ? (c < 72096
                ? (c < 71991
                  ? (c < 71960
                    ? (c >= 71957 && c <= 71958)
                    : c <= 71989)
                  : (c <= 71992 || (c < 71999
                    ? (c >= 71995 && c <= 71996)
                    : c <= 72002)))
                : (c <= 72103 || (c < 72161
                  ? (c < 72154
                    ? (c >= 72106 && c <= 72151)
                    : c <= 72159)
                  : (c <= 72161 || (c < 72192
                    ? (c >= 72163 && c <= 72164)
                    : c <= 72242)))))
              : (c <= 72254 || (c < 72760
                ? (c < 72368
                  ? (c < 72349
                    ? (c >= 72272 && c <= 72343)
                    : c <= 72349)
                  : (c <= 72440 || (c < 72714
                    ? (c >= 72704 && c <= 72712)
                    : c <= 72758)))
                : (c <= 72766 || (c < 72850
                  ? (c < 72818
                    ? c == 72768
                    : c <= 72847)
                  : (c <= 72871 || (c < 72960
                    ? (c >= 72873 && c <= 72886)
                    : c <= 72966)))))))))
          : (c <= 72969 || (c < 92880
            ? (c < 73112
              ? (c < 73030
                ? (c < 73020
                  ? (c < 73018
                    ? (c >= 72971 && c <= 73014)
                    : c <= 73018)
                  : (c <= 73021 || (c < 73027
                    ? (c >= 73023 && c <= 73025)
                    : c <= 73027)))
                : (c <= 73031 || (c < 73066
                  ? (c < 73063
                    ? (c >= 73056 && c <= 73061)
                    : c <= 73064)
                  : (c <= 73102 || (c < 73107
                    ? (c >= 73104 && c <= 73105)
                    : c <= 73110)))))
              : (c <= 73112 || (c < 77712
                ? (c < 73728
                  ? (c < 73648
                    ? (c >= 73440 && c <= 73462)
                    : c <= 73648)
                  : (c <= 74649 || (c < 74880
                    ? (c >= 74752 && c <= 74862)
                    : c <= 75075)))
                : (c <= 77808 || (c < 92160
                  ? (c < 82944
                    ? (c >= 77824 && c <= 78894)
                    : c <= 83526)
                  : (c <= 92728 || (c < 92784
                    ? (c >= 92736 && c <= 92766)
                    : c <= 92862)))))))
            : (c <= 92909 || (c < 94208
              ? (c < 93952
                ? (c < 93027
                  ? (c < 92992
                    ? (c >= 92928 && c <= 92975)
                    : c <= 92995)
                  : (c <= 93047 || (c < 93760
                    ? (c >= 93053 && c <= 93071)
                    : c <= 93823)))
                : (c <= 94026 || (c < 94176
                  ? (c < 94095
                    ? (c >= 94031 && c <= 94087)
                    : c <= 94111)
                  : (c <= 94177 || (c < 94192
                    ? c == 94179
                    : c <= 94193)))))
              : (c <= 100343 || (c < 110592
                ? (c < 110576
                  ? (c < 101632
                    ? (c >= 100352 && c <= 101589)
                    : c <= 101640)
                  : (c <= 110579 || (c < 110589
                    ? (c >= 110581 && c <= 110587)
                    : c <= 110590)))
                : (c <= 110882 || (c < 110960
                  ? (c < 110948
                    ? (c >= 110928 && c <= 110930)
                    : c <= 110951)
                  : (c <= 111355 || (c < 113776
                    ? (c >= 113664 && c <= 113770)
                    : c <= 113788)))))))))))
        : (c <= 113800 || (c < 124928
          ? (c < 120540
            ? (c < 120005
              ? (c < 119970
                ? (c < 119808
                  ? (c < 113822
                    ? (c >= 113808 && c <= 113817)
                    : c <= 113822)
                  : (c <= 119892 || (c < 119966
                    ? (c >= 119894 && c <= 119964)
                    : c <= 119967)))
                : (c <= 119970 || (c < 119982
                  ? (c < 119977
                    ? (c >= 119973 && c <= 119974)
                    : c <= 119980)
                  : (c <= 119993 || (c < 119997
                    ? c == 119995
                    : c <= 120003)))))
              : (c <= 120069 || (c < 120128
                ? (c < 120086
                  ? (c < 120077
                    ? (c >= 120071 && c <= 120074)
                    : c <= 120084)
                  : (c <= 120092 || (c < 120123
                    ? (c >= 120094 && c <= 120121)
                    : c <= 120126)))
                : (c <= 120132 || (c < 120146
                  ? (c < 120138
                    ? c == 120134
                    : c <= 120144)
                  : (c <= 120485 || (c < 120514
                    ? (c >= 120488 && c <= 120512)
                    : c <= 120538)))))))
            : (c <= 120570 || (c < 122907
              ? (c < 120714
                ? (c < 120630
                  ? (c < 120598
                    ? (c >= 120572 && c <= 120596)
                    : c <= 120628)
                  : (c <= 120654 || (c < 120688
                    ? (c >= 120656 && c <= 120686)
                    : c <= 120712)))
                : (c <= 120744 || (c < 122624
                  ? (c < 120772
                    ? (c >= 120746 && c <= 120770)
                    : c <= 120779)
                  : (c <= 122654 || (c < 122888
                    ? (c >= 122880 && c <= 122886)
                    : c <= 122904)))))
              : (c <= 122913 || (c < 123536
                ? (c < 123136
                  ? (c < 122918
                    ? (c >= 122915 && c <= 122916)
                    : c <= 122922)
                  : (c <= 123180 || (c < 123214
                    ? (c >= 123191 && c <= 123197)
                    : c <= 123214)))
                : (c <= 123565 || (c < 124904
                  ? (c < 124896
                    ? (c >= 123584 && c <= 123627)
                    : c <= 124902)
                  : (c <= 124907 || (c < 124912
                    ? (c >= 124909 && c <= 124910)
                    : c <= 124926)))))))))
          : (c <= 125124 || (c < 126559
            ? (c < 126523
              ? (c < 126497
                ? (c < 125259
                  ? (c < 125255
                    ? (c >= 125184 && c <= 125251)
                    : c <= 125255)
                  : (c <= 125259 || (c < 126469
                    ? (c >= 126464 && c <= 126467)
                    : c <= 126495)))
                : (c <= 126498 || (c < 126505
                  ? (c < 126503
                    ? c == 126500
                    : c <= 126503)
                  : (c <= 126514 || (c < 126521
                    ? (c >= 126516 && c <= 126519)
                    : c <= 126521)))))
              : (c <= 126523 || (c < 126545
                ? (c < 126537
                  ? (c < 126535
                    ? c == 126530
                    : c <= 126535)
                  : (c <= 126537 || (c < 126541
                    ? c == 126539
                    : c <= 126543)))
                : (c <= 126546 || (c < 126553
                  ? (c < 126551
                    ? c == 126548
                    : c <= 126551)
                  : (c <= 126553 || (c < 126557
                    ? c == 126555
                    : c <= 126557)))))))
            : (c <= 126559 || (c < 126635
              ? (c < 126585
                ? (c < 126567
                  ? (c < 126564
                    ? (c >= 126561 && c <= 126562)
                    : c <= 126564)
                  : (c <= 126570 || (c < 126580
                    ? (c >= 126572 && c <= 126578)
                    : c <= 126583)))
                : (c <= 126588 || (c < 126603
                  ? (c < 126592
                    ? c == 126590
                    : c <= 126601)
                  : (c <= 126619 || (c < 126629
                    ? (c >= 126625 && c <= 126627)
                    : c <= 126633)))))
              : (c <= 126651 || (c < 177984
                ? (c < 127344
                  ? (c < 127312
                    ? (c >= 127280 && c <= 127305)
                    : c <= 127337)
                  : (c <= 127369 || (c < 173824
                    ? (c >= 131072 && c <= 173791)
                    : c <= 177976)))
                : (c <= 178205 || (c < 194560
                  ? (c < 183984
                    ? (c >= 178208 && c <= 183969)
                    : c <= 191456)
                  : (c <= 195101 || (c >= 196608 && c <= 201546)))))))))))))))));
}

static inline bool aux_sym_predicate_token2_character_set_5(int32_t c) {
  return (c < 19968
    ? (c < 3520
      ? (c < 2616
        ? (c < 1646
          ? (c < 880
            ? (c < 178
              ? (c < 'A'
                ? (c < '*'
                  ? (c < '&'
                    ? c == '!'
                    : c <= '&')
                  : (c <= '+' || (c < '/'
                    ? c == '-'
                    : c <= '9')))
                : (c <= 'Z' || (c < '|'
                  ? (c < 'b'
                    ? c == '_'
                    : c <= 'z')
                  : (c <= '|' || (c < 170
                    ? c == '~'
                    : c <= 170)))))
              : (c <= 179 || (c < 248
                ? (c < 188
                  ? (c < 185
                    ? c == 181
                    : c <= 186)
                  : (c <= 190 || (c < 216
                    ? (c >= 192 && c <= 214)
                    : c <= 246)))
                : (c <= 705 || (c < 748
                  ? (c < 736
                    ? (c >= 710 && c <= 721)
                    : c <= 740)
                  : (c <= 748 || (c < 837
                    ? c == 750
                    : c <= 837)))))))
            : (c <= 884 || (c < 1369
              ? (c < 908
                ? (c < 895
                  ? (c < 890
                    ? (c >= 886 && c <= 887)
                    : c <= 893)
                  : (c <= 895 || (c < 904
                    ? c == 902
                    : c <= 906)))
                : (c <= 908 || (c < 1015
                  ? (c < 931
                    ? (c >= 910 && c <= 929)
                    : c <= 1013)
                  : (c <= 1153 || (c < 1329
                    ? (c >= 1162 && c <= 1327)
                    : c <= 1366)))))
              : (c <= 1369 || (c < 1479
                ? (c < 1471
                  ? (c < 1456
                    ? (c >= 1376 && c <= 1416)
                    : c <= 1469)
                  : (c <= 1471 || (c < 1476
                    ? (c >= 1473 && c <= 1474)
                    : c <= 1477)))
                : (c <= 1479 || (c < 1552
                  ? (c < 1519
                    ? (c >= 1488 && c <= 1514)
                    : c <= 1522)
                  : (c <= 1562 || (c < 1625
                    ? (c >= 1568 && c <= 1623)
                    : c <= 1641)))))))))
          : (c <= 1747 || (c < 2417
            ? (c < 2112
              ? (c < 1869
                ? (c < 1773
                  ? (c < 1761
                    ? (c >= 1749 && c <= 1756)
                    : c <= 1768)
                  : (c <= 1788 || (c < 1808
                    ? c == 1791
                    : c <= 1855)))
                : (c <= 1969 || (c < 2042
                  ? (c < 2036
                    ? (c >= 1984 && c <= 2026)
                    : c <= 2037)
                  : (c <= 2042 || (c < 2074
                    ? (c >= 2048 && c <= 2071)
                    : c <= 2092)))))
              : (c <= 2136 || (c < 2275
                ? (c < 2185
                  ? (c < 2160
                    ? (c >= 2144 && c <= 2154)
                    : c <= 2183)
                  : (c <= 2190 || (c < 2260
                    ? (c >= 2208 && c <= 2249)
                    : c <= 2271)))
                : (c <= 2281 || (c < 2382
                  ? (c < 2365
                    ? (c >= 2288 && c <= 2363)
                    : c <= 2380)
                  : (c <= 2384 || (c < 2406
                    ? (c >= 2389 && c <= 2403)
                    : c <= 2415)))))))
            : (c <= 2435 || (c < 2524
              ? (c < 2486
                ? (c < 2451
                  ? (c < 2447
                    ? (c >= 2437 && c <= 2444)
                    : c <= 2448)
                  : (c <= 2472 || (c < 2482
                    ? (c >= 2474 && c <= 2480)
                    : c <= 2482)))
                : (c <= 2489 || (c < 2507
                  ? (c < 2503
                    ? (c >= 2493 && c <= 2500)
                    : c <= 2504)
                  : (c <= 2508 || (c < 2519
                    ? c == 2510
                    : c <= 2519)))))
              : (c <= 2525 || (c < 2565
                ? (c < 2548
                  ? (c < 2534
                    ? (c >= 2527 && c <= 2531)
                    : c <= 2545)
                  : (c <= 2553 || (c < 2561
                    ? c == 2556
                    : c <= 2563)))
                : (c <= 2570 || (c < 2602
                  ? (c < 2579
                    ? (c >= 2575 && c <= 2576)
                    : c <= 2600)
                  : (c <= 2608 || (c < 2613
                    ? (c >= 2610 && c <= 2611)
                    : c <= 2614)))))))))))
        : (c <= 2617 || (c < 3014
          ? (c < 2831
            ? (c < 2730
              ? (c < 2654
                ? (c < 2635
                  ? (c < 2631
                    ? (c >= 2622 && c <= 2626)
                    : c <= 2632)
                  : (c <= 2636 || (c < 2649
                    ? c == 2641
                    : c <= 2652)))
                : (c <= 2654 || (c < 2693
                  ? (c < 2689
                    ? (c >= 2662 && c <= 2677)
                    : c <= 2691)
                  : (c <= 2701 || (c < 2707
                    ? (c >= 2703 && c <= 2705)
                    : c <= 2728)))))
              : (c <= 2736 || (c < 2768
                ? (c < 2749
                  ? (c < 2741
                    ? (c >= 2738 && c <= 2739)
                    : c <= 2745)
                  : (c <= 2757 || (c < 2763
                    ? (c >= 2759 && c <= 2761)
                    : c <= 2764)))
                : (c <= 2768 || (c < 2809
                  ? (c < 2790
                    ? (c >= 2784 && c <= 2787)
                    : c <= 2799)
                  : (c <= 2812 || (c < 2821
                    ? (c >= 2817 && c <= 2819)
                    : c <= 2828)))))))
            : (c <= 2832 || (c < 2929
              ? (c < 2887
                ? (c < 2866
                  ? (c < 2858
                    ? (c >= 2835 && c <= 2856)
                    : c <= 2864)
                  : (c <= 2867 || (c < 2877
                    ? (c >= 2869 && c <= 2873)
                    : c <= 2884)))
                : (c <= 2888 || (c < 2908
                  ? (c < 2902
                    ? (c >= 2891 && c <= 2892)
                    : c <= 2903)
                  : (c <= 2909 || (c < 2918
                    ? (c >= 2911 && c <= 2915)
                    : c <= 2927)))))
              : (c <= 2935 || (c < 2972
                ? (c < 2958
                  ? (c < 2949
                    ? (c >= 2946 && c <= 2947)
                    : c <= 2954)
                  : (c <= 2960 || (c < 2969
                    ? (c >= 2962 && c <= 2965)
                    : c <= 2970)))
                : (c <= 2972 || (c < 2984
                  ? (c < 2979
                    ? (c >= 2974 && c <= 2975)
                    : c <= 2980)
                  : (c <= 2986 || (c < 3006
                    ? (c >= 2990 && c <= 3001)
                    : c <= 3010)))))))))
          : (c <= 3016 || (c < 3253
            ? (c < 3146
              ? (c < 3077
                ? (c < 3031
                  ? (c < 3024
                    ? (c >= 3018 && c <= 3020)
                    : c <= 3024)
                  : (c <= 3031 || (c < 3072
                    ? (c >= 3046 && c <= 3058)
                    : c <= 3075)))
                : (c <= 3084 || (c < 3114
                  ? (c < 3090
                    ? (c >= 3086 && c <= 3088)
                    : c <= 3112)
                  : (c <= 3129 || (c < 3142
                    ? (c >= 3133 && c <= 3140)
                    : c <= 3144)))))
              : (c <= 3148 || (c < 3192
                ? (c < 3165
                  ? (c < 3160
                    ? (c >= 3157 && c <= 3158)
                    : c <= 3162)
                  : (c <= 3165 || (c < 3174
                    ? (c >= 3168 && c <= 3171)
                    : c <= 3183)))
                : (c <= 3198 || (c < 3214
                  ? (c < 3205
                    ? (c >= 3200 && c <= 3203)
                    : c <= 3212)
                  : (c <= 3216 || (c < 3242
                    ? (c >= 3218 && c <= 3240)
                    : c <= 3251)))))))
            : (c <= 3257 || (c < 3389
              ? (c < 3296
                ? (c < 3274
                  ? (c < 3270
                    ? (c >= 3261 && c <= 3268)
                    : c <= 3272)
                  : (c <= 3276 || (c < 3293
                    ? (c >= 3285 && c <= 3286)
                    : c <= 3294)))
                : (c <= 3299 || (c < 3328
                  ? (c < 3313
                    ? (c >= 3302 && c <= 3311)
                    : c <= 3314)
                  : (c <= 3340 || (c < 3346
                    ? (c >= 3342 && c <= 3344)
                    : c <= 3386)))))
              : (c <= 3396 || (c < 3450
                ? (c < 3406
                  ? (c < 3402
                    ? (c >= 3398 && c <= 3400)
                    : c <= 3404)
                  : (c <= 3406 || (c < 3430
                    ? (c >= 3412 && c <= 3427)
                    : c <= 3448)))
                : (c <= 3455 || (c < 3482
                  ? (c < 3461
                    ? (c >= 3457 && c <= 3459)
                    : c <= 3478)
                  : (c <= 3505 || (c < 3517
                    ? (c >= 3507 && c <= 3515)
                    : c <= 3517)))))))))))))
      : (c <= 3526 || (c < 6981
        ? (c < 4802
          ? (c < 3904
            ? (c < 3718
              ? (c < 3585
                ? (c < 3544
                  ? (c < 3542
                    ? (c >= 3535 && c <= 3540)
                    : c <= 3542)
                  : (c <= 3551 || (c < 3570
                    ? (c >= 3558 && c <= 3567)
                    : c <= 3571)))
                : (c <= 3642 || (c < 3664
                  ? (c < 3661
                    ? (c >= 3648 && c <= 3654)
                    : c <= 3661)
                  : (c <= 3673 || (c < 3716
                    ? (c >= 3713 && c <= 3714)
                    : c <= 3716)))))
              : (c <= 3722 || (c < 3782
                ? (c < 3751
                  ? (c < 3749
                    ? (c >= 3724 && c <= 3747)
                    : c <= 3749)
                  : (c <= 3769 || (c < 3776
                    ? (c >= 3771 && c <= 3773)
                    : c <= 3780)))
                : (c <= 3782 || (c < 3804
                  ? (c < 3792
                    ? c == 3789
                    : c <= 3801)
                  : (c <= 3807 || (c < 3872
                    ? c == 3840
                    : c <= 3891)))))))
            : (c <= 3911 || (c < 4304
              ? (c < 4152
                ? (c < 3976
                  ? (c < 3953
                    ? (c >= 3913 && c <= 3948)
                    : c <= 3969)
                  : (c <= 3991 || (c < 4096
                    ? (c >= 3993 && c <= 4028)
                    : c <= 4150)))
                : (c <= 4152 || (c < 4256
                  ? (c < 4176
                    ? (c >= 4155 && c <= 4169)
                    : c <= 4253)
                  : (c <= 4293 || (c < 4301
                    ? c == 4295
                    : c <= 4301)))))
              : (c <= 4346 || (c < 4704
                ? (c < 4688
                  ? (c < 4682
                    ? (c >= 4348 && c <= 4680)
                    : c <= 4685)
                  : (c <= 4694 || (c < 4698
                    ? c == 4696
                    : c <= 4701)))
                : (c <= 4744 || (c < 4786
                  ? (c < 4752
                    ? (c >= 4746 && c <= 4749)
                    : c <= 4784)
                  : (c <= 4789 || (c < 4800
                    ? (c >= 4792 && c <= 4798)
                    : c <= 4800)))))))))
          : (c <= 4805 || (c < 6112
            ? (c < 5792
              ? (c < 4992
                ? (c < 4882
                  ? (c < 4824
                    ? (c >= 4808 && c <= 4822)
                    : c <= 4880)
                  : (c <= 4885 || (c < 4969
                    ? (c >= 4888 && c <= 4954)
                    : c <= 4988)))
                : (c <= 5007 || (c < 5121
                  ? (c < 5112
                    ? (c >= 5024 && c <= 5109)
                    : c <= 5117)
                  : (c <= 5740 || (c < 5761
                    ? (c >= 5743 && c <= 5759)
                    : c <= 5786)))))
              : (c <= 5866 || (c < 5998
                ? (c < 5919
                  ? (c < 5888
                    ? (c >= 5870 && c <= 5880)
                    : c <= 5907)
                  : (c <= 5939 || (c < 5984
                    ? (c >= 5952 && c <= 5971)
                    : c <= 5996)))
                : (c <= 6000 || (c < 6070
                  ? (c < 6016
                    ? (c >= 6002 && c <= 6003)
                    : c <= 6067)
                  : (c <= 6088 || (c < 6108
                    ? c == 6103
                    : c <= 6108)))))))
            : (c <= 6121 || (c < 6576
              ? (c < 6400
                ? (c < 6176
                  ? (c < 6160
                    ? (c >= 6128 && c <= 6137)
                    : c <= 6169)
                  : (c <= 6264 || (c < 6320
                    ? (c >= 6272 && c <= 6314)
                    : c <= 6389)))
                : (c <= 6430 || (c < 6470
                  ? (c < 6448
                    ? (c >= 6432 && c <= 6443)
                    : c <= 6456)
                  : (c <= 6509 || (c < 6528
                    ? (c >= 6512 && c <= 6516)
                    : c <= 6571)))))
              : (c <= 6601 || (c < 6800
                ? (c < 6688
                  ? (c < 6656
                    ? (c >= 6608 && c <= 6618)
                    : c <= 6683)
                  : (c <= 6750 || (c < 6784
                    ? (c >= 6753 && c <= 6772)
                    : c <= 6793)))
                : (c <= 6809 || (c < 6860
                  ? (c < 6847
                    ? c == 6823
                    : c <= 6848)
                  : (c <= 6862 || (c < 6965
                    ? (c >= 6912 && c <= 6963)
                    : c <= 6979)))))))))))
        : (c <= 6988 || (c < 8490
          ? (c < 8029
            ? (c < 7406
              ? (c < 7232
                ? (c < 7084
                  ? (c < 7040
                    ? (c >= 6992 && c <= 7001)
                    : c <= 7081)
                  : (c <= 7141 || (c < 7168
                    ? (c >= 7143 && c <= 7153)
                    : c <= 7222)))
                : (c <= 7241 || (c < 7312
                  ? (c < 7296
                    ? (c >= 7245 && c <= 7293)
                    : c <= 7304)
                  : (c <= 7354 || (c < 7401
                    ? (c >= 7357 && c <= 7359)
                    : c <= 7404)))))
              : (c <= 7411 || (c < 7960
                ? (c < 7424
                  ? (c < 7418
                    ? (c >= 7413 && c <= 7414)
                    : c <= 7418)
                  : (c <= 7615 || (c < 7680
                    ? (c >= 7655 && c <= 7668)
                    : c <= 7957)))
                : (c <= 7965 || (c < 8016
                  ? (c < 8008
                    ? (c >= 7968 && c <= 8005)
                    : c <= 8013)
                  : (c <= 8023 || (c < 8027
                    ? c == 8025
                    : c <= 8027)))))))
            : (c <= 8029 || (c < 8304
              ? (c < 8134
                ? (c < 8118
                  ? (c < 8064
                    ? (c >= 8031 && c <= 8061)
                    : c <= 8116)
                  : (c <= 8124 || (c < 8130
                    ? c == 8126
                    : c <= 8132)))
                : (c <= 8140 || (c < 8160
                  ? (c < 8150
                    ? (c >= 8144 && c <= 8147)
                    : c <= 8155)
                  : (c <= 8172 || (c < 8182
                    ? (c >= 8178 && c <= 8180)
                    : c <= 8188)))))
              : (c <= 8305 || (c < 8458
                ? (c < 8336
                  ? (c < 8319
                    ? (c >= 8308 && c <= 8313)
                    : c <= 8329)
                  : (c <= 8348 || (c < 8455
                    ? c == 8450
                    : c <= 8455)))
                : (c <= 8467 || (c < 8484
                  ? (c < 8473
                    ? c == 8469
                    : c <= 8477)
                  : (c <= 8484 || (c < 8488
                    ? c == 8486
                    : c <= 8488)))))))))
          : (c <= 8493 || (c < 11720
            ? (c < 11517
              ? (c < 9312
                ? (c < 8517
                  ? (c < 8508
                    ? (c >= 8495 && c <= 8505)
                    : c <= 8511)
                  : (c <= 8521 || (c < 8528
                    ? c == 8526
                    : c <= 8585)))
                : (c <= 9371 || (c < 11264
                  ? (c < 10102
                    ? (c >= 9398 && c <= 9471)
                    : c <= 10131)
                  : (c <= 11492 || (c < 11506
                    ? (c >= 11499 && c <= 11502)
                    : c <= 11507)))))
              : (c <= 11517 || (c < 11648
                ? (c < 11565
                  ? (c < 11559
                    ? (c >= 11520 && c <= 11557)
                    : c <= 11559)
                  : (c <= 11565 || (c < 11631
                    ? (c >= 11568 && c <= 11623)
                    : c <= 11631)))
                : (c <= 11670 || (c < 11696
                  ? (c < 11688
                    ? (c >= 11680 && c <= 11686)
                    : c <= 11694)
                  : (c <= 11702 || (c < 11712
                    ? (c >= 11704 && c <= 11710)
                    : c <= 11718)))))))
            : (c <= 11726 || (c < 12540
              ? (c < 12321
                ? (c < 11744
                  ? (c < 11736
                    ? (c >= 11728 && c <= 11734)
                    : c <= 11742)
                  : (c <= 11775 || (c < 12293
                    ? c == 11823
                    : c <= 12295)))
                : (c <= 12329 || (c < 12353
                  ? (c < 12344
                    ? (c >= 12337 && c <= 12341)
                    : c <= 12348)
                  : (c <= 12438 || (c < 12449
                    ? (c >= 12445 && c <= 12447)
                    : c <= 12538)))))
              : (c <= 12543 || (c < 12832
                ? (c < 12690
                  ? (c < 12593
                    ? (c >= 12549 && c <= 12591)
                    : c <= 12686)
                  : (c <= 12693 || (c < 12784
                    ? (c >= 12704 && c <= 12735)
                    : c <= 12799)))
                : (c <= 12841 || (c < 12928
                  ? (c < 12881
                    ? (c >= 12872 && c <= 12879)
                    : c <= 12895)
                  : (c <= 12937 || (c < 13312
                    ? (c >= 12977 && c <= 12991)
                    : c <= 19903)))))))))))))))
    : (c <= 42124 || (c < 70487
      ? (c < 66560
        ? (c < 44032
          ? (c < 43360
            ? (c < 42965
              ? (c < 42623
                ? (c < 42512
                  ? (c < 42240
                    ? (c >= 42192 && c <= 42237)
                    : c <= 42508)
                  : (c <= 42539 || (c < 42612
                    ? (c >= 42560 && c <= 42606)
                    : c <= 42619)))
                : (c <= 42735 || (c < 42891
                  ? (c < 42786
                    ? (c >= 42775 && c <= 42783)
                    : c <= 42888)
                  : (c <= 42954 || (c < 42963
                    ? (c >= 42960 && c <= 42961)
                    : c <= 42963)))))
              : (c <= 42969 || (c < 43205
                ? (c < 43056
                  ? (c < 43015
                    ? (c >= 42994 && c <= 43013)
                    : c <= 43047)
                  : (c <= 43061 || (c < 43136
                    ? (c >= 43072 && c <= 43123)
                    : c <= 43203)))
                : (c <= 43205 || (c < 43259
                  ? (c < 43250
                    ? (c >= 43216 && c <= 43225)
                    : c <= 43255)
                  : (c <= 43259 || (c < 43312
                    ? (c >= 43261 && c <= 43306)
                    : c <= 43346)))))))
            : (c <= 43388 || (c < 43739
              ? (c < 43584
                ? (c < 43471
                  ? (c < 43444
                    ? (c >= 43392 && c <= 43442)
                    : c <= 43455)
                  : (c <= 43481 || (c < 43520
                    ? (c >= 43488 && c <= 43518)
                    : c <= 43574)))
                : (c <= 43597 || (c < 43642
                  ? (c < 43616
                    ? (c >= 43600 && c <= 43609)
                    : c <= 43638)
                  : (c <= 43710 || (c < 43714
                    ? c == 43712
                    : c <= 43714)))))
              : (c <= 43741 || (c < 43808
                ? (c < 43777
                  ? (c < 43762
                    ? (c >= 43744 && c <= 43759)
                    : c <= 43765)
                  : (c <= 43782 || (c < 43793
                    ? (c >= 43785 && c <= 43790)
                    : c <= 43798)))
                : (c <= 43814 || (c < 43868
                  ? (c < 43824
                    ? (c >= 43816 && c <= 43822)
                    : c <= 43866)
                  : (c <= 43881 || (c < 44016
                    ? (c >= 43888 && c <= 44010)
                    : c <= 44025)))))))))
          : (c <= 55203 || (c < 65474
            ? (c < 64323
              ? (c < 64275
                ? (c < 63744
                  ? (c < 55243
                    ? (c >= 55216 && c <= 55238)
                    : c <= 55291)
                  : (c <= 64109 || (c < 64256
                    ? (c >= 64112 && c <= 64217)
                    : c <= 64262)))
                : (c <= 64279 || (c < 64312
                  ? (c < 64298
                    ? (c >= 64285 && c <= 64296)
                    : c <= 64310)
                  : (c <= 64316 || (c < 64320
                    ? c == 64318
                    : c <= 64321)))))
              : (c <= 64324 || (c < 65136
                ? (c < 64848
                  ? (c < 64467
                    ? (c >= 64326 && c <= 64433)
                    : c <= 64829)
                  : (c <= 64911 || (c < 65008
                    ? (c >= 64914 && c <= 64967)
                    : c <= 65019)))
                : (c <= 65140 || (c < 65313
                  ? (c < 65296
                    ? (c >= 65142 && c <= 65276)
                    : c <= 65305)
                  : (c <= 65338 || (c < 65382
                    ? (c >= 65345 && c <= 65370)
                    : c <= 65470)))))))
            : (c <= 65479 || (c < 65856
              ? (c < 65576
                ? (c < 65498
                  ? (c < 65490
                    ? (c >= 65482 && c <= 65487)
                    : c <= 65495)
                  : (c <= 65500 || (c < 65549
                    ? (c >= 65536 && c <= 65547)
                    : c <= 65574)))
                : (c <= 65594 || (c < 65616
                  ? (c < 65599
                    ? (c >= 65596 && c <= 65597)
                    : c <= 65613)
                  : (c <= 65629 || (c < 65799
                    ? (c >= 65664 && c <= 65786)
                    : c <= 65843)))))
              : (c <= 65912 || (c < 66349
                ? (c < 66208
                  ? (c < 66176
                    ? (c >= 65930 && c <= 65931)
                    : c <= 66204)
                  : (c <= 66256 || (c < 66304
                    ? (c >= 66273 && c <= 66299)
                    : c <= 66339)))
                : (c <= 66378 || (c < 66464
                  ? (c < 66432
                    ? (c >= 66384 && c <= 66426)
                    : c <= 66461)
                  : (c <= 66499 || (c < 66513
                    ? (c >= 66504 && c <= 66511)
                    : c <= 66517)))))))))))
        : (c <= 66717 || (c < 68608
          ? (c < 67644
            ? (c < 66995
              ? (c < 66928
                ? (c < 66776
                  ? (c < 66736
                    ? (c >= 66720 && c <= 66729)
                    : c <= 66771)
                  : (c <= 66811 || (c < 66864
                    ? (c >= 66816 && c <= 66855)
                    : c <= 66915)))
                : (c <= 66938 || (c < 66964
                  ? (c < 66956
                    ? (c >= 66940 && c <= 66954)
                    : c <= 66962)
                  : (c <= 66965 || (c < 66979
                    ? (c >= 66967 && c <= 66977)
                    : c <= 66993)))))
              : (c <= 67001 || (c < 67463
                ? (c < 67392
                  ? (c < 67072
                    ? (c >= 67003 && c <= 67004)
                    : c <= 67382)
                  : (c <= 67413 || (c < 67456
                    ? (c >= 67424 && c <= 67431)
                    : c <= 67461)))
                : (c <= 67504 || (c < 67592
                  ? (c < 67584
                    ? (c >= 67506 && c <= 67514)
                    : c <= 67589)
                  : (c <= 67592 || (c < 67639
                    ? (c >= 67594 && c <= 67637)
                    : c <= 67640)))))))
            : (c <= 67644 || (c < 68101
              ? (c < 67828
                ? (c < 67705
                  ? (c < 67672
                    ? (c >= 67647 && c <= 67669)
                    : c <= 67702)
                  : (c <= 67742 || (c < 67808
                    ? (c >= 67751 && c <= 67759)
                    : c <= 67826)))
                : (c <= 67829 || (c < 67968
                  ? (c < 67872
                    ? (c >= 67835 && c <= 67867)
                    : c <= 67897)
                  : (c <= 68023 || (c < 68096
                    ? (c >= 68030 && c <= 68031)
                    : c <= 68099)))))
              : (c <= 68102 || (c < 68288
                ? (c < 68121
                  ? (c < 68117
                    ? (c >= 68108 && c <= 68115)
                    : c <= 68119)
                  : (c <= 68149 || (c < 68224
                    ? (c >= 68192 && c <= 68220)
                    : c <= 68252)))
                : (c <= 68295 || (c < 68416
                  ? (c < 68352
                    ? (c >= 68297 && c <= 68324)
                    : c <= 68405)
                  : (c <= 68437 || (c < 68480
                    ? (c >= 68448 && c <= 68466)
                    : c <= 68497)))))))))
          : (c <= 68680 || (c < 70094
            ? (c < 69600
              ? (c < 69296
                ? (c < 68864
                  ? (c < 68800
                    ? (c >= 68736 && c <= 68786)
                    : c <= 68850)
                  : (c <= 68903 || (c < 69291
                    ? (c >= 69248 && c <= 69289)
                    : c <= 69292)))
                : (c <= 69297 || (c < 69424
                  ? (c < 69415
                    ? (c >= 69376 && c <= 69404)
                    : c <= 69415)
                  : (c <= 69445 || (c < 69552
                    ? (c >= 69488 && c <= 69505)
                    : c <= 69572)))))
              : (c <= 69622 || (c < 69888
                ? (c < 69762
                  ? (c < 69745
                    ? (c >= 69632 && c <= 69701)
                    : c <= 69749)
                  : (c <= 69816 || (c < 69840
                    ? c == 69826
                    : c <= 69864)))
                : (c <= 69938 || (c < 70006
                  ? (c < 69968
                    ? (c >= 69956 && c <= 69959)
                    : c <= 70002)
                  : (c <= 70006 || (c < 70081
                    ? (c >= 70016 && c <= 70079)
                    : c <= 70084)))))))
            : (c <= 70095 || (c < 70320
              ? (c < 70206
                ? (c < 70144
                  ? (c < 70108
                    ? c == 70106
                    : c <= 70108)
                  : (c <= 70161 || (c < 70199
                    ? (c >= 70163 && c <= 70196)
                    : c <= 70199)))
                : (c <= 70206 || (c < 70282
                  ? (c < 70280
                    ? (c >= 70272 && c <= 70278)
                    : c <= 70280)
                  : (c <= 70285 || (c < 70303
                    ? (c >= 70287 && c <= 70301)
                    : c <= 70312)))))
              : (c <= 70376 || (c < 70450
                ? (c < 70415
                  ? (c < 70405
                    ? (c >= 70400 && c <= 70403)
                    : c <= 70412)
                  : (c <= 70416 || (c < 70442
                    ? (c >= 70419 && c <= 70440)
                    : c <= 70448)))
                : (c <= 70451 || (c < 70471
                  ? (c < 70461
                    ? (c >= 70453 && c <= 70457)
                    : c <= 70468)
                  : (c <= 70472 || (c < 70480
                    ? (c >= 70475 && c <= 70476)
                    : c <= 70480)))))))))))))
      : (c <= 70487 || (c < 113792
        ? (c < 72968
          ? (c < 71948
            ? (c < 71168
              ? (c < 70784
                ? (c < 70723
                  ? (c < 70656
                    ? (c >= 70493 && c <= 70499)
                    : c <= 70721)
                  : (c <= 70725 || (c < 70751
                    ? (c >= 70727 && c <= 70730)
                    : c <= 70753)))
                : (c <= 70849 || (c < 71040
                  ? (c < 70855
                    ? (c >= 70852 && c <= 70853)
                    : c <= 70855)
                  : (c <= 71093 || (c < 71128
                    ? (c >= 71096 && c <= 71102)
                    : c <= 71133)))))
              : (c <= 71230 || (c < 71453
                ? (c < 71296
                  ? (c < 71236
                    ? c == 71232
                    : c <= 71236)
                  : (c <= 71349 || (c < 71424
                    ? c == 71352
                    : c <= 71450)))
                : (c <= 71466 || (c < 71840
                  ? (c < 71680
                    ? (c >= 71488 && c <= 71494)
                    : c <= 71736)
                  : (c <= 71903 || (c < 71945
                    ? (c >= 71935 && c <= 71942)
                    : c <= 71945)))))))
            : (c <= 71955 || (c < 72245
              ? (c < 72096
                ? (c < 71991
                  ? (c < 71960
                    ? (c >= 71957 && c <= 71958)
                    : c <= 71989)
                  : (c <= 71992 || (c < 71999
                    ? (c >= 71995 && c <= 71996)
                    : c <= 72002)))
                : (c <= 72103 || (c < 72161
                  ? (c < 72154
                    ? (c >= 72106 && c <= 72151)
                    : c <= 72159)
                  : (c <= 72161 || (c < 72192
                    ? (c >= 72163 && c <= 72164)
                    : c <= 72242)))))
              : (c <= 72254 || (c < 72760
                ? (c < 72368
                  ? (c < 72349
                    ? (c >= 72272 && c <= 72343)
                    : c <= 72349)
                  : (c <= 72440 || (c < 72714
                    ? (c >= 72704 && c <= 72712)
                    : c <= 72758)))
                : (c <= 72766 || (c < 72850
                  ? (c < 72818
                    ? c == 72768
                    : c <= 72847)
                  : (c <= 72871 || (c < 72960
                    ? (c >= 72873 && c <= 72886)
                    : c <= 72966)))))))))
          : (c <= 72969 || (c < 92880
            ? (c < 73112
              ? (c < 73030
                ? (c < 73020
                  ? (c < 73018
                    ? (c >= 72971 && c <= 73014)
                    : c <= 73018)
                  : (c <= 73021 || (c < 73027
                    ? (c >= 73023 && c <= 73025)
                    : c <= 73027)))
                : (c <= 73031 || (c < 73066
                  ? (c < 73063
                    ? (c >= 73056 && c <= 73061)
                    : c <= 73064)
                  : (c <= 73102 || (c < 73107
                    ? (c >= 73104 && c <= 73105)
                    : c <= 73110)))))
              : (c <= 73112 || (c < 77712
                ? (c < 73728
                  ? (c < 73648
                    ? (c >= 73440 && c <= 73462)
                    : c <= 73648)
                  : (c <= 74649 || (c < 74880
                    ? (c >= 74752 && c <= 74862)
                    : c <= 75075)))
                : (c <= 77808 || (c < 92160
                  ? (c < 82944
                    ? (c >= 77824 && c <= 78894)
                    : c <= 83526)
                  : (c <= 92728 || (c < 92784
                    ? (c >= 92736 && c <= 92766)
                    : c <= 92862)))))))
            : (c <= 92909 || (c < 94208
              ? (c < 93952
                ? (c < 93027
                  ? (c < 92992
                    ? (c >= 92928 && c <= 92975)
                    : c <= 92995)
                  : (c <= 93047 || (c < 93760
                    ? (c >= 93053 && c <= 93071)
                    : c <= 93823)))
                : (c <= 94026 || (c < 94176
                  ? (c < 94095
                    ? (c >= 94031 && c <= 94087)
                    : c <= 94111)
                  : (c <= 94177 || (c < 94192
                    ? c == 94179
                    : c <= 94193)))))
              : (c <= 100343 || (c < 110592
                ? (c < 110576
                  ? (c < 101632
                    ? (c >= 100352 && c <= 101589)
                    : c <= 101640)
                  : (c <= 110579 || (c < 110589
                    ? (c >= 110581 && c <= 110587)
                    : c <= 110590)))
                : (c <= 110882 || (c < 110960
                  ? (c < 110948
                    ? (c >= 110928 && c <= 110930)
                    : c <= 110951)
                  : (c <= 111355 || (c < 113776
                    ? (c >= 113664 && c <= 113770)
                    : c <= 113788)))))))))))
        : (c <= 113800 || (c < 124928
          ? (c < 120540
            ? (c < 120005
              ? (c < 119970
                ? (c < 119808
                  ? (c < 113822
                    ? (c >= 113808 && c <= 113817)
                    : c <= 113822)
                  : (c <= 119892 || (c < 119966
                    ? (c >= 119894 && c <= 119964)
                    : c <= 119967)))
                : (c <= 119970 || (c < 119982
                  ? (c < 119977
                    ? (c >= 119973 && c <= 119974)
                    : c <= 119980)
                  : (c <= 119993 || (c < 119997
                    ? c == 119995
                    : c <= 120003)))))
              : (c <= 120069 || (c < 120128
                ? (c < 120086
                  ? (c < 120077
                    ? (c >= 120071 && c <= 120074)
                    : c <= 120084)
                  : (c <= 120092 || (c < 120123
                    ? (c >= 120094 && c <= 120121)
                    : c <= 120126)))
                : (c <= 120132 || (c < 120146
                  ? (c < 120138
                    ? c == 120134
                    : c <= 120144)
                  : (c <= 120485 || (c < 120514
                    ? (c >= 120488 && c <= 120512)
                    : c <= 120538)))))))
            : (c <= 120570 || (c < 122907
              ? (c < 120714
                ? (c < 120630
                  ? (c < 120598
                    ? (c >= 120572 && c <= 120596)
                    : c <= 120628)
                  : (c <= 120654 || (c < 120688
                    ? (c >= 120656 && c <= 120686)
                    : c <= 120712)))
                : (c <= 120744 || (c < 122624
                  ? (c < 120772
                    ? (c >= 120746 && c <= 120770)
                    : c <= 120779)
                  : (c <= 122654 || (c < 122888
                    ? (c >= 122880 && c <= 122886)
                    : c <= 122904)))))
              : (c <= 122913 || (c < 123536
                ? (c < 123136
                  ? (c < 122918
                    ? (c >= 122915 && c <= 122916)
                    : c <= 122922)
                  : (c <= 123180 || (c < 123214
                    ? (c >= 123191 && c <= 123197)
                    : c <= 123214)))
                : (c <= 123565 || (c < 124904
                  ? (c < 124896
                    ? (c >= 123584 && c <= 123627)
                    : c <= 124902)
                  : (c <= 124907 || (c < 124912
                    ? (c >= 124909 && c <= 124910)
                    : c <= 124926)))))))))
          : (c <= 125124 || (c < 126559
            ? (c < 126523
              ? (c < 126497
                ? (c < 125259
                  ? (c < 125255
                    ? (c >= 125184 && c <= 125251)
                    : c <= 125255)
                  : (c <= 125259 || (c < 126469
                    ? (c >= 126464 && c <= 126467)
                    : c <= 126495)))
                : (c <= 126498 || (c < 126505
                  ? (c < 126503
                    ? c == 126500
                    : c <= 126503)
                  : (c <= 126514 || (c < 126521
                    ? (c >= 126516 && c <= 126519)
                    : c <= 126521)))))
              : (c <= 126523 || (c < 126545
                ? (c < 126537
                  ? (c < 126535
                    ? c == 126530
                    : c <= 126535)
                  : (c <= 126537 || (c < 126541
                    ? c == 126539
                    : c <= 126543)))
                : (c <= 126546 || (c < 126553
                  ? (c < 126551
                    ? c == 126548
                    : c <= 126551)
                  : (c <= 126553 || (c < 126557
                    ? c == 126555
                    : c <= 126557)))))))
            : (c <= 126559 || (c < 126635
              ? (c < 126585
                ? (c < 126567
                  ? (c < 126564
                    ? (c >= 126561 && c <= 126562)
                    : c <= 126564)
                  : (c <= 126570 || (c < 126580
                    ? (c >= 126572 && c <= 126578)
                    : c <= 126583)))
                : (c <= 126588 || (c < 126603
                  ? (c < 126592
                    ? c == 126590
                    : c <= 126601)
                  : (c <= 126619 || (c < 126629
                    ? (c >= 126625 && c <= 126627)
                    : c <= 126633)))))
              : (c <= 126651 || (c < 177984
                ? (c < 127344
                  ? (c < 127312
                    ? (c >= 127280 && c <= 127305)
                    : c <= 127337)
                  : (c <= 127369 || (c < 173824
                    ? (c >= 131072 && c <= 173791)
                    : c <= 177976)))
                : (c <= 178205 || (c < 194560
                  ? (c < 183984
                    ? (c >= 178208 && c <= 183969)
                    : c <= 191456)
                  : (c <= 195101 || (c >= 196608 && c <= 201546)))))))))))))))));
}

static inline bool sym_identifier_character_set_1(int32_t c) {
  return (c < 8518
    ? (c < 1376
      ? (c < 454
        ? (c < '|'
          ? (c < '-'
            ? (c < '&'
              ? c == '!'
              : (c <= '&' || (c >= '*' && c <= '+')))
            : (c <= '-' || (c < '_'
              ? c == '/'
              : (c <= '_' || (c >= 'a' && c <= 'z')))))
          : (c <= '|' || (c < 186
            ? (c < 170
              ? c == '~'
              : (c <= 170 || c == 181))
            : (c <= 186 || (c < 248
              ? (c >= 223 && c <= 246)
              : (c <= 442 || (c >= 445 && c <= 447)))))))
        : (c <= 454 || (c < 881
          ? (c < 661
            ? (c < 460
              ? c == 457
              : (c <= 496 || (c >= 499 && c <= 659)))
            : (c <= 696 || (c < 736
              ? (c >= 704 && c <= 705)
              : (c <= 740 || c == 837))))
          : (c <= 883 || (c < 940
            ? (c < 890
              ? c == 887
              : (c <= 893 || c == 912))
            : (c <= 1013 || (c < 1163
              ? (c >= 1016 && c <= 1153)
              : c <= 1327)))))))
      : (c <= 1416 || (c < 8126
        ? (c < 8016
          ? (c < 7296
            ? (c < 4349
              ? (c >= 4304 && c <= 4346)
              : (c <= 4351 || (c >= 5112 && c <= 5117)))
            : (c <= 7304 || (c < 7681
              ? (c >= 7424 && c <= 7615)
              : (c <= 7957 || (c >= 7968 && c <= 8005)))))
          : (c <= 8023 || (c < 8096
            ? (c < 8064
              ? (c >= 8032 && c <= 8061)
              : (c <= 8071 || (c >= 8080 && c <= 8087)))
            : (c <= 8103 || (c < 8118
              ? (c >= 8112 && c <= 8116)
              : c <= 8119)))))
        : (c <= 8126 || (c < 8305
          ? (c < 8150
            ? (c < 8134
              ? (c >= 8130 && c <= 8132)
              : (c <= 8135 || (c >= 8144 && c <= 8147)))
            : (c <= 8151 || (c < 8178
              ? (c >= 8160 && c <= 8167)
              : (c <= 8180 || (c >= 8182 && c <= 8183)))))
          : (c <= 8305 || (c < 8495
            ? (c < 8336
              ? c == 8319
              : (c <= 8348 || (c >= 8458 && c <= 8467)))
            : (c <= 8500 || (c < 8508
              ? c == 8505
              : c <= 8509)))))))))
    : (c <= 8521 || (c < 66995
      ? (c < 42961
        ? (c < 11520
          ? (c < 9424
            ? (c < 8560
              ? c == 8526
              : (c <= 8575 || c == 8580))
            : (c <= 9449 || (c < 11500
              ? (c >= 11312 && c <= 11492)
              : (c <= 11502 || c == 11507))))
          : (c <= 11557 || (c < 42625
            ? (c < 11565
              ? c == 11559
              : (c <= 11565 || (c >= 42561 && c <= 42605)))
            : (c <= 42653 || (c < 42892
              ? (c >= 42787 && c <= 42887)
              : (c <= 42894 || (c >= 42897 && c <= 42954)))))))
        : (c <= 42961 || (c < 64256
          ? (c < 43000
            ? (c < 42965
              ? c == 42963
              : (c <= 42969 || c == 42998))
            : (c <= 43002 || (c < 43868
              ? (c >= 43824 && c <= 43866)
              : (c <= 43880 || (c >= 43888 && c <= 43967)))))
          : (c <= 64262 || (c < 66776
            ? (c < 65345
              ? (c >= 64275 && c <= 64279)
              : (c <= 65370 || (c >= 66600 && c <= 66639)))
            : (c <= 66811 || (c < 66979
              ? (c >= 66967 && c <= 66977)
              : c <= 66993)))))))
      : (c <= 67001 || (c < 120094
        ? (c < 93792
          ? (c < 67463
            ? (c < 67456
              ? (c >= 67003 && c <= 67004)
              : (c <= 67456 || (c >= 67459 && c <= 67461)))
            : (c <= 67504 || (c < 68800
              ? (c >= 67506 && c <= 67514)
              : (c <= 68850 || (c >= 71872 && c <= 71903)))))
          : (c <= 93823 || (c < 119995
            ? (c < 119894
              ? (c >= 119834 && c <= 119892)
              : (c <= 119963 || (c >= 119990 && c <= 119993)))
            : (c <= 119995 || (c < 120005
              ? (c >= 119997 && c <= 120003)
              : c <= 120067)))))
        : (c <= 120119 || (c < 120688
          ? (c < 120572
            ? (c < 120514
              ? (c >= 120146 && c <= 120485)
              : (c <= 120538 || (c >= 120540 && c <= 120545)))
            : (c <= 120596 || (c < 120630
              ? (c >= 120598 && c <= 120603)
              : (c <= 120654 || (c >= 120656 && c <= 120661)))))
          : (c <= 120712 || (c < 122624
            ? (c < 120746
              ? (c >= 120714 && c <= 120719)
              : (c <= 120770 || (c >= 120772 && c <= 120779)))
            : (c <= 122633 || (c < 125218
              ? (c >= 122635 && c <= 122654)
              : c <= 125251)))))))))));
}

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(45);
      if (lookahead == '"') ADVANCE(4);
      if (lookahead == '#') ADVANCE(37);
      if (lookahead == '%') ADVANCE(2);
      if (lookahead == '(') ADVANCE(53);
      if (lookahead == ')') ADVANCE(54);
      if (lookahead == ',') ADVANCE(49);
      if (lookahead == '.') ADVANCE(50);
      if (lookahead == ':') ADVANCE(6);
      if (lookahead == '?') ADVANCE(51);
      if (lookahead == '@') ADVANCE(43);
      if (lookahead == 'f') ADVANCE(56);
      if (lookahead == 'n') ADVANCE(60);
      if (lookahead == 't') ADVANCE(61);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(46);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(79);
      if (aux_sym_predicate_token2_character_set_1(lookahead)) ADVANCE(65);
      if (aux_sym_predicate_token2_character_set_2(lookahead)) ADVANCE(65);
      END_STATE();
    case 1:
      if (lookahead == '\n') ADVANCE(47);
      END_STATE();
    case 2:
      if (lookahead == '\n') ADVANCE(47);
      if (lookahead == '\r') ADVANCE(1);
      if (lookahead != 0) ADVANCE(2);
      END_STATE();
    case 3:
      if (lookahead == '"') ADVANCE(4);
      if (lookahead == '#') ADVANCE(37);
      if (lookahead == '%') ADVANCE(2);
      if (lookahead == ')') ADVANCE(54);
      if (lookahead == 'f') ADVANCE(66);
      if (lookahead == 't') ADVANCE(70);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(46);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(79);
      if (aux_sym_predicate_token2_character_set_1(lookahead)) ADVANCE(74);
      if (sym_identifier_character_set_1(lookahead)) ADVANCE(73);
      END_STATE();
    case 4:
      if (lookahead == '"') ADVANCE(80);
      if (lookahead != 0) ADVANCE(4);
      END_STATE();
    case 5:
      if (lookahead == '%') ADVANCE(2);
      if (lookahead == '@') ADVANCE(43);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(46);
      if (aux_sym_predicate_token2_character_set_3(lookahead)) ADVANCE(65);
      END_STATE();
    case 6:
      if (lookahead == '-') ADVANCE(48);
      END_STATE();
    case 7:
      if (lookahead == '-') ADVANCE(27);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(26);
      END_STATE();
    case 8:
      if (lookahead == '-') ADVANCE(21);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(20);
      END_STATE();
    case 9:
      if (lookahead == '-') ADVANCE(33);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(32);
      END_STATE();
    case 10:
      if (lookahead == '-') ADVANCE(42);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(41);
      END_STATE();
    case 11:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(9);
      END_STATE();
    case 12:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(81);
      END_STATE();
    case 13:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(11);
      END_STATE();
    case 14:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(12);
      END_STATE();
    case 15:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(13);
      END_STATE();
    case 16:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(14);
      END_STATE();
    case 17:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(15);
      END_STATE();
    case 18:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(10);
      END_STATE();
    case 19:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(18);
      END_STATE();
    case 20:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(19);
      END_STATE();
    case 21:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(20);
      END_STATE();
    case 22:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(16);
      END_STATE();
    case 23:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(17);
      END_STATE();
    case 24:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(8);
      END_STATE();
    case 25:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(24);
      END_STATE();
    case 26:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(25);
      END_STATE();
    case 27:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(26);
      END_STATE();
    case 28:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(22);
      END_STATE();
    case 29:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(23);
      END_STATE();
    case 30:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(7);
      END_STATE();
    case 31:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(30);
      END_STATE();
    case 32:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(31);
      END_STATE();
    case 33:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(32);
      END_STATE();
    case 34:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(28);
      END_STATE();
    case 35:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(29);
      END_STATE();
    case 36:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(34);
      END_STATE();
    case 37:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(35);
      END_STATE();
    case 38:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(36);
      END_STATE();
    case 39:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(38);
      END_STATE();
    case 40:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(39);
      END_STATE();
    case 41:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(40);
      END_STATE();
    case 42:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(41);
      END_STATE();
    case 43:
      if (aux_sym_predicate_token2_character_set_3(lookahead)) ADVANCE(55);
      END_STATE();
    case 44:
      if (eof) ADVANCE(45);
      if (lookahead == '%') ADVANCE(2);
      if (lookahead == '@') ADVANCE(43);
      if (lookahead == 'n') ADVANCE(60);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(46);
      if (aux_sym_predicate_token2_character_set_3(lookahead)) ADVANCE(65);
      END_STATE();
    case 45:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 46:
      ACCEPT_TOKEN(sym__whitespace);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(46);
      END_STATE();
    case 47:
      ACCEPT_TOKEN(sym_comment);
      END_STATE();
    case 48:
      ACCEPT_TOKEN(anon_sym_COLON_DASH);
      END_STATE();
    case 49:
      ACCEPT_TOKEN(anon_sym_COMMA);
      END_STATE();
    case 50:
      ACCEPT_TOKEN(anon_sym_DOT);
      END_STATE();
    case 51:
      ACCEPT_TOKEN(anon_sym_QMARK);
      END_STATE();
    case 52:
      ACCEPT_TOKEN(anon_sym_not);
      if (aux_sym_predicate_token2_character_set_4(lookahead)) ADVANCE(65);
      END_STATE();
    case 53:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 54:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 55:
      ACCEPT_TOKEN(aux_sym_predicate_token1);
      if (aux_sym_predicate_token2_character_set_4(lookahead)) ADVANCE(55);
      END_STATE();
    case 56:
      ACCEPT_TOKEN(aux_sym_predicate_token2);
      if (lookahead == 'a') ADVANCE(59);
      if (aux_sym_predicate_token2_character_set_5(lookahead)) ADVANCE(65);
      END_STATE();
    case 57:
      ACCEPT_TOKEN(aux_sym_predicate_token2);
      if (lookahead == 'e') ADVANCE(75);
      if (aux_sym_predicate_token2_character_set_4(lookahead)) ADVANCE(65);
      END_STATE();
    case 58:
      ACCEPT_TOKEN(aux_sym_predicate_token2);
      if (lookahead == 'e') ADVANCE(77);
      if (aux_sym_predicate_token2_character_set_4(lookahead)) ADVANCE(65);
      END_STATE();
    case 59:
      ACCEPT_TOKEN(aux_sym_predicate_token2);
      if (lookahead == 'l') ADVANCE(62);
      if (aux_sym_predicate_token2_character_set_4(lookahead)) ADVANCE(65);
      END_STATE();
    case 60:
      ACCEPT_TOKEN(aux_sym_predicate_token2);
      if (lookahead == 'o') ADVANCE(63);
      if (aux_sym_predicate_token2_character_set_4(lookahead)) ADVANCE(65);
      END_STATE();
    case 61:
      ACCEPT_TOKEN(aux_sym_predicate_token2);
      if (lookahead == 'r') ADVANCE(64);
      if (aux_sym_predicate_token2_character_set_4(lookahead)) ADVANCE(65);
      END_STATE();
    case 62:
      ACCEPT_TOKEN(aux_sym_predicate_token2);
      if (lookahead == 's') ADVANCE(58);
      if (aux_sym_predicate_token2_character_set_4(lookahead)) ADVANCE(65);
      END_STATE();
    case 63:
      ACCEPT_TOKEN(aux_sym_predicate_token2);
      if (lookahead == 't') ADVANCE(52);
      if (aux_sym_predicate_token2_character_set_4(lookahead)) ADVANCE(65);
      END_STATE();
    case 64:
      ACCEPT_TOKEN(aux_sym_predicate_token2);
      if (lookahead == 'u') ADVANCE(57);
      if (aux_sym_predicate_token2_character_set_4(lookahead)) ADVANCE(65);
      END_STATE();
    case 65:
      ACCEPT_TOKEN(aux_sym_predicate_token2);
      if (aux_sym_predicate_token2_character_set_4(lookahead)) ADVANCE(65);
      END_STATE();
    case 66:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(69);
      if (aux_sym_predicate_token2_character_set_5(lookahead)) ADVANCE(73);
      END_STATE();
    case 67:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(76);
      if (aux_sym_predicate_token2_character_set_4(lookahead)) ADVANCE(73);
      END_STATE();
    case 68:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(78);
      if (aux_sym_predicate_token2_character_set_4(lookahead)) ADVANCE(73);
      END_STATE();
    case 69:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'l') ADVANCE(71);
      if (aux_sym_predicate_token2_character_set_4(lookahead)) ADVANCE(73);
      END_STATE();
    case 70:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(72);
      if (aux_sym_predicate_token2_character_set_4(lookahead)) ADVANCE(73);
      END_STATE();
    case 71:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(68);
      if (aux_sym_predicate_token2_character_set_4(lookahead)) ADVANCE(73);
      END_STATE();
    case 72:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'u') ADVANCE(67);
      if (aux_sym_predicate_token2_character_set_4(lookahead)) ADVANCE(73);
      END_STATE();
    case 73:
      ACCEPT_TOKEN(sym_identifier);
      if (aux_sym_predicate_token2_character_set_4(lookahead)) ADVANCE(73);
      END_STATE();
    case 74:
      ACCEPT_TOKEN(sym_variable);
      if (aux_sym_predicate_token2_character_set_4(lookahead)) ADVANCE(74);
      END_STATE();
    case 75:
      ACCEPT_TOKEN(anon_sym_true);
      if (aux_sym_predicate_token2_character_set_4(lookahead)) ADVANCE(65);
      END_STATE();
    case 76:
      ACCEPT_TOKEN(anon_sym_true);
      if (aux_sym_predicate_token2_character_set_4(lookahead)) ADVANCE(73);
      END_STATE();
    case 77:
      ACCEPT_TOKEN(anon_sym_false);
      if (aux_sym_predicate_token2_character_set_4(lookahead)) ADVANCE(65);
      END_STATE();
    case 78:
      ACCEPT_TOKEN(anon_sym_false);
      if (aux_sym_predicate_token2_character_set_4(lookahead)) ADVANCE(73);
      END_STATE();
    case 79:
      ACCEPT_TOKEN(sym_integer);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(79);
      END_STATE();
    case 80:
      ACCEPT_TOKEN(sym_string);
      END_STATE();
    case 81:
      ACCEPT_TOKEN(sym_uuid);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 44},
  [2] = {.lex_state = 44},
  [3] = {.lex_state = 44},
  [4] = {.lex_state = 3},
  [5] = {.lex_state = 3},
  [6] = {.lex_state = 44},
  [7] = {.lex_state = 44},
  [8] = {.lex_state = 0},
  [9] = {.lex_state = 0},
  [10] = {.lex_state = 5},
  [11] = {.lex_state = 0},
  [12] = {.lex_state = 44},
  [13] = {.lex_state = 0},
  [14] = {.lex_state = 44},
  [15] = {.lex_state = 44},
  [16] = {.lex_state = 44},
  [17] = {.lex_state = 0},
  [18] = {.lex_state = 0},
  [19] = {.lex_state = 0},
  [20] = {.lex_state = 0},
  [21] = {.lex_state = 0},
  [22] = {.lex_state = 0},
  [23] = {.lex_state = 0},
  [24] = {.lex_state = 0},
  [25] = {.lex_state = 0},
  [26] = {.lex_state = 0},
  [27] = {.lex_state = 0},
  [28] = {.lex_state = 0},
  [29] = {.lex_state = 0},
  [30] = {.lex_state = 0},
  [31] = {.lex_state = 0},
  [32] = {.lex_state = 0},
  [33] = {.lex_state = 0},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [sym__whitespace] = ACTIONS(3),
    [sym_comment] = ACTIONS(3),
    [anon_sym_COLON_DASH] = ACTIONS(1),
    [anon_sym_COMMA] = ACTIONS(1),
    [anon_sym_DOT] = ACTIONS(1),
    [anon_sym_QMARK] = ACTIONS(1),
    [anon_sym_not] = ACTIONS(1),
    [anon_sym_LPAREN] = ACTIONS(1),
    [anon_sym_RPAREN] = ACTIONS(1),
    [aux_sym_predicate_token1] = ACTIONS(1),
    [aux_sym_predicate_token2] = ACTIONS(1),
    [sym_variable] = ACTIONS(1),
    [anon_sym_true] = ACTIONS(1),
    [anon_sym_false] = ACTIONS(1),
    [sym_integer] = ACTIONS(1),
    [sym_string] = ACTIONS(1),
    [sym_uuid] = ACTIONS(1),
  },
  [1] = {
    [sym_source_file] = STATE(32),
    [sym__constraint] = STATE(2),
    [sym_rule_definition] = STATE(2),
    [sym_fact_definition] = STATE(2),
    [sym_goal_definition] = STATE(2),
    [sym_body_atom] = STATE(33),
    [sym_atom] = STATE(23),
    [sym_predicate] = STATE(9),
    [aux_sym_source_file_repeat1] = STATE(2),
    [ts_builtin_sym_end] = ACTIONS(5),
    [sym__whitespace] = ACTIONS(3),
    [sym_comment] = ACTIONS(3),
    [anon_sym_not] = ACTIONS(7),
    [aux_sym_predicate_token1] = ACTIONS(9),
    [aux_sym_predicate_token2] = ACTIONS(11),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 9,
    ACTIONS(7), 1,
      anon_sym_not,
    ACTIONS(9), 1,
      aux_sym_predicate_token1,
    ACTIONS(11), 1,
      aux_sym_predicate_token2,
    ACTIONS(13), 1,
      ts_builtin_sym_end,
    STATE(9), 1,
      sym_predicate,
    STATE(23), 1,
      sym_atom,
    STATE(33), 1,
      sym_body_atom,
    ACTIONS(3), 2,
      sym__whitespace,
      sym_comment,
    STATE(3), 5,
      sym__constraint,
      sym_rule_definition,
      sym_fact_definition,
      sym_goal_definition,
      aux_sym_source_file_repeat1,
  [33] = 9,
    ACTIONS(15), 1,
      ts_builtin_sym_end,
    ACTIONS(17), 1,
      anon_sym_not,
    ACTIONS(20), 1,
      aux_sym_predicate_token1,
    ACTIONS(23), 1,
      aux_sym_predicate_token2,
    STATE(9), 1,
      sym_predicate,
    STATE(23), 1,
      sym_atom,
    STATE(33), 1,
      sym_body_atom,
    ACTIONS(3), 2,
      sym__whitespace,
      sym_comment,
    STATE(3), 5,
      sym__constraint,
      sym_rule_definition,
      sym_fact_definition,
      sym_goal_definition,
      aux_sym_source_file_repeat1,
  [66] = 7,
    ACTIONS(26), 1,
      anon_sym_RPAREN,
    ACTIONS(28), 1,
      sym_identifier,
    STATE(19), 1,
      sym_term,
    ACTIONS(3), 2,
      sym__whitespace,
      sym_comment,
    ACTIONS(32), 2,
      anon_sym_true,
      anon_sym_false,
    STATE(26), 2,
      sym_boolean,
      sym_atomic_string,
    ACTIONS(30), 4,
      sym_variable,
      sym_integer,
      sym_string,
      sym_uuid,
  [94] = 6,
    ACTIONS(28), 1,
      sym_identifier,
    STATE(31), 1,
      sym_term,
    ACTIONS(3), 2,
      sym__whitespace,
      sym_comment,
    ACTIONS(32), 2,
      anon_sym_true,
      anon_sym_false,
    STATE(26), 2,
      sym_boolean,
      sym_atomic_string,
    ACTIONS(30), 4,
      sym_variable,
      sym_integer,
      sym_string,
      sym_uuid,
  [119] = 7,
    ACTIONS(7), 1,
      anon_sym_not,
    ACTIONS(9), 1,
      aux_sym_predicate_token1,
    ACTIONS(11), 1,
      aux_sym_predicate_token2,
    STATE(9), 1,
      sym_predicate,
    STATE(29), 1,
      sym_atom,
    STATE(30), 1,
      sym_body_atom,
    ACTIONS(3), 2,
      sym__whitespace,
      sym_comment,
  [142] = 7,
    ACTIONS(7), 1,
      anon_sym_not,
    ACTIONS(9), 1,
      aux_sym_predicate_token1,
    ACTIONS(11), 1,
      aux_sym_predicate_token2,
    STATE(9), 1,
      sym_predicate,
    STATE(20), 1,
      sym_body_atom,
    STATE(29), 1,
      sym_atom,
    ACTIONS(3), 2,
      sym__whitespace,
      sym_comment,
  [165] = 2,
    ACTIONS(3), 2,
      sym__whitespace,
      sym_comment,
    ACTIONS(34), 5,
      anon_sym_COLON_DASH,
      anon_sym_COMMA,
      anon_sym_DOT,
      anon_sym_QMARK,
      anon_sym_LPAREN,
  [177] = 3,
    ACTIONS(38), 1,
      anon_sym_LPAREN,
    ACTIONS(3), 2,
      sym__whitespace,
      sym_comment,
    ACTIONS(36), 4,
      anon_sym_COLON_DASH,
      anon_sym_COMMA,
      anon_sym_DOT,
      anon_sym_QMARK,
  [191] = 4,
    STATE(9), 1,
      sym_predicate,
    STATE(21), 1,
      sym_atom,
    ACTIONS(3), 2,
      sym__whitespace,
      sym_comment,
    ACTIONS(9), 2,
      aux_sym_predicate_token1,
      aux_sym_predicate_token2,
  [206] = 2,
    ACTIONS(3), 2,
      sym__whitespace,
      sym_comment,
    ACTIONS(40), 4,
      anon_sym_COLON_DASH,
      anon_sym_COMMA,
      anon_sym_DOT,
      anon_sym_QMARK,
  [217] = 3,
    ACTIONS(3), 2,
      sym__whitespace,
      sym_comment,
    ACTIONS(42), 2,
      ts_builtin_sym_end,
      aux_sym_predicate_token1,
    ACTIONS(44), 2,
      anon_sym_not,
      aux_sym_predicate_token2,
  [230] = 2,
    ACTIONS(3), 2,
      sym__whitespace,
      sym_comment,
    ACTIONS(46), 4,
      anon_sym_COLON_DASH,
      anon_sym_COMMA,
      anon_sym_DOT,
      anon_sym_QMARK,
  [241] = 3,
    ACTIONS(3), 2,
      sym__whitespace,
      sym_comment,
    ACTIONS(48), 2,
      ts_builtin_sym_end,
      aux_sym_predicate_token1,
    ACTIONS(50), 2,
      anon_sym_not,
      aux_sym_predicate_token2,
  [254] = 3,
    ACTIONS(3), 2,
      sym__whitespace,
      sym_comment,
    ACTIONS(52), 2,
      ts_builtin_sym_end,
      aux_sym_predicate_token1,
    ACTIONS(54), 2,
      anon_sym_not,
      aux_sym_predicate_token2,
  [267] = 3,
    ACTIONS(3), 2,
      sym__whitespace,
      sym_comment,
    ACTIONS(56), 2,
      ts_builtin_sym_end,
      aux_sym_predicate_token1,
    ACTIONS(58), 2,
      anon_sym_not,
      aux_sym_predicate_token2,
  [280] = 2,
    ACTIONS(3), 2,
      sym__whitespace,
      sym_comment,
    ACTIONS(60), 4,
      anon_sym_COLON_DASH,
      anon_sym_COMMA,
      anon_sym_DOT,
      anon_sym_QMARK,
  [291] = 4,
    ACTIONS(62), 1,
      anon_sym_COMMA,
    ACTIONS(64), 1,
      anon_sym_DOT,
    STATE(24), 1,
      aux_sym_rule_definition_repeat1,
    ACTIONS(3), 2,
      sym__whitespace,
      sym_comment,
  [305] = 4,
    ACTIONS(66), 1,
      anon_sym_COMMA,
    ACTIONS(68), 1,
      anon_sym_RPAREN,
    STATE(22), 1,
      aux_sym_atom_repeat1,
    ACTIONS(3), 2,
      sym__whitespace,
      sym_comment,
  [319] = 4,
    ACTIONS(62), 1,
      anon_sym_COMMA,
    ACTIONS(70), 1,
      anon_sym_DOT,
    STATE(18), 1,
      aux_sym_rule_definition_repeat1,
    ACTIONS(3), 2,
      sym__whitespace,
      sym_comment,
  [333] = 2,
    ACTIONS(3), 2,
      sym__whitespace,
      sym_comment,
    ACTIONS(72), 3,
      anon_sym_COMMA,
      anon_sym_DOT,
      anon_sym_QMARK,
  [343] = 4,
    ACTIONS(66), 1,
      anon_sym_COMMA,
    ACTIONS(74), 1,
      anon_sym_RPAREN,
    STATE(25), 1,
      aux_sym_atom_repeat1,
    ACTIONS(3), 2,
      sym__whitespace,
      sym_comment,
  [357] = 4,
    ACTIONS(76), 1,
      anon_sym_COLON_DASH,
    ACTIONS(78), 1,
      anon_sym_DOT,
    ACTIONS(80), 1,
      anon_sym_QMARK,
    ACTIONS(3), 2,
      sym__whitespace,
      sym_comment,
  [371] = 4,
    ACTIONS(82), 1,
      anon_sym_COMMA,
    ACTIONS(85), 1,
      anon_sym_DOT,
    STATE(24), 1,
      aux_sym_rule_definition_repeat1,
    ACTIONS(3), 2,
      sym__whitespace,
      sym_comment,
  [385] = 4,
    ACTIONS(87), 1,
      anon_sym_COMMA,
    ACTIONS(90), 1,
      anon_sym_RPAREN,
    STATE(25), 1,
      aux_sym_atom_repeat1,
    ACTIONS(3), 2,
      sym__whitespace,
      sym_comment,
  [399] = 2,
    ACTIONS(3), 2,
      sym__whitespace,
      sym_comment,
    ACTIONS(92), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [408] = 2,
    ACTIONS(3), 2,
      sym__whitespace,
      sym_comment,
    ACTIONS(94), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [417] = 2,
    ACTIONS(3), 2,
      sym__whitespace,
      sym_comment,
    ACTIONS(96), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [426] = 2,
    ACTIONS(3), 2,
      sym__whitespace,
      sym_comment,
    ACTIONS(80), 2,
      anon_sym_COMMA,
      anon_sym_DOT,
  [435] = 2,
    ACTIONS(3), 2,
      sym__whitespace,
      sym_comment,
    ACTIONS(85), 2,
      anon_sym_COMMA,
      anon_sym_DOT,
  [444] = 2,
    ACTIONS(3), 2,
      sym__whitespace,
      sym_comment,
    ACTIONS(90), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [453] = 2,
    ACTIONS(98), 1,
      ts_builtin_sym_end,
    ACTIONS(3), 2,
      sym__whitespace,
      sym_comment,
  [461] = 2,
    ACTIONS(100), 1,
      anon_sym_QMARK,
    ACTIONS(3), 2,
      sym__whitespace,
      sym_comment,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 33,
  [SMALL_STATE(4)] = 66,
  [SMALL_STATE(5)] = 94,
  [SMALL_STATE(6)] = 119,
  [SMALL_STATE(7)] = 142,
  [SMALL_STATE(8)] = 165,
  [SMALL_STATE(9)] = 177,
  [SMALL_STATE(10)] = 191,
  [SMALL_STATE(11)] = 206,
  [SMALL_STATE(12)] = 217,
  [SMALL_STATE(13)] = 230,
  [SMALL_STATE(14)] = 241,
  [SMALL_STATE(15)] = 254,
  [SMALL_STATE(16)] = 267,
  [SMALL_STATE(17)] = 280,
  [SMALL_STATE(18)] = 291,
  [SMALL_STATE(19)] = 305,
  [SMALL_STATE(20)] = 319,
  [SMALL_STATE(21)] = 333,
  [SMALL_STATE(22)] = 343,
  [SMALL_STATE(23)] = 357,
  [SMALL_STATE(24)] = 371,
  [SMALL_STATE(25)] = 385,
  [SMALL_STATE(26)] = 399,
  [SMALL_STATE(27)] = 408,
  [SMALL_STATE(28)] = 417,
  [SMALL_STATE(29)] = 426,
  [SMALL_STATE(30)] = 435,
  [SMALL_STATE(31)] = 444,
  [SMALL_STATE(32)] = 453,
  [SMALL_STATE(33)] = 461,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, SHIFT_EXTRA(),
  [5] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 0),
  [7] = {.entry = {.count = 1, .reusable = false}}, SHIFT(10),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [11] = {.entry = {.count = 1, .reusable = false}}, SHIFT(8),
  [13] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 1),
  [15] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2),
  [17] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(10),
  [20] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(8),
  [23] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(8),
  [26] = {.entry = {.count = 1, .reusable = true}}, SHIFT(17),
  [28] = {.entry = {.count = 1, .reusable = false}}, SHIFT(28),
  [30] = {.entry = {.count = 1, .reusable = true}}, SHIFT(26),
  [32] = {.entry = {.count = 1, .reusable = false}}, SHIFT(27),
  [34] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_predicate, 1),
  [36] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_atom, 1),
  [38] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
  [40] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_atom, 5),
  [42] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_rule_definition, 5, .production_id = 1),
  [44] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_rule_definition, 5, .production_id = 1),
  [46] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_atom, 4),
  [48] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_goal_definition, 2),
  [50] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_goal_definition, 2),
  [52] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_fact_definition, 2),
  [54] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_fact_definition, 2),
  [56] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_rule_definition, 4, .production_id = 1),
  [58] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_rule_definition, 4, .production_id = 1),
  [60] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_atom, 3),
  [62] = {.entry = {.count = 1, .reusable = true}}, SHIFT(6),
  [64] = {.entry = {.count = 1, .reusable = true}}, SHIFT(12),
  [66] = {.entry = {.count = 1, .reusable = true}}, SHIFT(5),
  [68] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [70] = {.entry = {.count = 1, .reusable = true}}, SHIFT(16),
  [72] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_body_atom, 2),
  [74] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [76] = {.entry = {.count = 1, .reusable = true}}, SHIFT(7),
  [78] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [80] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_body_atom, 1),
  [82] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_rule_definition_repeat1, 2), SHIFT_REPEAT(6),
  [85] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_rule_definition_repeat1, 2),
  [87] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_atom_repeat1, 2), SHIFT_REPEAT(5),
  [90] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_atom_repeat1, 2),
  [92] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_term, 1),
  [94] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_boolean, 1),
  [96] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_atomic_string, 1),
  [98] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [100] = {.entry = {.count = 1, .reusable = true}}, SHIFT(14),
};

#ifdef __cplusplus
extern "C" {
#endif
#ifdef _WIN32
#define extern __declspec(dllexport)
#endif

extern const TSLanguage *tree_sitter_datalog_arde(void) {
  static const TSLanguage language = {
    .version = LANGUAGE_VERSION,
    .symbol_count = SYMBOL_COUNT,
    .alias_count = ALIAS_COUNT,
    .token_count = TOKEN_COUNT,
    .external_token_count = EXTERNAL_TOKEN_COUNT,
    .state_count = STATE_COUNT,
    .large_state_count = LARGE_STATE_COUNT,
    .production_id_count = PRODUCTION_ID_COUNT,
    .field_count = FIELD_COUNT,
    .max_alias_sequence_length = MAX_ALIAS_SEQUENCE_LENGTH,
    .parse_table = &ts_parse_table[0][0],
    .small_parse_table = ts_small_parse_table,
    .small_parse_table_map = ts_small_parse_table_map,
    .parse_actions = ts_parse_actions,
    .symbol_names = ts_symbol_names,
    .field_names = ts_field_names,
    .field_map_slices = ts_field_map_slices,
    .field_map_entries = ts_field_map_entries,
    .symbol_metadata = ts_symbol_metadata,
    .public_symbol_map = ts_symbol_map,
    .alias_map = ts_non_terminal_alias_map,
    .alias_sequences = &ts_alias_sequences[0][0],
    .lex_modes = ts_lex_modes,
    .lex_fn = ts_lex,
    .primary_state_ids = ts_primary_state_ids,
  };
  return &language;
}
#ifdef __cplusplus
}
#endif
