#include <stdio.h>
#include <fcntl.h>           /* For O_* constants */
       #include <sys/stat.h>        /* For mode constants */
       #include <semaphore.h>

sem_t *a;
sem_t *b;

int main()
{
	a = sem_open("/aaa", 0);
	if(SEM_FAILED == a)
	{
		perror("semopen a");
		return -1;
	}

	b = sem_open("/bbb", 0);
	if(SEM_FAILED == b)
	{
		perror("semopen b");
		return -1;
	}

	while(1)
	{
		sem_wait(b);
		printf("word\n");
		sleep(1);
		sem_post(a);
	}
}
