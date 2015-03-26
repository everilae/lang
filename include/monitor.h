#ifndef MONITOR_H
#define MONITOR_H 1

#include <pthread.h>
#include <stdbool.h>

#include <object.h>

typedef struct Monitor {
	OBJECT_HEAD;
	/* Mutex protecting lock and condition */
	pthread_mutex_t mutex;
	/* Condition for signalling availability changes */
	pthread_cond_t cond;
	/* Availability lock */
	bool locked;
} Monitor;

extern Type MonitorType;

#define MONITOR_INITIALIZER { \
	.mutex = PTHREAD_MUTEX_INITIALIZER, \
	.cond = PTHREAD_COND_INITIALIZER, \
	.locked = false }

#endif
