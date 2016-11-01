#include <stdio.h>
#include <signal.h>

void func(int sig)
{
	printf("I am right!\n");
	exit(0);
}

int main()
{
//	signal(11, func);
	signal(11, SIG_IGN);

	*((int*)NULL) = 10;

	while(1);
}
