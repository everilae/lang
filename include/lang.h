#ifndef LANG_H
#define LANG_H 1

#include <object.h>
#include <selector.h>
#include <type.h>
#include <int.h>
#include <bool.h>
#include <str.h>

extern Object* msg_send(Object* obj, SEL cmd, ...);
extern IMP get_implementation(Type* class, SEL cmd);

#endif
