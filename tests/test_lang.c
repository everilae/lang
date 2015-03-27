#include <assert.h>

#include <lang.h>

void
test_int()
{
	Object* i = msg_send(msg_send(ObPtr(&IntType), selector(alloc)), selector(init));
	assert(i);
	assert(((Int*) i)->value == 0);
	msg_send(i, selector(dealloc));

	i = msg_send(msg_send(ObPtr(&IntType), selector(alloc)), selector(initWithInt:), 1);
	assert(i);

	Object* i2 = msg_send(msg_send(ObPtr(&IntType), selector(alloc)), selector(initWithInt:), 123);
	assert(i2);

	Object* r = msg_send(i, selector(isEqual:), i);
	assert(r == True);

	msg_send(r, selector(repr));
	msg_send(i, selector(repr));
	msg_send(i2, selector(repr));

	r = msg_send(i, selector(add), i2);
	assert(r);

	msg_send(r, selector(repr));

	msg_send(r, selector(dealloc));
	msg_send(i2, selector(dealloc));
	msg_send(i, selector(dealloc));
}

void
test_str()
{
	Object* s = msg_send(msg_send(ObPtr(&StrType), selector(alloc)), selector(initWithCString:), "Hello, World!");
	assert(s);

	Object* s2 = msg_send(msg_send(ObPtr(&StrType), selector(alloc)), selector(initWithCString:), "Hello, Mars!");
	assert(s2);

	msg_send(s, selector(repr));
	msg_send(s2, selector(repr));

	msg_send(s2, selector(dealloc));
	msg_send(s, selector(dealloc));
}

void
test_type()
{
	assert(msg_send(ObPtr(&TypeType), selector(respondsToSelector:), selector(alloc)) == True);
}

void
test_monitor()
{
	Object* o = new(&ObjectType);
	SYNCHRONIZED(o) {
		printf("synchronized\n");
	}
}

int
main(void)
{
	test_type();
	test_int();
	test_str();
	test_monitor();
	return 0;
}
