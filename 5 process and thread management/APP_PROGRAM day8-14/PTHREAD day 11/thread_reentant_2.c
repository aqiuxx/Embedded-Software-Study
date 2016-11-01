#include <stdio.h>
#include <pthread.h>
#include <strings.h>
#include <malloc.h>

#ifdef _REENTRANT
pthread_key_t rbuf_key;
pthread_once_t once_control = PTHREAD_ONCE_INIT;

void myfree(void *p)
{
	free(p);
}

void create_mykey(void)
{
	pthread_key_create(&rbuf_key, myfree);
}
#endif

char *rev_buf(const char *buf, int len)
{

#ifdef _REENTRANT
	pthread_once(&once_control, create_mykey);

	char *rbuf = pthread_getspecific(rbuf_key);
	if(NULL == rbuf)
	{
		rbuf = malloc(100);
		pthread_setspecific(rbuf_key, rbuf);
	}
	printf("%lu:%p\n", pthread_self(), rbuf);
#else
	static char rbuf[100];
#endif
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
