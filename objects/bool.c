#include <lang.h>

static Object*
Bool_repr(Object* this, va_list ap)
{
	if (IntPtr(this)->value) {
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

	.new = Int_new,
	.delete = Object_delete,

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
