#pragma once

#include <cassert> 

#include <vld.h>
#include "red-black-tree.h"

void Print(Rbt& t, RbtNode* n);

int test_rbt()
{
	Rbt tree;

	//tree.Insert(5);  // 1
	//tree.Insert(3);  // 2
	//tree.Insert(8);  // 3
	//tree.Insert(4); // 4
	//tree.Insert(1);  // 5
	//tree.Insert(6);  // 6
	//tree.Insert(9);  // 7
	//tree.Insert(2);  // 8
	//tree.Insert(6);  // 9
	//tree.Insert(8);  // 10
	//tree.Insert(9);  // 11


	//tree.Insert(5);
	//tree.Insert(2);
	//tree.Insert(10);
	//tree.Insert(12);
	//tree.Insert(8);
	//tree.Insert(6);
	//tree.Insert(9);

	tree.Insert(20);
	tree.Insert(10);
	tree.Insert(4);
	tree.Insert(14);
	tree.Insert(30);
	tree.Insert(25);
	tree.Insert(24);
	tree.Insert(28);
	tree.Insert(40);
	tree.Insert(48);
	tree.Insert(35);
	tree.Insert(38);
	tree.Insert(32);
	tree.Insert(37);
	tree.Insert(26);
	tree.Insert(27);
	tree.Insert(29);
	tree.Insert(37);
	tree.Insert(37);

	Print(tree, tree.GetRoot());

	//Draw(tree, tree.GetRoot());

	return 0;
}


void Print(Rbt& tree, RbtNode* node) // for debugging
{
	std::cout << "\n\n NODE " << node->key;
	
	if (node->red)
		std::cout << " red";
	if (!node->red)
		std::cout << " black";
	if (node->red == true && node->left == nullptr && node->right == nullptr)
		std::cout << " WARN! (leaf)";

	std::cout << "\n   left ";

	if (node->left != nullptr)
	{
		std::cout << node->left->key;
		if (node->left->red)
			std::cout << " red";
		if (!node->left->red)
			std::cout << " black";
		if (node->red == true && node->left != nullptr && node->left->red == true)
			std::cout << " WARN!";
	}
	else
		std::cout << "null";

	std::cout << "\n   right ";

	if (node->right != nullptr)
	{
		std::cout << node->right->key;
		if (node->right->red)
			std::cout << " red";
		if (!node->right->red)
			std::cout << " black";
		if (node->red == true && node->right != nullptr && node->right->red == true)
			std::cout << " WARN!";
	}
	else
		std::cout << "null";

	std::cout << "\n   uncle ";

	if (node->GetUncle() != nullptr)
	{
		std::cout << node->GetUncle()->key;
		if (node->GetUncle()->red)
			std::cout << " red";
		if (!node->GetUncle()->red)
			std::cout << " black";
	}
	else
		std::cout << "null";

	std::cout << "\n   parent ";

	if (node->parent != nullptr)
	{
		std::cout << node->parent->key;
		if (node->parent->red)
			std::cout << " red";
		if (!node->parent->red)
			std::cout << " black";
	}
	else
		std::cout << "null";

	std::cout << "\n   g-parent ";

	if (node->GetGrandParent() != nullptr)
	{
		std::cout << node->GetGrandParent()->key;
		if (node->GetGrandParent()->red)
			std::cout << " red";
		if (!node->GetGrandParent()->red)
			std::cout << " black";
	}
	else
		std::cout << "null";

	if (node->left)
	{
		Print(tree, node->left);
	}

	if (node->right)
	{
		Print(tree, node->right);
	}

}

