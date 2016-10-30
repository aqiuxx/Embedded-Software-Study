#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int times;
	char *str;

	char buf[100] = {0}; 
//get arg from argv
	if(3 == argc)
	{
		times = atoi(argv[1]);
		str = argv[2];
	}
//get arg from env
	else if(str = getenv("STR"))
	{
		times = atoi( getenv("TIMES") );
	}
	else
	{
		FILE *fp = fopen(".myecho", "r");
		fgets(buf, sizeof buf, fp);
		times = atoi(buf);

		fgets(buf, sizeof buf, fp);
		str = buf;
	
	}
//get arg from file


	while(times--)
		printf("%s\n", str);

}
