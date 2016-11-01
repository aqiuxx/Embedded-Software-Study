#include <stdio.h>
#include <sys/types.h>
#include <signal.h>

int main(int argc, char **argv)
{
	if(3 != argc)
	{
		printf("Usage: <%s> <pid> <sig>\n", argv[0]);
		return -1;
	}

	kill( atoi(argv[1]), atoi(argv[2]) );
}
