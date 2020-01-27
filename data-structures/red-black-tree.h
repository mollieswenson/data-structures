#pragma once

#include <iostream>
#include <cassert>

#include <vld.h>

#include "test-red-black-tree.h" // temp

enum Direction { LEFT, RIGHT };

enum Color { RED, BLACK };

struct RbtNode 
{
    RbtNode(int k) : key(k) {};
    ~RbtNode() { };

    int key{};

	//bool red{ true };

	Color color = RED ;

    RbtNode* left{ nullptr };
    RbtNode* right{ nullptr };

	RbtNode* parent{ nullptr };

	RbtNode* GetGrandParent()
	{
		if (parent && parent->parent)
			return parent->parent;

		return nullptr;
	}

	RbtNode* GetSibling()
	{
		if (this == parent->left)
			return parent->right;
		else
			return parent->left;
	}

	RbtNode* GetUncle()
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


	void RotateColor(RbtNode* n);

private:
	RbtNode* InsertRecur(RbtNode* n, RbtNode* p, int k); // recursive insert
	void InOrderRecur(RbtNode* n, int arr[], int& i); // recursive inorder
	int CountRecur(RbtNode* n); // recursive counter
	void DeleteRecur(RbtNode* n); // recursive delete

	void Check(RbtNode* n);

	void Rotate(RbtNode*);
	void Recolor(RbtNode*);

	RbtNode* GetParent(int); // returns parent of given node
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

	node = NewNode(parent, k); // is node already in this spot? 

	if (node->parent->color == RED)
	{
		RotateColor(node);
	}

	

	return node;
}



void Rbt::RotateColor(RbtNode* n) // null leafs are black!
{
	if (n == root)
		n->color = BLACK;

	if (n->GetUncle() && n->GetUncle()->color != BLACK) // red uncle
	{
		n->parent->color = BLACK;
		n->GetUncle()->color = BLACK;
		n->GetGrandParent()->color = RED;

		RotateColor(n->GetGrandParent());
	}
	else if (n->GetUncle() == nullptr || n->GetUncle()->color == BLACK) // black uncle
	{   // doesnt work on root.,. 
		if (n != root && n == n->parent->left && n->GetGrandParent() != nullptr && n->GetGrandParent()->left == n->parent) // (LL) node is left child, parent is left child
		{
			n->parent->right = n->parent->parent; // gparent becomes n->parent's right child			
			n->GetGrandParent()->parent->left = n->parent; // ggparent becomes gparent

			n->GetGrandParent()->left = nullptr; // remove left ch of gparent / now n->parent's right child

			if (n->parent->parent == root) // if n's parent is now root, fix root ===== needed? 
				root = n->parent;

			n->parent->parent = n->GetGrandParent()->parent; // hook n->parent up to new predecessor (handles nullptr for root case)
			n->GetSibling()->parent = n->parent; // hook sibling up to correct parent
			n->GetSibling()->left = nullptr; // remove sibling right ch now pointing to its own parent

			n->parent->color == RED ? n->parent->color = BLACK : n->parent->color = RED; // swap colors of parent and sibling (old gparent) 
			n->GetSibling()->color == RED ? n->GetSibling()->color = BLACK : n->GetSibling()->color = RED;
		}
		else if (n != root && n == n->parent->right && n->GetGrandParent() != nullptr && n->GetGrandParent()->left == n->parent) // (LR) node is right, parent is left 
		{
			n->left = n->parent; // parent becomes n's left child
			n->parent = n->left->parent->parent; // hook n->parent up to new predecessor (handles nullptr for root case)
			n->left->parent = n; // hook former parent up to new predecessor

			RotateColor(n->left); // should hit LL case on next

		}
		else if (n != root && n == n->parent->right && n->GetGrandParent() != nullptr && n->GetGrandParent()->right == n->parent) // RR
		{
			n->parent->left = n->parent->parent; // gparent becomes n->parent's left child
			n->parent->parent->right = n; // n becomes n->parent's right child
			if(n->GetGrandParent()->parent)
				n->GetGrandParent()->parent->left = n->parent; // fix ptr to n->parent

			if (n->parent->parent == root) // if n's parent is now root, fix root
				root = n->parent;

			n->parent->parent = n->parent->parent->parent; // hook n->parent up to its parent (handles nullptr for root case)
			n->GetSibling()->parent = n->parent; // hook new sibling up to correct parent

			n->GetSibling()->right = nullptr; // remove sibling right ch now pointing to its own parent

			// under what circumstances do we swap colors? 

			n->parent->color == RED ? n->parent->color = BLACK : n->parent->color = RED; // swap colors of parent and sibling (old gparent) 
			n->GetSibling()->color == RED ? n->GetSibling()->color = BLACK : n->GetSibling()->color = RED;
			
		}
		else if (n != root && n == n->parent->left && n->GetGrandParent() != nullptr && n->GetGrandParent()->right == n->parent) // RL (mirror LR)
		{
			n->right = n->parent; // parent becomes n's left child
			n->GetGrandParent()->parent->right = n; // n becomes ggparent right ch
			n->left = n->GetGrandParent(); // gparent becomes n's left ch

			n->parent->left = nullptr;
			n->GetGrandParent()->right = nullptr;

			n->parent = n->GetGrandParent()->parent; // hook n->parent up to new predecessor (handles nullptr for root case)
			n->left->parent = n; // hook former parent up to new predecessor
			n->right->parent = n; // hook former parent up to new predecessor

			n->color = BLACK;
			n->left->color = RED;





			//RotateColor(n->right); 
		}
		else
		{
			assert(true);
			return;
		}

	}
	else
	{
		return;
	}




}







void Rbt::Rotate(RbtNode* n) 
{
	if (n->color == RED && n->parent->color == RED) // 2 consecutive red nodes, rotate opposite dir of n   *everything must stay in order*
	{

		if (n->parent->parent->right == n->parent && n->parent->right == n) // rotate gparent left; gparent becomes parent's left child (RR)
			n->parent->left = n->parent->parent; // rotate gparent

		if (n->parent->parent->left == n->parent && n->parent->left == n) // rotate gparent right; gparent becomes parent's right child (LL)
			n->parent->right = n->parent->parent; // rotate gparent

		if (n->parent->parent == root) // if n's parent is now root, fix root
			root = n->parent; // update root

		if (n->parent == n->parent->parent->left) // hook parent up to new child
			n->parent->parent->left = nullptr;

		if (n->parent == n->parent->parent->right) // hook parent up to new child
			n->parent->parent->right = nullptr;

		n->parent->parent = n->parent->parent->parent; // hook new parent up to predecessor; should handle nullptr for root case
		
		n->GetSibling()->parent = n->parent; // hook sibling up to correct parent

		if (n->GetSibling()->left == n->parent)  // remove sibling child conn to new parent
			n->GetSibling()->left = nullptr; 

		if (n->GetSibling()->right == n->parent)  // remove sibling child conn to new parent
			n->GetSibling()->right = nullptr;

		n->GetSibling()->color == RED ? n->GetSibling()->color = BLACK : n->GetSibling()->color = RED;  // recolor sibling
		n->parent->color == RED ? n->parent->color = BLACK : n->parent->color = RED;                   // recolor parent 

		if (n->parent == root)
			n->parent->color = BLACK;
	}
}

void Rbt::Recolor(RbtNode* n) {}



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


// dont allow red root 
// recursive balance up the tree..

//void Rbt::Balance(RbtNode* n)
//{
//	// if there is no uncle, then uncle is BLACK
//
//	if (n->GetUncle() != nullptr && n->GetUncle()->color == RED && n->parent != nullptr && n->parent->color != BLACK) // case where n->uncle is red, n->parent is not black    
//	{
//		n->parent->color = BLACK;
//		n->GetUncle()->color = BLACK; // uncle and parent to black
//
//		if (n->GetGrandParent() != nullptr)
//		{
//			n->GetGrandParent()->color = RED;  // g-parent to red
//
//			if(n == n->parent->left) // rotate g-parent opposite dir of par-node conn
//				Rotate(n->GetGrandParent(), RIGHT);
//			if (n == n->parent->right)
//				Rotate(n->GetGrandParent(), LEFT); // something wrong here
//
//			Balance(n); // recurse on new n (is n pointing to former gparent now?)
//		}
//
//	}
//
//}
//
//RbtNode* Rbt::Rotate(RbtNode*n, Direction d)
//{
//	if (n->GetGrandParent() == nullptr)
//		return nullptr;
//
//
//	if (n->parent && n->parent->right && d == LEFT) // we already know n->right and n->right->right exist
//	{
//		n->parent->left = n->right; // fix top level left child ptr
//
//		n->right->parent = n->parent;   // set parent ptr of n's right child ( rc is future parent of n) to current parent of n
//		n->parent = n->right;           // set parent ptr of n to n's current right child (rc is future parent of n)
//		if(n->right->left)
//			n->right->left->parent = n; // (fixup) if it exists, set parent ptr of r/l grandchild to n
//
//		RbtNode* temp = n->right->left;
//
//		n->right->left = n; // hook new parent up to new child
//		n->right = temp; // hook old parent up to new child
//	}
//
//	if (n->parent && n->parent->right && d == RIGHT) // we already know n->left and n->left->left exist
//	{
//		n->parent->right = n->left; // fix top level right child ptr
//
//		n->left->parent = n->parent; // set parent ptr of n's right child ( rc is future parent of n) to current parent of n
//		n->parent = n->left;         // set parent ptr of n to n's current right child (rc is future parent of n)
//		if (n->left->right)
//			n->left->right->parent = n; // (fixup) if it exists, set parent ptr of r/l grandchild to n
//
//		RbtNode* temp = n->left->right;
//
//		n->left->right = n; // hook new parent up to new child
//		n->left = temp; // hook old parent up to new child
//	}
//
//	return nullptr;
//}
//





//	if (n->GetUncle() != nullptr && n->GetUncle()->color == RED) // case with red uncle and non-black parent
//	{
//
//		if (n->parent != nullptr && n->parent->color != BLACK)
//		{
//			n->GetUncle()->color = BLACK;
//			n->parent->color = BLACK;  // should parent still be colored black if there is no uncle? 
//
//			if (n->GetGrandParent() != nullptr)
//				n->GetGrandParent()->color = RED; // should g-parent parent still be colored black if there is no uncle? 
//		}
//	}
//
//
//
//
//
//	if (n->GetUncle() != nullptr && n->GetUncle()->color == RED && n->parent != nullptr && n->parent->color != BLACK && n->GetGrandParent() != nullptr) // case where n->uncle is red, n->parent is not black (change both to black)      
//	{
//		n->parent->color = BLACK;
//		n->GetUncle()->color = BLACK;  // what should happen when one or more grandparent, uncle or parent doesn't exist? 
//		n->GetGrandParent()->color = RED;
//	}
//
//
//
//	if (n->GetUncle() == nullptr && n->parent != nullptr && n->parent->color != BLACK) // case with no uncle, n->parent is not black (what to do?)
//	{
//
//	}
//
//
//
//	if (n->GetUncle() && n->GetUncle()->color == BLACK) // black uncle...
//	{
//		if (n->GetGrandParent()->left == n->parent && n->parent->right == n) // left -> right triangle case (rotate to left)
//		{
//			Rotate(n->parent, LEFT);
//		}
//
//		if (n->GetGrandParent()->right == n->parent && n->parent->left == n) // right -> left triangle case (rotate to right)
//		{
//			Rotate(n->parent, RIGHT); // when to color? 
//		}
//
//		if (n->GetGrandParent()->left == n->parent && n->parent->left == n) // left -> left line case
//		{
//
//		}
//
//		if (n->GetGrandParent()->right == n->parent && n->parent->right == n) // right -> right line case
//		{
//
//		}
//	}
//
//
//
//}













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




///////////////////////

//void Rbt::Insert(int k)
//{
//	if (root == nullptr)
//	{
//		root = NewNode(nullptr, k);
//		root->red = false;
//		return;
//	}
//
//	if (Search(k) != nullptr)
//		return;
//
//	RbtNode* node = InsertRecur(root, nullptr, k);
//
//	//Balance(node);
//	//Check(root);
//}
//
//RbtNode* Rbt::InsertRecur(RbtNode* n, RbtNode* p, int k)
//{
//	if (n == nullptr)
//		return NewNode(p, k);
//
//	if (k == n->key)
//		return nullptr;
//
//	if (k < n->key)
//		n->left = InsertRecur(n->left, n, k);
//
//	if (k > n->key)
//		n->right = InsertRecur(n->right, n, k);
//
//	return n;
//}

void Rbt::Check(RbtNode* n)
{
	if (n == nullptr)
		return;

	// root and leaves are black
	// red nodes only have black children (black nodes can have black children)
	// all paths from a node to a dummy node/nullptr have the same number of black nodes

	std::cout << "\n\n NODE " << n->key;;

	if (n->color == RED)
		std::cout << " red";
	else
		std::cout << " black";

	if (n->left != nullptr && n->left->color == RED)
		std::cout << "\n  red";
	else
		std::cout << "\n  black";

	if (n->right != nullptr && n->right->color == RED)
		std::cout << "\n  red";
	else
		std::cout << "\n  black";
	


	if (n->color == RED)
	{
		if (n->left != nullptr && n->left->color == BLACK)
		{
			std::cout << "\n   child " << n->left << " must be black!";
		}

		if (n->right != nullptr && n->right->color == BLACK)
		{
			std::cout << "\n   child " << n->right << " must be black!";
		}
	}



	Check(n->left);
	Check(n->right);
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


