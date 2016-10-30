#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

int main()
{
	//create file or open file
	FILE *fp = fopen("test.txt", "a+");
	if(NULL == fp)
	{
		perror("fopen");
		return -1;
	}

	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	while ((read = getline(&line, &len, fp)) != -1) {
	   printf("Retrieved line of length %zu :\n", read);
	   printf("%s", line);
	}


	//write date to test_file
	int num;

	if (line){
		num = atoi(line);
		num ++;
	}
	else num = 1;

	while(1)
	{
		time_t t = time(NULL);

		struct tm *tt = localtime(&t);

		printf("%d, %04d－%02d－%02d %02d:%02d:%02d\n",
			num, tt->tm_year+1900, tt->tm_mon, tt->tm_mday, tt->tm_hour, tt->tm_min, tt->tm_sec);

		fprintf(fp,"%d, %04d－%02d－%02d %02d:%02d:%02d\n",
			num, tt->tm_year+1900, tt->tm_mon, tt->tm_mday, tt->tm_hour, tt->tm_min, tt->tm_sec);
		fflush(fp);
		num++;
		sleep(1);
		printf("\r");
	}

	//free(line);
	//ctrl + c  ---> ?????
	//close file
}
