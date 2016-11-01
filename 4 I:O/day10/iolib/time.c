#include <stdio.h>
#include <time.h>


int main()
{
//	time_t t;
//	time(&t);

	while(1)
	{
		time_t t = time(NULL);

		struct tm *ttt = localtime(&t);

		printf("%02d:%02d:%02d", ttt->tm_hour, ttt->tm_min, ttt->tm_sec); fflush(stdout);
		sleep(1);
		printf("\r");
	}
}
