#include <stdio.h>
#include <stdlib.h>

#ifndef N
#define N 13
#endif

#ifndef ADDR_SIZE
#define ADDR_SIZE 4
#endif

typedef int datatype;

typedef struct node
{
	datatype data;
	struct node * next;
}HASH,hash_t;

HASH ** hash_create()
{
	int i;
	HASH ** h = (HASH **)malloc(4 * ADDR_SIZE);

	for (i = 0; i < N; ++i)
	{
		h[i] = (hash_t *)malloc(sizeof(hash_t));
		h[i]->next = NULL;
	}

	return h;
}

int hash_insert(HASH **h, datatype value)
{
	datatype key = value % N;
	hash_t * p = h[key];

	hash_t * tmp;
	tmp = (hash_t *)malloc(sizeof(hash_t));
	tmp->data = value;

	while(p->next != NULL && value > p->next->data)
	{
		p = p->next;
	}

	tmp->next = p->next;
	p->next = tmp;

	return 0;
}

int hash_search(HASH ** h, datatype value)
{
	datatype key = value % N;
	hash_t * p = h[key];

	while(p->next != NULL )
	{
		p = p->next;
		if ( value == p->data)
		{
			printf("data is foud in key = %d\n", key);
			return 1;
		}
	}

	return 0;
}

int hash_show(HASH **h)
{
	hash_t * p ;

	int i;
	for (i = 0; i < N; ++i)
	{
		p = h[i];
		if (p->next == NULL)
		{
			printf("+++NULL++\n");
		}

		while(p->next != NULL)
		{
			p = p->next;
			printf("%d\n", p->data);
		}
		putchar(10);
	}
	return 0;
}


int main(int argc, char const *argv[])
{
	datatype a[11] =  {23, 34, 14, 38, 46, 16, 68, 15, 7, 31, 26};

	HASH ** h = hash_create();

	int i;
	for (i = 0; i < 11; ++i)
	{
		hash_insert(h, a[i]);
	}

	hash_show(h);

	hash_search(h, 38);

	return 0;
}



