#include <stdio.h>
#include <fcntl.h>           /* For O_* constants */
       #include <sys/stat.h>        /* For mode constants */
       #include <semaphore.h>


sem_t *a;
sem_t *b;

int main()
{
	a = sem_open("/aaa", O_CREAT, 0666, 1);
	if(SEM_FAILED == a)
	{
		perror("semopen a");
		return -1;
	}

	b = sem_open("/bbb", O_CREAT, 0666, 0);
	if(SEM_FAILED == b)
	{
		perror("semopen b");
		return -1;
	}

	while(1)
	{
		sem_wait(a);
		printf("hello\n");
		sem_post(b);
	}
}
