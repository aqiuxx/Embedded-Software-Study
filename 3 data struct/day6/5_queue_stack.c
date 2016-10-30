#include <stdio.h>
#include <stdlib.h>

#ifndef N
#define N 32
#endif

typedef int data_t;

typedef struct Queue
{
	data_t *data;
	int front,rear;
}queue_t;

queue_t * queue_create(){
	queue_t *queue;
	queue = (queue_t *)malloc(sizeof(queue_t));
	queue->data = (data_t *)malloc(sizeof(data_t) * N);

	queue->rear = queue->front = 0;

	return queue;
}


int queue_isempty(queue_t *q){

	return (q->front == q->rear);
}

int queue_full(queue_t *q){
	return (q->front ==(q->rear +1)%N );
}

int queue_insert(queue_t *q, data_t value){
	if (queue_full(q))
	{
		printf("overflow\n");
		return -1;
	}
	else{
		printf("ssssss\n");
		q->data[q->rear] = value;
		printf("%d\n",q->data[q->rear]);
		q->rear = (q->rear + 1) %N;

	}
	return 0;
}

int queue_out(queue_t *q){
	data_t value;
	if (queue_isempty(q))
	{
		printf("empty\n");
		return -1;
	}
	else{
		printf("ssssss\n");
		value = q->data[q->front];
		q->front = (q->front + 1) %N;
	}
	return value;
}

int queue_show(queue_t *p){
	int i = p->front;
	while(i != p->rear){
		printf("%d\n", p->data[i]);
		i = (i+1)%N;
	}
	return 0;
}

int main(int argc, char const *argv[])
{
	queue_t *q;
	data_t value;
	q = queue_create();

	queue_insert(q, 1);
	queue_insert(q, 2);
	queue_insert(q, 3);
	queue_insert(q, 4);
	queue_insert(q, 5);

	queue_show(q);

	printf("%d\n",queue_out(q));

	queue_show(q);

	return 0;
}
