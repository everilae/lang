#include <lang.h>

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

	.selectors = SELECTOR_LIST(
		SELECTOR(repr, Selector_repr)
	),
};
