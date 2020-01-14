#pragma once

#include <iostream>
#include <cassert> 

#include <vld.h>

template <typename T>
class Iterator;

template <typename T>
class Vector
{
public:
    Vector(); // default 

    Vector(int size, T ValT); // fill

    //template <typename Iterator>
    //Vector(Iterator first, Iterator last); // range (broken)

    Vector(const Vector& v); // copy 

    ~Vector();

    template <typename T>
    Vector& operator=(Vector& rhs) // assignment
    {
        if (this == &rhs)
            return *this;
        return rhs;
    }

    // ELEMENT ACCESS

    T& at(const size_t pos) const;  // access element; 
    T& operator[](const size_t pos) const { return at(pos); };  // access element using []

    friend std::ostream& operator<<(std::ostream& os, const Vector<T>& v); // ostream

    T& front() const; // access the first element
    T& back() const; // access the last element
    T* data() const; // direct access to the underlying array 

    Iterator<T> begin(); // returns iterator at front
    Iterator<T> end();   // returns iterator at back (1 after last element/0 if empty)

    // CAPACITY

    size_t size() const; // returns current number of elements
    size_t capacity() const;// returns max elements before resize
    void reserve(size_t);  // allocate to specified capacity
    void shrink_to_fit();  // reduce capacity to fit size

    // MODIFIERS

    void assign(const int pos, const T& ValT); // replaces all elements in the Vector with value
    void clear(); // clears the contents
    void insert(const size_t pos, const T& ValT); // inserts ValT before pos
    void erase(const size_t beg, const size_t end);  // erases range of elements 
    void erase(const size_t);  // erases a specified element
    void push_back(const T&); // adds element at end
    void emplace_back(); // constructs element in place
    void pop_back(); // removes last elelement
    void swap(size_t a, size_t b); // swaps elements at pos a and pos b

private:
    T* _array;
    size_t _size{ 0 };
    size_t _base{ 8 };
    size_t _capacity{ _base };

    size_t _calc_capacity(size_t);
    void _reallocate(size_t);
    void _manage_capacity();
    void _check(const size_t) const;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& v);

template <typename T>
Vector<T>::Vector() // default
{
    _array = new T[_capacity]{};
}

template <typename T>
Vector<T>::Vector(int size, T ValT) // fill 
{
    _capacity = _calc_capacity(size);
    _array = new T[_capacity]{};

    for (size_t i = 0; i < size; i++)
        push_back(ValT);
}

//template <typename T>
//template <typename Iterator>
//Vector<T>::Vector(Iterator first, Iterator last) // range [first, last]
//{
//    Iterator temp = first;
//    int size = 0;
//
//    while (temp != last)
//    {
//        temp++;
//        size++;
//    }
//
//    _capacity = _calc_capacity(size);
//    _array = new T[_capacity]{};
//
//    T& test = *first;
//
//    while (first != last)
//    {
//        push_back(*first);            // illegal indirection, but first is a pointer i should be able to deref for this? 
//        first++;
//    }
//}

template <typename T>
Vector<T>::Vector(const Vector& v) // copy
{
    _capacity = _calc_capacity(v._size);
    _array = new T[_capacity]{};

    for (size_t i = 0; i < v.size(); i++)
        push_back(v.at(i));
}

template <typename T>
Vector<T>::~Vector()
{
    delete[] _array;
}

// ACCESS

template <typename T>
T& Vector<T>::at(const size_t pos) const
{
    _check(pos);
    return _array[pos];
}

template <typename T>
T& Vector<T>::front() const
{
    _check(0);
    return _array[0];
}

template <typename T>
T& Vector<T>::back() const
{
    _check(_size - 1);
    return _array[_size - 1];
}

template <typename T>
T* Vector<T>::data() const
{
    return _array;
}

template <typename T>
class Iterator
{
    size_t i;
    Vector<T>& parent;

public:
    Iterator(Vector<T>& v, size_t pos) : parent(v), i(pos) {}

    T& operator*() { return parent.at(i); }

    Iterator* operator++(int)
    {
        i++;
        return this;
    }

    Iterator* operator--(int)
    {
        i--;
        return this;
    }

    template <typename T>
    friend bool operator==(Iterator<T>& lhs, Iterator<T>& rhs);

    template <typename T>
    friend bool operator!=(Iterator<T>& lhs, Iterator<T>& rhs);
};

template <typename T>
Iterator<T> Vector<T>::begin()
{
    _check(0);
    Iterator<T> i(*this, 0);
    return i;
}

template <typename T>
Iterator<T> Vector<T>::end()
{
    Iterator<T> i(*this, _size);
    return i;
}

// CAPACITY

template <typename T>
size_t Vector<T>::size() const { return _size; }

template <typename T>
size_t Vector<T>::capacity() const { return _capacity; }

template <typename T>
void Vector<T>::shrink_to_fit()
{
    if (_calc_capacity(_size) < _capacity)
        _reallocate(_calc_capacity(_size));
}

template <typename T>
void Vector<T>::reserve(size_t cap)
{
    if (_calc_capacity(cap) > _size)
        _reallocate(_calc_capacity(cap));
}

// MODIFIERS

template <typename T>
void Vector<T>::assign(const int pos, const T& ValT)
{
    clear();
    if (_capacity < pos) { _reallocate(_calc_capacity(pos)); }

    for (size_t i = 0; i < pos; i++)
        push_back(ValT);
}

template <typename T>
void Vector<T>::clear()
{
    while (_size)
        pop_back();
}

template <typename T>
void Vector<T>::insert(const size_t pos, const T& ValT)
{
    _check(pos);
    _manage_capacity();

    for (size_t i = _size; i > pos; i--)
        _array[i] = _array[i - 1];

    _array[pos] = ValT;
    _size++;
}

template <typename T>
void Vector<T>::erase(const size_t first, const size_t last)
{
    if (first > last)
        return;

    size_t count = last - first;
    while (count <= last)
    {
        erase(first); // inefficient
        count--;
    }
}

template <typename T>
void Vector<T>::erase(const size_t pos)
{
    _check(pos);

    for (size_t i = pos; i < size(); i++)
        _array[i] = _array[i + 1];

    _size--;
}

template <typename T>
void Vector<T>::push_back(const T& m)
{
    _manage_capacity();
    _array[_size] = m;
    _size++;
}

template <typename T>
void Vector<T>::emplace_back() // should take constructor args for T
{
    _manage_capacity();
    _array[_size] = T{};
    _size++;
}

template <typename T>
void Vector<T>::pop_back()
{
    if (!_size)
        return;

    _array[_size - 1] = T{};
    _size--;
}

template <typename T>
void Vector<T>::swap(size_t a, size_t b)
{
    _check(a);
    _check(b);

    T* temp = new T;
    *temp = _array[a];
    _array[a] = _array[b];
    _array[b] = *temp;
    delete temp;
}

// COMPARISON

template <typename T>
bool operator==(Iterator<T>& lhs, Iterator<T>& rhs) { return *lhs == *rhs; }

template <typename T>
bool operator!=(Iterator<T>& lhs, Iterator<T>& rhs) { return !(lhs == rhs); }

// PRIVATE MEMBERS

template <typename T>
size_t Vector<T>::_calc_capacity(size_t size)
{
    size_t temp = _base;
    while (temp < size)
        temp *= 2;

    return temp;
}

template <typename T>
void Vector<T>::_reallocate(size_t cap)
{
    cap = _calc_capacity(cap);

    T* temp = new T[_capacity = cap];
    for (size_t i = 0; i < _size; i++)
        temp[i] = _array[i];

    delete[] _array;
    _array = temp;
}

template <typename T>
void Vector<T>::_manage_capacity()
{
    assert(_capacity >= _size);
    if (_capacity == _size)
        _reallocate(_capacity * 2);
}

template <typename T>
void Vector<T>::_check(const size_t pos) const
{
    assert(_size != 0 && pos >= 0 && pos < _size);
}

// OTHER

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& v)
{
    os << "[ ";

    for (size_t i = 0; i < v._size; i++)
    {
        os << v._array[i] << " ";
    }

    os << "]";
    return os;
}
