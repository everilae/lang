#include <lang.h>

static id
Method_repr(Method this, SEL cmd)
{
	printf("[... @selector(%s) ...]\n", this->name);
	return NULL;
}

struct class MethodType = {
	OBJECT_INITIALIZER(TypeType),

	.super = &ObjectType,
	.name = "method",

	.size = sizeof(Method),

	.methods = METHOD_LIST(
		METHOD(repr, Method_repr)
	),
};
