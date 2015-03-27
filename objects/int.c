#include <lang.h>

struct class IntType;

static id
Int_init(Int* this, SEL cmd)
{
	this->value = 0;
	return ObPtr(this);
}

static id
Int_initWithInt(Int* this, SEL cmd, int i)
{
	this->value = i;
	return ObPtr(this);
}

static id
Int_eq(Int* this, SEL cmd, id other)
{
	if (object_getClass(other) != &IntType) {
		return NO;
	}

	return Bool(this->value == IntPtr(other)->value);
}

static id
Int_repr(Int* this, SEL cmd)
{
	printf("%d\n", this->value);
	return NULL;
}

#define INT_OP(name_, op) \
static id \
Int_ ## name_(Int* this, SEL cmd, id other) \
{ \
	if (object_getClass(other) != &IntType) { \
		ABORT("ERROR: unsupported operand types for '" #name_ "': '%s' and '%s'", \
		      (object_getClass(this)->name), (object_getClass(other)->name)); \
	} \
	return Int_initWithInt(IntPtr(msgSend(ObPtr(&IntType), SELECTOR(alloc))), SELECTOR(initWithInt:), this->value op IntPtr(other)->value); \
}

INT_OP(add, +)
INT_OP(sub, -)
INT_OP(mul, *)
INT_OP(div, /)

struct class IntType = {
	OBJECT_INITIALIZER(TypeType),

	.super = &ObjectType,
	.name = "int",

	.size = sizeof(Int),

	.methods = METHOD_LIST(
		METHOD(init, Int_init),
		METHOD(initWithInt:, Int_initWithInt),
		METHOD(isEqual:, Int_eq),
		METHOD(repr, Int_repr),
		METHOD(add, Int_add),
		METHOD(sub, Int_sub),
		METHOD(mul, Int_mul),
		METHOD(div, Int_div)
	),
};
