//哈夫曼树的建立
#pragma once
#include<iostream>
#include<string>
#include"Heap.h"
using namespace std;

template<class T>
struct HuffmanTreeNode
{
	HuffmanTreeNode<T>* _left;
	HuffmanTreeNode<T>* _right;
	T _weight;
	HuffmanTreeNode(const T& weight)
		:_left(NULL)
		, _right(NULL)
		, _weight(weight)
	{}
};
template<class T>
class HuffmanTree
{
	typedef HuffmanTreeNode<T> Node;
public:
	HuffmanTree(const T*a, int size, T invaild)
	{
		_CreatHuffmanTree(a, size, invaild);
	}
	Node* GetRoot()
	{
		return _root;
	}
protected:
	void _CreatHuffmanTree(const T*a,int size,T invaild)
	{
		Heap<Node*,Less<Node*>>hp;
		for (int i = 0; i < size; i++)
		{
			if (a[i] != invaild)
				hp.Insert(new Node(a[i]));//建立小堆
		}
		//当_v中只剩下一个数据时，哈弗曼树建立完成
		while (hp.Size()>1)
		{
			Node* left = hp.GetTop();
			hp.Remove();
			Node* right = hp.GetTop();
			hp.Remove();
			Node*parent = new Node(left->_weight + right->_weight);
			parent->_left = left;
			parent->_right = right;
			hp.Insert(parent);
		}
		_root = hp.GetTop();
	}
private:
	Node* _root;
};
