#pragma once

#include <cassert> 

#include <vld.h>
#include "red-black-tree.h"

void Print(Rbt& t, RbtNode* n);
void PrintKeys(Rbt& tree);
void PrintWarnings(Rbt& t, RbtNode* n);

int test_rbt()
{
	
	// use to verify structure: https://www.cs.usfca.edu/~galles/visualization/RedBlack.html
    RbtNode* node{};
    Rbt c;




    for (int i = 1; i < 21; i++) // keys 1-20 in order
        c.Insert(i);

    node = c.GetRoot();
    assert(node->key == 8); // expected root node
    assert(node->parent == nullptr); // expected parent
    assert(node->left == c.Search(4)); // expected left
    assert(node->right == c.Search(12)); // expected right
    assert(node->color == BLACK); // expected color

    node = c.GetRoot()->right->right->right;           // verify some random nodes
    assert(node->key == 18); 
    assert(node->parent == c.Search(16));
    assert(node->left == c.Search(17));
    assert(node->right == c.Search(19));
    assert(node->color == RED);

    node = c.GetRoot()->left->right->left;
    assert(node->key == 5);
    assert(node->parent == c.Search(6));
    assert(node->left == nullptr);
    assert(node->right == nullptr);
    assert(node->color == BLACK);

    node = c.GetRoot()->right->right->right->left;
    assert(node->key == 17);
    assert(node->parent == c.Search(18));
    assert(node->left == nullptr);
    assert(node->right == nullptr);
    assert(node->color == BLACK);

    node = c.GetRoot()->right->right->right->right;
    assert(node->key == 19);
    assert(node->parent == c.Search(18));
    assert(node->left == nullptr);
    assert(node->right == c.Search(20));
    assert(node->color == BLACK);

    node = c.GetRoot()->right->right->right->right->right;
    assert(node->key == 20);
    assert(node->parent == c.Search(19));
    assert(node->left == nullptr);
    assert(node->right == nullptr);
    assert(node->color == RED);

    node = c.GetRoot()->right->left;
    assert(node->key == 10);
    assert(node->parent == c.Search(12));
    assert(node->left == c.Search(9));
    assert(node->right == c.Search(11));
    assert(node->color == BLACK);

    node = c.GetRoot()->left->left->right;
    assert(node->key == 3);
    assert(node->parent == c.Search(2));
    assert(node->left == nullptr);
    assert(node->right == nullptr);
    assert(node->color == BLACK);

     //Print(c, c.GetRoot());

    Rbt a;  // insert some keys out of order

    a.Insert(9);
    a.Insert(32);
	a.Insert(19); // RL, RR
	a.Insert(6);  // recolor
	a.Insert(7);  // LR, LL
	a.Insert(42);
	a.Insert(66); // RR
	a.Insert(39); // recolor
	a.Insert(29); 
	a.Insert(12); // recolor
	a.Insert(25); // recolor, recolor
	a.Insert(22); // LL
	
	// check inserts so far...

	node = a.GetRoot(); 
	assert(node->key == 19); // expected root node
	assert(node->parent == nullptr); // expected parent
	assert(node->left == a.Search(7)); // expected left
	assert(node->right == a.Search(42)); // expected right
	assert(node->color == BLACK); // expected color

	node = a.GetRoot()->left;
	assert(node->key == 7);
	assert(node->parent == a.Search(19));
	assert(node->left == a.Search(6));
	assert(node->right == a.Search(9));
	assert(node->color == BLACK);

	node = a.GetRoot()->left->left;
	assert(node->key == 6);
	assert(node->parent == a.Search(7));
	assert(node->left == nullptr);
	assert(node->right == nullptr);
	assert(node->color == BLACK);

	node = a.GetRoot()->left->right;
	assert(node->key == 9);
	assert(node->parent == a.Search(7));
	assert(node->left == nullptr);
	assert(node->right == a.Search(12));
	assert(node->color == BLACK);

	node = a.GetRoot()->left->right->right;
	assert(node->key == 12);
	assert(node->parent == a.Search(9));
	assert(node->left == nullptr);
	assert(node->right == nullptr);
	assert(node->color == RED);

	node = a.GetRoot()->right;  // right subtree
	assert(node->key == 42);
	assert(node->parent == a.Search(19));
	assert(node->left == a.Search(32));
	assert(node->right == a.Search(66));
	assert(node->color == BLACK);

	node = a.GetRoot()->right->left;
	assert(node->key == 32);
	assert(node->parent == a.Search(42));
	assert(node->left == a.Search(25));
	assert(node->right == a.Search(39));
	assert(node->color == RED);

	node = a.GetRoot()->right->left->left;
	assert(node->key == 25);
	assert(node->parent == a.Search(32));
	assert(node->left == a.Search(22));
	assert(node->right == a.Search(29));
	assert(node->color == BLACK);

	node = a.GetRoot()->right->left->left->left;
	assert(node->key == 22);
	assert(node->parent == a.Search(25));
	assert(node->left == nullptr);
	assert(node->right == nullptr);
	assert(node->color == RED);

	node = a.GetRoot()->right->left->left->right;
	assert(node->key == 29);
	assert(node->parent == a.Search(25));
	assert(node->left == nullptr);
	assert(node->right == nullptr);
	assert(node->color == RED);

	node = a.GetRoot()->right->left->right;
	assert(node->key == 39);
	assert(node->parent == a.Search(32));
	assert(node->left == nullptr);
	assert(node->right == nullptr);
	assert(node->color == BLACK);

	node = a.GetRoot()->right->right;
	assert(node->key == 66);
	assert(node->parent == a.Search(42));
	assert(node->left == nullptr);
	assert(node->right == nullptr);
	assert(node->color == BLACK);

	a.Insert(30); // insert some more numbers
	a.Insert(31);
	a.Insert(24);
	a.Insert(37);
	a.Insert(38);
	a.Insert(77);
	a.Insert(88);
	a.Insert(90);
	a.Insert(89);
	a.Insert(91);

	node = a.GetRoot()->right;
	assert(node->key == 32);
	assert(node->parent == a.Search(19));
	assert(node->left == a.Search(25));
	assert(node->right == a.Search(77));
	assert(node->color == RED);

	node = a.GetRoot()->right->left->right;
	assert(node->key == 30);
	assert(node->parent == a.Search(25));
	assert(node->left == a.Search(29));
	assert(node->right == a.Search(31));
	assert(node->color == BLACK);

	node = a.GetRoot()->right->right;
	assert(node->key == 77);
	assert(node->parent == a.Search(32));
	assert(node->left == a.Search(42));
	assert(node->right == a.Search(89));
	assert(node->color == BLACK);

	node = a.GetRoot()->right->right->right;
	assert(node->key == 89);
	assert(node->parent == a.Search(77));
	assert(node->left == a.Search(88));
	assert(node->right == a.Search(90));
	assert(node->color == RED);

	node = a.GetRoot()->right->right->right->right->right;
	assert(node->key == 91);
	assert(node->parent == a.Search(90));
	assert(node->left == nullptr);
	assert(node->right == nullptr);
	assert(node->color == RED);



	//a.Delete(9); // delete some nodes
	a.Delete(77);



	std::cout << "\n\n ==================== ";
	Print(a, a.GetRoot());

	return 0;
}

void PrintKeys(Rbt& tree) // for debugging
{
    int* keys = tree.InOrder();
    for (int i = 0; i < tree.GetCount(); i++)
        std::cout << "\n " << keys[i];

    delete keys;
}

void PrintWarnings(Rbt& tree, RbtNode* node) // for debugging
{
    if (node == tree.GetRoot() && node->color != BLACK)
        std::cout << "\nWARNING! non-black root node on node " << node;

    if (node->color == BLACK && node->color == RED)

        std::cout << "\nWARNING! too many colors on node " << node;
    if (node->color != BLACK && node->color != RED)

        std::cout << "\nWARNING! no color on node " << node;

    if (node->color == RED && node->left != nullptr && node->left->color == RED)
        std::cout << "\nWARNING! red with red child on nodes " << node << " and " << node->left;

    if (node->color == RED && node->right != nullptr && node->right->color == RED)
        std::cout << "nWARNING! red with red child on nodes " << node << " and " << node->right;

    if (node->left)
        PrintWarnings(tree, node->left);

    if (node->right)
        PrintWarnings(tree, node->right);
}

void Print(Rbt& tree, RbtNode* node) // for debugging
{
	std::cout << "\n\n NODE " << node->key;

	if (node->color == RED)
		std::cout << " red";
	if (node->color == BLACK)
		std::cout << " black";

	std::cout << "\n   left ";

	if (node->left != nullptr)
	{
		std::cout << node->left->key;
		if (node->left->color == RED)
			std::cout << " red";
		if (node->left->color == BLACK)
			std::cout << " black";
	}
	else
		std::cout << "null black";

	std::cout << "\n   right ";

	if (node->right != nullptr)
	{
		std::cout << node->right->key;
		if (node->right->color == RED)
			std::cout << " red";
		if (node->right->color == BLACK)
			std::cout << " black";
	}
	else
		std::cout << "null black";

	//std::cout << "\n   uncle ";

	//if (node->GetUncle() != nullptr)
	//{
	//	std::cout << node->GetUncle()->key;
	//	if (node->GetUncle()->color == RED)
	//		std::cout << " red";
	//	if (!node->GetUncle()->color == BLACK)
	//		std::cout << " black";
	//}
	//else
	//	std::cout << "null";

	std::cout << "\n   parent ";

	if (node->parent != nullptr)
	{
		std::cout << node->parent->key;
		if (node->parent->color == RED)
			std::cout << " red";
		if (node->parent->color == BLACK)
			std::cout << " black";
	}
	else
		std::cout << "null black";

	//std::cout << "\n   g-parent ";

	//if (node->GetGrandParent() != nullptr)
	//{
	//	std::cout << node->GetGrandParent()->key;
	//	if (node->GetGrandParent()->color == RED)
	//		std::cout << " red";
	//	if (!node->GetGrandParent()->color == BLACK)
	//		std::cout << " black";
	//}
	//else
	//	std::cout << "null";

	if (node->left)
	{
		Print(tree, node->left);
	}

	if (node->right)
	{
		Print(tree, node->right);
	}

}

