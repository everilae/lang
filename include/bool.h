#ifndef BOOL_H
#define BOOL_H 1

#include <object.h>

extern struct class BoolType;
extern id YES;
extern id NO;

#define Bool(expr) ((expr) ? YES : NO)

#endif
