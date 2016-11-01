#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *env[])
{
	while(argc--)
		printf("%s\n", *argv++);

	printf("========================================\n");

//	printf("%s\n", getenv("XXX"));

	while(*env)
		printf("%s\n", *env++);
}
