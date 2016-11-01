#include <stdio.h>


int main()
{
	srand( time(NULL) );

	int i = 10;
	while(i--)
		printf("%d\n", rand() );
}
