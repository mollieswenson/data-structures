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

    for(int i = 1; i < 21; i++) // keys 1-20 in order
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

     Print(c, c.GetRoot());


     /// works up to this point... 

    Rbt a;  // insert some keys out of order

    a.Insert(1);
    a.Insert(32);
    a.Insert(19);
    a.Insert(15);
    a.Insert(65);
    a.Insert(24);
    a.Insert(33);

    std::cout << "\n\n ==================== ";
    Print(a, a.GetRoot());

    a.Insert(7); // something going wrong here

    std::cout << "\n\n ==================== ";
    Print(a, a.GetRoot());

    

    
    
    

    //std::cout << "\n\n ==================== ";
    //Print(a, a.GetRoot());

    //

    //std::cout << "\n\n ==================== ";
    //Print(a, a.GetRoot());







    //


    //a.Insert(45);
    //a.Insert(48);


    ////

    ////a.Insert(14);
    ////a.Insert(13);
    ////a.Insert(3);
    ////a.Insert(31);
    ////a.Insert(8);

    ////a.Insert(29);
    ////a.Insert(25);
    ////a.Insert(13);
    ////a.Insert(17);
    ////a.Insert(50);
    //




    //node = a.GetRoot();
    //assert(node->key == 20); // expected node
    //assert(node->parent == nullptr); // expected parent
    //assert(node->left == a.Search(10)); // expected left
    //assert(node->right == a.Search(30)); // expected right
    //assert(node->color == BLACK); // expected color

    //node = node->left;
    //assert(node->key == 10);
    //assert(node->parent == a.Search(20));
    //assert(node->left == nullptr);
    //assert(node->right == nullptr);
    //assert(node->color == RED);

    //node = node->parent->right;
    //assert(node->key == 30);
    //assert(node->parent == a.Search(20));
    //assert(node->left == nullptr);
    //assert(node->right == nullptr);
    //assert(node->color == RED);

    //// Print(a, a.GetRoot());

    //




    //// a few random tests... 
   
    //node = a.GetRoot()->left->right->right->left;
    //assert(node->key == 16);
    //assert(node->parent == a.Search(18));
    //assert(node->left == nullptr);
    //assert(node->right == a.Search(17));
    //assert(node->color == BLACK);




    //Rbt b; 

    //b.Insert(3);
    //b.Insert(2);
    //b.Insert(1);


    //// holy shit it works

    //PrintWarnings(a, a.GetRoot());

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

