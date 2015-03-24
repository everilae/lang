#include <stdio.h>

#include <type.h>
#include <none.h>

static void
None_new(Object* this, va_list ap)
{
	fprintf(stderr, "ERROR: cannot create 'None'\n");
	abort();
}

static void
None_delete(Object* this)
{
	fprintf(stderr, "ERROR: tried to delete 'None'\n");
	abort();
}

static void
None_repr(Object* this)
{
	printf("None\n");
}

Type NoneType = {
	.class = &TypeType,
	.base = &ObjectType,
	.name = "NoneType",

	.size = sizeof(None),

	.new = None_new,
	.delete = None_delete,

	.selectors = ((Selector[]) {
		SELECTOR(repr, None_repr),
		{0},
	}),
};

None none = {&NoneType};
