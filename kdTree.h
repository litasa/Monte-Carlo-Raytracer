#pragma once
#ifndef KDTREE_H
#define KDTREE_H

#include <vector>

template <class TYPE, class DATA>
struct KdNode
{
	friend KdTree<TYPE, DATA>;

public:
	KdNode(std::vector<TYPE> &key, DATA &data) : m_key(key), m_data(data), m_left(nullptr), m_right(nullptr) {};

	~KdNode()
	{
		if (m_left != nullptr)
		{
			delete m_left;
			m_left = nullptr;
		}
		if (m_right != nullptr)
		{
			delete m_right;
			m_right = nullptr;
		}
	}

private:
	std::vector<TYPE> m_key;
	DATA m_data;
	KdNode* m_left;
	KdNode* m_right;
};

template<typename TYPE, typename DATA>
class KdTree
{
public:
	KdTree(unsigned int depth) : m_root(nullptr), m_depth(depth) {};
	~KdTree()
	{
		if (m_root != nullptr)
		{
			delete m_root;
			m_root = nullptr;
		}
	}

	void push(std::vector<TYPE> &key)
	{
		KdNode<TYPE, DATA>* newNode = new KdNode<TYPE, DATA>(key);

		if (m_root == nullptr)
		{
			m_root = newNode;
			return;
		}

		KdNode<TYPE, DATA> *currentNode = m_root;
		KdNode<TYPE, DATA> *parentNode = m_root;

		int level = 0;

		while (true)
		{
			parentNode = currentNode;

			if (key[level] < currentNode->m_key[level])
			{
				currentNode = currentNode->m_left;

				if (currentNode == nullptr)
				{
					parentNode->m_left = newNode;
					return;
				}
			}
			else
			{
				currentNode = currentNode->m_right;
				if (currentNode == nullptr)
				{
					parentNode->m_right = newNode;
					return;
				}
			}

			level++;

			if (level >= m_depth)
			{
				level = 0;
			}
		}
	}

private:
	KdNode<TYPE, DATA>* m_root;
	int m_depth;
};

#endif KDTREE_H