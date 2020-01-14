#pragma once

#include <iostream>
#include <cassert>

#include <vld.h>
#include "hash-function.h"

// CHAINED HASH NODE

template <typename KeyT, typename ValT>
struct ChainedNode
{
    ChainedNode<KeyT, ValT>() {};
    ~ChainedNode<KeyT, ValT>() {};

    KeyT key{}; 
    ValT value{};

    ChainedNode* next{ };
    ChainedNode* prev{ };

    template <typename KeyT, typename ValT>
    ChainedNode<KeyT, ValT>& operator=(ChainedNode<KeyT, ValT>& rhs)
    {
        if (this == &rhs)
            return *this;
        return rhs;
    }
};

template <typename KeyT, typename ValT>
class ChainedIterator;

// CHAINED HASH TABLE

template <typename KeyT, typename ValT>
class ChainedHashTable
{
    using NodeType = ChainedNode<KeyT, ValT>;

public:
    ChainedHashTable() { m_array = new NodeType*[m_capacity] {nullptr}; };
    ChainedHashTable(size_t cap) : m_capacity(cap) { m_array = new NodeType*[m_capacity] {nullptr}; };
    ~ChainedHashTable() { ClearArray(); delete[] m_array; };

    void Insert(KeyT&, ValT);  // insert a node
    ValT* Search(KeyT&); // search for a node
    void Delete(KeyT&); // delete a node
    void Update(KeyT&, ValT); // change a node's value
    void Clear() { ClearArray; } // delete all nodes 

    ChainedIterator<KeyT, ValT> begin(); // returns iterator at first node
    ChainedIterator<KeyT, ValT> end();   // returns iterator to last node

    size_t GetSize() { return m_size; }; // returns total number of nodes
    size_t GetCapacity() { return m_capacity; }; // returns total number of buckets

    void Print(); // for testing

private:
    size_t m_size { 0 }; // nodes in the table
    size_t m_capacity{ 8 }; // buckets in the array

    NodeType** m_array;

    size_t Hash(const KeyT&); // hash function (can add type overrides to HashFunc)
    void ClearArray(); // clears all nodes from m_array
    void Reallocate(size_t); // reallocate new array, hash and move all nodes 
};

template <typename KeyT, typename ValT>
void ChainedHashTable<KeyT, ValT>::Insert(KeyT& k, ValT v)
{ 
    if (m_size / m_capacity >= 1) // load factor
        Reallocate(m_capacity * 2);

    NodeType* node = new NodeType; 
    node->value = v; 
    node->key = k;

    size_t pos = Hash(k); 

    if (!m_array[pos])
    {
        m_array[pos] = node;
    }
    else
    {
        NodeType* current = m_array[pos];

        while (current->next)
            current = current->next;

        current->next = node;
        node->prev = current;
    }

    m_size++;
}

template <typename KeyT, typename ValT>
ValT* ChainedHashTable<KeyT, ValT>::Search(KeyT& k) // return ptr here...
{
    size_t pos = Hash(k);
    assert(m_array[pos]);

    NodeType* current = m_array[pos];

    while (current->key != k)
        current = current->next;

    assert(current);

    return &current->value;
}

template <typename KeyT, typename ValT>
void ChainedHashTable<KeyT, ValT>::Update(KeyT& k, ValT v)
{
    int pos = Hash(k);
    NodeType* current = m_array[pos];

    while (current->key != k)
        current = current->next;

    assert(current);

    current->value = v;
}

template <typename KeyT, typename ValT>
void ChainedHashTable<KeyT, ValT>::Delete(KeyT& k)
{
    size_t pos = Hash(k);
    NodeType* current = m_array[pos];

    while (current->key != k)
        current = current->next;

    assert(current);

    NodeType* before = current->prev;
    NodeType* after = current->next;

    if (!before && !after) // single node
        m_array[pos] = nullptr;
        
    if (!before && after) // first
        m_array[pos] = after;

    if (before && after) // middle
    {
        before->next = after;
        after->prev = before;
    }

    if (before && !after) // last
        before->next = nullptr;

    delete current;
    m_size--;
}

template <typename KeyT, typename ValT>
size_t ChainedHashTable<KeyT, ValT>::Hash(const KeyT& k) // hash func
{
    return HashFunction<KeyT>::Hash(k) % m_capacity;
}

template <typename KeyT, typename ValT>
void ChainedHashTable<KeyT, ValT>::ClearArray()
{
    NodeType* current{};
    NodeType* next{};

    for (int i = 0; i < m_capacity; i++)
    {
        current = m_array[i];

        while (current)
        {
            next = current->next;
            delete current;
            current = next;
            m_size--;
        }
    }
}

template <typename KeyT, typename ValT>
void ChainedHashTable<KeyT, ValT>::Reallocate(size_t s)
{
    m_capacity = s;
    NodeType** new_array = new NodeType*[m_capacity] {nullptr};
    NodeType* node{};
    NodeType* last{};
    NodeType* next{};

    size_t pos{};

    for (size_t i = 0; i < m_capacity / 2; i++) // each src bucket
    {
        node = m_array[i];

        while (node) // each node in src bucket
        {
            pos = Hash(node->key);
             
            if (!new_array[pos])
            {
                next = node->next;

                new_array[pos] = node;
                node->prev = nullptr;
                node->next = nullptr;

                node = next;
            }
            else 
            {
                next = node->next;
                last = new_array[pos];

                while (last->next)
                    last = last->next;

                last->next = node;
                node->prev = last;
                node->next = nullptr;

                node = next;          
            }
        }
        m_array[i] = nullptr;
    }
    delete m_array;
    m_array = new_array;
    
}

template <typename KeyT, typename ValT>
ChainedIterator<KeyT, ValT> ChainedHashTable<KeyT, ValT>::end()
{
    size_t pos = m_capacity - 1;
    while (!m_array[pos])
        pos--;

    ChainedIterator<KeyT, ValT> i(this->m_array, pos);
    return i;
}

template <typename KeyT, typename ValT>
ChainedIterator<KeyT, ValT> ChainedHashTable<KeyT, ValT>::begin()
{
    ChainedIterator<KeyT, ValT> i(this->m_array, 0);
    return i;
}

template <typename KeyT, typename ValT>
void ChainedHashTable<KeyT, ValT>::Print()
{
    for (size_t i = 0; i < m_capacity; i++)
    {
        std::cout << "\n\nBucket [" << i << "] ";
        
        NodeType* node = m_array[i];

        while (node)
        {
            std::cout << "(" << node->value << ") ";
            node = node->next;
        }
    }
}


template <typename KeyT, typename ValT>   // key iterator
class ChainedIterator
{
    size_t i;
    ChainedNode<KeyT, ValT>** parent;

public:
    ChainedIterator<KeyT, ValT>(ChainedNode<KeyT, ValT>** par, size_t pos) : i(pos), parent(par) {}

    KeyT& operator*()
    {
        // to do

        assert(parent[i] != nullptr);
        return parent[i]->key;
    }

    ChainedIterator* operator++(int)
    {

        // to do

        do { i++; } while (!parent[i]);

        return this;
    }

    ChainedIterator* operator--(int)
    {
        // to do

        do { i--; } while (!parent[i]);

        return this;
    }

    friend bool operator==(ChainedIterator<KeyT, ValT>& lhs, ChainedIterator<KeyT, ValT>& rhs);
    friend bool operator!=(ChainedIterator<KeyT, ValT>& lhs, ChainedIterator<KeyT, ValT>& rhs);
};

template <typename KeyT, typename ValT>
bool operator==(ChainedIterator<KeyT, ValT>& lhs, ChainedIterator<KeyT, ValT>& rhs) { return *lhs == *rhs; }

template <typename KeyT, typename ValT>
bool operator!=(ChainedIterator<KeyT, ValT>& lhs, ChainedIterator<KeyT, ValT>& rhs) { return !(lhs == rhs); }