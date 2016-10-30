#include <stdio.h>
#include <stdlib.h>

#ifndef N
#define N 4
#endif

typedef int data_t;

typedef struct seqstack
{
	data_t *data;
	int maxlen;
	int top;
}seqstack_t;

seqstack_t * seqstack_create( int len){
	seqstack_t *ss;
	ss = (seqstack_t *)malloc(sizeof(seqstack_t));
	ss->data = (data_t *)malloc(sizeof(data_t) * len);

	ss->top = -1;
	ss->maxlen = len;

	return ss;
}

int seqstack_clear(seqstack_t *s){

	s->top = -1;
	return 0;
}

int seqstack_isempty(seqstack_t *s){

	return (s->top == -1 ? 1 : 0);
}

int seqstack_full(seqstack_t *s){

	return (s->top == s->maxlen - 1 ? 1 : 0);
}

int seqstack_push(seqstack_t *s, data_t value){
	if (seqstack_full(s))
	{
		printf("overflow\n");
		return -1;
	}
	else{
		printf("ssssss\n");
		s->top++;
		s->data[s->top] = value;
		//printf("%d\n", s->data[s->top]);
	}
	return 0;
}

int seqstack_pop(seqstack_t *s){
	data_t value;
	if (seqstack_isempty(s))
	{
		printf("seqstack_isempty\n");
		return -1;
	}
	else{
		printf("ssssss\n");
		value = s->data[s->top];
		s->top--;
		//printf("%d\n", s->data[s->top]);
	}
	return value;
}

int seqstack_show(seqstack_t *s){

	int i = 0;
#if 0
	for(i = 0; i < s->top; i++)
	{
		printf("%d ", s->data[i]);
	}
	putchar(10);
#endif
#if 1
	for(i = 0; i <= s->top; i++)
	{
		printf("%d ", s->data[i]);
	}
#endif

	putchar(10);

	return 0;
}

int main(int argc, char const *argv[])
{
	seqstack_t *s;
	s = seqstack_create(N);

	seqstack_push(s, 1);
	seqstack_push(s, 2);
	seqstack_push(s, 3);
	seqstack_push(s, 4);
	seqstack_push(s, 5);

	seqstack_pop(s);

	seqstack_show(s);

	return 0;
}
