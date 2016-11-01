#include "tpool.h"
#include <malloc.h>

static void *dotask(void *arg)
{
	tpool_t *tpool = (tpool_t*)arg;

	while(1)
	{
		//if have task
		printf("[%lu]start\n", pthread_self());
		pthread_mutex_lock(&tpool->tasklock);
		while(NULL == tpool->taskhead)
			pthread_cond_wait(&tpool->dotaskcond, &tpool->tasklock);

		ttask_t *mytask = tpool->taskhead;
		tpool->taskhead = mytask->next;
		pthread_mutex_unlock(&tpool->tasklock);

		//do task
		mytask->func(mytask->arg);

		free(mytask);
		printf("[%lu]end\n", pthread_self());


	//cut tsk to do
	}
}

tpool_t *tpool_create(int nthread)
{
	tpool_t *tpool = malloc(sizeof(tpool_t));

	tpool->taskhead = NULL;
	pthread_mutex_init(&tpool->tasklock, NULL);

	tpool->tids = malloc(nthread * sizeof(pthread_t));
	pthread_cond_init(&tpool->dotaskcond, NULL);

	while(nthread--)
		pthread_create(&tpool->tids[nthread], NULL, dotask, tpool);

	return tpool;
}

int tpool_add_task(tpool_t *tpool, void * (*taskfunc)(void *), void *taskarg)
{
	ttask_t *mytask = malloc(sizeof(ttask_t));
	mytask->func = taskfunc;
	mytask->arg = taskarg;
	mytask->next = NULL;

	pthread_mutex_lock(&tpool->tasklock);
	mytask->next = tpool->taskhead;
	tpool->taskhead = mytask;
	pthread_mutex_unlock(&tpool->tasklock);

	pthread_cond_signal(&tpool->dotaskcond);	
}

int tpool_destroy(tpool_t *tpool)
{
	
}

