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

Object*
msg_send(Object* obj, SEL cmd, ...)
{
	if (!obj) {
		goto noimpl;
	}

	register uintptr_t rsp asm("r12");

	asm volatile (
		/* Save arguments */
		"pushq\t%%rdi\n\t"
		"pushq\t%%rsi\n\t"
		"pushq\t%%rdx\n\t"
		"pushq\t%%rcx\n\t"
		"pushq\t%%r8\n\t"
		"pushq\t%%r9\n\t"
		"pushq\t%%rax\n\t"
		/* Save stack pointer, pray to god no functions touch r12 */
		"movq\t%%rsp, %0\n\t"
		/* Clear bottom 4 bits, moves stack up and aligns */
		"andq\t$-0x10, %%rsp\n\t"
		: "=r"(rsp)
		:
	);

	register IMP imp asm("r11") = get_implementation(ObType(obj), cmd);

	asm volatile (
		/* Restore stack pointer */
		"movq\t%0, %%rsp\n\t"
		/* Restore args */
		"popq\t%%rax\n\t"
		"popq\t%%r9\n\t"
		"popq\t%%r8\n\t"
		"popq\t%%rcx\n\t"
		"popq\t%%rdx\n\t"
		"popq\t%%rsi\n\t"
		"popq\t%%rdi\n\t"
		:: "r"(rsp)
	);

	/* trampoline */
	asm volatile goto (
		"cmpq\t$0, %0\n\t"
		"je %l[noimpl]\n\t"
		"popq\t%%r12\n\t"
		"jmp\t*%0\n\t"
		:
		: "r"(imp)
		:
		: noimpl
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

Type ObjectType = {
	OBJECT_INITIALIZER(TypeType),
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
