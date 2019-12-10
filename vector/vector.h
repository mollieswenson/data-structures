#pragma once

#include <iostream>
#include <array>         // do i even need this? 
#include <cassert> 
#include <vector>
#include <typeinfo>
#include <string>

#include <vld.h>

#include "tests.h"


// implement the std::vector-like class with dynamic array: https://en.cppreference.com/w/cpp/container/vector
// did not include allocators or iterators.. don't know enough 

template <typename T>
class it;

template <typename T> 
class Vector
{
private:
    T* array;
    size_t next_empty{ 0 };
    size_t base{ 8 };
    size_t array_cap{ base };   // right place to initialize these? initializer list? 

    size_t calc_cap(size_t sz);
    void reallocate(size_t cap);
    void manage_capacity();
    bool verify_exists(const size_t index) const;

public:
    Vector(); // defualt constructor
    Vector(int size, T val); // fill constructor 

    template <typename it>
    Vector(it first, it last); // range constructor

    Vector(const Vector &v); // copy constructor that takes another vector 

    ~Vector();

    template <typename T>
    Vector& operator=(Vector& rhs) // assignment operator
    {
        if (this == &rhs)
            return *this;
        return rhs;
    }

    // ELEMENT ACCESS

    T& at(const size_t index) const;  // access specified element

    template <typename T>
    T& operator[](size_t index) { return at(index); };  // access specified element  

    template <typename T>
    friend std::ostream& operator<<(std::ostream& os, const Vector<T>& v); // ostream operator

    T& front() const; // access the first element
    T& back() const; // access the last element
    T* data() const; // direct access to the underlying array 

    it<T> begin(); // returns iterator
    it<T> end();

    // CAPACITY

    const bool empty() const; // returns true if empty
    size_t size() const; // returns current number of elements
    size_t capacity() const;// returns max elements before resize
    void shrink_to_fit();  // reduce capacity to fit size

    // MODIFIERS
    // 
    void assign(const int count, const T& value); // replaces elements in the Vector with value

    void clear(); // clears the contents

    void insert(const size_t pos, const T val); // inserts val before pos

    template<typename it>
    void insert(it first, it last, const Vector<T> coll); // inserts a range of elements at a position 

    template<typename it, typename args>
    void emplace(it pos, args args);  // construct an element in a specified position

    void erase(const size_t first, const size_t last);  // erases range of specified elements  -- something's broken in hhere
    void erase(const size_t pos);  // erases a specified element

    void push_back(const T m); // adds element at end

    void emplace_back(); // construct element in place

    void pop_back(); // remove last elelement

    void swap(size_t a, size_t b); // swaps elements a and b

    //template <typename T>
    void swap(Vector<T>& other); // swaps elements of this Vector with elements of other Vector 
};

template <typename T> 
std::ostream& operator<<(std::ostream& os, const Vector<T>& v);

/////////////////////////////////////////////////////////////////////////// PRIVATE MEMBERS

template <typename T>
size_t Vector<T>::calc_cap(size_t sz)
{
    int temp = base;
    while (temp < sz)
        temp *= 2;       // base(2) rate of growth. should it be base^2?

    return temp;
}

template <typename T>
void Vector<T>::reallocate(size_t cap)
{
    cap = calc_cap(cap);

    T* temp = new T[array_cap = cap];
    for (size_t i = 0; i < next_empty; i++)
        temp[i] = array[i];

    delete[] array;
    array = temp;
    std::cout << "\n   reallocated to array_capacity " << array_cap;
}

template <typename T>
void Vector<T>::manage_capacity()
{
    assert(array_cap >= next_empty);
    if (array_cap == next_empty)
        reallocate(array_cap * 2);
}

template <typename T>
bool Vector<T>::verify_exists(const size_t index) const // returns true if index exists 
{
    if (-1 < index < next_empty)
        return true;

    try { array[index]; throw std::out_of_range("Exception: That index doesnt exist"); }
    catch (std::out_of_range& e) { std::cout << e.what(); }
}

/////////////////////////////////////////////////////////////////////////// CONSTRUCTORS


// const(Type a, Type b) : variable(a), other_var(b) {}

template <typename T>
Vector<T>::Vector() // default constructor
{
    array = new T[array_cap]{};
}

template <typename T>
Vector<T>::Vector(int size, T val) // fill constructor 
{
    array_cap = calc_cap(size);
    array = new T[array_cap]{};

    for (size_t i = 0; i < size; i++)
        push_back(val);
}

template <typename T> // this breaks if i try to combine these
template <typename it>
Vector<T>::Vector(it first, it last) // range constructor
{
    it temp = first;
    int size = 0;

    while (temp != last)
    {
        temp++;
        size++;
    }

    array_cap = calc_cap(size);
    array = new T[array_cap]{};

    while (first != last)
    {
        push_back(*first);  // sometimes first isn't a pointer?
        first++;
    }
}

template <typename T>
Vector<T>::Vector(const Vector &v) // copy constructor
{
    array_cap = calc_cap(v.next_empty);
    array = new T[array_cap]{};

    for (size_t i = 0; i < v.size(); i++)
        push_back(v.at(i));
}

template <typename T>
Vector<T>::~Vector()
{
    delete[] array;
}


// assignment operator


/////////////////////////////////////////////////////////////////////////// ELEMENT ACCESS

template <typename T>
T& Vector<T>::at(const size_t index) const // access specified element
{
    if (verify_exists(index))
        return array[index];

    T empty{};
    return empty; // why can't i return T{}? 
}

// operator[] in header file because reasons (why doesn't it work here?)

template <typename T>
T& Vector<T>::front() const  // access the first element
{
    if (verify_exists(0))
        return array[0];

    T empty{};
    return empty;
}

template <typename T>
T& Vector<T>::back() const // access the last element
{
    if (verify_exists(next_empty - 1))
        return array[next_empty - 1];

    T empty{};
    return empty;
}

template <typename T>
T* Vector<T>::data() const { return array; } // direct access to the underlying array 


/////////////////////////////////////////////////////////////////////////// ITERATORS 

template <typename T>
class it
{
    size_t i;
    Vector<T>& parent;

public: 
    it(Vector<T>& v, size_t pos) : parent(v), i(pos) {}

    T& operator*() { return parent.at(i); }

    it* operator++(int)
    {
        i++;
        return this;
    }


    template <typename T>
    friend bool operator==(it<T>& lhs, it<T>& rhs);

    template <typename T>
    friend bool operator!=(it<T>& lhs, it<T>& rhs);

  
};

template <typename T>
bool operator==(it<T>& lhs, it<T>& rhs) { return lhs.i == rhs.i; }

template <typename T>
bool operator!=(it<T>& lhs, it<T>& rhs) { return !(lhs == rhs); }



template <typename T>
it<T> Vector<T>::begin() 
{
    it<T> i(*this, 0);
    return i;
}

template <typename T>
it<T> Vector<T>::end()
{
    it<T> i(*this, next_empty - 1);
    return i;
}

/////////////////////////////////////////////////////////////////////////// CAPACITY  (excluded std::max_size and reserve)

template <typename T>
const bool Vector<T>::empty() const { return (next_empty == 0); } // returns true if empty

template <typename T>
size_t Vector<T>::size() const { return next_empty; } // returns current number of elements

template <typename T>
size_t Vector<T>::capacity() const { return array_cap; } // returns max elements before resize

template <typename T>
void Vector<T>::shrink_to_fit()  // reduce capacity to fit size
{
    if (calc_cap(next_empty) < array_cap)
        reallocate(calc_cap(next_empty));
}

/////////////////////////////////////////////////////////////////////////// MODIFIERS

template <typename T>
void Vector<T>::assign(const int count, const T& value) // replaces elements in the Vector with value
{
    clear();
    if (array_cap < count) { reallocate(calc_cap(count)); }

    for (size_t i = 0; i < count; i++)
        push_back(value);
}

template <typename T>
void Vector<T>::clear() // clears the contents
{
    while (next_empty)
        pop_back();
}

template <typename T>
void Vector<T>::insert(const size_t pos, const T val) // inserts val before pos
{
    if (verify_exists(pos))
    {
        manage_capacity();
        for (size_t i = next_empty; i >= pos; i--)
            array[i] = array[i - 1];

        array[pos] = val;
        next_empty++;
    }
}

template <typename T>
template <typename it>
void Vector<T>::insert(it first, it last, const Vector<T> coll) {} // inserts a range of elements at a position 


template <typename T>
template <typename it, typename args>
void Vector<T>::emplace(it pos, args args) {} // construct an element in a specified position


template <typename T>
void Vector<T>::erase(const size_t first, const size_t last)   // erases range of specified elements  --  something's broken in here
{
    if (verify_exists(last) && verify_exists(first))
    {
        for (size_t i = first; i < last; i++)
        {
            erase(i);
        }
    }
}

template <typename T>
void Vector<T>::erase(const size_t pos)   // erases a specified element
{
    if (verify_exists(pos))
    {
        for (size_t i = pos; i < size(); i++)
            array[i] = array[i + 1];

        next_empty--;
    }
}

template <typename T>
void Vector<T>::push_back(const T m) // adds element at end
{
    manage_capacity();
    array[next_empty] = m;
    next_empty++;
}

template <typename T>
void Vector<T>::emplace_back() // construct element in place
{
    manage_capacity();
    array[next_empty] = T{};
    next_empty++;
}

template <typename T>
void Vector<T>::pop_back() // remove last elelement
{
    if (next_empty)
    {
        array[next_empty - 1] = T{};
        next_empty--;
    }
}

template <typename T>
void Vector<T>::swap(size_t a, size_t b) // swaps elements a and b
{
    if (verify_exists(a) && verify_exists(b))
    {
        T temp = array[a];
        array[a] = array[b];
        array[b] = temp;
    }
}

template <typename T>
void Vector<T>::swap(Vector& other) { } // swaps elements of this Vector with elements of other Vector 

/////////////////////////////////////////////////////////////////////////// OTHER

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& v)
{
    os << "[ ";

    for (size_t i = 0; i < v.next_empty; i++)
    {
        os << v.array[i] << " ";
    }

    os << "]";
 
    // how to handle this when we have some type that doesn't work here?

    return os;
}

/////////////////////////////////////////////////////////////////////////// TEST TYPE

struct myCustomType  // test data type that allocates its own memory 
{
    int* num = nullptr;
    int cnt{ 3 };

    myCustomType() { num = new int[cnt] {}; std::cout << "\n   myCustomType constructor " << num; }
    myCustomType(int n) { cnt = n; myCustomType(); std::cout << "\n   myCustomType(n) constructor " << num; } // how to create Vector of a type with args (use this constructor)? 
    ~myCustomType() { std::cout << "\n   myCustomType destructor " << num; delete[] num; }
    friend std::ostream& operator<<(std::ostream& os, const myCustomType& t);
};

std::ostream& operator<<(std::ostream& os, const myCustomType& t) // ostream for myCustomType
{
    for (size_t i = 0; i < t.cnt; i++)
        os << t.num[i] << " ";

    return os;
}