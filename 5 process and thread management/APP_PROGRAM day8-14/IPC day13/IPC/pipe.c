#include <stdio.h>

int main()
{

	int fd[2];
	pipe(fd);

	int pid = fork();

	if(0 == pid)
	{	
		sleep(3);
		write(fd[1], "hello", 5);
	}
	else
	{

		char buf[10] = {0};
		read(fd[0], buf, 5);

		printf("recv: %s\n", buf);
	}
}
