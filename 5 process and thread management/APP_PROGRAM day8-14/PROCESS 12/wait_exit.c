#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	pid_t pid;

	pid = fork();
	if(-1 == pid)
	{
		perror("fork");
		exit(-1);
	}
	if(0 == pid)
	{
		sleep(3);
		exit(2);
	}
	else
	{
		int s;
//		wait(&s);
		while(0 == waitpid(pid, &s, WNOHANG))
		{
			printf("waiting !\n");
			sleep(1);
		}

		printf("child process exit: %d\n", WEXITSTATUS(s) );
	}
	

	return 0;
}
