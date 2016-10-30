#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, const char *argv[])
{
	pid_t pid, ret;
	if((pid = fork()) < 0)
	{
		printf("Error fork \n");
		exit(-1);
	}

	else if(pid == 0 )
	{
		printf("sleep 5s");
		sleep(5);
		exit(3);
	}

	else
	{
		/*ret = 0;
		while(!ret)
		{
			ret = waitpid( pid, NULL, WNOHANG);

			if(ret == pid)
			{
				printf("child process id %d", ret);
				exit(2);
			
			}
			else
				sleep(1);
		}*/

		int s;
		while(  0 == waitpid(pid, &s, WNOHANG))
		{
			printf("child  process");
			sleep(1);
		}
	}

	return 0;
}

