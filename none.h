#ifndef NONE_H
#define NONE_H 1

#include <object.h>

typedef struct {
	OBJECT_HEAD;
} None;

extern Type NoneType;
extern None none;

#endif
