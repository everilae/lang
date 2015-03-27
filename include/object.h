#ifndef OBJECT_H
#define OBJECT_H 1

/* #include <stdatomic.h> */
#define _Atomic
#define ATOMIC_VAR_INIT(v) v

struct Monitor;

#define OBJECT_HEAD \
	struct Type* class; \
	_Atomic struct Monitor* monitor

#define OBJECT_INITIALIZER(cls) \
	.class = &cls, \
	.monitor = ATOMIC_VAR_INIT(NULL)

typedef struct Type Type;

typedef struct {
	OBJECT_HEAD;
} Object;

extern Type ObjectType;

#define ObPtr(p) ((Object*) (p))
#define ObType(p) (ObPtr(p)->class)

#endif
