#include <lang.h>

Type IntType;

static Object*
Int_init(Int* this, SEL cmd)
{
	this->value = 0;
	return ObPtr(this);
}

static Object*
Int_initWithInt(Int* this, SEL cmd, int i)
{
	this->value = i;
	return ObPtr(this);
}

static Object*
Int_eq(Int* this, SEL cmd, Object* other)
{
	if (ObType(other) != &IntType) {
		return False;
	}

	return Bool(this->value == IntPtr(other)->value);
}

static Object*
Int_repr(Int* this, SEL cmd)
{
	printf("%d\n", this->value);
	return NULL;
}

#define INT_OP(name_, op) \
static Object* \
Int_ ## name_(Int* this, SEL cmd, Object* other) \
{ \
	if (ObType(other) != &IntType) { \
		ABORT("ERROR: unsupported operand types for '" #name_ "': '%s' and '%s'", \
		      (ObType(this)->name), (ObType(other)->name)); \
	} \
	return Int_initWithInt(IntPtr(msg_send(ObPtr(&IntType), selector(alloc))), selector(initWithInt:), this->value op IntPtr(other)->value); \
}

INT_OP(add, +)
INT_OP(sub, -)
INT_OP(mul, *)
INT_OP(div, /)

Type IntType = {
	OBJECT_INITIALIZER(TypeType),

	.base = &ObjectType,
	.name = "int",

	.size = sizeof(Int),

	.selectors = SELECTOR_LIST(
		SELECTOR(init, Int_init),
		SELECTOR(initWithInt:, Int_initWithInt),
		SELECTOR(isEqual:, Int_eq),
		SELECTOR(repr, Int_repr),
		SELECTOR(add, Int_add),
		SELECTOR(sub, Int_sub),
		SELECTOR(mul, Int_mul),
		SELECTOR(div, Int_div)
	),
};
