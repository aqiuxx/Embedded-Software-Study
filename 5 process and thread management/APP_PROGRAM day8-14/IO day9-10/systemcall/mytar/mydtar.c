#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define MAXFILE 10

typedef struct info{
	char name[20];
	size_t size;
}FILEINTO;

typedef struct header{
	FILEINTO infos[MAXFILE];
	int nextheader;
}HEADER;

int dtarfile(int fdtar, HEADER *header)
{
	int i = 0;
	for(;i<MAXFILE; i++)
	{
		if(*header->infos[i].name=='\0' && header->infos[i].size==0)
			break;
	
		int fd = open(header->infos[i].name, O_WRONLY|O_CREAT|O_TRUNC, 0666);
		int size = header->infos[i].size;
		char buf[size];
		read(fdtar, buf, size);
		write(fd, buf, size);

		close(fd);
	}
	
}

int main(int argc, char *argv[])
{
	if(2 != argc)
	{
		printf("Usage: %s <*.mytar>\n", argv[0]);
		return -1;
	}

	//read header from tarfile
	int fdtar = open(argv[1], O_RDONLY);
	if(-1 == fdtar)
	{
		perror("read header");
		return -1;
	}	

	HEADER myheader = {0};
	//read header
	read(fdtar, &myheader, sizeof myheader);
	

	dtarfile(fdtar, &myheader);

	//close
	close(fdtar);
}
