#include <assert.h>

#include <lang.h>

void
test_int()
{
	id i = msgSend(msgSend(ObPtr(&IntType), SELECTOR(alloc)), SELECTOR(init));
	assert(i);
	assert(((Int*) i)->value == 0);
	msgSend(i, SELECTOR(dealloc));

	i = msgSend(msgSend(ObPtr(&IntType), SELECTOR(alloc)), SELECTOR(initWithInt:), 1);
	assert(i);

	id i2 = msgSend(msgSend(ObPtr(&IntType), SELECTOR(alloc)), SELECTOR(initWithInt:), 123);
	assert(i2);

	id r = msgSend(i, SELECTOR(isEqual:), i);
	assert(r == YES);

	msgSend(r, SELECTOR(repr));
	msgSend(i, SELECTOR(repr));
	msgSend(i2, SELECTOR(repr));

	r = msgSend(i, SELECTOR(add), i2);
	assert(r);

	msgSend(r, SELECTOR(repr));

	msgSend(r, SELECTOR(dealloc));
	msgSend(i2, SELECTOR(dealloc));
	msgSend(i, SELECTOR(dealloc));
}

void
test_str()
{
	id s = msgSend(msgSend(ObPtr(&StrType), SELECTOR(alloc)), SELECTOR(initWithCString:), "Hello, World!");
	assert(s);

	id s2 = msgSend(msgSend(ObPtr(&StrType), SELECTOR(alloc)), SELECTOR(initWithCString:), "Hello, Mars!");
	assert(s2);

	msgSend(s, SELECTOR(repr));
	msgSend(s2, SELECTOR(repr));

	msgSend(s2, SELECTOR(dealloc));
	msgSend(s, SELECTOR(dealloc));
}

void
test_type()
{
	assert(msgSend((id) &TypeType, SELECTOR(respondsToSelector:), SELECTOR(alloc)) == YES);
}

void
test_monitor()
{
	id o = msgSend(msgSend(ObPtr(&ObjectType), SELECTOR(alloc)), SELECTOR(init));
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
