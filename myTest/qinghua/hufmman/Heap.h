//自己写的最小堆（因为在加强巩固，所以没用STL里的）
#pragma once
#include<iostream>
#include<vector>
using namespace std;

template<class T>
struct Less
{
	bool operator()(const T&left, const T&right)
	{
		return left->_weight < right->_weight;
	}
};

template<class T,class Compare=Less<T>>
class Heap
{
public:
	Heap()
	{}
	Heap(const T*v, int size, int valid)
	{
		for (int i = 0; i < size; i++)
		{
			if (v[i] != valid)
				_v.push_back(v[i]);
		}
		int _size = _v.size();
		int begin = (_size - 2) / 2;
		for (int root = begin; root >= 0; root--)
		{
			AdjustDown(root);
		}
	}
	void Insert(const T& value)
	{
		_v.push_back(value);
		int leaf = _v.size() - 1;
		AdjustUp(leaf);
	}
	void Remove()
	{
		swap(_v[0], _v[_v.size() - 1]);
		_v.pop_back();
		AdjustDown(0);
	}
	T& GetTop()
	{
		if (!_v.empty())
			return _v[0];
	}
	bool Empty()
	{
		if (_v.empty())
			return true;
		return false;
	}
	int Size()
	{
		return _v.size();
	}
protected:
	void AdjustDown(int root)
	{
		size_t left = root * 2 + 1;
		size_t right = left + 1;
		int key = left;
		while (left < _v.size())
		{
			if (right < _v.size() && Compare()(_v[right], _v[left]))
				key = right;
			if (Compare()(_v[key], _v[root]))
			{
				swap(_v[key], _v[root]);
				root = key;
				left = root * 2 + 1;
				right = left + 1;
				key = left;
			}
			else
				break;
		}
	}
	void AdjustUp(int leaf)
	{
		int root = (leaf - 1) / 2;
		while (leaf > 0)
		{
			if (Compare()(_v[leaf], _v[root]))
			{
				swap(_v[leaf], _v[root]);
				leaf = root;
				root = (leaf - 1) / 2;
			}
			else
				break;
		}
	}
private:
	vector<T> _v;
};