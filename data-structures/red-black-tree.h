#pragma once

#include <iostream>
#include <cassert>

#include <vld.h>

enum Direction { LEFT, RIGHT };

struct RbtNode 
{
    RbtNode(int k) : key(k) {};
    ~RbtNode() { };

    int key{};

	bool red{ true };

    RbtNode* left{ nullptr };
    RbtNode* right{ nullptr };

	RbtNode* parent{ nullptr };

	RbtNode* GetGrandParent()
	{
		if (parent && parent->parent)
		{
			return parent->parent;
		}

		return nullptr;
	}

	RbtNode* GetUncle()
	{ 
		if (parent && GetGrandParent())
		{
			if (GetGrandParent()->left == parent && GetGrandParent()->right != nullptr)
			{
				return GetGrandParent()->right;
			}

			if (GetGrandParent()->right == parent && GetGrandParent()->left != nullptr)
			{
				return GetGrandParent()->left;
			}
		}

		return nullptr;
	}
};


class Rbt
{
public:
	Rbt() {};
	~Rbt() { if (root) { DeleteRecur(root); } };

	void Insert(int); // insert a node using given key
	void Delete(int); // deletes node with given key
	RbtNode* Search(int); // returns ptr to node with given key, or nullptr if key doesn't exist
	int* InOrder(); // returns ordered array of all elements

	RbtNode* GetRoot() { return root; }; // returns the root node of the tree
	int GetCount() { return CountRecur(root); }; // returns the number of nodes in the tree

	void Balance(RbtNode* n);
	RbtNode* Rotate(RbtNode*, enum Direction);

private:
	RbtNode* InsertRecur(RbtNode* n, RbtNode* p, int k); // recursive insert
	void InOrderRecur(RbtNode* n, int arr[], int& i); // recursive inorder
	int CountRecur(RbtNode* n); // recursive counter
	void DeleteRecur(RbtNode* n); // recursive delete

	void Check(RbtNode* n);

	RbtNode* Recolor(RbtNode*);


	RbtNode* GetParent(int); // returns parent of given node
	RbtNode* NewNode(RbtNode* p, int k); // creates a new node



	RbtNode* root{ nullptr }; // topmost node in tree
};

void Rbt::Insert(int k)
{
	if (root == nullptr)
	{
		root = NewNode(nullptr, k);
		root->red = false;
		return;
	}

	if (Search(k) != nullptr)
		return;

	RbtNode* node = InsertRecur(root, nullptr, k);

	//Balance(node);
	//Check(root);
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

void Rbt::Check(RbtNode* n)
{
	if (n == nullptr)
		return;

	// root and leaves are black
	// red nodes only have black children (black nodes can have black children)
	// all paths from a node to a dummy node/nullptr have the same number of black nodes

	std::cout << "\n\n NODE " << n->key;;

	if (n->red)
		std::cout << " red";
	else
		std::cout << " black";

	if (n->left != nullptr && n->left->red)
		std::cout << "\n  red";
	else
		std::cout << "\n  black";

	if (n->right != nullptr && n->right->red)
		std::cout << "\n  red";
	else
		std::cout << "\n  black";
	


	if (n->red)
	{
		if (n->left != nullptr && !n->left->red)
		{
			std::cout << "\n   child " << n->left << " must be black!";
		}

		if (n->right != nullptr && !n->right->red)
		{
			std::cout << "\n   child " << n->right << " must be black!";
		}
	}



	Check(n->left);
	Check(n->right);
}







void Rbt::Balance(RbtNode* n) // don't allow root to be black..
{
	if (n->GetUncle() && n->GetUncle()->red) // red uncle...
	{
		n->parent->red ? !n->parent->red : n->parent->red;
		n->GetGrandParent()->red ? !n->GetGrandParent()->red : n->GetGrandParent()->red;
		n->GetUncle()->red ? !n->GetUncle()->red : n->GetUncle()->red; // redundant

	}
	
	if (n->GetUncle() && !(n->GetUncle()->red)) // black uncle...
	{
		if (n->GetGrandParent()->left == n->parent && n->parent->right == n) // left -> right triangle case (rotate to left)
		{
			Rotate(n->parent, LEFT);
		}

		if (n->GetGrandParent()->right == n->parent && n->parent->left == n) // right -> left triangle case (rotate to right)
		{
			Rotate(n->parent, RIGHT); // when to color? 
		}

		if (n->GetGrandParent()->left == n->parent && n->parent->left == n) // left -> left line case
		{

		}

		if (n->GetGrandParent()->right == n->parent && n->parent->right == n) // right -> right line case
		{

		}
	}
	
	
	
}

RbtNode* Rbt::Recolor(RbtNode* n)
{
	return nullptr;
}


RbtNode* Rbt::Rotate(RbtNode*n, Direction d)
{
	if (d == LEFT)
	{
		n->parent->left = n->right; // fix top level left

		n->right->parent = n->parent; // fix parent data members
		n->parent = n->right;
		n->right->left->parent = n;

		RbtNode* temp = n->right->left;

		n->right->left = n; // hook new parent up to new child
		n->right = temp; // hook old parent up to new child
	}

	if (d == RIGHT)
	{
		n->parent->right = n->left; // fix top level left

		n->left->parent = n->parent; // fix parent data members
		n->parent = n->left;
		n->left->right->parent = n;

		RbtNode* temp = n->left->right;

		n->left->right = n; // hook new parent up to new child
		n->left = temp; // hook old parent up to new child
	}

	return nullptr;
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

	if (rm_node->left != nullptr && rm_node->right != nullptr) // both subtrees case
	{
		RbtNode* successor = rm_node->right;

		while (successor->left != nullptr)
			successor = successor->left; // min of right subtree

		// case where removing root and min of right subtree is root->right
		successor == root->right ? root->right = nullptr : GetParent(successor->key)->left = nullptr;

		rm_node->key = successor->key;
		delete successor;
		return;
	}

	RbtNode* parent = GetParent(rm_node->key);

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
	if (n->left)
		DeleteRecur(n->left);

	if (n->right)
		DeleteRecur(n->right);

	delete n;
}

RbtNode* Rbt::NewNode(RbtNode* p, int k)
{
	RbtNode* node = new RbtNode(k);
	node->parent = p;
	return node;
}


