#include <stdio.h>
#include <stdlib.h>

//#include "lowbits.c"
//#include "highbits.c"
#include "union.c"

void print_binary(value_t v) {
    const size_t n = sizeof(value_t) / sizeof(uintptr_t);
    uintptr_t ls[n];
    memcpy(ls, &v, sizeof(value_t));

    for (int i = 0; i < n; i++) {
        for (int j = 8 * sizeof(uintptr_t) - 1; j >= 0; j--) {
            putchar((ls[i] >> j) & 1 ? '1' : '0');
        }
        puts("");
    }
}

int main() {

	// Object
	{
		void *obj = malloc(123);
		value_t v = VALUE_FROM_OBJECT(obj);
		printf("Object %p\nTagged: ", obj);
        print_binary(v);
        puts("");

		assert(VALUE_IS_OBJECT(v));
		assert(VALUE_TO_OBJECT(v) == obj);
	}

	// Integer
	{
		intptr_t ls[] = {
			-1, 10, 1000000, INTEGER_MAX, INTEGER_MIN, 424242, -10000
		};

		for (int i = 0; i < sizeof(ls)/sizeof(*ls); i++) {
			value_t v = VALUE_FROM_INTEGER(ls[i]);
            printf("Integer %ld\nTagged: ", ls[i]);
            print_binary(v);
            puts("");

            assert(VALUE_IS_INTEGER(v));
			assert(ls[i] == VALUE_TO_INTEGER(v));
		}
	}

	// Float
	{
		float ls[] = {
			-1.0, 88.88, 10e-16, 199.9876e12, -1111111111
		};

		for (int i = 0; i < sizeof(ls)/sizeof(*ls); i++) {
			value_t v = VALUE_FROM_FLOAT(ls[i]);
            printf("Float %f\nTagged: ", ls[i]);
            print_binary(v);
            puts("");

            assert(VALUE_IS_FLOAT(v));
			assert(ls[i] == VALUE_TO_FLOAT(v));
		}
	}

	// String
	{
		char *str = malloc(20);
		strcpy(str, "Hello, World");

		value_t v = VALUE_FROM_STRING(str);
		printf("String %s\nTagged: ", str);
        print_binary(v);
        puts("");

		assert(VALUE_IS_STRING(v));
		assert(VALUE_TO_STRING(v) == str);
	}

	// Tiny string
	{
		tinystr_t s1 = { "Short" };
		value_t v1 = VALUE_FROM_TINYSTR(s1);
		printf("Tiny string %s\nTagged: ", s1.data);
        print_binary(v1);
        puts("");

		assert(!memcmp(s1.data, VALUE_TO_TINYSTR(v1).data, 8));

		tinystr_t s2 = { "1234567" };
		value_t v2 = VALUE_FROM_TINYSTR(s2);
		printf("Tiny string %s\nTagged: ", s2.data);
        print_binary(v2);
        puts("");

		assert(!memcmp(s2.data, VALUE_TO_TINYSTR(v2).data, 8));
	}

    return 0;
}
