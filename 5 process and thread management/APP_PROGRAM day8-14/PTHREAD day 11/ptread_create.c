#include <stdio.h>
#include <pthread.h>

void *func(void *arg)
{
	char buf[8*1024*1024] = {0};

	while(1)
		printf("%s\n", (char *)arg);
}

int main()
{
	pthread_t tid;
	
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setstacksize(&attr, 10*1024*1024);

	pthread_create(&tid, &attr, func, "jjjjjjjjjjjjjjjjjjjjjjjjjj");

	while(1)
		printf("aaaaaaaaaaaaaa\n");
}
