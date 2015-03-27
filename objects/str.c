#include <string.h>

#include <lang.h>

Type StrType;

static Object* 
Str_initWithCString(Str* this, SEL cmd, const char* cstr)
{
	this->value = cstr;
	return ObPtr(this);
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
	OBJECT_INITIALIZER(TypeType),

	.base = &ObjectType,
	.name = "str",

	.size = sizeof(Str),

	.selectors = SELECTOR_LIST(
		SELECTOR(initWithCString:, Str_initWithCString),
		SELECTOR(isEqual:, Str_eq),
		SELECTOR(repr, Str_repr)
	),
};
