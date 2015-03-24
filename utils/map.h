#ifndef MAP_H
#define MAP_H 1

typedef struct MapNode* Map;
typedef int MapKey;

extern Map map_new(MapKey key, void* value);
extern void* map_get(Map map, MapKey key);
extern Map map_set(Map map, MapKey key, void* value);
extern void map_delete(Map map);

#endif
