#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <string.h>

int main()
{
	if(-1 == mkfifo("/home/linux/up.fifo", 0666) )
	{
		if(EEXIST!= errno)
		{
			perror("mkfifo up");
			return -1;
		}
	}

	if(-1 == mkfifo("/home/linux/down.fifo", 0666) )
	{
		if(EEXIST!= errno)
		{
			perror("mkfifo down");
			return -1;
		}
	}

	int fdup = open("/home/linux/up.fifo", O_RDONLY);
	if(-1 == fdup)
	{
		perror("open up");
		return -1;
	} 

	int fddown= open("/home/linux/down.fifo", O_WRONLY);
	if(-1 == fddown)
	{
		perror("open down");
		return -1;
	} 

	char buf[100] = {0};
	while(1)
	{
		read(fdup, buf, 100);
		printf("recv: %s\n", buf);
		if(0 == strcmp("time", buf) )
		{
			time_t t;
			time(&t);
			strncpy(buf, ctime(&t), 24);
		}

		write(fddown, buf, 100);
	}
}
