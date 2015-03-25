#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <map.h>

static void
string_repr(const void* value)
{
	puts(value ? (const char*) value : "(nil)");
}

int
main(void)
{
	Map m = map_new(7, "7");

	map_set(m, 10, "10");
	map_set(m, 5, "5");
	map_set(m, 20, "20");

	const char* s = NULL;

#define TEST_VAL(val) \
	s = map_get(m, val); \
	if (s && !strcmp(s, #val)) { \
		printf("%s\n", s); \
	} else { \
		printf("%s != %s\n", s ? s : "(nil)", #val); \
		exit(EXIT_FAILURE); \
	}

	TEST_VAL(5)
	TEST_VAL(10)
	TEST_VAL(20)
	TEST_VAL(7)

#define TEST_NOT_VAL(val) \
	s = map_get(m, val); \
	if (s) { \
		printf("Whoa, " #val " should not be\n"); \
		exit(EXIT_FAILURE); \
	}

	TEST_NOT_VAL(100)

	if (map_set(NULL, 1, "1")) {
		printf("map_set(NULL, ...) did not return NULL\n");
		exit(EXIT_FAILURE);
	}

	map_repr(m, string_repr);
	map_delete(m);
}
