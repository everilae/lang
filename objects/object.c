#include <string.h>

#include <lang.h>
#include <debug.h>

IMP
class_getMethodImplementation(Class class, SEL cmd)
{
	register IMP imp = NULL;
	while (class && !imp) {
		for (
			register Method meth = class->methods;
			meth && object_getClass(meth); /* end-of-method-list is a NULL struct kindof */
			meth++
		) {
			if (cmd == method_getName(meth)) {
				imp = method_getImplementation(meth);
				break;
			}
		}
		class = class_getSuperClass(class);
	}

	return imp;
}

#if 0
id
msgSend(register id obj, register SEL cmd, ...)
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

	register IMP imp = class_getMethodImplementation(object_getClass(obj), cmd);

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
#endif

static id
Object_init(id this)
{
	Monitor mon = (Monitor) msgSend(msgSend(ObPtr(&MonitorType), SELECTOR(alloc)), SELECTOR(init));
	atomic_store(&this->monitor, mon);
	return this;
}

static id
Object_dealloc(id this)
{
	free(this);
	return NULL;
}

static id
Object_eq(id this, SEL cmd, id other)
{
	return Bool(this == other);
}

static id
Object_repr(id this, SEL cmd)
{
	printf("<%s object at %p>\n", class_getName(object_getClass(this)), (void*) this);
	return NULL;
}

static id
Object_wait(id this, SEL cmd)
{
	Monitor mon;
	if ((mon = atomic_load(&this->monitor))) {
	}
	return NULL;
}

static id
Object_notify(id this, SEL cmd)
{
	Monitor mon;
	if ((mon = atomic_load(&this->monitor))) {
	}
	return NULL;
}

static id
Object_performSelector(id this, SEL cmd, SEL sel)
{
	return msgSend(this, sel);
}

#include <assert.h>

static id
Object_respondsToSelector(id this, SEL cmd, SEL sel)
{
	return Bool(class_getMethodImplementation(object_getClass(this), sel));
}

struct class ObjectType = {
	OBJECT_INITIALIZER(TypeType),

	.super = NULL,
	.name = "object",

	.size = sizeof(struct object),

	.methods = METHOD_LIST(
		METHOD(init, Object_init),
		METHOD(dealloc, Object_dealloc),
		METHOD(isEqual:, Object_eq),
		METHOD(repr, Object_repr),
		METHOD(wait, Object_wait),
		METHOD(notify, Object_notify),
		METHOD(performSelector:, Object_performSelector),
		METHOD(respondsToSelector:, Object_respondsToSelector)
	),
};
