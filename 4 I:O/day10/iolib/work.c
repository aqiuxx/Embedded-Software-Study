#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(int argc, const char *argv[])
{
	FILE *fp;
	char temp[30];
	int line_count = 1;
	int j = 10;
	time_t source_time;
	struct tm *str_time;
	int year,month,day,hour,minutes,second;
	if ((fp = fopen("test.txt","a+")) == NULL)
	{
		fprintf(stderr, "fopen() failed:%s\n",strerror(errno));
		return -1;
	}
//	fseek(fp,0,SEEK_SET);
	printf("whence:%ld\n",ftell(fp));
	rewind(fp);

//	fgets(temp,30,fp);
//	printf("%s",temp);
	while (fgets(temp,30,fp) != NULL)
	{
		line_count++;
//		printf("%s",temp);
	}
//	printf(" line:%d,whence:%ld\n",line_count,ftell(fp));
	while (j)
	{
		printf(" line:%d,whence:%ld\n",line_count,ftell(fp));
	//	printf("line:%d\n",line_count);
		source_time = time(NULL);
		str_time = localtime(&source_time);
		year = str_time->tm_year+1900;
		month = str_time->tm_mon+1;
		day = str_time->tm_mday;
		hour = str_time->tm_hour;
		minutes = str_time->tm_min;
		second = str_time->tm_sec;
		printf("%03d, %0d-%d-%d %02d:%02d:%02d\n",line_count,year,month,day,hour,minutes,second);
		fprintf(fp,"%03d, %0d-%d-%d %02d:%02d:%02d\n",line_count,year,month,day,hour,minutes,second);
		fflush(fp);
		line_count++;
		sleep(1);
	}
	fclose(fp);
	return 0;
}
