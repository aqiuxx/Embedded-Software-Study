#include <stdio.h>
#include <pthread.h>

pthread_mutex_t flaglock;
int flag = 1;

void *hello(void *p)
{
	while(1)
	{
		pthread_mutex_lock(&flaglock);

		if(1 != flag)
		{
			pthread_mutex_unlock(&flaglock);
			continue;
		}
		pthread_mutex_unlock(&flaglock);

		printf("hello\n");
		
		
		pthread_mutex_lock(&flaglock);
		flag = 2;
		pthread_mutex_unlock(&flaglock);
	}
}

void *the(void *p)
{
	while(1)
	{
		pthread_mutex_lock(&flaglock);

		if(2 != flag)
		{
			pthread_mutex_unlock(&flaglock);
			continue;
		}
		pthread_mutex_unlock(&flaglock);

		printf("the\n");
		
		
		pthread_mutex_lock(&flaglock);
		flag = 3;
		pthread_mutex_unlock(&flaglock);
	}
}

void *word(void *p)
{
	while(1)
	{
		pthread_mutex_lock(&flaglock);

		if(3 != flag)
		{
			pthread_mutex_unlock(&flaglock);
			continue;
		}
		pthread_mutex_unlock(&flaglock);

		printf("word\n");
		
		
		pthread_mutex_lock(&flaglock);
		flag = 1;
		pthread_mutex_unlock(&flaglock);
	}
}

int main()
{
	pthread_mutex_init(&flaglock, NULL);

	pthread_t t1, t2, t3;
	pthread_create(&t1, NULL, hello, NULL);
	pthread_create(&t2, NULL, word, NULL);
	pthread_create(&t3, NULL, the, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
}

