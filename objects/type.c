#include <lang.h>

static Object*
Type_alloc(Type* class, SEL cmd)
{
	if (!class) {
		return NULL;
	}

	Object* o = calloc(1, class->size);
	if (!o) {
		return NULL;
	}

	ObType(o) = class;
	return o;
}

static void
Type_repr(Object* this, SEL cmd)
{
	printf("<type '%s'>\n", ((Type*) this)->name);
}

Type TypeType = {
	OBJECT_INITIALIZER(TypeType),

	.base = &ObjectType,
	.name = "type",

	.size = sizeof(Type),

	.selectors = SELECTOR_LIST(
		SELECTOR(alloc, Type_alloc),
		SELECTOR(repr, Type_repr)
	)
};
