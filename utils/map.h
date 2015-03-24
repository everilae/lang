#ifndef MAP_H
#define MAP_H 1

typedef struct MapNode* Map;
typedef int MapKey;
typedef void (*MapFunc)(void* value, void* arg);

extern Map map_new(MapKey key, void* value);
extern void* map_get(Map map, MapKey key);
extern Map map_set(Map map, MapKey key, void* value);
extern void map_delete(Map map);
extern void map_repr(Map map, void (*value_repr)(const void* value));
extern void map_for_each(Map map, MapFunc f, void* arg);

#endif
