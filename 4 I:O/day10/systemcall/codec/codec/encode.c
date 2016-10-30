#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <malloc.h>

static char num_data(const char *start, int nleft)
{
	char num = 1;

	while(nleft--)
	{
		if(*start == *(start+1))
			num++;
		else
			break;

		start++;
	}

	return num;
}

char *encode(const char buf[127]/*  *buf  */, int size, int *n)
{
	//create answer buffer
	char *ebuf = malloc(size*2);

	int count = 0;
	//encode buf ---> buffer
	while(size--)
	{
		//recode data ebuf
		//recode data num into ebuf
		*ebuf++ = *buf;
		*ebuf++ = num_data(buf, size);
	
		printf("%c:%d\n", *buf, num_data(buf, size));

		count++;
		buf += *(ebuf-1);
		size = size - *(ebuf-1) + 1;
	}

	//return
	*n = 2*count;
	return ebuf - *n;
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
	strcat(strcat(destfile, argv[1]), ".en");
	int fdd = open(destfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if(-1 == fdd)
	{
		perror("open des file");
		return -1;
	}

	//read src
	char buf[127];
	int n;
	char *ebuf;

	int ret;
	while(ret = read(fds, buf, sizeof buf) )
	{	
		//encode data
		ebuf = encode(buf, ret, &n);

		//write into newfile
		write(fdd, ebuf, n);
	}

	//close src & new
	close(fds);
	close(fdd);
}
