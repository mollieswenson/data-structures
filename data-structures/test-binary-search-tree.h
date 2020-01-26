#pragma once

#include <cassert> 

#include <vld.h>
#include "binary-search-tree.h"

void Print(BstNode*);

int test_bst()
{
    Bst tree;

    tree.Insert(7);  // 1
    tree.Insert(0);  // 2
    tree.Insert(3);  // 3
    tree.Insert(10); // 4
    tree.Insert(1);  // 5
    tree.Insert(5);  // 6
    tree.Insert(4);  // 7
    tree.Insert(2);  // 8
    tree.Insert(6);  // 9
    tree.Insert(8);  // 10
    tree.Insert(9);  // 11

    assert(tree.GetRoot()->key == 7); // expected key at root
    assert(tree.Search(12) == nullptr); // non-existent key not in the table
    assert(tree.GetCount() == 11); // expected number of nodes

    tree.Insert(9);  // duplicate keys are disregarded
    tree.Insert(9);
    tree.Insert(9); 

    assert(tree.GetCount() == 11); // expected number of nodes

    int* keys = tree.InOrder();
    for (int i = 0; i < tree.GetCount(); i++)
        assert(tree.Search(i)->key == keys[i]); // keys in expected order
    delete keys;

    tree.Delete(3); // delete node with l and r

    tree.Delete(10); // delete node with only l child
    tree.Delete(1); // delete node with only r child

    tree.Delete(2); // delete an l leaf
    tree.Delete(9); // delete a r leaf

    tree.Delete(7); // delete root

    assert(tree.Search(3) == nullptr); // deleted keys not in the table
    assert(tree.Search(10) == nullptr);
    assert(tree.Search(1) == nullptr);
    assert(tree.Search(2) == nullptr);
    assert(tree.Search(9) == nullptr);
    assert(tree.Search(7) == nullptr);

    assert(tree.GetRoot()->key == 8); // expected key at root
    assert(tree.GetCount() == 5); // expected number of nodes

    keys = tree.InOrder();

    assert(keys[0] == 0); // expected remaining keys
    assert(keys[1] == 4);
    assert(keys[2] == 5);
    assert(keys[3] == 6);
    assert(keys[4] == 8);

    delete keys;

    Bst huge;

    for (int i = 100; i < 200; i++) // add 0 - 299 out of order
        huge.Insert(i);

    for (int i = 0; i < 100; i++)
        huge.Insert(i);

    for (int i = 199; i < 300; i++)
        huge.Insert(i);

    keys = huge.InOrder();
    for (int i = 0; i < huge.GetCount(); i++)
        assert(huge.Search(i)->key == keys[i]); // keys in expected order
    delete keys;

    Bst empty;

    return 0;
}


void Print(BstNode* n) // for debugging
{
    if (n)
    {
        std::cout << "\n\n NODE " << n->key;

        std::cout << "\n   L.ch ";
        if(n->left != nullptr)
            std::cout << n->left->key;
        else
            std::cout << "null";

        std::cout << "\n   R.ch ";
        if (n->right)
            std::cout << n->right->key;
        else
            std::cout << "null";

        if(n->left)
            Print(n->left);

        if(n->right)
            Print(n->right);
    }

}