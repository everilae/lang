#include <type.h>
#include <selector.h>

static void
Type_new(Object* this_, va_list ap)
{
	Type* this = (Type*) this_;

	this->name = va_arg(ap, const char*);
	this->base = va_arg(ap, Type*);
	this->size = va_arg(ap, size_t);
}

static void
Type_repr(Object* this, va_list ap)
{
	printf("<type '%s'>\n", ((Type*) this)->name);
}

Type TypeType = {
	.class = &TypeType,
	.base = &ObjectType,
	.name = "type",

	.size = sizeof(Type),

	.new = Type_new,
	.delete = Object_delete,

	.selectors = ((Selector[]) {
		SELECTOR(repr, Type_repr),
		{0},
	})
};
