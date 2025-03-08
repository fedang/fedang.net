// Copyright (c) 2025 Federico Angelilli
// Licensed under the 3-Clause BSD License
// See fedang.net/posts/pointer-tagging

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

// The last byte must be zero
typedef struct {
	char data[8];
} tinystr_t;

typedef enum {
    TAG_OBJECT,
    TAG_INTEGER,
    TAG_FLOAT,
    TAG_STRING,
	TAG_TINYSTR,
} value_tag_t;

typedef struct {
    value_tag_t tag;
    union {
        void *object;
        intptr_t integer;
        float float_;
        char *string;
        tinystr_t tinystr;
    } to;
} value_t;

// Object value
#define VALUE_IS_OBJECT(val) ((val).tag == TAG_OBJECT)
#define VALUE_FROM_OBJECT(obj) ((value_t){ .tag = TAG_OBJECT, .to.object = (void *)(obj) })
#define VALUE_TO_OBJECT(val) ((val).to.object)

// Integer value
#define INTEGER_MAX INTPTR_MAX
#define INTEGER_MIN INTPTR_MIN

#define VALUE_IS_INTEGER(val) ((val).tag == TAG_INTEGER)
#define VALUE_FROM_INTEGER(num) ((value_t){ .tag = TAG_INTEGER, .to.integer = (num) })
#define VALUE_TO_INTEGER(val) ((val).to.integer)

// Float value
#define VALUE_IS_FLOAT(val) ((val).tag == TAG_FLOAT)
#define VALUE_FROM_FLOAT(num) ((value_t){ .tag = TAG_FLOAT, .to.float_ = (num) })
#define VALUE_TO_FLOAT(val) ((val).to.float_)

// String value
#define VALUE_IS_STRING(val) ((val).tag == TAG_STRING)
#define VALUE_FROM_STRING(str) ((value_t){ .tag = TAG_STRING, .to.string = (char *)(str) })
#define VALUE_TO_STRING(val) ((val).to.string)

// Tiny string value
#define VALUE_IS_TINYSTR(val) ((val).tag == TAG_TINYSTR)
#define VALUE_FROM_TINYSTR(str) ((value_t){ .tag = TAG_TINYSTR, .to.tinystr = (str) })
#define VALUE_TO_TINYSTR(val) ((val).to.tinystr)
