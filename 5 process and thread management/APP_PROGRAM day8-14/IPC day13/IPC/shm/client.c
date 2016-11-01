#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main()
{

	key_t mykey = ftok(".", 'a');
	int shmid = shmget(mykey, 100, 0666);
	if(-1 == shmid)
	{
		perror("shmget");
		return -1;
	}

	char *p = shmat(shmid, NULL, 0);

	printf("recv: %s\n", p);

	shmdt(p);

	shmctl(shmid, IPC_RMID, NULL);
}

