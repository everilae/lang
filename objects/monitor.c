#include <lang.h>
#include <debug.h>

static Object*
Monitor_acquire(Monitor* this, SEL cmd)
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
}

static Object*
Monitor_release(Monitor* this, SEL cmd)
{
	pthread_mutex_t* mut = &this->mutex;
	pthread_cond_t* cnd = &this->cond;

	pthread_mutex_lock(mut);
	this->locked = false;
	pthread_mutex_unlock(mut);
	pthread_cond_signal(cnd);

	DPRINTF("release\n");
}

Type MonitorType = {
	OBJECT_INITIALIZER(TypeType),

	.base = &ObjectType,
	.name = "monitor",

	.selectors = SELECTOR_LIST(
		SELECTOR(enter, Monitor_acquire),
		SELECTOR(exit, Monitor_release)
	),
};
