#pragma once

#include <iostream>
#include <cassert>

#include <vld.h>

enum Color { RED, BLACK };


// support search(tree, key), Predecessor(tree, key), Successor(tree, key),Max(tree), Min(tree) in O(log n) time and explain how

struct RbtNode 
{
    RbtNode(int k) : key(k) {};
    ~RbtNode() { };

    int key{};
	Color color = RED ;

    RbtNode* left{ nullptr };
    RbtNode* right{ nullptr };
	RbtNode* parent{ nullptr };

    RbtNode* GetSibling(); // return ptr to sibling
    RbtNode* GetUncle(); // returns ptr to uncle of this node
    RbtNode* GetGrandParent(); // returns ptr to grandparent of this node

    bool RedParent() { return (parent != nullptr && parent->color == RED); }; // true if red
    bool RedUncle(); // true when a red uncle exists, otherwise false
	bool BlackUncle(); // true when a black uncle exists, otherwise false

    bool ParentIsLeftChild() { return (parent->parent != nullptr && parent->parent->left == parent); }; // true if parent is left child
    bool IsLeft() { return parent != nullptr && parent->left == this; };
};

class Rbt
{
public:
	Rbt() {};
	~Rbt() { if (root) { DeleteRecur(root); } };

	RbtNode* Insert(int); // insert a node using given key
	void Delete(int); // deletes node with given key
	RbtNode* Search(int); // returns ptr to node with given key, or nullptr if key doesn't exist
	int* InOrder(); // returns ordered array of all elements

	RbtNode* GetRoot() { return root; }; // returns the root node of the tree
	int GetCount() { return CountRecur(root); }; // returns the number of nodes in the tree

    RbtNode* GetParent(int); // returns parent of given node

private:
	RbtNode* InsertRecur(RbtNode* n, RbtNode* p, int k); // recursive insert
	void Rebalance(RbtNode* n);
    void DeleteRecur(RbtNode* n); // recursive delete
	void InOrderRecur(RbtNode* n, int arr[], int& i); // recursive inorder
	int CountRecur(RbtNode* n); // recursive counter
	RbtNode* NewNode(RbtNode* p, int k); // creates a new node
	RbtNode* root{ nullptr }; // topmost node in tree
};

RbtNode* Rbt::Insert(int k)
{
	if (root == nullptr) // root 
	{
		root = NewNode(nullptr, k);
		root->color = BLACK;
		return root;
	}

	RbtNode* node = root;
	RbtNode* parent = root;

	while (node != nullptr) 
	{
		if (k == node->key)
			return nullptr;

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
    Rebalance(node);
	return node;
}

void Rbt::Rebalance(RbtNode* n)
{
	n->color = RED;

	while (n != root && n->RedParent())
	{
		if (n->RedUncle())// red uncle.. 
		{
			n->parent->color = BLACK;
			n->parent->parent->color = RED;
			n->GetUncle()->color = BLACK;
			n = n->parent->parent;
		}
		else
		{
			if (n->ParentIsLeftChild() && !n->IsLeft()) // LR
			{
				RbtNode* l = n->left;

				n->left = n->parent;
				n->parent = n->left->parent;

				n->parent->left = n;
				n->left->parent = n;

				n->left->right = l;
				n = n->left;
			}
			else if (!n->ParentIsLeftChild() && n->IsLeft()) // RL
			{
				RbtNode* r = n->right;

				n->right = n->parent;
				n->parent = n->right->parent;

				n->parent->right = n;
				n->right->parent = n;

				n->right->left = r;

				n = n->right;
			}
			else if (n->ParentIsLeftChild() && n->IsLeft()) // LL
			{
				assert(n->parent != root); 
				RbtNode* temp = n->parent->right;

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

				n->parent->color == RED ? n->parent->color = BLACK : n->parent->color = RED;
				n->GetSibling()->color == RED ? n->GetSibling()->color = BLACK : n->GetSibling()->color = RED;
			}
			else if (!n->ParentIsLeftChild() && !n->IsLeft()) // RR
			{
				assert(n->parent != root);
				RbtNode* temp = n->parent->left;

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
				n->parent->parent = n->parent->parent->parent; // handles null

				n->parent->left->parent = n->parent;
				n->parent->left->right = temp;

				if (temp)
					temp->parent = n->parent->left;

				n->parent->color == RED ? n->parent->color = BLACK : n->parent->color = RED;
				n->GetSibling()->color == RED ? n->GetSibling()->color = BLACK : n->GetSibling()->color = RED;
			}
		}
	}

	if (n == root)
		n->color = BLACK;
}

RbtNode* Rbt::NewNode(RbtNode* p, int k)
{
	RbtNode* node = new RbtNode(k);

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

RbtNode* Rbt::InsertRecur(RbtNode* n, RbtNode* p, int k)
{
	if (n == nullptr)
		return NewNode(p, k);

	if (k == n->key)
		return nullptr;

	if (k < n->key)
		n->left = InsertRecur(n->left, n, k);

	if (k > n->key)
		n->right = InsertRecur(n->right, n, k);
		
	return n;
}

RbtNode* Rbt::Search(int k)
{
	RbtNode* node = root;

	while (node != nullptr)
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





void Rbt::Delete(int k)
{
	if (root == nullptr)
		return;

	RbtNode* rm_node = Search(k);
	
	if (!rm_node)
		return;

	if (rm_node->left != nullptr && rm_node->right != nullptr) // both subtrees case
	{
		RbtNode* successor = rm_node->right;

		while (successor->left != nullptr)
			successor = successor->left; // min of right subtree

		// case where removing root and min of right subtree is root->right
		successor == root->right ? root->right = nullptr : GetParent(successor->key)->left = nullptr;

		rm_node->key = successor->key;
		delete successor;

	}

	RbtNode* parent = GetParent(rm_node->key);

	if (!parent)
		return;

	if (rm_node->left == nullptr && rm_node->right == nullptr) // leaf case
		k < parent->key ? parent->left = nullptr : parent->right = nullptr;

	if (parent->left == rm_node) // single left subtree case
		rm_node->left != nullptr ? parent->left = rm_node->left : parent->left = rm_node->right;

	if (parent->right == rm_node) // single right subtree case
		rm_node->left != nullptr ? parent->right = rm_node->left : parent->right = rm_node->right;

	delete rm_node;
	return;
}

RbtNode* Rbt::GetParent(int k)
{
	RbtNode* node = root;
	RbtNode* parent{};

	while (node != nullptr)
	{
		if (k == node->key)
			return parent;

		if (k < node->key)
		{
			parent = node;
			node = node->left;
		}

		if (k > node->key)
		{
			parent = node;
			node = node->right;
		}
	}

	return nullptr;
}

int* Rbt::InOrder()
{
	if (root == nullptr)
		return nullptr;

	int len = CountRecur(root);
	int* arr = new int[len];
	int i = 0;

	InOrderRecur(root, arr, i); // fill up arr

	for (i = 0; i < len - 1; i++) // put in order
	{
		for (int j = 0; j < len - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}

	return arr;
}

void Rbt::InOrderRecur(RbtNode* n, int arr[], int& i)
{
	arr[i] = n->key;
	i++;

	if (n->left)
		InOrderRecur(n->left, arr, i);

	if (n->right)
		InOrderRecur(n->right, arr, i);
}

int Rbt::CountRecur(RbtNode* n)
{
	if (n == nullptr)
		return 0;

	int total = 1;
	total += CountRecur(n->left);
	total += CountRecur(n->right);
	return total;
}

void Rbt::DeleteRecur(RbtNode* n)
{

	if (n->left != nullptr)
		DeleteRecur(n->left);

	if (n->right != nullptr)
		DeleteRecur(n->right);

	delete n;
}

RbtNode* RbtNode::GetSibling()
{
    if (this == parent->left)
        return parent->right;
    else
        return parent->left;
}

RbtNode* RbtNode::GetUncle()
{
    if (parent && parent->parent)
    {
        if (parent->parent->left == parent && parent->parent->right != nullptr)
            return parent->parent->right;

        if (parent->parent->right == parent && parent->parent->left != nullptr)
            return parent->parent->left;
    }

    return nullptr;
}

bool RbtNode::RedUncle()
{
	if (parent && parent->parent)
	{
		if (parent->parent->left == parent && parent->parent->right != nullptr)
			return parent->parent->right->color == RED;

		if (parent->parent->right == parent && parent->parent->left != nullptr)
			return parent->parent->left->color == RED;
	}

	return false; // no parent or gparent
}

bool RbtNode::BlackUncle()
{
	if (parent && parent->parent)
	{
		if (parent->parent->left == parent && parent->parent->right != nullptr)
			return parent->parent->right->color == BLACK;

		if (parent->parent->right == parent && parent->parent->left != nullptr)
			return parent->parent->left->color == BLACK;
	}

	return false; // no parent or gparent
}




RbtNode* RbtNode::GetGrandParent()
{
    if (parent && parent->parent)
        return parent->parent;

    return nullptr;
}