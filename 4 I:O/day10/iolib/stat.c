#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
	struct stat buf = {0};

	stat("1.txt", &buf);

	printf("size: %ld\n", buf.st_size);	
}
