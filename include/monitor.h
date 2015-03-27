#ifndef MONITOR_H
#define MONITOR_H 1

#include <pthread.h>
#include <stdbool.h>

#include <object.h>

typedef struct Monitor {
	OBJECT_HEAD;
	/* Mutex for guarding Monitor access */
	pthread_mutex_t mutex;
	/* Condition for signalling availability changes */
	pthread_cond_t cond;
	/* Availability lock */
	bool locked;
	/* Current owner, if any (undefined when locked == false) */
	pthread_t owner;
} Monitor;

extern Type MonitorType;

#define MONITOR_INITIALIZER { \
	OBJECT_INITIALIZER(MonitorType), \
	.mutex = PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP, \
	.cond = PTHREAD_COND_INITIALIZER, \
	.locked = false }

/* Optimizing compilers should see that this will run 1. and only 1. */
#define SYNCHRONIZED(o) \
	for (int __synchronized_running = (msg_send(ObPtr(ObPtr(o)->monitor), selector(enter)), 1); \
	     __synchronized_running; \
	     __synchronized_running = (msg_send(ObPtr(ObPtr(o)->monitor), selector(exit)), 0))

#endif
