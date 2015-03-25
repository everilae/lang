#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>

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
	assert(m != NULL);
	assert(map_set(m, 10, "10") != NULL);
	assert(map_set(m, 5, "5") != NULL);
	assert(map_set(m, 20, "20") != NULL);

	const char* s = NULL;

#define TEST_VAL(val) s = map_get(m, val); assert(s && !strcmp(s, #val))

	TEST_VAL(5);
	TEST_VAL(10);
	TEST_VAL(20);
	TEST_VAL(7);

#define TEST_NOT_VAL(val) assert(map_get(m, val) == NULL)

	TEST_NOT_VAL(100);
	TEST_NOT_VAL(0);
	TEST_NOT_VAL(INT_MAX);
	TEST_NOT_VAL(INT_MIN);

	assert(map_set(NULL, 1, "1") == NULL);

	map_repr(m, string_repr);
	map_delete(m);
}
