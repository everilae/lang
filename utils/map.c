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

void
map_repr(Map map, void (*value_repr)(const void* value))
{
	if (!map || !value_repr) {
		return;
	}

	map_repr(map->left, value_repr);
	printf("%d -> ", map->key);
	value_repr(map->value);
	map_repr(map->right, value_repr);
}

void
map_for_each(Map map, MapFunc f, void* arg)
{
	if (!map || !f) {
		return;
	}

	map_for_each(map->left, f, arg);
	f(map->value, arg);
	map_for_each(map->right, f, arg);
}
