#ifndef OBJECT_H
#define OBJECT_H 1

#include <stdatomic.h>

#define OBJECT_HEAD \
	struct class* isa; \
	_Atomic (struct monitor*) monitor

#define OBJECT_INITIALIZER(cls) \
	.isa = &cls, \
	.monitor = ATOMIC_VAR_INIT(NULL)

typedef struct object {
	OBJECT_HEAD;
}* id;

extern struct class ObjectType;

#define ObPtr(obj) ((id) (obj))
#define object_getClass(obj) (((id) (obj))->isa)
#define object_setClass(obj, cls) (((id) (obj))->isa = cls)
#endif
