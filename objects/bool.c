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
	.class = &TypeType,
	.base = &IntType,
	.name = "bool",

	.size = sizeof(Int),

	.new = Int_new,
	.delete = Object_delete,

	.selectors = ((Selector[]) {
		SELECTOR(repr, Bool_repr),
		{0}
	}),
};

Object* True = ObPtr(&((Int) {
	&BoolType,
	1,
}));

Object* False = ObPtr(&((Int) {
	&BoolType,
	0,
}));
