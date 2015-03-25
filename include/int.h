#ifndef INT_H
#define INT_H 1

#include <object.h>

typedef struct {
	OBJECT_HEAD;
	int value;
} Int;

extern Type IntType;
extern void Int_new(Object* this, va_list ap);
extern void init_int_type();

#define IntPtr(p) ((Int*) p)

#endif
