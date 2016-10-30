#include <stdio.h>
#include <stdlib.h>


#ifndef N
#define N 27
#define N_1M 4
#define N_5M 11
#define N_1H 11
#endif

typedef int data_t;


/*球队列的结构体声明*/
typedef struct node
{
	data_t data;
	struct node* next;
}ball_linknode_t;

typedef struct
{
	ball_linknode_t *front;
	ball_linknode_t *rear;
}ball_seqlist_t;


/*****************栈相关函数***********************/

//定义结构体
// typedef struct {
// 	data_t data[N];
// 	int top;
// }seqstack_t;

typedef struct seqstack
{
	data_t *data;
	int maxlen;
	int top;
}seqstack_t;

//创建一个空的栈
seqstack_t * seqstack_create( int len){
	seqstack_t *s;
	s = (seqstack_t *)malloc(sizeof(seqstack_t));
	s->data = (data_t *)malloc(sizeof(data_t) * len);

	//s->top = 0;
	s->top = -1;
	s->maxlen = len;

	return s;
}

int seqstack_clear(seqstack_t *s){

	s->top = -1;
	return 0;
}

//判断栈是否为满
int seqstack_full(seqstack_t *s)
{
	//return s->top ==  s->maxlen ? 1 : 0;
	return s->top == s->maxlen - 1 ? 1 : 0; 
}

//判断栈是否为空
int seqstack_empty(seqstack_t *s)
{
	//return s->top == 0 ? 1 : 0;
	return s->top == -1 ? 1 : 0;
}

//入栈（压栈）
int seqstack_push(seqstack_t *s, data_t value)
{
	if(seqstack_full(s))
	{
		printf("seqstack is full\n");
		return -1;
	}

	//s->data[s->top] = value;
	//s->top++;

	s->top++;
	s->data[s->top] = value;

	return 0;
}


//出栈（弹栈）
data_t seqstack_pop(seqstack_t *s)
{
	data_t value;

	if(seqstack_empty(s))
	{
		printf("seqstack is empty\n");
		return -1;
	}
#if 0
	s->top--;
	value = s->data[s->top];
#endif

#if 1
	value = s->data[s->top];
	s->top--;
#endif

	return value;
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

/******************队列相关函数***********************/

/*球队列的创建*/
ball_seqlist_t * ball_seqlist_create()
{
	ball_seqlist_t * ball_sq;

	ball_sq = (ball_seqlist_t *)malloc(sizeof(ball_seqlist_t));

	ball_sq->front = ball_sq->rear = (ball_linknode_t *)malloc(sizeof(ball_linknode_t));


	ball_sq->front->next = NULL;

	return ball_sq;
}

/*球队列的入队*/
int ball_seqlist_in(ball_seqlist_t *ball_sq, data_t value)
{
	ball_linknode_t * tmp = (ball_linknode_t *)malloc(sizeof(ball_linknode_t));

	tmp->data = value;

	tmp->next = NULL;


	ball_sq->rear->next = tmp;

	ball_sq->rear = tmp;

	return 0;
}

/*球队列的判断空函数*/
int ball_seqlist_isEmpty(ball_seqlist_t *ball_sq)
{
	return ball_sq->front == ball_sq->rear ? 1 : 0;
}

/*球队列的显示*/
int ball_seqlist_show(ball_seqlist_t *ball_sq){

	ball_linknode_t *p = ball_sq->front;

	while( p->next ){

		// printf("%d ", p->data);

		p = p->next;
		printf("%d ", p->data);

	}

	// printf("%d,\n", p->data);

	putchar(10);

	return 0;
}

/*球队列的出队*/
data_t ball_seqlist_out(ball_seqlist_t *ball_sq)
{

#if 1
	ball_linknode_t *temp = NULL;
	data_t value;

	if(ball_seqlist_isEmpty(ball_sq))
	{
		printf("linkqueue is empty\n");
		return (data_t)-1;
	}

	temp = ball_sq->front->next;
	ball_sq->front->next = temp->next;

	value = temp->data;

	free(temp);
	temp = NULL;

	if(ball_sq->front->next == NULL)
	{
		ball_sq->rear = ball_sq->front;
	}

	return value;

#else

	if(ball_seqlist_isEmpty(ball_sq))
	{
		printf("linkqueue is empty\n");
		return (data_t)-1;
	}

	ball_linknode_t * tmp = ball_sq->front;
	data_t value;

	ball_sq->front = ball_sq->front->next;
	value = ball_sq->front->data;

	free(tmp);
	tmp = NULL;

	// ball_seqlist_show(ball_sq);
	// getchar();
	return value;

#endif

}




/***************** 队列和栈 相关操作***********************/

/*将剩余元素全部出栈，并逆序加载在队列末端*/
void PopAllBallStack(seqstack_t *s, ball_seqlist_t *ball_sq)
	{
		while(!seqstack_empty(s))
			ball_seqlist_in(ball_sq, seqstack_pop(s));
		return;
	}

/*队列变为满时，判断是否是初始状态*/

int ball_seqlist_Check(ball_seqlist_t *ball_sq)
{
	ball_linknode_t *p = ball_sq->front->next;
	// ball_linknode_t *p = ball_sq->front;  //会导致头删除问题出错

	while( p->next ){


		if (p->data > p->next->data)
		{
			return 0;
		}

		p = p->next;

	}

	return 1;
}

/***************** main 函数**********************/
int main(int argc, char const *argv[])
{
	ball_seqlist_t * ball_sq1 = ball_seqlist_create();

	data_t value1;

/*****************test ball_seqlist is ok***********************/
	ball_seqlist_in(ball_sq1, 10);
	ball_seqlist_in(ball_sq1, 20);
	ball_seqlist_in(ball_sq1, 30);
	ball_seqlist_in(ball_sq1, 40);
	ball_seqlist_in(ball_sq1, 50);

	ball_seqlist_show(ball_sq1);


	value1 = ball_seqlist_out(ball_sq1);
	printf("value1 = %d\n", value1);

	value1 = ball_seqlist_out(ball_sq1);
	printf("value2 = %d\n", value1);

	ball_seqlist_show(ball_sq1);
	/*********************************************************/

/*****************test ball_stack is ok***********************/
	seqstack_t *s = seqstack_create(32);

	seqstack_push(s, 10);
	seqstack_push(s, 20);
	seqstack_push(s, 30);
	seqstack_push(s, 40);
	seqstack_push(s, 50);
	seqstack_show(s);

	printf("%d\n", seqstack_pop(s));
	seqstack_show(s);
	printf("%d\n", seqstack_pop(s));
	seqstack_show(s);
	printf("%d\n", seqstack_pop(s));
	seqstack_show(s);
	printf("%d\n", seqstack_pop(s));
	seqstack_show(s);
	printf("%d\n", seqstack_pop(s));
	seqstack_show(s);
	printf("%d\n", seqstack_pop(s));
	seqstack_show(s);
/**************************************************************/
	printf("ball_sq START\n");
	int flag = 0 , count = 0, i = 0;

	ball_seqlist_t * ball_sq = ball_seqlist_create();
	data_t value;

	for (i = 1; i <= N; ++i)
	{
		ball_seqlist_in(ball_sq, i);
	}
	ball_seqlist_show(ball_sq);


	seqstack_t *s_1minute = seqstack_create(N_1H);
	seqstack_t *s_5minute = seqstack_create(N_5M);
	seqstack_t *s_1hour = seqstack_create(N_1H);

	while(!flag){
		count ++;

		value = ball_seqlist_out(ball_sq);
		// if (-1 == value)
		// {
		// 	printf("%d\n", count);
		// 	getchar();
		// }

		if (s_1minute->top != N_1M - 1)
		{
			seqstack_push(s_1minute, value);
		}
		else//(s_1minute->top != N_1M - 1)
		{
			PopAllBallStack(s_1minute, ball_sq);
			if (s_5minute->top != N_5M - 1)
			{
				seqstack_push(s_5minute, value);
			}
			else//if (s_5minute->top != N_5M - 1)
			{
				PopAllBallStack(s_5minute, ball_sq);
				if (s_1hour->top != N_1H - 1)
				{
					seqstack_push(s_1hour, value);
				}
				else//if (s_1hour->top != N_1H - 1)
				{
					PopAllBallStack(s_1hour, ball_sq);
					ball_seqlist_in(ball_sq, value);
					if (ball_seqlist_Check(ball_sq))
					{
						flag = 1;
						printf("Its cost %d minutes\n", count);
					}

				}//if (s_1hour->top != N_1H - 1)

			}//if (s_5minute->top != N_5M - 1)
		}// if (s_1minute->top != N_1M - 1)

	}//while(!flag)

	ball_seqlist_show(ball_sq);

	int hour = count / 60;
    printf("it passed %d days %d hours %d minutes\n", hour/24, hour%24, count%60);

	return 0;
}


/*****************栈相关函数***********************/

/*typedef struct stack_node
{
	data_t data;
	struct stack_node * next;
}linkstack_t;


/／创建一个空的栈
linkstack_t *linkstack_create()
{
	linkstack_t *s = (linkstack_t *)malloc(sizeof(linkstack_t));

	s->next = NULL;

	return s;
}

// 判断栈是否为空
int linkstack_empty(linkstack_t *s)
{
	return s->next == NULL ? 1 : 0;
}

// 入栈（压栈）(单链表的头插法)
int linkstack_push(linkstack_t *s, data_t value)
{
	linkstack_t *temp = (linkstack_t *)malloc(sizeof(linkstack_t));
	temp->data = value;

	temp->next = s->next;
	s->next = temp;

	return 0;
}

// 出栈（弹栈） (类似与单链表的头删法)
data_t linkstack_pop(linkstack_t *s)
{
	linkstack_t *temp = NULL;
	data_t value = 0;

	if(linkstack_empty(s))
	{
		printf("linkstack is empty\n");
		return (data_t)-1;
	}

	temp = s->next;
	s->next = temp->next;

	value = temp->data;

	free(temp);
	temp = NULL;

	return value;
}

// 队列打印数据
int linkstack_show(linkstack_t *s)
{
	while(s->next != NULL)
	{
		s = s->next;
		printf("%d ", s->data);
	}

	putchar(10);

	return 0;
}*/