#include <stdio.h>
#include <pthread.h>
#include <strings.h>
#include <malloc.h>

char *rev_buf(const char *buf, int len)
{
//	static char rbuf[100];

	char *rbuf = malloc(100);
	bzero(rbuf, 100);

	while(len--)
		rbuf[len] = *buf++;

	return rbuf;
}

void *func1(void *arg)
{
	char buf[] = "1234567890";
	printf("[%lu] %s\n", pthread_self(), buf);
	char *rbuf = rev_buf(buf, 10);
	sleep(2);
	printf("[%lu] %s\n", pthread_self(), rbuf);
}

void *func2(void *arg)
{
	char buf[] = "abcde";
	printf("[%lu] %s\n", pthread_self(), buf);
	sleep(1);
	char *rbuf = rev_buf(buf, 5);
	printf("[%lu] %s\n", pthread_self(), rbuf);
}

int main()
{
	pthread_t t1, t2;
	pthread_create(&t1, NULL, func1, NULL);
	pthread_create(&t2, NULL, func2, NULL);

	pause();
}
