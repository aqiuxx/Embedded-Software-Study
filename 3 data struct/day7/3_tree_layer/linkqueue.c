#include "linkqueue.h"

//创建一个空的队列
linkqueue_t *linkqueue_create()
{
	linkqueue_t *lq = (linkqueue_t *)malloc(sizeof(linkqueue_t));
	lq->front = lq->rear = (linknode_t *)malloc(sizeof(linknode_t));

	lq->front->next = NULL;

	return lq;
}

//入队
int linkqueue_input(linkqueue_t *lq, datatype value)
{
	linknode_t *temp = (linknode_t *)malloc(sizeof(linknode_t));
	temp->data = value;
	temp->next = NULL;

	lq->rear->next = temp; //将temp指向的结点插入到rear后面
	lq->rear = temp; //将rear指向最后一个结点

	return 0;
}

//判断队列是否为空
int linkqueue_empty(linkqueue_t *lq)
{
	return lq->front == lq->rear ? 1 : 0;
}

//出队
//方法一：删除头结点
datatype linkqueue_output_del(linkqueue_t *lq)
{
	if(linkqueue_empty(lq))
	{
		printf("linkqueue is empty\n");
		return (datatype)-1;
	}
	
	linknode_t *temp = lq->front;
	datatype value;

	lq->front = lq->front->next;
	value = lq->front->data;

	free(temp);
	temp = NULL;

	return value;
}

//方法二：保留头结点
datatype linkqueue_output_undel(linkqueue_t *lq)
{
	linknode_t *temp = NULL;
	datatype value;

	if(linkqueue_empty(lq))
	{
		printf("linkqueue is empty\n");
		return (datatype)-1;
	}

	temp = lq->front->next;
	lq->front->next = temp->next;

	value = temp->data;

	free(temp);
	temp = NULL;

	if(lq->front->next == NULL)
	{
		lq->rear = lq->front;
	}

	return value;
}
