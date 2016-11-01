#include "tpool.h"
#include <stdio.h>

void *show_int(void *arg)
{
	printf("[%lu]%d\n", pthread_self(), (int)arg);
	sleep(1);
}

int main()
{
	//create a tpool
	tpool_t *mypool = tpool_create(1000);

	//add n task
	int n = 1000;
	while(n--)
	{
		tpool_add_task(mypool, show_int, (void *)n);
	}

	//delete tpool
	tpool_destroy(mypool);

	pause();
}
