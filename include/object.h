#ifndef OBJECT_H
#define OBJECT_H 1

#include <stdarg.h>

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

extern void* new(Type* class, ...);
extern void delete(Object* o);

extern void Object_new(Object* this, va_list ap);
extern void Object_delete(Object* this);

#define ObPtr(p) ((Object*) (p))
#define ObType(p) (ObPtr(p)->class)

#endif
