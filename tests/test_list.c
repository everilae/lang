#include <assert.h>

#include <list.h>

int
main(void)
{
	assert(ISNUL(nul));

	Cons* list = CONS(123, int, CONS(345, int, CONS(234, int, nul)));
	repr_list(list, repr_int_cons);
	assert(FIRST(list, int) == 123);
	assert(FIRST(REST(list), int) == 345);

	return 0;
}
