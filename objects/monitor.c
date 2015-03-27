#include <lang.h>
#include <debug.h>

static id
Monitor_init(Monitor this, SEL cmd)
{
	pthread_mutexattr_t mutexattr;

	if (pthread_mutexattr_init(&mutexattr)) {
		goto mutex_error;
	}

	pthread_mutexattr_settype(&mutexattr, PTHREAD_MUTEX_RECURSIVE);

	if (pthread_mutex_init(&this->mutex, &mutexattr)) {
		goto mutex_error;
	}

	pthread_mutexattr_destroy(&mutexattr);

	pthread_condattr_t condattr;
	if (pthread_condattr_init(&condattr)) {
		goto cond_error;
	}

	if (pthread_cond_init(&this->cond, &condattr)) {
		goto cond_error;
	}

	pthread_condattr_destroy(&condattr);
	return (id) this;

cond_error:
	pthread_mutexattr_destroy(&mutexattr);

mutex_error:
	free(this);
	return NULL;
}

static id
Monitor_dealloc(Monitor this)
{
	pthread_cond_destroy(&this->cond);
	pthread_mutex_destroy(&this->mutex);
	free(this);
	return NULL;
}

static id
Monitor_acquire(Monitor this, SEL cmd)
{
	pthread_mutex_t* mut = &this->mutex;
	pthread_cond_t* cnd = &this->cond;
	pthread_t self = pthread_self();

	DPRINTF("acquire\n");

	pthread_mutex_lock(mut);
	if (this->locked && pthread_equal(this->owner, self)) {
		goto locked;
	}
	while (this->locked) {
		pthread_cond_wait(cnd, mut);
	}
	this->locked = true;
	this->owner = self;
locked:
	pthread_mutex_unlock(mut);
	return NULL;
}

static id
Monitor_release(Monitor this, SEL cmd)
{
	pthread_mutex_t* mut = &this->mutex;
	pthread_cond_t* cnd = &this->cond;

	pthread_mutex_lock(mut);
	this->locked = false;
	pthread_mutex_unlock(mut);
	pthread_cond_signal(cnd);

	DPRINTF("release\n");
	return NULL;
}

struct class MonitorType = {
	OBJECT_INITIALIZER(TypeType),

	.super = &ObjectType,
	.name = "monitor",

	.size = sizeof(struct monitor),

	.methods = METHOD_LIST(
		METHOD(init, Monitor_init),
		METHOD(dealloc, Monitor_dealloc),
		METHOD(enter, Monitor_acquire),
		METHOD(exit, Monitor_release)
	),
};
