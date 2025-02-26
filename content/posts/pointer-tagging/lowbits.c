#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

// The last byte must be zero
typedef struct {
	char data[8];
} tinystr_t;

// Only the integer tag sets the lowest bit
typedef enum {
    TAG_OBJECT  = 0,		// 0b000
    TAG_INTEGER = 1,		// 0b001
    TAG_FLOAT   = 2,		// 0b010
    TAG_STRING  = 4,		// 0b100
	TAG_TINYSTR = 6,		// 0b110
} value_tag_t;

typedef uintptr_t value_t;

#define VALUE_BITS 64
#define VALUE_TAG_BITS 3
#define VALUE_TAG_MASK 7	// 0b111

#define VALUE_GET_TAG(val, mask) (value_tag_t)((value_t)(val) & mask)
#define VALUE_SET_TAG(val, tag) ((value_t)(val) | tag)
#define VALUE_UNSET_TAG(val) ((val) & ~VALUE_TAG_MASK)

// Object value
#define VALUE_IS_OBJECT(val) (VALUE_GET_TAG(val, VALUE_TAG_MASK) == TAG_OBJECT)
#define VALUE_FROM_OBJECT(obj) VALUE_SET_TAG(obj, TAG_OBJECT)
#define VALUE_TO_OBJECT(val) (void *)VALUE_UNSET_TAG(val)

// Integer value
#define INTEGER_SHIFT 1
#define INTEGER_MASK 1
#define INTEGER_SIGN_BIT ((value_t)1 << (VALUE_BITS - 1))

#define INTEGER_MAX (((value_t)1 << (VALUE_BITS - 1 - INTEGER_SHIFT)) - 1)
#define INTEGER_MIN -((value_t)1 << (VALUE_BITS - 1 - INTEGER_SHIFT))

#define VALUE_IS_INTEGER(val) (VALUE_GET_TAG(val, INTEGER_MASK) == TAG_INTEGER)
#define VALUE_FROM_INTEGER(num) value_tag_integer(num)
#define VALUE_TO_INTEGER(val) value_untag_integer(val)

value_t value_tag_integer(intptr_t num) {
	assert(num < INTEGER_MIN || num > INTEGER_MAX);
	return (value_t)num << INTEGER_SHIFT | (num & INTEGER_SIGN_BIT) | TAG_INTEGER;
}

intptr_t value_untag_integer(value_t val) {
	assert(VALUE_IS_INTEGER(val));
	return (intptr_t)val >> INTEGER_SHIFT | (val & INTEGER_SIGN_BIT);
}

// Float value
#define FLOAT_SHIFT 31

#define VALUE_IS_FLOAT(val) (VALUE_GET_TAG(val, VALUE_TAG_MASK) == TAG_FLOAT)
#define VALUE_FROM_FLOAT(num) value_tag_float(num)
#define VALUE_TO_FLOAT(val) value_untag_float(val)

value_t value_tag_float(float num) {
    union {
        uint32_t raw;
        float num;
    } pun;
    pun.num = num;
    return VALUE_SET_TAG((value_t)pun.raw << FLOAT_SHIFT, TAG_FLOAT);
}

float value_untag_float(value_t val) {
	assert(VALUE_IS_FLOAT(val));
    union {
        uint32_t raw;
        float num;
    } pun;
    pun.raw = (val >> FLOAT_SHIFT) & 0xffffffff;
    return pun.num;
}

// String value
#define VALUE_IS_STRING(val) (VALUE_GET_TAG(val, VALUE_TAG_MASK) == TAG_STRING)
#define VALUE_FROM_STRING(str) VALUE_SET_TAG(str, TAG_STRING)
#define VALUE_TO_STRING(val) (char *)VALUE_UNSET_TAG(val)

// Tiny string value
#define VALUE_IS_TINYSTR(val) (VALUE_GET_TAG(val, VALUE_TAG_MASK) == TAG_TINYSTR)
#define VALUE_FROM_TINYSTR(num) value_tag_tinystr(num)
#define VALUE_TO_TINYSTR(val) value_untag_tinystr(val)

value_t value_tag_tinystr(tinystr_t str) {
	assert(str.data[7] == '\0');
	return ((value_t)str.data[0] <<  8)
		 | ((value_t)str.data[1] << 16)
		 | ((value_t)str.data[2] << 24)
		 | ((value_t)str.data[3] << 32)
		 | ((value_t)str.data[4] << 40)
		 | ((value_t)str.data[5] << 48)
		 | ((value_t)str.data[6] << 56)
		 | TAG_TINYSTR;
}

tinystr_t value_untag_tinystr(value_t val) {
	assert(VALUE_IS_TINYSTR(val));
    tinystr_t str = {
		(val >>  8) & 0xff,
		(val >> 16) & 0xff,
		(val >> 24) & 0xff,
		(val >> 32) & 0xff,
		(val >> 40) & 0xff,
		(val >> 48) & 0xff,
		(val >> 56) & 0xff,
	};
    return str;
}
