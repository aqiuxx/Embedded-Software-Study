#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/types.h>
       #include <sys/stat.h>
       #include <unistd.h>

int main()
{
	DIR *dp = opendir(".");

	struct dirent *p;

	struct stat s;
	while( p = readdir(dp) )
	{
//		printf("%s\n", p->d_name);
		stat(p->d_name, &s);
		printf( "%10ld \033[1;31;40m %s  \033[0m\n", s.st_size, p->d_name );
	}
}
