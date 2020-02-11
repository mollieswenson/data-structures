#pragma once

#include <vld.h>

enum Color { RED, BLACK, D_BLACK };

template <typename Key>
struct RbtNode
{
	template <typename Key> friend class RedBlackTree;
	RbtNode(int k) : key(k) {};
	~RbtNode() { };

	Key key{};

	Color color = RED;

	RbtNode<Key>* parent{ nullptr };
	RbtNode<Key>* left{ nullptr };
	RbtNode<Key>* right{ nullptr };

private:
	RbtNode<Key>* GetSibling(); // returns sibling of this node
	RbtNode<Key>* GetUncle(); // returns uncle of this node

	bool HasRedChild(); // true when red child exists, otherwise false
	bool HasRedSibling(); // true when red sibling exists, otherwise false
	bool HasRedUncle(); // true when a red uncle exists, otherwise false

	bool ParentIsLeftChild() { return (parent->parent && parent->parent->left == parent); }; // true when parent is left child
	bool IsLeftChild() { return parent && parent->left == this; }; // true when this node is left child
};

template <typename Key>
RbtNode<Key>* RbtNode<Key>::GetSibling()
{
	if (!this)
		return nullptr;

	if (this == parent->left)
		return parent->right;
	else if (this == parent->right)
		return parent->left;
	else   //  non-null child of parent back
	{
		if (parent->left)
			return parent->left;
		else
			return parent->right;
	}
}

template <typename Key>
RbtNode<Key>* RbtNode<Key>::GetUncle()
{
	if (parent && parent->parent)
	{
		if (parent->parent->left == parent && parent->parent->right)
			return parent->parent->right;

		if (parent->parent->right == parent && parent->parent->left)
			return parent->parent->left;
	}

	return nullptr;
}

template <typename Key>
bool RbtNode<Key>::HasRedUncle()
{
	if (parent && parent->parent)
	{
		if (parent->parent->left == parent && parent->parent->right)
			return parent->parent->right->color == RED;

		if (parent->parent->right == parent && parent->parent->left)
			return parent->parent->left->color == RED;
	}

	return false;
}

template <typename Key>
bool RbtNode<Key>::HasRedChild()
{
	if (left && left->color == RED)
		return true;

	if (right && right->color == RED)
		return true;

	return false;
}

template <typename Key>
bool RbtNode<Key>::HasRedSibling()
{
	if (parent)
	{
		if (IsLeftChild() && parent->right)
			return parent->right->color == RED;

		if (!IsLeftChild() && parent->left)
			return parent->left->color == RED;
	}

	return false;
}
