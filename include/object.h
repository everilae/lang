#ifndef OBJECT_H
#define OBJECT_H 1

struct Monitor;

#define OBJECT_HEAD \
	struct Type* class; \
	struct Monitor* monitor

#define OBJECT_INITIALIZER(cls) \
	.class = &cls, \
	.monitor = NULL

typedef struct Type Type;

typedef struct {
	OBJECT_HEAD;
} Object;

extern Type ObjectType;

#define ObPtr(p) ((Object*) (p))
#define ObType(p) (ObPtr(p)->class)

#endif
