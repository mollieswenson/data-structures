
#include <iostream>

//#pragma once

struct myCustomType;  // test data type that allocates its own memory 

// implement the std::vector-like class with dynamic array: https://en.cppreference.com/w/cpp/container/vector
// did not include allocators or iterators.. don't know enough 

template <typename T> class Vector
{
private:
    T* array;
    size_t next_empty{ 0 };
    size_t base{ 8 };
    size_t array_cap{ base };   // right place to initialize these? initializer list? 

    size_t calc_cap(int sz);
    void reallocate(int cap);
    void manage_capacity();

public:
    Vector(); // defualt constructor
    Vector(int size, T val); // fill constructor 

    template<typename it> 
    Vector<T>(it first, it last); // range constructor

    Vector(const Vector &v); // copy constructor that takes another vector 
    ~Vector();

    Vector& operator=(Vector& rhs); // assignment operator

    void assign(const int count, const T& value); // replaces elements in the Vector with value

    // ELEMENT ACCESS

    T& at(const size_t index) const;  // access specified element
    T& operator[](size_t index); // access specified element  

    template <typename T> 
    friend std::ostream& operator<<(std::ostream& os, const Vector<T>& v); // ostream operator

    T& front() const; // access the first element
    T& back() const; // access the last element
    T* data() const; // direct access to the underlying array 

    // CAPACITY

    const bool empty() const; // returns true if empty
    size_t size() const; // returns current number of elements
    size_t capacity() const;// returns max elements before resize
    void shrink_to_fit();  // reduce capacity to fit size

    // MODIFIERS

    void clear(); // clears the contents

    void insert(const size_t pos, const T val); // inserts val before pos

    template<typename it> 
    void insert(it first, it last, const Vector<T> coll); // inserts a range of elements at a position 

    template<typename it, typename args>
    void emplace(it pos, args&&);  // construct an element in a specified position
    
    void erase(const size_t first, const size_t last);   // erases range of specified elements  -- something's broken in hhere
    void erase(const size_t pos);   // erases a specified element

    void push_back(const T m); // adds element at end

    void emplace_back(); // construct element in place

    void pop_back(); // remove last elelement

    void swap(size_t a, size_t b); // swaps elements a and b

    template <typename T>
    void swap(Vector<T>& other); // swaps elements of this Vector with elements of other Vector 
};

template <typename T> std::ostream& operator<<(std::ostream& os, const Vector<T>& v);
