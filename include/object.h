#ifndef OBJECT_H
#define OBJECT_H 1

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <pthread.h>

typedef struct {
	pthread_mutex_t mutex;
	pthread_cond_t cond;
} Monitor;

#define MONITOR_INITIALIZER \
	.monitor.mutex = PTHREAD_MUTEX_INITIALIZER, \
	.monitor.cond = PTHREAD_COND_INITIALIZER

#define OBJECT_HEAD \
	struct Type* class; \
	Monitor monitor

#define OBJECT_INITIALIZER(cls) \
	.class = &cls, \
	MONITOR_INITIALIZER

typedef struct Type Type;

typedef struct {
	OBJECT_HEAD;
} Object;

extern Type ObjectType;

extern void* new(Type* class, ...);
extern void delete(Object* o);

extern void Object_new(Object* this, va_list ap);
extern void Object_delete(Object* this);

#define ObPtr(p) ((Object*) (p))
#define ObType(p) (ObPtr(p)->class)

#define ABORT(...) do { fprintf(stderr, __VA_ARGS__); abort(); } while (0)

#endif
