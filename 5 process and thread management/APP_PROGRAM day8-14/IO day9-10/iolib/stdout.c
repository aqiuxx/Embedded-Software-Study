#include <stdio.h>

//stdin
//stdout /dev/tty
//stderr /dev/tty

int main()
{
//	fwrite("stdout hello", 1, 10, stdout);
//	fwrite("stderr hello", 1, 10, stderr);

//	fprintf(stdout, "hello: %s", "out");
//	fprintf(stderr, "hello: %s", "err");

//	fclose(stdout);

	freopen("1.txt", "w", stdout);

	printf("hello===================");  //fprintf(stdout, "hello");

}
