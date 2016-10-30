#include <stdio.h>
#include <stdlib.h>

#ifndef N
#define N 32
#endif

typedef int data_t;

typedef struct Queuelink
{
	data_t data;
	struct Queuelink * next;
}linkqueue_t;

linkqueue_t * tail_g;

linkqueue_t * linkqueue_create(){
	linkqueue_t *lq = (linkqueue_t *)malloc(sizeof(linkqueue_t));
	lq->next = NULL;
	tail_g = lq;

	return lq;
}

int linkqueue_in( data_t value){
	linkqueue_t *tmp = (linkqueue_t *)malloc(sizeof(linkqueue_t));

	tmp->data = value;
	tmp->next =NULL;

	tail_g->next = tmp;
	tail_g = tmp;

	return 0;
}

data_t linkqueue_out(linkqueue_t *lq){
	data_t value;
	linkqueue_t *head = lq;

	if (head->next)
	{
		lq = lq->next;
		value = lq->data;

		head->next = lq->next;
		free(lq);
		lq = NULL;

		if(head->next == NULL)
			tail_g = head;

		return value;
	}

	printf("linkqueue_out error\n");
	return -1;

}


int linkqueue_show(linkqueue_t *lq){
	linkqueue_t *p = lq;
	while( p->next ){
		p = p->next;
		printf("%d\n", p->data);
	}
	return 0;
}

int main(int argc, char const *argv[])
{
	linkqueue_t *lq;

	lq = linkqueue_create();


	linkqueue_in( 1);
	linkqueue_in( 2);
	linkqueue_in( 3);
	linkqueue_in( 4);


	linkqueue_show(lq);

	printf("return data%d\n",linkqueue_out(lq));
	printf("return data%d\n",linkqueue_out(lq));
	printf("return data%d\n",linkqueue_out(lq));
	printf("return data%d\n",linkqueue_out(lq));
	printf("return data%d\n",linkqueue_out(lq));

	linkqueue_in( 1);
	//linkqueue_show(lq);

	linkqueue_in( 2);
	linkqueue_show(lq);

	return 0;
}
