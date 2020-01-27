#pragma once

#include <cassert> 

#include <vld.h>
#include "red-black-tree.h"

void Print(Rbt& t, RbtNode* n);

int test_rbt()
{
	Rbt tree;

	// use to test https://www.cs.usfca.edu/~galles/visualization/RedBlack.html

	tree.Insert(10);
	tree.Insert(20);
	tree.Insert(30); // rotate and recolor

	std::cout << "\n\n ============== 30 ";
	Print(tree, tree.GetRoot());

	tree.Insert(15);

	std::cout << "\n\n ============== 15";
	Print(tree, tree.GetRoot());

	tree.Insert(50);

	std::cout << "\n\n ============== 50";
	Print(tree, tree.GetRoot());

	tree.Insert(16);

	std::cout << "\n\n ============== 16";
	Print(tree, tree.GetRoot());

	tree.Insert(9);

	std::cout << "\n\n ============== 9";
	Print(tree, tree.GetRoot());

	tree.Insert(18);

	std::cout << "\n\n ============== 18";
	Print(tree, tree.GetRoot());

	tree.Insert(40);

	std::cout << "\n\n ============== 40";
	Print(tree, tree.GetRoot());

	tree.Insert(35);

	std::cout << "\n\n ============== 35";
	Print(tree, tree.GetRoot());

	tree.Insert(8);

	std::cout << "\n\n ============== 8";
	Print(tree, tree.GetRoot());

	tree.Insert(1);

	std::cout << "\n\n ============== 1";
	Print(tree, tree.GetRoot());

	//tree.Insert(2); // endless recursion

	std::cout << "\n\n ============== 2";
	Print(tree, tree.GetRoot());



	return 0;
}


void Print(Rbt& tree, RbtNode* node) // for debugging
{
	std::cout << "\n\n NODE " << node->key;

	if (node->color == RED)
		std::cout << " red";
	if (node->color == BLACK)
		std::cout << " black";

	if (node == tree.GetRoot() && node->color != BLACK)
		std::cout << "                   WARN! (non-black root node)";
	if (node->color == BLACK && node->color == RED)
		std::cout << "                   WARN! (node has too many colors)";
	if (node->color != BLACK && node->color != RED)
		std::cout << "                   WARN! (node has no color)";

	if (node->color == RED && node->left != nullptr && node->left->color == RED)
		std::cout << "                   WARN! (red with red child)";

	if (node->color == RED && node->right != nullptr && node->right->color == RED)
		std::cout << "                   WARN! (red with red child)";


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
		//if (node->parent->color == RED)
		//	std::cout << " red";
		//if (!node->parent->color == BLACK)
		//	std::cout << " black";
	}
	else
		std::cout << "null";

	/*std::cout << "\n   g-parent ";

	if (node->GetGrandParent() != nullptr)
	{
		std::cout << node->GetGrandParent()->key;
		if (node->GetGrandParent()->color == RED)
			std::cout << " red";
		if (!node->GetGrandParent()->color == BLACK)
			std::cout << " black";
	}
	else
		std::cout << "null";*/

	if (node->left)
	{
		Print(tree, node->left);
	}

	if (node->right)
	{
		Print(tree, node->right);
	}

}

