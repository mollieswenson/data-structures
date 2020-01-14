#pragma once

#include <iostream>
#include <cassert> 

#include <vld.h>
#include "hash-function.h"

// LINEAR HASH NODE

template <typename KeyT, typename ValT>
struct LinearNode
{
    LinearNode<KeyT, ValT>() {};
    ~LinearNode<KeyT, ValT>() {};

    KeyT key{};
    ValT value{};

    bool deleted{false};

    template <typename KeyT, typename ValT>
    LinearNode<KeyT, ValT>& operator=(LinearNode<KeyT, ValT>& rhs)
    {
        if (this == &rhs)
            return *this;
        return rhs;
    }
};

template <typename KeyT, typename ValT>
class LinearIterator;

// LINEAR PROBING HASH TABLE

template <typename KeyT, typename ValT>
class LinearProbeHashTable
{
using NodeType = LinearNode<KeyT, ValT>;

public:
    LinearProbeHashTable() { Init(); };
    LinearProbeHashTable(size_t cap) : m_capacity(cap) { Init(); };
    ~LinearProbeHashTable() 
    { 
        for (size_t i = 0; i < m_capacity; i++)
            delete m_array[i];

        delete[] m_array; 
        delete m_deleted;
    }

    void Insert(KeyT&, ValT&); // insert a node
    void Update(KeyT&, ValT); // change a node's value
    ValT* Search(KeyT&); // get a node's value 
    void Delete(KeyT&); // delete a node
    void Clear(); // delete all nodes

    LinearIterator<KeyT, ValT> begin(); // returns iterator to first node
    LinearIterator<KeyT, ValT> end();   // returns iterator to last node

    size_t GetSize() { return m_size; }; // returns total number of nodes
    size_t GetCapacity() { return m_capacity; }; // returns max number of nodes arr can hold

    void Print();

private:
    size_t m_size{ 0 }; // total number of nodes
    size_t m_capacity{ 8 }; // size of underlying array

    NodeType** m_array; // ptr to node in array
    NodeType* m_deleted = new NodeType; // placeholder for deleted nodes

    NodeType* Find(KeyT&); // retuns node for KeyT
    size_t Hash(const KeyT& k); // returns index in array
    void Reallocate(size_t); // allocate new array, rehash and move all nodes
    void Init(); // array and placeholder for deleted nodes   
};

template <typename KeyT, typename ValT>
void LinearProbeHashTable<KeyT, ValT>::Insert(KeyT& k, ValT& v) 
{
    if (m_size == m_capacity)
        Reallocate(m_capacity * 2);

    NodeType* node = new NodeType;
    node->value = v;
    node->key = k;

    size_t pos = Hash(k);

    while (m_array[pos] && !m_array[pos]->deleted)
        pos == m_capacity - 1 ? pos = 0 : pos++;

    m_array[pos] = node;
    m_size++;
}

template <typename KeyT, typename ValT>
void LinearProbeHashTable<KeyT, ValT>::Update(KeyT& k, ValT v) // change a node's value
{
    NodeType* node = Find(k);
    if (node)
        node->value = v;
}

template <typename KeyT, typename ValT>
ValT* LinearProbeHashTable<KeyT, ValT>::Search(KeyT& k)  // get a node's value 
{
    NodeType* node = Find(k);
    if (node)
        return &node->value;

    return nullptr;
}

template <typename KeyT, typename ValT>
void LinearProbeHashTable<KeyT, ValT>::Delete(KeyT& k)
{   
    NodeType* temp = Find(k);
    if (temp)
    {
        temp = m_deleted;
        m_size--;
    }
}

template <typename KeyT, typename ValT>
void LinearProbeHashTable<KeyT, ValT>::Clear()
{
    for (size_t i = 0; i < m_capacity; i++)
        delete m_array[i];

    delete m_array;
    m_array = new NodeType*[m_capacity] {nullptr};
    m_size = 0;
}

template <typename KeyT, typename ValT>
size_t LinearProbeHashTable<KeyT, ValT>::Hash(const KeyT& k) // hash func
{
    return HashFunction<KeyT>::Hash(k) % m_capacity;
}

template <typename KeyT, typename ValT>
typename LinearProbeHashTable<KeyT, ValT>::NodeType* LinearProbeHashTable<KeyT, ValT>::Find(KeyT& k)
{
    size_t pos = Hash(k);
    size_t count = 0;
    while (!m_array[pos] || m_array[pos]->key != k)
    {
        pos == m_capacity - 1 ? pos = 0 : pos++;
        count++;
        if (count > m_capacity) //failed search
            return nullptr;
    }

    NodeType* node = m_array[pos];
    return node;
}

template <typename KeyT, typename ValT>
void LinearProbeHashTable<KeyT, ValT>::Reallocate(size_t s)
{
    assert(s >= m_size);

    m_capacity = s;
    NodeType** new_array = new NodeType*[m_capacity]{nullptr};
    
    size_t pos{};
    for (size_t i = 0; i < m_size; i++)
    {
        pos = Hash(m_array[i]->key);

        while (new_array[pos])
            pos == m_capacity - 1 ? pos = 0 : pos++;

        new_array[pos] = m_array[i];
    }

    delete m_array;
    m_array = new_array;
}

template <typename KeyT, typename ValT>
void LinearProbeHashTable<KeyT, ValT>::Init()
{
    m_array = new NodeType*[m_capacity] {nullptr};
    m_deleted->deleted = true;
}

template <typename KeyT, typename ValT>
LinearIterator<KeyT, ValT> LinearProbeHashTable<KeyT, ValT>::end()
{
    size_t pos = m_capacity - 1;
    while (!m_array[pos])
        pos--;

    LinearIterator<KeyT, ValT> i(this->m_array, pos);
    return i;
}

template <typename KeyT, typename ValT>
LinearIterator<KeyT, ValT> LinearProbeHashTable<KeyT, ValT>::begin()
{
    LinearIterator<KeyT, ValT> i(this->m_array, 0);
    return i;
}

template <typename KeyT, typename ValT>
void LinearProbeHashTable<KeyT, ValT>::Print()
{
    for (size_t i = 0; i < m_capacity; i++)
    {
        std::cout << "\n[" << i << "] ";

        if (m_array[i])
            std::cout << m_array[i]->value;
    }
}


template <typename KeyT, typename ValT>   // key iterator
class LinearIterator
{
    size_t i;
    LinearNode<KeyT, ValT>** parent;

public:
    LinearIterator<KeyT, ValT>(LinearNode<KeyT, ValT>** par, size_t pos) : i(pos), parent(par) {}

    KeyT& operator*()
    {
        assert(parent[i] != nullptr);
        return parent[i]->key;  
    }

    LinearIterator* operator++(int)
    {
        do { i++; }
        while (!parent[i]);

        return this;
    }

    LinearIterator* operator--(int)
    {
        do { i--; }
        while (!parent[i]);

        return this;
    }

    friend bool operator==(LinearIterator<KeyT, ValT>& lhs, LinearIterator<KeyT, ValT>& rhs);
    friend bool operator!=(LinearIterator<KeyT, ValT>& lhs, LinearIterator<KeyT, ValT>& rhs);
};

template <typename KeyT, typename ValT>
bool operator==(LinearIterator<KeyT, ValT>& lhs, LinearIterator<KeyT, ValT>& rhs) { return *lhs == *rhs; }

template <typename KeyT, typename ValT>
bool operator!=(LinearIterator<KeyT, ValT>& lhs, LinearIterator<KeyT, ValT>& rhs) { return !(lhs == rhs); }
