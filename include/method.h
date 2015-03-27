#ifndef METHOD_H
#define METHOD_H 1

#include <object.h>

typedef const char* SEL;
typedef id (*IMP)(id obj, SEL cmd, ...);

typedef struct method {
	OBJECT_HEAD;
	SEL name;
	IMP imp;
}* Method;

extern struct class MethodType;

#define SELECTOR(cmd) (#cmd)
#define METHOD(name_, imp_) { \
	OBJECT_INITIALIZER(MethodType), \
	.name = SELECTOR(name_), \
	.imp = (IMP) imp_ \
}
#define METHOD_LIST_END {NULL}
#define METHOD_LIST(...) ((struct method[]) {__VA_ARGS__, METHOD_LIST_END})

#define method_getName(m) ((m)->name)
#define method_getImplementation(m) ((m)->imp)

#endif
