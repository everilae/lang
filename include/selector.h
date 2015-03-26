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
#define SELECTOR(cmd_, imp_) { \
	OBJECT_INITIALIZER(SelectorType), \
	.cmd = selector(cmd_), \
	.imp = (IMP) imp_ \
}
#define SELECTOR_LIST_END {NULL}
#define SELECTOR_LIST(...) ((Selector[]) {__VA_ARGS__, SELECTOR_LIST_END})

#endif
