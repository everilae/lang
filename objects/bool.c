#include <lang.h>

static id
Bool_repr(Int* this, SEL cmd)
{
	if (this->value) {
		printf("True\n");
	} else {
		printf("False\n");
	}
	return NULL;
}

struct class BoolType = {
	OBJECT_INITIALIZER(TypeType),

	.super = &IntType,
	.name = "bool",

	.size = sizeof(Int),

	.methods = METHOD_LIST(
		METHOD(repr, Bool_repr)
	),
};

id YES = (id) &((Int) {
	OBJECT_INITIALIZER(BoolType),
	.value = 1,
});

id NO = (id) &((Int) {
	OBJECT_INITIALIZER(BoolType),
	.value = 0,
});
