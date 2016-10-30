#ifndef _LINKQUEUE_H_
#define _LINKQUEUE_H_


#include <stdio.h>
#include <stdlib.h>

//定义数据类型
typedef int datatype;

//定义结构体
typedef struct node{
	datatype data;
	struct node *next;
}linknode_t;

typedef struct{
	linknode_t *front;
	linknode_t *rear;
}linkqueue_t;

extern linkqueue_t *linkqueue_create();
extern int linkqueue_input(linkqueue_t *lq, datatype value);
extern int linkqueue_empty(linkqueue_t *lq);
extern datatype linkqueue_output_del(linkqueue_t *lq);
extern datatype linkqueue_output_undel(linkqueue_t *lq);

#endif
