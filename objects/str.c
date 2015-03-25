#include <stdio.h>
#include <string.h>

#include <lang.h>

#define StrPtr(p) ((Str*) p)

Type StrType;

static void
Str_new(Object* this_, va_list ap)
{
	Str* this = StrPtr(this_);
	this->value = va_arg(ap, __typeof__(this->value));
}

static Object*
Str_eq(Str* this, SEL cmd, Object* other)
{
	if (ObType(other) != &StrType) {
		return False;
	}

	return Bool(!strcmp(this->value, StrPtr(other)->value));
}

static void
Str_repr(Str* this, SEL cmd)
{
	printf("\"%s\"\n", this->value);
}

Type StrType = {
	.class = &TypeType,
	.base = &ObjectType,
	.name = "str",

	.size = sizeof(Str),

	.new = Str_new,
	.delete = Object_delete,

	.selectors = ((Selector[]) {
		SELECTOR(eq, Str_eq),
		SELECTOR(repr, Str_repr),
		{0},
	}),
};