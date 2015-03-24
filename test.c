#include <lang.h>

void
test_int()
{
	Object* i = new(&IntType, 1);
	Object* i2 = new(&IntType, 123);

	Object* r = msg_send(i, selector(eq), i);
	msg_send(r, selector(repr));

	msg_send(i, selector(repr));
	msg_send(i2, selector(repr));

	r = msg_send(i, selector(add), i2);
	if (r) {
		msg_send(r, selector(repr));
	}

	delete(i2);
	delete(i);
}

void
test_str()
{
	Object* s = new(&StrType, "Hello, World!");
	Object* s2 = new(&StrType, "Hello, Mars!");

	msg_send(s, selector(repr));
	msg_send(s2, selector(repr));

	delete(s2);
	delete(s);
}

int
main(void)
{
	test_int();
	test_str();
	return 0;
}
