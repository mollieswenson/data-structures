#pragma once

#include <iostream>
#include <cassert>

#include <vld.h>

struct bst_node 
{
    bst_node(int k) : key(k) {};
    ~bst_node() { };

    int key{};

    bst_node* left{nullptr};
    bst_node* right{nullptr};
};

class bst
{
public:
    bst() {};
    ~bst() { if (root) { DeleteRecur(root); } };

    bst_node* Insert(int); // insert a node using given key
    void Delete(int); // deletes node with given key
    bst_node* Search(int); // returns ptr to node with given key, or nullptr if key doesn't exist
    int* InOrder(); // returns ordered array of all elements
    
    bst_node* GetRoot() { return root; }; // returns the root node of the tree
    int GetCount() { return CountRecur(root); }; // returns the number of nodes in the tree

private:
    bst_node* InsertRecur(bst_node*, int); // recursive insert
    void InOrderRecur(bst_node* n, int arr[], int& i); // recursive inorder
    int CountRecur(bst_node* n); // recursive counter
    void DeleteRecur(bst_node* n); // recursive delete

    bst_node* GetParent(int); // returns parent of given node
    bst_node* NewNode(int); // creates a new node

    bst_node* root{ nullptr }; // topmost node in tree
};

bst_node* bst::Insert(int k)
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

bst_node* bst::InsertRecur(bst_node* n, int k)
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

bst_node* bst::Search(int k)
{
    bst_node* node = root;

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

void bst::Delete(int k)
{
    if (root == nullptr)
        return;

    bst_node* rm_node = Search(k);

    if (rm_node->left != nullptr && rm_node->right != nullptr) // both subtrees case
    {
        bst_node* successor = rm_node->right;

        while (successor->left != nullptr)
            successor = successor->left; // min of right subtree

        // case where removing root and min of right subtree is root->right
        successor == root->right ? root->right = nullptr : GetParent(successor->key)->left = nullptr;

        rm_node->key = successor->key;
        delete successor;
        return;
    }

    bst_node* parent = GetParent(rm_node->key);

    if (rm_node->left == nullptr && rm_node->right == nullptr) // leaf case
        k < parent->key ? parent->left = nullptr : parent->right = nullptr;

    if(parent->left == rm_node) // single left subtree case
        rm_node->left != nullptr ? parent->left = rm_node->left : parent->left = rm_node->right;

    if (parent->right == rm_node) // single right subtree case
        rm_node->left != nullptr ? parent->right = rm_node->left : parent->right = rm_node->right;
    
    delete rm_node;
    return;
}

bst_node* bst::GetParent(int k)
{
    bst_node* node = root;
    bst_node* parent{};

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

int* bst::InOrder()
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

void bst::InOrderRecur(bst_node* n, int arr[], int& i)
{
    arr[i] = n->key;
    i++;

    if (n->left)
        InOrderRecur(n->left, arr, i);

    if (n->right)
        InOrderRecur(n->right, arr, i);
}

int bst::CountRecur(bst_node* n)
{
    if (n == nullptr)
        return 0;

    int total = 1;
    total += CountRecur(n->left);
    total += CountRecur(n->right);
    return total;
}

void bst::DeleteRecur(bst_node* n)
{
    if (n->left)
        DeleteRecur(n->left);

    if (n->right)
        DeleteRecur(n->right);

    delete n;
}

bst_node* bst::NewNode(int k)
{
    bst_node* node = new bst_node(k);
    return node;
}
