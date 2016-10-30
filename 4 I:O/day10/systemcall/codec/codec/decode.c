#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <malloc.h>

static int get_num(const char *buf, int size)
{
	int count = 0;
	int i = 0;
	for(;i<size/2; i++)
	{
		count += *++buf;
		buf++;
	}

	return count;
}

char *decode(const char buf[1024]/*  *buf  */, int size, int *n)
{
	//create answer buffer
	int total = get_num(buf, size);
	char *dbuf = malloc(total);

	char c, num;
	int i = 0;
	for(;i<size/2; i++)
	{
		c = *buf++;
		num = *buf++;

		while(num--)
			*dbuf++ = c;
	}

	*n = total;
	return dbuf-total;
}

int main(int argc, char *argv[])
{
	if(2 != argc)
	{
		printf("Usage: %s <file>\n", argv[0]);
		return -1;
	}

	//open source
	int fds = open(argv[1], O_RDONLY);
	if(-1 == fds)
	{
		perror("open src file");
		return -1;
	}

	//create new file
	char destfile[20] = {0};
	strncpy(destfile, argv[1], strlen(argv[1])-3);
	int fdd = open(destfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if(-1 == fdd)
	{
		perror("open des file");
		return -1;
	}

	//read src
	char buf[1024];
	int n;
	char *dbuf;

	int ret;
	while(ret = read(fds, buf, sizeof buf) )
	{	
		//encode data
		dbuf = decode(buf, ret, &n);

		//write into newfile
		write(fdd, dbuf, n);
	}

	//close src & new
	close(fds);
	close(fdd);
}
