#ifndef TYPE_H
#define TYPE_H 1

#include <stddef.h>

#include <object.h>

typedef struct class {
	OBJECT_HEAD;
	struct class* super;
	const char* name;
	size_t size;
	struct method* methods;
}* Class;

extern struct class TypeType;

#define class_getName(cls) ((cls)->name)
#define class_getSuperClass(cls) ((cls)->super)
#define class_getInstanceSize(cls) ((cls)->size)

#endif
