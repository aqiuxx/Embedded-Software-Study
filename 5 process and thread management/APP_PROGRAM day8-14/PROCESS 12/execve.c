#include <stdio.h>
#include <unistd.h>

int main()
{
	printf("aaaaaaaaaaaaa\n");

	freopen("1.xxx", "w", stdout);
	
	if(-1 == execl("/bin/ls", "/bin/ls", "-l", NULL))
	{
		perror("exe");
		return -1;
	}


	printf("aaaaaaaaaaaaa\n");


}
