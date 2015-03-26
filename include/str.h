#ifndef STR_H
#define STR_H 1

#include <object.h>

typedef struct {
	OBJECT_HEAD;
	const char *value;
} Str;

extern Type StrType;

#define StrPtr(p) ((Str*) p)

#endif
