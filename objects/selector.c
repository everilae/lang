#include <lang.h>

static void
Selector_new(Object* this, va_list ap)
{
}

static Object*
Selector_repr(Selector* this, SEL cmd)
{
	printf("@selector(%s)\n", this->cmd);
	return NULL;
}

Type SelectorType = {
	OBJECT_INITIALIZER(TypeType),

	.base = &ObjectType,
	.name = "selector",

	.size = sizeof(Selector),

	.new = Selector_new,
	.delete = Object_delete,

	.selectors = SELECTOR_LIST(
		SELECTOR(repr, Selector_repr)
	),
};
