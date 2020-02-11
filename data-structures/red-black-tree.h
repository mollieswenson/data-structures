#pragma once

#include <iostream>
#include <cassert>

#include <vld.h>

#include "red-black-tree-node.h"

template <typename Key>
class RedBlackTree
{
	using Node = RbtNode<Key>;

public:
	RedBlackTree() {};
	~RedBlackTree() { if (root) { DeleteRecur(root); } };

	void Insert(const Key&); // inserts a node using given key, returns ptr to new node, nullptr if node already existed
	Node* Search(const Key&) const; // returns ptr to node with given key, or nullptr if key doesn't exist
	
	void Delete(const Key&); // deletes node with given key
	Key* InOrder(); // returns ordered array of all keys

	Node* GetPredecessor(const Key&); // returns predecessor of given key
	Node* GetSuccesor(const Key&);// returns successor of given key

	Node* GetMax(); // return largest key value in the tree
	Node* GetMin(); // returns smallest key value in the tree

	Node* GetRoot() { return root; }; // returns the root node of the tree
	int GetCount() { return CountRecur(root); }; // returns the number of nodes in the tree

private:
	Node* NewNode(Node* n, const Key& k);

	bool IsRed(Node*); // returns true if node exists and is red, otherwise false
	void SwapColor(Node*); // if node exists, swaps colors, otherwise no effect
	void Rotate(Node*);

    void DeleteRecur(Node*);
	void InOrderRecur(Node* n, Key arr[], int& i);
	int CountRecur(Node*);
	
	Node* root{ nullptr }; // topmost node in tree
};

template <typename Key>
void RedBlackTree<Key>::Insert(const Key& k)
{
	if (!root)
	{
		root = NewNode(nullptr, k);
		root->color = BLACK;
		return;
	}

	Node* node = root;
	Node* parent = root;

	while (node) 
	{
		if (k == node->key)
			return;

		if (k < node->key) 
		{
			parent = node;
			node = node->left;
		}
		else
		{
			parent = node;
			node = node->right;
		}
	}

	node = NewNode(parent, k);

	while (node != root && IsRed(node->parent))
	{
		if (node->HasRedUncle()) // red uncle
		{
			node->parent->color = BLACK;
			node->parent->parent->color = RED;
			node->GetUncle()->color = BLACK;
			node = node->parent->parent;
		}
		else // black/no uncle
		{
			if (node->ParentIsLeftChild() && !node->IsLeftChild()) // LR
			{
				Rotate(node);
				node = node->left;
			}
			else if (!node->ParentIsLeftChild() && node->IsLeftChild()) // RL
			{
				Rotate(node);
				node = node->right;
			}
			else if (node->ParentIsLeftChild() && node->IsLeftChild()) // LL
			{
				Rotate(node);
				SwapColor(node->parent);
				SwapColor(node->GetSibling());
			}
			else if (!node->ParentIsLeftChild() && !node->IsLeftChild()) // RR
			{
				Rotate(node);
				SwapColor(node->parent);
				SwapColor(node->GetSibling());
			}
		}
	}

	if (node == root)
		node->color = BLACK;
}

template <typename Key>
RbtNode<Key>* RedBlackTree<Key>::Search(const Key& k) const
{
	Node* node = root;

	while (node)
	{
		if (k == node->key)
			return node;

		if (k < node->key)
			node = node->left;
		else
			node = node->right;
	}

	return nullptr;
}

template <typename Key>
RbtNode<Key>* RedBlackTree<Key>::GetSuccesor(const Key& k)
{
	Node* node = Search(k);

	if (!node)
		return nullptr;

	if (node->right)
	{
		node = node->right;
		while (node->left)
			node = node->left;
		return node;
	}
	else 
	{
		while (node->parent && !node->IsLeftChild())
			node = node->parent;
		return node->parent;
	}

	return nullptr;
}

template <typename Key>
RbtNode<Key>* RedBlackTree<Key>::GetPredecessor(const Key& k)
{
	Node* node = Search(k);

	if (!node)
		return nullptr;

	if (node->left)
	{
		node = node->left;
		while (node->right)
			node = node->right;
		return node;
	}
	else
	{
		while (node->parent && node->IsLeftChild())
			node = node->parent;
		return node->parent;
	}

	return nullptr;
}

template <class Key>
RbtNode<Key>* RedBlackTree<Key>::GetMin()
{
	Node* node = root;

	while (node->left)
		node = node->left;

	return node;
}

template <typename Key>
RbtNode<Key>* RedBlackTree<Key>::GetMax()
{
	Node* node = root;

	while (node->right)
		node = node->right;

	return node;
}

template <typename Key>
void RedBlackTree<Key>::Delete(const Key& k) // this is a huge function..
{
	Node* rm = Search(k);

	if (!rm)
		return;

	Node* succ = nullptr;

	if (!rm->left && !rm->right) // leaf case
	{
		if (rm == root)
		{
			root = nullptr;
			delete rm;
			return;
		}

		if (rm->IsLeftChild())
			rm->parent->left = nullptr;
		else
			rm->parent->right = nullptr;

		succ = rm;
	}
	else if (rm->left && rm->right) // both children
	{
		succ = rm->left;
		while (succ->right != nullptr)
			succ = succ->right;

		rm->key = succ->key;

		if (succ->IsLeftChild())
			succ->parent->left = nullptr;
		else
			succ->parent->right = nullptr;

		succ->key = k;
		rm = succ;
	}
	else if (rm->left || rm->right)  // one child
	{
		if (rm->left)
			succ = rm->left;
		else
			succ = rm->right;

		if (rm->IsLeftChild())
			rm->parent->left = succ;
		else
			rm->parent->right = succ;

		succ->parent = rm->parent;
	}

	if (IsRed(rm) || IsRed(succ))  // one or both of rm/succ is red
	{

		if (succ)
			succ->color = BLACK;
	}
	else if (!IsRed(rm) && !IsRed(succ)) // both rm and succ are black
	{
		succ->color = D_BLACK;
	}

	Node* sib = nullptr;

	while (succ != root && succ->color == D_BLACK)
	{
		sib = succ->GetSibling();

		if (sib && sib->color == BLACK && sib->HasRedChild()) // a. sibling is black, at least one red child
		{
			if (sib->IsLeftChild() && IsRed(sib->left)) // LL 
			{
				Rotate(sib->left);
				SwapColor(sib->left);
				succ->color = BLACK;
			}
			else if (!sib->IsLeftChild() && IsRed(sib->right)) // RR
			{
				Rotate(sib->right);
				SwapColor(sib->right);
				succ->color = BLACK;
			}
			else if (sib->IsLeftChild() && IsRed(sib->right))  // LR
			{
				Rotate(sib->right);
				SwapColor(sib);
				SwapColor(sib->parent);
			}
			else if (!sib->IsLeftChild() && IsRed(sib->left))  // RL
			{
				Rotate(sib->left);
				SwapColor(sib);
				SwapColor(sib->parent);
			}
		}
		else if (sib == nullptr || (sib->color == BLACK && !sib->HasRedChild())) // b. sibling is black, no red child
		{
			sib->color = RED;
			succ->color = BLACK;
		}
		else if (IsRed(sib)) // c. sibling is red
		{
			if (sib->IsLeftChild()) // L
			{
				Rotate(sib->right);
				succ->color = BLACK;

				SwapColor(sib);
				SwapColor(sib->right->GetSibling());
			}
			else if (!sib->IsLeftChild()) // R
			{
				Rotate(sib->left);
				succ->color = BLACK;

				SwapColor(sib);
				SwapColor(sib->left->GetSibling());
			}
		}
	}

	assert(rm->key == k);
	delete rm;
}

template <typename Key>
RbtNode<Key>* RedBlackTree<Key>::NewNode(Node* p, const Key& k)
{
	Node* node = new Node(k);

	if (root)
	{
		node->parent = p;

		if (k < p->key)
			p->left = node;
		else
			p->right = node;
	}

	return node;
}

template <typename Key>
void RedBlackTree<Key>::Rotate(Node* n)
{
    if (n->ParentIsLeftChild() && !n->IsLeftChild()) // LR
    {
        Node* l = n->left;

        n->left = n->parent;
        n->parent = n->left->parent;

        n->parent->left = n;
        n->left->parent = n;

        n->left->right = l;
    }
    else if (!n->ParentIsLeftChild() && n->IsLeftChild()) // RL
    {
        Node* r = n->right;

        n->right = n->parent;
        n->parent = n->right->parent;

        n->parent->right = n;
        n->right->parent = n;

        n->right->left = r;
    }
    else if (n->ParentIsLeftChild() && n->IsLeftChild()) // LL
    {
        Node* temp = n->parent->right;

        if (n->parent->parent == root)
            root = n->parent;
        else
        {
            if (n->parent->parent->parent->key < n->parent->key)
                n->parent->parent->parent->right = n->parent;
            else
                n->parent->parent->parent->left = n->parent;
        }

        n->parent->right = n->parent->parent;
        n->parent->parent = n->parent->parent->parent;

        n->parent->right->parent = n->parent;
        n->parent->right->left = temp;

        if (temp)
            temp->parent = n->parent->right;
    }
    else if (!n->ParentIsLeftChild() && !n->IsLeftChild()) // RR
    {
        Node* temp = n->parent->left;

        if (n->parent->parent == root)
            root = n->parent;
        else
        {
            if (n->parent->parent->parent->key < n->parent->key)
                n->parent->parent->parent->right = n->parent;
            else
                n->parent->parent->parent->left = n->parent;
        }

        n->parent->left = n->parent->parent;
        n->parent->parent = n->parent->parent->parent;

        n->parent->left->parent = n->parent;
        n->parent->left->right = temp;

        if (temp)
            temp->parent = n->parent->left;
    }

    if (n == root)
        n->color = BLACK;
}

template <typename Key>
Key* RedBlackTree<Key>::InOrder()  // This can be a lot better 
{
	if (!root)
		return nullptr;

	int len = CountRecur(root);
	Key* arr = new Key[len];
	int i = 0;

	InOrderRecur(root, arr, i); // fill up arr

	for (i = 0; i < len - 1; i++) // put in order
	{
		for (int j = 0; j < len - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				Key temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}

	return arr;
}

template <typename Key>
void RedBlackTree<Key>::InOrderRecur(Node* n, Key arr[], int& i) // So can this
{
	arr[i] = n->key;
	i++;

	if (n->left)
		InOrderRecur(n->left, arr, i);

	if (n->right)
		InOrderRecur(n->right, arr, i);
}

template <typename Key>
int RedBlackTree<Key>::CountRecur(Node* n)
{
	if (!n)
		return 0;

	int total = 1;
	total += CountRecur(n->left);
	total += CountRecur(n->right);
	return total;
}

template <typename Key>
void RedBlackTree<Key>::DeleteRecur(Node* n)
{
	if (n->left)
		DeleteRecur(n->left);

	if (n->right)
		DeleteRecur(n->right);

	delete n;
}

template <typename Key>
bool RedBlackTree<Key>::IsRed(Node* n)
{
	if (!n)
		return false;

	return n->color == RED;	
}

template <typename Key>
void RedBlackTree<Key>::SwapColor(Node* n)
{
	if (!n)
		return;

	n->color == RED ? n->color = BLACK : n->color = RED;
}
