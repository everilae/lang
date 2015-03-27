#ifndef OBJECT_H
#define OBJECT_H 1

#include <stdarg.h>
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

extern void* new(Type* class, ...);
extern void delete(Object* o);

extern void Object_new(Object* this, va_list ap);
extern void Object_delete(Object* this);

#define ObPtr(p) ((Object*) (p))
#define ObType(p) (ObPtr(p)->class)

#endif
