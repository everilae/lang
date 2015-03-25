#ifndef TYPE_H
#define TYPE_H 1

#include <object.h>
#include <selector.h>

typedef struct Type {
	OBJECT_HEAD;
	struct Type* base;
	const char* name;

	size_t size;

	/* life and death */
	void (*new)(Object* this, va_list ap);
	void (*delete)(Object* this);
	void* (*alloc)(struct Type*);

	Selector *selectors;
} Type;

extern Type TypeType;

#define ObType(p) (ObPtr(p)->class)

#endif
