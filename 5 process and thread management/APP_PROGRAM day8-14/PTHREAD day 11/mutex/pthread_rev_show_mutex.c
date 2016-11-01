#include <stdio.h>
#include <pthread.h>

typedef struct{
	char start[100];
	int len;
	pthread_mutex_t arrlock;
}ARR;

void *revbuf(void *p)
{
	ARR *arr = (ARR*)p;

	while(1)
	{
		pthread_mutex_lock(&arr->arrlock);

		int i = 0;
		for(;i<arr->len/2; i++)
		{
			arr->start[i] = arr->start[i]^arr->start[arr->len-i-1];
			arr->start[arr->len-i-1] = arr->start[i]^arr->start[arr->len-i-1];
			arr->start[i] = arr->start[i]^arr->start[arr->len-i-1];
		}

		pthread_mutex_unlock(&arr->arrlock);
	}
}


void *showbuf(void *p)
{
	ARR *arr = (ARR*)p;

	while(1)
	{
		
		pthread_mutex_lock(&arr->arrlock);

		printf("%s\n", arr->start);

		pthread_mutex_unlock(&arr->arrlock);
	}
}

int main()
{
	ARR  arr= {{"123456789"}, 9, 0};
	pthread_mutex_init(&arr.arrlock, NULL);

	pthread_t t1, t2;
	pthread_create(&t1, NULL, revbuf, &arr);
	pthread_create(&t2, NULL, showbuf, &arr);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
}

