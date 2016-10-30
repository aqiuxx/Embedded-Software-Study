#include "bitree.h"

//创建一颗二叉树
bitree_t *bitree_create(int n, int i)  //n表示一共有n个结点 i表示根结点的大小
{
	bitree_t *bt = (bitree_t *)malloc(sizeof(bitree_t));

	bt->data = i;

	if(2 * i <= n)
	{
		bt->lchild = bitree_create(n, 2 * i);
	}
	else
	{
		bt->lchild = NULL;
	}

	if(2 * i + 1 <= n)
	{
		bt->rchild = bitree_create(n, 2 * i + 1);
	}
	else
	{
		bt->rchild = NULL;
	}

	return bt;
}

//先序遍历
int bitree_before_order(bitree_t *root)
{
	if(root == NULL)
	{
		return -1;
	}

	printf("%d ", root->data);

	if(root->lchild != NULL)
	{
		bitree_before_order(root->lchild);
	}

	if(root->rchild != NULL)
	{
		bitree_before_order(root->rchild);
	}

	return 0;
}

//中序遍历
int bitree_in_order(bitree_t *root)
{
	if(root == NULL)
	{
		return -1;
	}

	if(root->lchild != NULL)
	{
		bitree_in_order(root->lchild);
	}

	printf("%d ", root->data);

	if(root->rchild != NULL)
	{
		bitree_in_order(root->rchild);
	}

	return 0;
}

//后序遍历
int bitree_after_order(bitree_t *root)
{
	if(root == NULL)
	{
		return -1;
	}

	if(root->lchild != NULL)
	{
		bitree_after_order(root->lchild);
	}

	if(root->rchild != NULL)
	{
		bitree_after_order(root->rchild);
	}
	
	printf("%d ", root->data);

	return 0;
}
