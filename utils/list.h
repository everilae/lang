#ifndef LINKEDLIST_H
#define LINKEDLIST_H 1

typedef struct Cons {
	void* car;
	struct Cons* cdr;
} Cons;

#define CONS(car, type, cdr) (&((Cons) {&((type) {car}), cdr}))
#define REST(l) ((l)->cdr)
#define ISNUL(l) ((l) == nul)
#define FIRST(l, type) (*((type*) (l)->car))
#define CAR(c) ((c)->car)

extern Cons* nul;

void repr_list(const Cons* cons, void (*repr_cons)(const Cons*));
void repr_int_cons(const Cons* cons);

#endif
