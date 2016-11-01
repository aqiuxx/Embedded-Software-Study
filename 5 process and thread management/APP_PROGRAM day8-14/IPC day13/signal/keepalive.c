#include <stdio.h>
#include <signal.h>

void func(int arg)
{
	return;
}

int main()
{
	signal(2, func);
	signal(SIGKILL, SIG_IGN);

	while(1)
	{
		printf("aaaaaaaaaaaa\n");
		sleep(1);
	}
}
