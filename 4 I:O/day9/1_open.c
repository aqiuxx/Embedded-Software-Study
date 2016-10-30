#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
//#include <sys/types.h>
#include <unistd.h>


int main(int argc, char const *argv[])
{
	int i;
	int fd = open("1.txt",O_RDWR | O_CREAT, 0666);
	if (-1 == fd)
	{
		printf("%d %s\n", errno, strerror(errno) );
		return -1;
	}

#if 1
	char buf[10] = {"0123456789"};
	if( -1 == write(fd, buf, 10))
	{
		perror("write 1.txt");
		return -1;
	}
#endif
	printf("buf_read_before0 %s\n", buf);
	lseek(fd, 0, SEEK_SET);
	int ret = read(fd, buf, 10);

	printf("buf_read_before1 %s\n", buf);


	for (i = 0; i < 5; ++i)
	{
		buf[i] ^= buf[10 - i -1];
		buf[10-i -1] ^= buf[i];
		buf[i] ^= buf[10 - i -1];
	}

	printf("buf_read_after0 %s\n", buf);

	lseek(fd, 0, SEEK_SET);

	if( -1 == write(fd, buf, 10))
	{
		perror("write 1.txt");
		return -1;
	}


	printf("buf_read_after %s\n", buf);

	return 0;
}
