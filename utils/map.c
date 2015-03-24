#include <stdio.h>
#include <stdlib.h>

#include <map.h>

struct MapNode {
	struct MapNode* left;
	struct MapNode* right;
	void* value;
	MapKey key;
};

Map
map_new(MapKey key, void* value)
{
	Map map = calloc(1, sizeof(*map_new(0, 0)));

	if (map) {
		map->key = key;
		map->value = value;
	}

	return map;
}

void
map_delete(Map map)
{
	if (map) {
		map_delete(map->left);
		map_delete(map->right);
		free(map);
	}
}

Map
map_set(Map map, MapKey key, void* value)
{
	if (!map) {
		return NULL;
	}

	Map* dir = NULL;

	/* TODO: balancing */
	/* 3-way compare thingie */
	if (key > map->key) {
		dir = &map->right;
	} else if (key < map->key) {
		dir = &map->left;
	} else {
		/* Equal, we have arrived */
		map->value = value;
		return map;
	}

	if (!(*dir)) {
		/* empty leaf, create new */
		if (!(*dir = map_new(key, value))) {
			/* OUT OF MEMORY */
			return NULL;
		}
		return *dir;
	}

	/* Goto direction */
	return map_set(*dir, key, value);
}

void*
map_get(Map map, MapKey key)
{
	if (!map) {
		return NULL;
	}

	if (key > map->key) {
		return map_get(map->right, key);
	} else if (key < map->key) {
		return map_get(map->left, key);
	}

	return map->value;
}

#ifdef TEST

#include <string.h>

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

	map_delete(m);
}

#endif
