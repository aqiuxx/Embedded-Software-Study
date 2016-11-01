#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main()
{
	key_t mykey = ftok(".", 'a');
	int shmid = shmget(mykey, 100, IPC_CREAT | 0666);
	if(-1 == shmid)
	{
		perror("shmget");
		return -1;
	}

	char *p = shmat(shmid, NULL, 0);

	printf("input: ");fflush(stdout);
	gets(p);

}
