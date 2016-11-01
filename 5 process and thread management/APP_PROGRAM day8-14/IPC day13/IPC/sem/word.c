#include <stdio.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
#include <sys/types.h>
       #include <sys/ipc.h>
       #include <sys/sem.h>
int main()
{
	int semid = semget(888, 2, IPC_CREAT | 0666);
	if(-1 == semid)
	{
		perror("semget");
		return -1;
	}

	while(1)
	{
		struct sembuf P = {1, -1, 0};
		semop(semid, &P, 1);

		printf("world\n");
		sleep(1);

		struct sembuf V = {0, 1, 0};
		semop(semid, &V, 1);
	}
}
