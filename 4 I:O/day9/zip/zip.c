#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <malloc.h>

/**
 * 注意:
 * 1	数组越界问题
 * 2	buf_size 最大取 127
 * 3	size必须的是两倍
 *
 * 缺陷：
 * 当某一个数的个数大于127时，压缩算法效率有问题
 */

#ifndef BUF_SIZE
#define BUF_SIZE 127
#endif

char * encode(char *buf_src, int len, int *n)
{
	int i = 0, j = 0;

	char * buf_dest = (char*)malloc(len * 2);//此处注意必须的事两倍

	while(i < len)
	{
		int k = 1;
		char c = buf_src[i];
		printf("%d %c\n",len, c);

		while( i+k < len && c == buf_src[i+k] )//数组是否越界
		{
			k++;
		}

		i += k;

		buf_dest[j] = c;

		//相同的位数k
		buf_dest[j+1] = k;

		j = j + 2;
	}

	*n = j;
	return buf_dest;
}

/*char * uencode(char *buf_src, int len, int *n)
{
	return ;
}*/

int main(int argc, char const *argv[])
{
	if (2 != argc)
	{
		printf("Usage: %s <file>", argv[0]);
		return -1;
	}
	int fds = open(argv[1],O_RDWR, 0666);
	if (-1 == fds)
	{
		printf("%d %s\n", errno, strerror(errno) );
		return -1;
	}

	char DestFile[20] = {0};
	strcat(strcat(DestFile,argv[1]),"_zip.txt");

	int fdd = open(DestFile,O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (-1 == fdd)
	{
		printf("%d %s\n", errno, strerror(errno) );
		return -1;
	}

	//解压文件打开
	int fds1 = open(DestFile,O_RDWR, 0666);
	if (-1 == fds1)
	{
		printf("%d %s\n", errno, strerror(errno) );
		return -1;
	}

	char DestFile1[20] = {0};
	strcat(strcat(DestFile1,argv[1]),"_unzip.txt");

	int fdd1 = open(DestFile1,O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (-1 == fdd1)
	{
		printf("%d %s\n", errno, strerror(errno) );
		return -1;
	}

	/* ********************************************************* */
	/**
	 * 压缩
	 */
	char buf_src[BUF_SIZE] = {0};

	int ret;
	int n;
	char* buf_dest;

	while(ret = read(fds, buf_src, BUF_SIZE))
	{
		buf_dest = encode(buf_src, ret, &n);

		if( -1 == write(fdd, buf_dest, n))
		{
			perror("write data to  ");
			return -1;
		}
	}

	printf("buf_dest_read_after %s\n", buf_dest);

	/* ********************************************************* */
	/**
	 * 解缩
	 */

/*	char buf_src1[BUF_SIZE] = {0};

	int ret1;
	int n1;
	char* buf_dest1;

	while(ret = read(fds1, buf_src1, BUF_SIZE))
	{
		buf_dest = encode(buf_src, ret, &n);

		if( -1 == write(fdd, buf_dest, n))
		{
			perror("write data to  ");
			return -1;
		}
	}

	printf("buf_dest_read_after %s\n", buf_dest);*/


	return 0;
}
