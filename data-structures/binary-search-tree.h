#pragma once

#include <iostream>
#include <cassert>

#include <vld.h>

struct BstNode 
{
    BstNode(int k) : key(k) {};
    ~BstNode() { };

    int key{};

    BstNode* left{nullptr};
    BstNode* right{nullptr};
};

class Bst
{
public:
    Bst() {};
    ~Bst() { if (root) { DeleteRecur(root); } };

    BstNode* Insert(int); // insert a node using given key
    void Delete(int); // deletes node with given key
    BstNode* Search(int); // returns ptr to node with given key, or nullptr if key doesn't exist
    int* InOrder(); // returns ordered array of all elements
    
    BstNode* GetRoot() { return root; }; // returns the root node of the tree
    int GetCount() { return CountRecur(root); }; // returns the number of nodes in the tree

private:
    BstNode* InsertRecur(BstNode*, int); // recursive insert
    void InOrderRecur(BstNode* n, int arr[], int& i); // recursive inorder
    int CountRecur(BstNode* n); // recursive counter
    void DeleteRecur(BstNode* n); // recursive delete

    BstNode* GetParent(int); // returns parent of given node
    BstNode* NewNode(int); // creates a new node

    BstNode* root{ nullptr }; // topmost node in tree
};

BstNode* Bst::Insert(int k)
{
    if (root == nullptr)
    {
        root = NewNode(k);
        return root;
    }

    if (Search(k) != nullptr)
        return nullptr;
        
    return InsertRecur(root, k);
}

BstNode* Bst::InsertRecur(BstNode* n, int k)
{   
    if (n == nullptr)
        return NewNode(k); 

    if (k == n->key) 
        return nullptr;

    if (k < n->key)
        n->left = InsertRecur(n->left, k);

    if (k > n->key)
        n->right = InsertRecur(n->right, k);

    return n;   
}

BstNode* Bst::Search(int k)
{
    BstNode* node = root;

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

void Bst::Delete(int k)
{
    if (root == nullptr)
        return;

    BstNode* rm_node = Search(k);

    if (rm_node->left != nullptr && rm_node->right != nullptr) // both subtrees case
    {
        BstNode* successor = rm_node->right;

        while (successor->left != nullptr)
            successor = successor->left; // min of right subtree

        // case where removing root and min of right subtree is root->right
        successor == root->right ? root->right = nullptr : GetParent(successor->key)->left = nullptr;

        rm_node->key = successor->key;
        delete successor;
        return;
    }

    BstNode* parent = GetParent(rm_node->key);

    if (rm_node->left == nullptr && rm_node->right == nullptr) // leaf case
        k < parent->key ? parent->left = nullptr : parent->right = nullptr;

    if(parent->left == rm_node) // single left subtree case
        rm_node->left != nullptr ? parent->left = rm_node->left : parent->left = rm_node->right;

    if (parent->right == rm_node) // single right subtree case
        rm_node->left != nullptr ? parent->right = rm_node->left : parent->right = rm_node->right;
    
    delete rm_node;
    return;
}

BstNode* Bst::GetParent(int k)
{
    BstNode* node = root;
    BstNode* parent{};

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

int* Bst::InOrder()
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

void Bst::InOrderRecur(BstNode* n, int arr[], int& i)
{
    arr[i] = n->key;
    i++;

    if (n->left)
        InOrderRecur(n->left, arr, i);

    if (n->right)
        InOrderRecur(n->right, arr, i);
}

int Bst::CountRecur(BstNode* n)
{
    if (n == nullptr)
        return 0;

    int total = 1;
    total += CountRecur(n->left);
    total += CountRecur(n->right);
    return total;
}

void Bst::DeleteRecur(BstNode* n)
{
    if (n->left)
        DeleteRecur(n->left);

    if (n->right)
        DeleteRecur(n->right);

    delete n;
}

BstNode* Bst::NewNode(int k)
{
    BstNode* node = new BstNode(k);
    return node;
}
