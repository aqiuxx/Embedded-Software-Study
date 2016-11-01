#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	int fdup = open("/home/linux/up.fifo", O_WRONLY);
	if(-1 == fdup)
	{
		perror("open up");
		return -1;
	} 

	int fddown = open("/home/linux/down.fifo", O_RDONLY);
	if(-1 == fddown)
	{
		perror("open down");
		return -1;
	} 

	char buf[100] = {0};
	while(1)
	{
		printf("input: "); fflush(stdout);
		gets(buf);
		write(fdup, buf, 100);
		read(fddown, buf, 100);

		printf("recv : %s\n", buf);
	}
}
