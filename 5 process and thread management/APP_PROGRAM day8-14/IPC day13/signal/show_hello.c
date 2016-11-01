#include <stdio.h>
#include <signal.h>

void func(int arg)
{
	printf("hello\n");
	alarm(3);
	return;
}

int main()
{
	signal(SIGALRM, func);
	alarm(3);

	while(1)
	{
		printf("aaaaaaaaaaaa\n");
		sleep(1);
	}
}
