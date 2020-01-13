#pragma once

#include <iostream>
#include <cassert>

#include <vld.h>

// CHAINED HASH NODE

template <typename key, typename val>
struct ChainedNode
{
    ChainedNode<key, val>() {};
    ~ChainedNode<key, val>() {};

    key hash_key{}; 
    val value{};

    ChainedNode* next{ };
    ChainedNode* prev{ };

    template <typename key, typename val>
    ChainedNode<key, val>& operator=(ChainedNode<key, val>& rhs)
    {
        if (this == &rhs)
            return *this;
        return rhs;
    }
};

// CHAINED HASH TABLE

template <typename key, typename val>
class ChainedHashTable
{
public:
    ChainedHashTable() { m_array = new ChainedNode<key, val>*[m_capacity] {nullptr}; };
    ChainedHashTable(size_t cap) : m_capacity(cap) { m_array = new ChainedNode<key, val>*[m_capacity] {nullptr}; };
    ~ChainedHashTable() { m_clear(); delete[] m_array; };

    void Insert(key&, val);  // insert a node
    const val& Search(key&); // const breaks this
    void Delete(key&); // delete a node
    void Update(key&, val); // change a node's value
    void Clear() { m_clear; } // delete all nodes 

    size_t GetSize() { return m_size; }; // returns total number of nodes
    size_t GetCapacity() { return m_capacity; }; // returns total number of buckets

private:
    size_t m_size { 0 }; // nodes in the table
    size_t m_capacity{ 8 }; // buckets in the array

    ChainedNode<key, val>** m_array;

    size_t m_hash(const char*); // hash fucn for const char*
    size_t m_hash(int); // hash function for int
    void m_clear(); // clears all nodes from m_array
    void m_reallocate(size_t); // reallocate new array, hash and move all nodes 
};

template <typename key, typename val>
void ChainedHashTable<key, val>::Insert(key& hash_key, val value)
{ 
    if (m_size / m_capacity >= 1) // load factor
        m_reallocate(m_capacity * 2);

    ChainedNode<key, val>* node = new ChainedNode<key, val>; 
    node->value = value; 
    node->hash_key = hash_key;

    size_t pos = m_hash(hash_key); 

    if (!m_array[pos])
    {
        m_array[pos] = node;
    }
    else
    {
        ChainedNode<key, val>* current = m_array[pos];

        while (current->next)
            current = current->next;

        current->next = node;
        node->prev = current;
    }

    m_size++;
}

template <typename key, typename val>
const val& ChainedHashTable<key, val>::Search(key& hash_key)
{
    size_t pos = m_hash(hash_key);
    assert(m_array[pos]);

    ChainedNode<key, val>* current = m_array[pos];

    while (current->hash_key != hash_key)
        current = current->next;

    assert(current);

    return current->value;
}

template <typename key, typename val>
void ChainedHashTable<key, val>::Update(key& hash_key, val value)
{
    int pos = Hash(hash_key);
    ChainedNode<key, val>* current = m_array[pos];

    while (current->hash_key != hash_key)
        current = current->next;

    assert(current);

    current->value = value;
}

template <typename key, typename val>
void ChainedHashTable<key, val>::Delete(key& hash_key)
{
    size_t pos = m_hash(hash_key);
    ChainedNode<key, val>* current = m_array[pos];

    while (current->hash_key != hash_key)
        current = current->next;

    assert(current);

    ChainedNode<key, val>* before = current->prev;
    ChainedNode<key, val>* after = current->next;

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

template <typename key, typename val>
size_t ChainedHashTable<key, val>::m_hash(const char* hash_key) // hash const char *
{
    int hash = 401; // start with prime

    while (*hash_key != '\0')
    {
        hash = hash << 4; // left shift
        hash = hash + (int)(*hash_key); // plus (int)hash_key
        hash_key++;
    }
    return hash % m_capacity; // not sufficiently random?
}

template <typename key, typename val>
size_t ChainedHashTable<key, val>::m_hash(int hash_key) // hash int
{
    int hash = 401;
    hash = hash << 4;
    hash = hash + hash_key;
    return hash % m_capacity; 
}

template <typename key, typename val>
void ChainedHashTable<key, val>::m_clear()
{
    ChainedNode<key, val>* current{};
    ChainedNode<key, val>* next{};

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

template <typename key, typename val>
void ChainedHashTable<key, val>::m_reallocate(size_t s)
{
    m_capacity = s;
    ChainedNode<key, val>** new_array = new ChainedNode<key, val>*[m_capacity] {nullptr};
    ChainedNode<key, val>* node{};
    ChainedNode<key, val>* last{};
    ChainedNode<key, val>* next{};

    size_t pos{};

    for (size_t i = 0; i < m_capacity / 2; i++) // each src bucket
    {
        node = m_array[i];

        while (node) // each node in src bucket
        {
            pos = m_hash(node->hash_key);
             
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

template <typename key, typename val>
bool operator==(ChainedNode<key, val>& lhs, ChainedNode<key, val>& rhs) { return *lhs == *rhs; }

template <typename key, typename val>
bool operator!=(ChainedNode<key, val>& lhs, ChainedNode<key, val>& rhs) { return !(lhs == rhs); }
