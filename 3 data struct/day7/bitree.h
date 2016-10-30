#ifndef _BITREE_H_
#define _BITREE_H_

#include <stdio.h>
#include <stdlib.h>

//定义结构体
typedef struct node_t{
	int data;
	struct node_t *lchild;
	struct node_t *rchild;
}bitree_t;

extern bitree_t *bitree_create(int n, int i);  //n表示一共有n个结点 i表示根结点的大小
extern int bitree_before_order(bitree_t *root);
extern int bitree_in_order(bitree_t *root);
extern int bitree_after_order(bitree_t *root);

#endif
