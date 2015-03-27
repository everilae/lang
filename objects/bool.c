#include <lang.h>

static Object*
Bool_repr(Int* this, SEL cmd)
{
	if (this->value) {
		printf("True\n");
	} else {
		printf("False\n");
	}
	return NULL;
}

Type BoolType = {
	OBJECT_INITIALIZER(TypeType),

	.base = &IntType,
	.name = "bool",

	.size = sizeof(Int),

	.selectors = SELECTOR_LIST(
		SELECTOR(repr, Bool_repr)
	),
};

Object* True = ObPtr(&((Int) {
	OBJECT_INITIALIZER(BoolType),
	.value = 1,
}));

Object* False = ObPtr(&((Int) {
	OBJECT_INITIALIZER(BoolType),
	.value = 0,
}));
