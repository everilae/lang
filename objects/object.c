#include <object.h>
#include <debug.h>
#include <inttypes.h>
#include <stdarg.h>
#include <string.h>

#include <lang.h>

void*
new(Type* class, ...)
{
	void* o;
	if (class->alloc) {
		o = class->alloc(class);
	} else {
		o = calloc(1, class->size);
	}

	if (!o) {
		return NULL;
	}

	ObType(o) = class;
	va_list ap;
	va_start(ap, class);
	class->new(o, ap);
	va_end(ap);

	return o;
}

void
delete(Object* o)
{
	if (!o) {
		return;
	}

	if (ObType(o)->delete) {
		ObType(o)->delete(o);
	}

	free(o);
}

/**
 * Called from asm.
 */
IMP
get_implementation(Type* class, SEL cmd)
{
	IMP imp = NULL;
	while (class && !imp) {
		for (Selector* sel = class->selectors; sel && sel->class; sel++) {
			if (cmd == sel->cmd) {
				imp = sel->imp;
				break;
			}
		}
		class = class->base;
	}

	return imp;
}
/*
Object*
msg_send(Object* obj, SEL cmd, ...)
{
	IMP imp = get_implementation(ObType(obj), cmd);
	if (imp) {
		/ * trampoline * /
		__asm__ __volatile__ ("jmp\t*%0\n\t" :: "r"(imp));
	}
	return NULL;
}
*/
void
Object_new(Object* this, va_list ap)
{
	DPRINTF("new(%s)\n", ObType(this)->name);
}

void
Object_delete(Object* this)
{
	DPRINTF("delete(%s)\n", ObType(this)->name);
}

static Object*
Object_eq(Object* this, SEL cmd, Object* other)
{
	return Bool(this == other);
}

static Object*
Object_repr(Object* this, SEL cmd)
{
	printf("<%s object at %p>\n", ObType(this)->name, (void*) this);
	return NULL;
}

Type ObjectType = {
	.class = &TypeType,
	.base = NULL,
	.name = "object",

	.size = sizeof(Object),

	.new = Object_new,
	.delete = Object_delete,

	.selectors = ((Selector[]) {
		SELECTOR(eq, Object_eq),
		SELECTOR(repr, Object_repr),
		{0},
	})
};
