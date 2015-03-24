#include <selector.h>
#include <type.h>

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
	.class = &TypeType,
	.base = &ObjectType,
	.name = "selector",

	.size = sizeof(Selector),

	.new = Selector_new,
	.delete = Object_delete,

	.selectors = ((Selector[]) {
		SELECTOR(repr, Selector_repr),
		{0},
	}),
};
