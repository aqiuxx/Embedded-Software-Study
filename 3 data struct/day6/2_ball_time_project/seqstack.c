#include "seqstack.h"

//创建一个空的栈
seqstack_t *seqstack_create()
{
	seqstack_t *s;
	s = (seqstack_t *)malloc(sizeof(seqstack_t));

	//s->top = 0;
	s->top = -1;

	return s;
}

//判断栈是否为满
int seqstack_full(seqstack_t *s)
{
	//return s->top == N ? 1 : 0;
	return s->top == N - 1 ? 1 : 0; 
}

//判断栈是否为空
int seqstack_empty(seqstack_t *s)
{
	//return s->top == 0 ? 1 : 0;
	return s->top == -1 ? 1 : 0;
}

//入栈（压栈）
int seqstack_push(seqstack_t *s, datatype_t value)
{
	if(seqstack_full(s))
	{
		printf("seqstack is full\n");
		return -1;
	}
#if 0
	s->data[s->top] = value;
	s->top++;
#else
	s->top++;
	s->data[s->top] = value;
#endif
	return 0;
}

//打印数据
int seqstack_show(seqstack_t *s)
{
	int i = 0;
#if 0
	for(i = 0; i < s->top; i++)
	{
		printf("%d ", s->data[i]);
	}
	putchar(10);
#else
	for(i = 0; i <= s->top; i++)
	{
		printf("%d ", s->data[i]);
	}
#endif

	putchar(10);

	return 0;
}

//出栈（弹栈）
datatype_t seqstack_pop(seqstack_t *s)
{
	datatype_t value;

	if(seqstack_empty(s))
	{
		printf("seqstack is empty\n");
		return -1;
	}
#if 0
	s->top--;
	value = s->data[s->top];
#else
	value = s->data[s->top];
	s->top--;
#endif

	return value;
}
