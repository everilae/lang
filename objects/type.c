#include <lang.h>

static id
Type_alloc(Class class, SEL cmd)
{
	if (!class) {
		return NULL;
	}

	id o = calloc(1, class_getInstanceSize(class));
	if (!o) {
		return NULL;
	}

	object_setClass(o, class);
	return o;
}

static void
Type_repr(Class this, SEL cmd)
{
	printf("<type '%s'>\n", class_getName(this));
}

struct class TypeType = {
	OBJECT_INITIALIZER(TypeType),

	.super = &ObjectType,
	.name = "type",

	.size = sizeof(struct class),

	.methods = METHOD_LIST(
		METHOD(alloc, Type_alloc),
		METHOD(repr, Type_repr)
	)
};
