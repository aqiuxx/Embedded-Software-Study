#include <stdio.h>
#include <time.h>

int linesoffile(FILE *fp)
{
	int linenum = 0;
	
	int c;
	while(EOF != (c = fgetc(fp)) )
		if('\n' == c)
			linenum++;

	return linenum;
}

int main(int argc, char *argv[])
{
	if(2 != argc)
	{
		printf("Usage: %s <logfile>\n", argv[0]);
		return -1;
	}


	FILE *fp = fopen(argv[1], "a+");
	if(NULL == fp)
	{
		perror("fopen log");
		return -1;
	}

	int i = linesoffile(fp);

	while(1)
	{
		//get time
		time_t t = time(NULL);

		//to str (ctime)
		
		//printtime
//		printf("%d,%s", i++, ctime(&t) );
		fprintf(fp, "%d,%s", i++, ctime(&t) );
		fflush(fp);
		sleep(1);
	}
}
