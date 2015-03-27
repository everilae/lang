#include <assert.h>

#include <lang.h>

void
test_int()
{
	Object* i = new(&IntType, 1);
	assert(i != NULL);

	Object* i2 = new(&IntType, 123);
	assert(i2 != NULL);

	Object* r = msg_send(i, selector(eq), i);
	assert(r == True);

	msg_send(r, selector(repr));
	msg_send(i, selector(repr));
	msg_send(i2, selector(repr));

	r = msg_send(i, selector(add), i2);
	assert(r);

	msg_send(r, selector(repr));

	delete(i2);
	delete(i);
}

void
test_str()
{
	Object* s = new(&StrType, "Hello, World!");
	assert(s);

	Object* s2 = new(&StrType, "Hello, Mars!");
	assert(s2);

	msg_send(s, selector(repr));
	msg_send(s2, selector(repr));

	delete(s2);
	delete(s);
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
	test_int();
	test_str();
	test_monitor();
	return 0;
}
