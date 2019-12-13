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
// also looking at blz/vector.h https://ghosthub.corp.blizzard.net/blizzard/blz/blob/master/include/blz/vector.h

// QUESTIONS
// i noticed blz::vector public functions mostly only call protected members, not other public...
// what is the reason for that? is that more efficient? less prone to errors? more testable?
// what does m_capacity_is_embedded mean on blz::vector::m_elements?
// template <typename T> vs. template <class T> -- should i use typename unless class is specifically required? 
// should my iterator class be part of the vector class, or a separate class like i have it? 
// are iterator classes expected to work with different container types or are they specific to one (ie Vector)?
// why is blz::vector capacity sizeof(size_type) * 8 - 1; (what occupies that one subtracted space?)
// should i assert instead of trying to handle exception on trying to access out of bounds array index?

// TO DO
// add typedefs
// add allocators
// more separation between protected and public functions, such as separate
// _init, _construct, and _destroy functions that the public constructors call
//  prefix members with m_ when they are private/protected data
// prefix members with _ when they are private/ protected functions
// standardize parameter names
// handle bad index better for at(), front, back(), and maybe iterators 
// test using asserts instead of visually verifying correct data
// maybe refactor everything back into class def


template <typename T>
class it;

template <typename T> 
class Vector
{
private:
    T* array;
    size_t next_empty{ 0 };
    size_t base{ 8 };
    size_t array_cap{ base };

    size_t calc_cap(size_t sz);
    void reallocate(size_t cap);
    void manage_capacity();
    bool verify_exists(const size_t index) const;

public:
    Vector(); // default 
    Vector(int size, T val); // fill 

    template <typename it>
    Vector(it first, it last); // range 

    Vector(const Vector &v); // copy 

    ~Vector();

    template <typename T>
    Vector& operator=(Vector& rhs) // assignment
    {
        if (this == &rhs)
            return *this;
        return rhs;
    }

    // ELEMENT ACCESS

    T& at(const size_t index) const;  // access specified element

    template <typename T>
    T& operator[](size_t index) { return at(index); };  // access specified element []

    template <typename T>
    friend std::ostream& operator<<(std::ostream& os, const Vector<T>& v); // ostream

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

    void assign(const int count, const T& value); // replaces elements in the Vector with value

    void clear(); // clears the contents

    void insert(const size_t pos, const T val); // inserts val before pos

    void erase(const size_t first, const size_t last);  // erases range of specified elements
    void erase(const size_t pos);  // erases a specified element

    void push_back(const T m); // adds element at end

    void emplace_back(); // constructs element in place

    void pop_back(); // removes last elelement

    void swap(size_t a, size_t b); // swaps elements at index a and index b
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
    if (0 <= index && index <= next_empty)
        return true;

    try { array[index]; throw std::out_of_range("Exception: That index doesnt exist"); }
    catch (std::out_of_range& e) { std::cout << e.what(); }
}

/////////////////////////////////////////////////////////////////////////// CONSTRUCTORS

template <typename T>
Vector<T>::Vector() // default
{
    array = new T[array_cap]{};
}

template <typename T>
Vector<T>::Vector(int size, T val) // fill 
{
    array_cap = calc_cap(size);
    array = new T[array_cap]{};

    for (size_t i = 0; i < size; i++)
        push_back(val);
}

template <typename T> // this breaks if i try to combine these.. what is this supposed to look like? 
template <typename it>
Vector<T>::Vector(it first, it last) // range
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
        push_back(*first);
        first++;
    }
}

template <typename T>
Vector<T>::Vector(const Vector &v) // copy
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

/////////////////////////////////////////////////////////////////////////// ELEMENT ACCESS

template <typename T>
T& Vector<T>::at(const size_t index) const // access specified element like http://www.cplusplus.com/reference/vector/vector/at/ 
{                                          // i wanted at/front/back to return a reference when index is valid, and throw exception when not (like std::vector)
    if (verify_exists(index))              // veryify_exists throws an exception when index is invalid, but then we come back here and still have to return something.
        return array[index];               // bc::array doesn't throw excpetion, instead has BC_ASSERT(n < N, n, N) where N is size, n is index
                                           // does this mean we always expect n to be valid in production code and there is never an exception?
    T empty{};
    return empty;
}

// operator[] implemented in class def because defining it here didn't work. why?

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
    if (verify_exists(next_empty))
        return array[next_empty];

    T empty{};
    return empty;
}

template <typename T> 
T* Vector<T>::data() const // direct access to the underlying array 
{ 
    if (next_empty > 0)
        return array;
 
    return nullptr;
} 

template <typename T> 
class it // iterator
{
    size_t i;
    Vector<T>& parent;

public: 
    it(Vector<T>& v, size_t pos) : parent(v), i(pos) {}

    T& operator*() { return parent.at(i); }

    it* operator++(int) // todo: address when iterator goes out of bounds
    {
        i++;
        return this;
    }

    template <typename T>
    friend bool operator==(it<T>& lhs, it<T>& rhs); // are two iterators at the same position the exact same iterator? 

    template <typename T>
    friend bool operator!=(it<T>& lhs, it<T>& rhs);
};

template <typename T>
it<T> Vector<T>::begin() // gets iterator at the first element
{
    verify_exists(0);
    it<T> i(*this, 0); // should you be allowed to create an iterator for an empty vector?
    return i;
}

template <typename T>
it<T> Vector<T>::end()// gets iterator at the last element
{
    verify_exists(next_empty - 1);
    it<T> i(*this, next_empty - 1); // should you be allowed to create an iterator for an empty vactor?
    return i;
}

/////////////////////////////////////////////////////////////////////////// CAPACITY

template <typename T>
const bool Vector<T>::empty() const { return (next_empty == 0); } // returns true if empty

template <typename T>
size_t Vector<T>::size() const { return next_empty; } // returns current number of elements

template <typename T>
size_t Vector<T>::capacity() const { return array_cap; } // returns max elements before resize

template <typename T>
void Vector<T>::shrink_to_fit()  // reduces capacity to fit size
{
    if (calc_cap(next_empty) < array_cap)
        reallocate(calc_cap(next_empty));
}

/////////////////////////////////////////////////////////////////////////// MODIFIERS

template <typename T>
void Vector<T>::assign(const int count, const T& val) // replaces elements in the Vector with value
{
    clear();
    if (array_cap < count) { reallocate(calc_cap(count)); }

    for (size_t i = 0; i < count; i++)
        push_back(val);
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
    if (!verify_exists(pos))
        return;

    manage_capacity();
    for (size_t i = next_empty; i >= pos; i--)
        array[i] = array[i - 1];

    array[pos] = val;
    next_empty++;
}

template <typename T>
void Vector<T>::erase(const size_t first, const size_t last)   // erases range of specified elements
{
    if (first > last)
        return;

    int count = last - first; 
    while (count < last)
    {
        erase(first); // i don't think this is efficient
        count--;
    }
}

template <typename T>
void Vector<T>::erase(const size_t pos)   // erases a specified element
{
    if (!verify_exists(pos))
        return;

    for (size_t i = pos; i < size(); i++)
        array[i] = array[i + 1];

    next_empty--;
}

template <typename T>
void Vector<T>::push_back(const T m) // adds element at end
{
    manage_capacity();
    array[next_empty] = m;
    next_empty++;
}

template <typename T>
void Vector<T>::emplace_back() // construct element in place (should take constructor args)
{
    manage_capacity();
    array[next_empty] = T{};
    next_empty++;
}

template <typename T>
void Vector<T>::pop_back() // remove last elelement
{
    if (!next_empty)
        return;

    array[next_empty - 1] = T{}; // construct a new object there in memory so that data is actually gone.. is this neccessary? 
    next_empty--;
}

template <typename T>
void Vector<T>::swap(size_t a, size_t b) // swaps elements a and b
{
    if (verify_exists(a) && verify_exists(b))
    {
        T* temp = new T;
        *temp = array[a];
        array[a] = array[b];
        array[b] = *temp;
        delete temp;
    }
}

/////////////////////////////////////////////////////////////////////////// TEST TYPE

struct myCustomType  // user-defined data type for tests
{
    int number{ 3 }; 
    int* ptr = nullptr;

    myCustomType() { }
    myCustomType(int n) { number = n; }
    ~myCustomType() {  }
    friend std::ostream& operator<<(std::ostream& os, const myCustomType& t);
    int operator*() { return number; }

    myCustomType operator++(int) // these are here so this type works with the tests 
    {
        number++;
        return *this;
    }

    template <typename T>
    friend bool operator==(it<T>& lhs, it<T>& rhs);

    template <typename T>
    friend bool operator!=(it<T>& lhs, it<T>& rhs);
};

/////////////////////////////////////////////////////////////////////////// OTHER
/// 
std::ostream& operator<<(std::ostream& os, const myCustomType& t) // ostream for myCustomType
{
    os << "x";
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& v) // ostream for Vector
{
    os << "[ ";

    for (size_t i = 0; i < v.next_empty; i++)
    {
        os << v.array[i] << " "; // is there a way to handle when T doesn't support << ?
    }

    os << "]";
    return os;
}

template <typename T>
bool operator==(it<T>& lhs, it<T>& rhs) { return *lhs == *rhs; } // is this right for iterator? both iterator and myCustomType use this.. is that oka? 

template <typename T>
bool operator!=(it<T>& lhs, it<T>& rhs) { return !(lhs == rhs); }
