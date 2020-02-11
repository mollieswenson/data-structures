#pragma once

#include <cassert> 

#include <vld.h>
#include "red-black-tree.h"

//void Print(RedBlackTree& t, Node* n);
//void PrintKeys(RedBlackTree& tree);
//void PrintWarnings(RedBlackTree& t, Node* n);

int test_rbt()
{
	
	// use to verify structure: https://www.cs.usfca.edu/~galles/visualization/RedBlack.html
	// 
    RbtNode<int>* node{};

    RedBlackTree<int> a;  // insert some keys out of order

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

	assert(a.GetSuccesor(9)->key == 12); // get successor tests
	assert(a.GetSuccesor(25)->key ==29);
	assert(a.GetSuccesor(29)->key == 32);
	assert(a.GetSuccesor(6)->key == 7);
	assert(a.GetSuccesor(19)->key == 22);
	assert(a.GetSuccesor(66) == nullptr);

	assert(a.GetPredecessor(12)->key == 9);  // get predecessor tests
	assert(a.GetPredecessor(29)->key == 25);
	assert(a.GetPredecessor(39)->key == 32);
	assert(a.GetPredecessor(7)->key == 6);
	assert(a.GetPredecessor(22)->key == 19);
	assert(a.GetPredecessor(6) == nullptr);

	assert(a.GetMax()->key == 66); // min/max tests
	assert(a.GetMin()->key == 6);

	//std::cout << "\n\n ==================== "; 
	//Print(a, a.GetRoot());

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

	//std::cout << "\n\n ==================== "; // is this right? 
	//Print(a, a.GetRoot());

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

	a.Insert(35); // insert a bunch more
	a.Insert(14);
	a.Insert(13);
	a.Insert(34);

	a.Insert(40);
	a.Insert(1);
	a.Insert(21);
	a.Insert(23);

	a.Insert(11);
	a.Insert(27);
	a.Insert(28);
	a.Insert(33);

	a.Insert(10);
	a.Insert(8);
	a.Insert(5);
	a.Insert(36);

	a.Insert(16);
	a.Insert(15);
	a.Insert(4);
	a.Insert(3);

	a.Insert(41);
	a.Insert(43);
	a.Insert(17);
	a.Insert(18);

	node = a.GetRoot()->left;
	assert(node->key == 19);
	assert(node->parent == a.Search(32));
	assert(node->left == a.Search(10));
	assert(node->right == a.Search(25));
	assert(node->color == BLACK);

	node = a.GetRoot()->left->left->left->left->left;
	assert(node->key == 3);
	assert(node->parent == a.Search(5));
	assert(node->left == a.Search(1));
	assert(node->right == a.Search(4));
	assert(node->color == BLACK);

	node = a.GetRoot()->left->left->right->right;
	assert(node->key == 16);
	assert(node->parent == a.Search(14));
	assert(node->left == a.Search(15));
	assert(node->right == a.Search(17));
	assert(node->color == RED);

	node = a.GetRoot()->left->right->right;
	assert(node->key == 30);
	assert(node->parent == a.Search(25));
	assert(node->left == a.Search(28));
	assert(node->right == a.Search(31));
	assert(node->color == RED);

	node = a.GetRoot()->right->left->left;
	assert(node->key == 35);
	assert(node->parent == a.Search(38));
	assert(node->left == a.Search(34));
	assert(node->right == a.Search(37));
	assert(node->color == RED);

	node = a.GetRoot()->right->left->right;
	assert(node->key == 42);
	assert(node->parent == a.Search(38));
	assert(node->left == a.Search(40));
	assert(node->right == a.Search(66));
	assert(node->color == RED);

	node = a.GetRoot()->right->right;
	assert(node->key == 89);
	assert(node->parent == a.Search(77));
	assert(node->left == a.Search(88));
	assert(node->right == a.Search(90));
	assert(node->color == BLACK);

	a.Insert(2);
	a.Insert(0);
	a.Insert(20);
	a.Insert(26);

	a.Delete(66);
	a.Delete(77);
	a.Delete(88);
	a.Delete(89);
	a.Delete(90);
	a.Delete(91);

	//PrintKeys(a);

	int* keys = a.InOrder();
	for (int i = 0; i < a.GetCount(); i++)
		assert(a.Search(i)->key == keys[i]); // keys in expected order
	delete keys;


    RedBlackTree<int> b;

    b.Insert(40);
    b.Delete(40); //case where root is only node
    assert(b.GetRoot() == nullptr);

    b.Insert(40);
    b.Insert(30);
    b.Insert(20);
    b.Insert(10);
    b.Delete(10); // case where node to delete is a left leaf (null successor is black by default)

    node = b.GetRoot();
    assert(node->key == 30); // expected root node
    assert(node->parent == nullptr); // expected parent
    assert(node->left == b.Search(20)); // expected left
    assert(node->right == b.Search(40)); // expected right
    assert(node->color == BLACK); // expected color

    node = b.GetRoot()->left;
    assert(node->key == 20);
    assert(node->parent == b.Search(30));
    assert(node->left == nullptr);
    assert(node->right == nullptr);
    assert(node->color == BLACK);

    b.Insert(50); 
    b.Delete(50); // mirror of previous case (right)

    node = b.GetRoot();
    assert(node->key == 30);
    assert(node->parent == nullptr);
    assert(node->left == b.Search(20));
    assert(node->right == b.Search(40));
    assert(node->color == BLACK);

    node = b.GetRoot()->right;
    assert(node->key == 40);
    assert(node->parent == b.Search(30));
    assert(node->left == nullptr);
    assert(node->right == nullptr);
    assert(node->color == BLACK);

    b.Delete(20); // previous case where delete is 1 below root

    node = b.GetRoot();
    assert(node->key == 30);
    assert(node->parent == nullptr);
    assert(node->left == nullptr);
    assert(node->right == b.Search(40));
    assert(node->color == BLACK);

    node = b.GetRoot()->right;
    assert(node->key == 40);
    assert(node->parent == b.Search(30));
    assert(node->left == nullptr);
    assert(node->right == nullptr);
    assert(node->color == RED);

    b.Insert(20);
    b.Insert(10);
    b.Insert(40);
    b.Delete(20); // case where node to delete and/or predecessor is red (left)

    node = b.GetRoot();
    assert(node->key == 30);
    assert(node->parent == nullptr);
    assert(node->left == b.Search(10));
    assert(node->right == b.Search(40));
    assert(node->color == BLACK);

    node = b.GetRoot()->left;
    assert(node->key == 10);
    assert(node->parent == b.Search(30));
    assert(node->left == nullptr);
    assert(node->right == nullptr);
    assert(node->color == BLACK);

    b.Insert(50);
    b.Delete(40); // previous case mirrored (right)

    node = b.GetRoot();
    assert(node->key == 30);
    assert(node->parent == nullptr);
    assert(node->left == b.Search(10));
    assert(node->right == b.Search(50));
    assert(node->color == BLACK);

    node = b.GetRoot()->right;
    assert(node->key == 50);
    assert(node->parent == b.Search(30));
    assert(node->left == nullptr);
    assert(node->right == nullptr);
    assert(node->color == BLACK);

    b.Delete(10);
    b.Delete(50);
    b.Insert(20);
    b.Insert(40);
    b.Insert(35);

    /// Rotate cases (sibling is black, at least one if sibling's chilren is red)

    b.Delete(20); // RL

    node = b.GetRoot();
    assert(node->key == 35);
    assert(node->parent == nullptr);
    assert(node->left == b.Search(30));
    assert(node->right == b.Search(40));
    assert(node->color == BLACK);

    node = b.GetRoot()->left;
    assert(node->key == 30);
    assert(node->parent == b.Search(35));
    assert(node->left == nullptr);
    assert(node->right == nullptr);
    assert(node->color == BLACK);

    node = b.GetRoot()->right;
    assert(node->key == 40);
    assert(node->parent == b.Search(35));
    assert(node->left == nullptr);
    assert(node->right == nullptr);
    assert(node->color == BLACK);

    b.Insert(25);
    b.Delete(40); // LR

    node = b.GetRoot();
    assert(node->key == 30);
    assert(node->parent == nullptr);
    assert(node->left == b.Search(25));
    assert(node->right == b.Search(35));
    assert(node->color == BLACK);

    node = b.GetRoot()->left;
    assert(node->key == 25);
    assert(node->parent == b.Search(30));
    assert(node->left == nullptr);
    assert(node->right == nullptr);
    assert(node->color == BLACK);

    node = b.GetRoot()->right;
    assert(node->key == 35);
    assert(node->parent == b.Search(30));
    assert(node->left == nullptr);
    assert(node->right == nullptr);
    assert(node->color == BLACK);

    b.Delete(25);
    b.Delete(35);
    b.Insert(20); 
    b.Insert(40);
    b.Insert(35);
    b.Insert(50);

    b.Delete(20); // RR

    node = b.GetRoot();
    assert(node->key == 40);
    assert(node->parent == nullptr);
    assert(node->left == b.Search(30));
    assert(node->right == b.Search(50));
    assert(node->color == BLACK);

    node = b.GetRoot()->left;
    assert(node->key == 30);
    assert(node->parent == b.Search(40));
    assert(node->left == nullptr);
    assert(node->right == b.Search(35));
    assert(node->color == BLACK);

    node = b.GetRoot()->left->right;
    assert(node->key == 35);
    assert(node->parent == b.Search(30));
    assert(node->left == nullptr);
    assert(node->right == nullptr);
    assert(node->color == RED);

    node = b.GetRoot()->right;
    assert(node->key == 50);
    assert(node->parent == b.Search(40));
    assert(node->left == nullptr);
    assert(node->right == nullptr);
    assert(node->color == BLACK);

    b.Insert(25);
    b.Delete(50); // LL

    node = b.GetRoot();
    assert(node->key == 30);
    assert(node->parent == nullptr);
    assert(node->left == b.Search(25));
    assert(node->right == b.Search(40));
    assert(node->color == BLACK);

    node = b.GetRoot()->left;
    assert(node->key == 25);
    assert(node->parent == b.Search(30));
    assert(node->left == nullptr);
    assert(node->right == nullptr);
    assert(node->color == BLACK);

    node = b.GetRoot()->right;
    assert(node->key == 40);
    assert(node->parent == b.Search(30));
    assert(node->left == b.Search(35));
    assert(node->right == nullptr);
    assert(node->color == BLACK);

    node = b.GetRoot()->right->left;
    assert(node->key == 35);
    assert(node->parent == b.Search(40));
    assert(node->left == nullptr);
    assert(node->right == nullptr);
    assert(node->color == RED);


    RedBlackTree<int> c;

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


	return 0;
}
//
//void PrintKeys(RedBlackTree& tree) // for debugging
//{
//
//    int* keys = tree.InOrder();
//    for (int i = 0; i < tree.GetCount(); i++)
//        std::cout << "\n " << keys[i];
//
//    delete keys;
//}
//
//void PrintWarnings(RedBlackTree& tree, Node* node) // for debugging
//{
//    if (node == tree.GetRoot() && node->color != BLACK)
//        std::cout << "\nWARNING! non-black root node on node " << node;
//
//    if (node->color == BLACK && node->color == RED)
//
//        std::cout << "\nWARNING! too many colors on node " << node;
//    if (node->color != BLACK && node->color != RED)
//
//        std::cout << "\nWARNING! no color on node " << node;
//
//    if (node->color == RED && node->left != nullptr && node->left->color == RED)
//        std::cout << "\nWARNING! red with red child on nodes " << node << " and " << node->left;
//
//    if (node->color == RED && node->right != nullptr && node->right->color == RED)
//        std::cout << "nWARNING! red with red child on nodes " << node << " and " << node->right;
//
//    if (node->left)
//        PrintWarnings(tree, node->left);
//
//    if (node->right)
//        PrintWarnings(tree, node->right);
//}
//
//void Print(RedBlackTree& tree, Node* node) // for debugging
//{
//    if (tree.GetRoot() == nullptr)
//    {
//        std::cout << "\n\n EMPTY TREE";
//        return;
//    }
//        
//
//	std::cout << "\n\n NODE " << node->key;
//
//	if (node->color == RED)
//		std::cout << " red";
//	if (node->color == BLACK)
//		std::cout << " black";
//
//	std::cout << "\n   left ";
//
//	if (node->left != nullptr)
//	{
//		std::cout << node->left->key;
//		if (node->left->color == RED)
//			std::cout << " red";
//		if (node->left->color == BLACK)
//			std::cout << " black";
//	}
//	else
//		std::cout << "null black";
//
//	std::cout << "\n   right ";
//
//	if (node->right != nullptr)
//	{
//		std::cout << node->right->key;
//		if (node->right->color == RED)
//			std::cout << " red";
//		if (node->right->color == BLACK)
//			std::cout << " black";
//	}
//	else
//		std::cout << "null black";
//
//	//std::cout << "\n   uncle ";
//
//	//if (node->GetUncle() != nullptr)
//	//{
//	//	std::cout << node->GetUncle()->key;
//	//	if (node->GetUncle()->color == RED)
//	//		std::cout << " red";
//	//	if (!node->GetUncle()->color == BLACK)
//	//		std::cout << " black";
//	//}
//	//else
//	//	std::cout << "null";
//
//	std::cout << "\n   parent ";
//
//	if (node->parent != nullptr)
//	{
//		std::cout << node->parent->key;
//		if (node->parent->color == RED)
//			std::cout << " red";
//		if (node->parent->color == BLACK)
//			std::cout << " black";
//	}
//	else
//		std::cout << "null black";
//
//	//std::cout << "\n   g-parent ";
//
//	//if (node->GetGrandParent() != nullptr)
//	//{
//	//	std::cout << node->GetGrandParent()->key;
//	//	if (node->GetGrandParent()->color == RED)
//	//		std::cout << " red";
//	//	if (!node->GetGrandParent()->color == BLACK)
//	//		std::cout << " black";
//	//}
//	//else
//	//	std::cout << "null";
//
//	if (node->left)
//	{
//		Print(tree, node->left);
//	}
//
//	if (node->right)
//	{
//		Print(tree, node->right);
//	}
//
//}

