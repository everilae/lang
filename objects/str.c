#include <string.h>

#include <lang.h>

struct class StrType;

static id 
Str_initWithCString(Str* this, SEL cmd, const char* cstr)
{
	this->value = cstr;
	return ObPtr(this);
}

static id
Str_eq(Str* this, SEL cmd, id other)
{
	if (object_getClass(other) != &StrType) {
		return NO;
	}

	return Bool(!strcmp(this->value, StrPtr(other)->value));
}

static void
Str_repr(Str* this, SEL cmd)
{
	printf("\"%s\"\n", this->value);
}

struct class StrType = {
	OBJECT_INITIALIZER(TypeType),

	.super = &ObjectType,
	.name = "str",

	.size = sizeof(Str),

	.methods = METHOD_LIST(
		METHOD(initWithCString:, Str_initWithCString),
		METHOD(isEqual:, Str_eq),
		METHOD(repr, Str_repr)
	),
};
