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
    bool RedLeft() { return (left != nullptr && left->color == RED); }; // true if red
    bool RedRight() { return (right != nullptr && right->color == RED); }; // true if red
    bool RedParent() { return (parent != nullptr && parent->color == RED); }; // true if red
    bool RedUnlce(); // true if red
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
    void RotateColorRecur(RbtNode* n); // recursive recolor and rotate
    void DeleteRecur(RbtNode* n); // recursive delete


    void RotateLeft(RbtNode* n);
    void RotateRight(RbtNode* n);

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
		if (k == node->key) // node exists
			return nullptr;

		if (k < node->key)  // traverse 
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
    RotateColorRecur(node);   // maintain RBT properties

	return node;
}





void Rbt::RotateColorRecur(RbtNode* n)
{
    // using https://www.cs.auckland.ac.nz/software/AlgAnim/red_black.html

    n->color = RED;

    while ((n != root) && n->RedParent()) // non-root with red parent.. 
    {
        if (n->ParentIsLeftChild()) // ..left parent..
        {
            if (n->RedUnlce()) // ..red uncle          (case 1)
            {
                n->parent->color = BLACK;
                n->GetUncle()->color = BLACK;
                n->GetGrandParent()->color = RED; // what if there is no gparent? 
                n = n->GetGrandParent();
            }
            else // black uncle..
            {
                if (!n->IsLeft())  // ..n is parent's right ch (case 2)
                {
                    n = n->parent;
                    RotateLeft(n);
                }
                n->parent->color = BLACK;              // (case 3)
                if (n->GetGrandParent())
                {
                    n->GetGrandParent()->color = RED;
                    RotateRight(n->GetGrandParent());
                }
            }
        }
        else // .. parent is right child..
        {
            if (n->RedUnlce()) // ..red uncle          (case 1)
            {
                n->parent->color = BLACK;
                n->GetUncle()->color = BLACK;
                n->GetGrandParent()->color = RED; // what if there is no gparent? 
                n = n->GetGrandParent();
            }
            else // black uncle..
            {
                if (n->IsLeft())  // ..n is parent's right ch (case 2)
                {
                    n = n->parent;
                    RotateRight(n);
                }
                n->parent->color = BLACK;              // (case 3)
                if (n->GetGrandParent())
                {
                    n->GetGrandParent()->color = RED;
                    RotateLeft(n->GetGrandParent());
                }

            }
        }

        root->color == BLACK;
        // root = n? 
    }
}

void Rbt::RotateLeft(RbtNode* n)
{
    RbtNode* temp = n->right; 

    n->right = temp->left; // #1
    if (temp->left != nullptr)
        temp->left->parent = n; // #2

    temp->parent = n->parent; // #3

    if (n->parent == nullptr)
        root = temp; // # 4
    else
    {
        if (n->IsLeft())
            n->parent->left = temp; // #5
        else
            n->parent->right = temp;  // #5
    }

    temp->left = n;  // #6
    n->parent = temp; // #7
}

void Rbt::RotateRight(RbtNode* n)
{
    RbtNode* temp = n->right;
    n->right = temp->right; // #1

    if (temp->right != nullptr)
        temp->right->parent = n; // #2

    temp->parent = n->parent; // #3

    if (n->parent == nullptr)
        root = temp;
    else
    {
        if (n->IsLeft())
            n->parent->right = temp;
        else
            n->parent->left = temp;
            
    }

    temp->left = n;
    n->parent = temp;
}
  

RbtNode* Rbt::NewNode(RbtNode* p, int k)
{
	RbtNode* node = new RbtNode(k);

	if (root)
	{
		node->parent = p;

		if (k < p->key)
			p->left = node; // parent's ptr
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

bool RbtNode::RedUnlce()
{
    if (parent && parent->parent)
    {
        if (parent->parent->left == parent && parent->parent->right != nullptr)
            return parent->parent->right->color == RED;

        if (parent->parent->right == parent && parent->parent->left != nullptr)
            return parent->parent->left->color == RED;
    }

    return false;
}

RbtNode* RbtNode::GetGrandParent()
{
    if (parent && parent->parent)
        return parent->parent;

    return nullptr;
}