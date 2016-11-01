#include <stdio.h>

int main()
{
	FILE *fp = fopen("1.txt", "w");
	if(NULL == fp)
	{
		perror("fopen");
		return -1;
	}

	setvbuf(fp, NULL, _IONBF, 0);

	printf("%d\n", fwrite("hello", 1, 5, fp) );
	
//	fflush(fp);

	sleep(10);


	fclose(fp);
}
