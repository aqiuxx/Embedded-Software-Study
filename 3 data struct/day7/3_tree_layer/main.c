#include "linkqueue.h"
//#include "bitree.h"

int bitree_level_order(bitree_t *root)
{
	//创建一个队列
	linkqueue_t *lq = linkqueue_create();

	//将根结点入队
	linkqueue_input(lq, root);

	//循环出队，判断是否有左右子树，如果存在，则入队
	while(!linkqueue_empty(lq))
	{
		root = linkqueue_output_undel(lq);

		printf("%d ", root->data);

		if(root->lchild != NULL)
		{
			linkqueue_input(lq, root->lchild);
		}

		if(root->rchild != NULL)
		{
			linkqueue_input(lq, root->rchild);
		}

	}

	return 0;
}

int main(int argc, const char *argv[])
{
	bitree_t *bt;
	bt = bitree_create(8, 1);

	bitree_level_order(bt);
	putchar(10);

	return 0;
}
