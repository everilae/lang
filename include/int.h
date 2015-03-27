#ifndef INT_H
#define INT_H 1

#include <object.h>

typedef struct {
	OBJECT_HEAD;
	int value;
} Int;

extern struct class IntType;

#define IntPtr(p) ((Int*) p)

#endif
