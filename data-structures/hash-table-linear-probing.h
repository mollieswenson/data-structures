#pragma once

#include <iostream>
#include <cassert> 

#include <vld.h>
#include "hash-table-chaining.h"

// LINEAR HASH NODE

template <typename key, typename val>
struct LinearNode
{
    LinearNode<key, val>() {};
    ~LinearNode<key, val>() {};

    key key{};
    val value{};

    bool deleted{false};

    template <typename key, typename val>
    ChainedNode<key, val>& operator=(ChainedNode<key, val>& rhs)
    {
        if (this == &rhs)
            return *this;
        return rhs;
    }
};

// LINEAR PROBING HASH TABLE

template <typename key, typename val>
class LinearProbeHashTable
{
public:
    LinearProbeHashTable() { m_init(); };
    LinearProbeHashTable(size_t cap) : m_capacity(cap) { m_init(); };
    ~LinearProbeHashTable() 
    { 
        for (size_t i = 0; i < m_capacity; i++)
            delete m_array[i];

        delete[] m_array; 
        delete m_deleted;
    }

    void Insert(key&, val&); // insert a node
    void Update(key& k, val v) { m_find(k)->value = v; }; // change a node's value
    const val& Search(key& k) { return m_find(k)->value; }; // get a node's value
    void Delete(key&); // delete a node
    void Clear(); // delete all nodes

    size_t GetSize() { return m_size; }; // returns total number of nodes
    size_t GetCapacity() { return m_capacity; }; // returns max number of nodes arr can hold

private:
    size_t m_size{ 0 }; // total number of nodes
    size_t m_capacity{ 8 }; // size of underlying array

    LinearNode<key, val>** m_array; // ptr to node in array
    LinearNode<key, val>* m_deleted = new LinearNode<key, val>; // placeholder for deleted nodes

    LinearNode<key, val>* m_find(key&); // retuns node for key
    size_t m_hash(const char*); // hash func for const char *
    size_t m_hash(int); // hash fucn for int
    void m_reallocate(size_t); // allocate new array, rehash and move all nodes
    void m_init(); // ititializer creates array and placeholder for deleted nodes   
};

template <typename key, typename val>
void LinearProbeHashTable<key, val>::Insert(key& k, val& v) 
{
    if (m_size == m_capacity)
        m_reallocate(m_capacity * 2);

    LinearNode<key, val>* node = new LinearNode<key, val>;
    node->value = v;
    node->key = k;

    size_t pos = m_hash(k);

    while (m_array[pos] && !m_array[pos]->deleted)
        pos == m_capacity - 1 ? pos = 0 : pos++;

    m_array[pos] = node;
    m_size++;
}

template <typename key, typename val>
void LinearProbeHashTable<key, val>::Delete(key& k)
{   
    LinearNode<key, val>* temp = m_find(k);
    temp = m_deleted; // ?    m_find(k) = m_deleted;
    m_size--;
}

template <typename key, typename val>
void LinearProbeHashTable<key, val>::Clear()
{
    for (size_t i = 0; i < m_capacity; i++)
        delete m_array[i];

    delete m_array;
    m_array = new LinearNode<key, val>*[m_capacity] {nullptr};
    m_size = 0;
}

template <typename key, typename val>
size_t LinearProbeHashTable<key, val>::m_hash(const char* k) // hash const char *
{
    int hash = 401;

    while (*k != '\0')
    {
        hash = hash << 4;
        hash = hash + (int)(*k);
        k++;
    }
    return hash % m_capacity;
}

template <typename key, typename val>
size_t LinearProbeHashTable<key, val>::m_hash(int k) // hash int
{
    int hash = 401;
    hash = hash << 4;
    hash = hash + k;
    return hash % m_capacity;
}

template <typename key, typename val>
LinearNode<key, val>* LinearProbeHashTable<key, val>::m_find(key& k)
{
    size_t pos = m_hash(k);
    size_t count = 0;
    while (!m_array[pos] || m_array[pos]->key != k)
    {
        pos == m_capacity - 1 ? pos = 0 : pos++;
        count++;
        assert(count < m_capacity); //failed search
    }

    LinearNode<key, val>* node = m_array[pos];
    return node;
}

template <typename key, typename val>
void LinearProbeHashTable<key, val>::m_reallocate(size_t s)
{
    assert(s >= m_size);

    m_capacity = s;
    LinearNode<key, val>** new_array = new LinearNode<key, val>*[m_capacity]{nullptr};
    
    size_t pos{};
    for (size_t i = 0; i < m_size; i++)
    {
        pos = m_hash(m_array[i]->key);

        while (new_array[pos])
            pos == m_capacity - 1 ? pos = 0 : pos++;

        new_array[pos] = m_array[i];
    }

    delete m_array;
    m_array = new_array;
}

template <typename key, typename val>
void LinearProbeHashTable<key, val>::m_init()
{
    m_array = new LinearNode<key, val>*[m_capacity] {nullptr};
    m_deleted->deleted = true;
}

