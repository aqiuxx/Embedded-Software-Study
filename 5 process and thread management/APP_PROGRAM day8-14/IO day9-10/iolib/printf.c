#include <stdio.h>
#include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>

int main()
{
//	close(1);

/*
	int fd = open("/dev/tty", O_WRONLY);

	write(fd, "aaaaaaaaaaaaaaaaa", 10);

*/
	while(1)
	{
		printf("aaaaaaaaaaaaaaaaa");
		usleep(5000);
	}
}
