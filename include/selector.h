#ifndef SELECTOR_H
#define SELECTOR_H 1

#include <object.h>

typedef const char* SEL;
typedef Object* (*IMP)(Object* this, SEL cmd, ...);

typedef struct {
	OBJECT_HEAD;
	SEL cmd;
	IMP imp;
} Selector;

extern Type SelectorType;

#define selector(cmd) (#cmd)
#define SELECTOR(cmd, imp) {&SelectorType, selector(cmd), (IMP) imp}

#endif
