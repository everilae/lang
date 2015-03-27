#ifndef TYPE_H
#define TYPE_H 1

#include <stddef.h>

#include <object.h>
#include <selector.h>

typedef struct Type {
	OBJECT_HEAD;
	struct Type* base;
	const char* name;
	size_t size;
	Selector *selectors;
} Type;

extern Type TypeType;

#define ObType(p) (ObPtr(p)->class)

#endif
