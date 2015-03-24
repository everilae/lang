#include <stdio.h>
#include <list.h>

Cons* nul = &((Cons) {NULL, NULL});

typedef void (*repr_cons_fun)(const Cons*);

static void
do_repr_list(const Cons *cons, repr_cons_fun repr_cons)
{
	if (!cons || ISNUL(cons)) {
		return;
	}

	repr_cons(cons);

	if (REST(cons) && !ISNUL(REST(cons))) {
		putchar(' ');
	}

	do_repr_list(REST(cons), repr_cons);
}

void
repr_list(const Cons* cons, repr_cons_fun repr_cons)
{
	if (!cons) {
		printf("(NULL)");
	} else if (ISNUL(cons)) {
		printf("()");
	} else {
		printf("(");
		do_repr_list(cons, repr_cons);
		printf(")\n");
	}
}

void
repr_int_cons(const Cons* cons)
{
	if (cons && CAR(cons)) {
		printf("%d", FIRST(cons, int));
	} else {
		printf("NULL");
	}
}

#ifdef TEST

#ifdef NDEBUG
#undef NDEBUG
#endif

#include <assert.h>

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

#endif
