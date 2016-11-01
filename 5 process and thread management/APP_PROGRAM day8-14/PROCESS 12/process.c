#include <stdio.h>

int main()
{
	int a;

	while(1)
	a = fork();
	if(a)
	{
		while(1)
			printf("aaaaaaaaaaaaaaaaaaaaa\n");
	}
	else
	{
		while(1)
			printf("adddddddddddddddddddddddddddddddaaaaaaaaaaaaaaaaaaaaa\n");
	}
}
