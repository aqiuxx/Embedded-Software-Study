//单向循环链表的实现

#include <stdio.h>
#include <stdlib.h>

//定义数据类型
typedef int datatype_t;

//定义结构体
typedef struct node{
	datatype_t data;
	struct node *next;
}looplist_t;

//创建一个空的链表
looplist_t *looplist_create()
{
	looplist_t *h;
	h = (looplist_t *)malloc(sizeof(looplist_t));

	h->next = h;

	return h;
}

//头插法
int looplist_insert_head(looplist_t *h, datatype_t value)
{
	looplist_t *temp = (looplist_t *)malloc(sizeof(looplist_t));
	temp->data = value;

	temp->next = h->next;
	h->next = temp;

	return 0;
}

//打印数据
int looplist_show_undel(looplist_t *h)
{
	looplist_t *p = h;
	while(h->next != p)
	{
		h = h->next;
		printf("%d ", h->data);
	}

	putchar(10);

	return 0;
}

//去头
looplist_t * looplist_cut_head(looplist_t *h)
{
	looplist_t *p = h;

	while(h->next != p)
	{
		h = h->next;
	}

	h->next = p->next;

	free(p);
	p = NULL;

	return h->next;	
}

//打印数据
int looplist_show_del(looplist_t *h)
{
	looplist_t *p = h;
	while(h->next != p)
	{
		printf("%d ", h->data);
		h = h->next;
	}
	printf("%d ", h->data);

	putchar(10);

	return 0;
}

int Josep(int n, int k, int m){
	looplist_t *h = looplist_create();
	int i = 0;
	for( i = n; i > 0; i-- )
		looplist_insert_head(h,i);

	h = looplist_cut_head(h);
	looplist_show_del(h);
	
	for(i = 1; i < k-1; i++)
		h = h->next;

	looplist_show_del(h);
	
	int j = 0;
	while(h->next != h){
	//while(j<4){
		for(i = 0; i < m - 1; i++)
			h = h->next;
		
		printf("while====%d\n", h->next->data);
		h->next = h->next->next;
		j++;
	}
	
	printf("while====%d\n", h->next->data);

	return 0;
}

int main(int argc, const char *argv[])
{
		
	Josep(8,3,4);
	return 0;
}
