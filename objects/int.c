#include <lang.h>

Type IntType;

void
Int_new(Object* this_, va_list ap)
{
	Int* this = IntPtr(this_);
	this->value = va_arg(ap, __typeof__(this->value));
}

static Object*
Int_eq(Int* this, SEL cmd, Object* other)
{
	if (ObType(other) != &IntType) {
		return False;
	}

	return Bool(IntPtr(this)->value == IntPtr(other)->value);
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
	return new(&IntType, this->value op IntPtr(other)->value); \
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

	.new = Int_new,
	.delete = Object_delete,

	.selectors = SELECTOR_LIST(
		SELECTOR(eq, Int_eq),
		SELECTOR(repr, Int_repr),
		SELECTOR(add, Int_add),
		SELECTOR(sub, Int_sub),
		SELECTOR(mul, Int_mul),
		SELECTOR(div, Int_div)
	),
};
