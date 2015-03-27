#include <string.h>

#include <lang.h>
#include <debug.h>

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
	register IMP imp = NULL;
	while (class && !imp) {
		for (
			register Selector* sel = class->selectors;
			sel && sel->class;
			sel++
		) {
			if (cmd == sel->cmd) {
				imp = sel->imp;
				break;
			}
		}
		class = class->base;
	}

	return imp;
}

Object*
msg_send(Object* obj, SEL cmd, ...)
{
	if (!obj) {
		goto noimpl;
	}

	asm volatile (
		/* Save arguments */
		"pushq\t%%rdi\n\t"
		"pushq\t%%rsi\n\t"
		"pushq\t%%rdx\n\t"
		"pushq\t%%rcx\n\t"
		"pushq\t%%r8\n\t"
		"pushq\t%%r9\n\t"
		"pushq\t%%rax\n\t"
		::
	);

	register IMP imp = get_implementation(ObType(obj), cmd);

	asm volatile (
		/* Restore args */
		"popq\t%%rax\n\t"
		"popq\t%%r9\n\t"
		"popq\t%%r8\n\t"
		"popq\t%%rcx\n\t"
		"popq\t%%rdx\n\t"
		"popq\t%%rsi\n\t"
		"popq\t%%rdi\n\t"
		:
		:
		: "rax", "r9", "r8", "rcx", "rdx", "rsi", "rdi"
	);

	if (!imp) {
		goto noimpl;
	}

	/* trampoline */
	asm volatile (
		"jmp\t*%0\n\t"
		:
		: "r"(imp)
	);

noimpl:
	return NULL;
}

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

static Object*
Object_wait(Object* this, SEL cmd)
{
	Monitor* mon;
	if ((mon = this->monitor)) {
	}
	return NULL;
}

static Object*
Object_notify(Object* this, SEL cmd)
{
	Monitor* mon;
	if ((mon = this->monitor)) {
	}
	return NULL;
}

Type ObjectType = {
	OBJECT_INITIALIZER(TypeType),

	.base = NULL,
	.name = "object",

	.size = sizeof(Object),

	.new = Object_new,
	.delete = Object_delete,

	.selectors = SELECTOR_LIST(
		SELECTOR(eq, Object_eq),
		SELECTOR(repr, Object_repr),
		SELECTOR(wait, Object_wait),
		SELECTOR(notify, Object_notify)
	),
};
