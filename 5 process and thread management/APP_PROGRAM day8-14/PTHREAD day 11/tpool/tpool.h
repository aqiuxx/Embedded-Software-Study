#ifndef _TP_
#define _TP_

#include <pthread.h>

typedef struct ttask{
	void * (*func)(void *);
	void *arg;

	struct ttask *next;
}ttask_t;

typedef struct tpool{
	ttask_t *taskhead;
	pthread_mutex_t tasklock;

	pthread_t *tids;
	pthread_cond_t dotaskcond;
}tpool_t;

tpool_t *tpool_create(int nthread);
int tpool_add_task(tpool_t *tpool, void * (*taskfunc)(void *), void *taskarg);
int tpool_destroy(tpool_t *tpool);


#endif
