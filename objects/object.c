#include <string.h>

#include <lang.h>
#include <debug.h>

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

static Object*
Object_init(Object* this)
{
	return this;
}

static Object*
Object_dealloc(Object* this)
{
	free(this);
	return NULL;
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
	if (this->monitor) {
	}
	return NULL;
}

static Object*
Object_notify(Object* this, SEL cmd)
{
	if (this->monitor) {
	}
	return NULL;
}

static Object*
Object_performSelector(Object* this, SEL cmd, SEL sel)
{
	return msg_send(this, sel);
}

static Object*
Object_respondsToSelector(Object* this, SEL cmd, SEL sel)
{
	return Bool(get_implementation(ObType(this), sel));
}

Type ObjectType = {
	OBJECT_INITIALIZER(TypeType),

	.base = NULL,
	.name = "object",

	.size = sizeof(Object),

	.selectors = SELECTOR_LIST(
		SELECTOR(init, Object_init),
		SELECTOR(dealloc, Object_dealloc),
		SELECTOR(isEqual:, Object_eq),
		SELECTOR(repr, Object_repr),
		SELECTOR(wait, Object_wait),
		SELECTOR(notify, Object_notify),
		SELECTOR(performSelector:, Object_performSelector),
		SELECTOR(respondsToSelector:, Object_respondsToSelector)
	),
};
