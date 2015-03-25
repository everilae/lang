#ifndef BOOL_H
#define BOOL_H 1

#include <object.h>

extern Type BoolType;
extern Object* True;
extern Object* False;
extern void init_bool_type();

#define Bool(expr) ((expr) ? True : False)

#endif
