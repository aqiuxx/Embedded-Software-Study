#include <stdio.h>
#include <stdlib.h>

#ifndef N
#define N 11
#endif


int quicksort(int a[], int low, int high)
{
	int i,  j;
	i = low;
	j = high;
	int key = a[low];

	while( i < j)
	{
		while(i < j && a[j] >= key) j--;
		a[i] = a[j];

		while(i<j && a[i] <= key) i++;
		a[j] = a[i];
	}

	a[i] = key;

	if (low < i - 1)
	{
		quicksort(a, low, i-1);
	}

	if (high > i + 1)
	{
		quicksort(a, i+1, high);
	}



	return 0;
}


int main(int argc, char const *argv[])
{
	int a[N] =  {23, 34, 14, 38, 46, 16, 68, 15, 7, 31, 26};

	quicksort(a, 0, N-1);

	int i;
	for (i = 0; i < N; ++i)
	{
		printf("%d ", a[i]);
	}

	putchar(10);

	return 0;
}



