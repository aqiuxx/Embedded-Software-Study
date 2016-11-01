#include <stdio.h>
#include <pthread.h>

void *func(void *arg)
{
	sleep(2);
	*((int*)arg) = 0;
}

int main()
{
	volatile int a = 1;

	pthread_t t;
	pthread_create(&t, NULL, func, &a);

	while(a);

	printf("aaaaaaaaaaaaaaaa\n");
}
