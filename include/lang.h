#ifndef LANG_H
#define LANG_H 1

#include <object.h>
#include <method.h>
#include <type.h>
#include <monitor.h>
#include <int.h>
#include <bool.h>
#include <str.h>

extern id msgSend(id obj, SEL cmd, ...);
extern IMP class_getMethodImplementation(Class class, SEL cmd);

#include <stdio.h>
#include <stdlib.h>
#define ABORT(...) do { fprintf(stderr, __VA_ARGS__); abort(); } while (0)

#endif
