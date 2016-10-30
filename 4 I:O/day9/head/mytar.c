#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#ifndef MAXFILE
#define MAXFILE 10
#endif

typedef struct info
{
	char name[20];
	size_t size;
}FILEINFO;

typedef struct header{
	FILEINFO infos[MAXFILE];
	int nextheader;
}HEADER;

int getfilesize(const char *file)
{
	int fd = open(file, O_RDONLY);
	if (-1 == fd)
	{
		return 0;
	}

	return lseek(fd, 0 ,SEEK_END);
}

int fillheader(HEADER *myheader, char *files[], int n)
{
	if (MAXFILE >= n)
	{
		while(n--)
		{
			strcpy(myheader->infos[n].name, files[n]);
			myheader->infos[n].size = getfilesize(files[n]);
		}
	}

	return 0;
}

int writefiledata(int fdtar, HEADER *header)
{
	int i = 0;
	for(;i<MAXFILE; i++)
	{
		if(*header->infos[i].name=='\0' && header->infos[i].size==0)
			break;

		int fd = open(header->infos[i].name, O_RDONLY);

		char buf[1024];
		int n;
		while(n = read(fd, buf, sizeof buf))
			write(fdtar, buf, n);

		close(fd);
	}
}

int main(int argc, char *argv[])
{
	if(3 > argc)
	{
		printf("Usage: %s <*.mytar> [file...]\n", argv[0]);
		return -1;
	}
	//scan files
	//create header
	HEADER myheader = {0};
	fillheader(&myheader, argv+2, argc-2);

	//create tarfile
	int fdtar = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if(-1 == fdtar)
	{
		perror("create tar file");
		return -1;
	}

	//write header and file datas
	write(fdtar, &myheader, sizeof myheader);

	writefiledata(fdtar, &myheader);

	//close
	close(fdtar);

	return 0;
}
