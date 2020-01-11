#pragma once

#include <iostream>
#include <cassert>

#include <vld.h>

// CHAINED HASH NODE

template <typename key, typename val>
struct ChainedHashNode
{
    ChainedHashNode<key, val>() {};
    ~ChainedHashNode<key, val>() {};

    key hash_key{}; 
    val value{};

    ChainedHashNode* next{ };
    ChainedHashNode* prev{ };

    template <typename key, typename val>
    ChainedHashNode<key, val>& operator=(ChainedHashNode<key, val>& rhs)
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
    ChainedHashTable();
    ChainedHashTable(size_t);
    ~ChainedHashTable();

    void Insert(key&, val); 
    const val& Search(key&);// const breaks this
    void Delete(key&);
    void Update(key&, val);
    void Clear() { m_clear; }

    size_t GetSize() { return m_size; };
    size_t GetCapacity() { return m_capacity; };

    void Dist(); // check dist of nodes among buckets, not sure if useful
    void Print(bool values = false); // prints bucket info, true to also print node vals per bucket

private:
    size_t m_size { 0 }; // nodes in the table
    size_t m_capacity{ 8 }; // buckets in the array

    ChainedHashNode<key, val>* m_array[8]{ nullptr }; // why can't i use m_capacity for the size?

    size_t m_hash(const char*);
    size_t m_hash(int);
    void m_clear(); // clears all nodes from m_array
};

template <typename key, typename val>
ChainedHashTable<key, val>::ChainedHashTable() { }

template <typename key, typename val>
ChainedHashTable<key, val>::ChainedHashTable(size_t cap) : m_capacity(cap) { }

template <typename key, typename val>
ChainedHashTable<key, val>::~ChainedHashTable() { m_clear(); }

template <typename key, typename val>
void ChainedHashTable<key, val>::Insert(key& hash_key, val value)
{ 
    ChainedHashNode<key, val>* node = new ChainedHashNode<key, val>; 
    node->value = value; 
    node->hash_key = hash_key;

    size_t pos = m_hash(hash_key); 

    if (m_array[pos] != nullptr)
    {
        ChainedHashNode<key, val>* current = m_array[pos];

        current = m_array[pos];

        while (current->next)
            current = current->next;

        current->next = node;
        node->prev = current;
        m_size++;
    }

    if (m_array[pos] == nullptr) 
    {
        m_array[pos] = node;
        m_size++;
    }

    // use copy constructor to reallocate to larger array if load factor above x?
}

template <typename key, typename val>
const val& ChainedHashTable<key, val>::Search(key& hash_key)
{
    size_t pos = m_hash(hash_key);
    assert(m_array[pos] != nullptr);

    ChainedHashNode<key, val>* current = m_array[pos];

    while (current->hash_key != hash_key)
        current = current->next;

    assert(current != nullptr);

    return current->value;
}

template <typename key, typename val>
void ChainedHashTable<key, val>::Update(key& hash_key, val value)
{
    int pos = Hash(hash_key);
    ChainedHashNode<key, val>* current = m_array[pos];

    while (current->hash_key != hash_key)
        current = current->next;

    assert(current != nullptr);

    current->value = value;
}

template <typename key, typename val>
void ChainedHashTable<key, val>::Delete(key& hash_key)
{
    size_t pos = m_hash(hash_key);
    ChainedHashNode<key, val>* current = m_array[pos];

    while (current->hash_key != hash_key)
        current = current->next;

    assert(current != nullptr);

    ChainedHashNode<key, val>* before = current->prev;
    ChainedHashNode<key, val>* after = current->next;

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
    hash = hash << 4; // left shift
    hash = hash + hash_key; // plus hash_key
    return hash % m_capacity; 
}

template <typename key, typename val>
void ChainedHashTable<key, val>::m_clear()
{
    ChainedHashNode<key, val>* current{};
    ChainedHashNode<key, val>* next{};

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
void ChainedHashTable<key, val>::Dist()
{
    ChainedHashNode<key, val>* current{};
    ChainedHashNode<key, val>* next{};
    size_t count{};

    for (size_t i = 0; i < m_capacity; i++) // buckets
    {
        current = m_array[i];

        while (current) 
        {
            next = current->next;
            current = next;
            count++;
        }
        // count is nodes in this bucket.. what to do with this info?
        count = 0;
    }
}

template <typename key, typename val> // maybe move to tests, but need to access m_array..
void ChainedHashTable<key, val>::Print(bool values)  
{
    ChainedHashNode<key, val>* current{};
    ChainedHashNode<key, val>* next{};
    size_t count{};

    double lf = (double)m_size / (double)m_capacity;
    double diff{};

    std::cout << "\n\nCapacity: " << m_capacity;
    std::cout << "\nSize: " << m_size;
    std::cout << "\nLoad Fact: " << (double)m_size / (double)m_capacity << "\n";

    for (size_t i = 0; i < m_capacity; i++) // buckets
    {
        current = m_array[i];
        std::cout << "\nBucket [" << i << "]";

        while (current)
        {
            if(values)
                std::cout << " (" << current->hash_key << ")";

            next = current->next;
            current = next;
            count++;
        }
        std::cout << " [" << count << " nodes]";
        diff += (count / lf);
        count = 0;
    }
}

template <typename key, typename val>
bool operator==(ChainedHashNode<key, val>& lhs, ChainedHashNode<key, val>& rhs) { return *lhs == *rhs; }

template <typename key, typename val>
bool operator!=(ChainedHashNode<key, val>& lhs, ChainedHashNode<key, val>& rhs) { return !(lhs == rhs); }
