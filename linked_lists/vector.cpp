#pragma once
#include "pch.h"
#include<iostream>
#include "linked_list.h"
#include <assert.h>
#include <vld.h>


/*!

C++ Vector Class

What do I need to do to implement this ?

The data type to go into the vector
A pointer to the first element in the vector
The number of elements currently in the vector
The maximum number of elements that can fit into the vector

So we are using an array to create a vector.Why not just use an array ?

An array you need to know the size of ahead of time, a vector handles resizing for you.So I think that is the main feature we’re after here.

The vector *is* an array.We have to tell it what size it is.If it needs to get bigger, we need to arrange a new vector of the appropriate size, move it, and delete the old vector.

Are we moving anything ? Do we need to reallocate storage for each element and move them or can we just change the pointer to the new head ?

I think that we do have to move everything, because vectors are by nature stored contiguously in memory, so we need to find a bigger chunk of memory if we have more than will fit in the current spot.

Now what is the purpose of doubling the allocated size when we run out of space ? Why not just one more when we need to ? Doesn’t that have the potential to reserve WAY more space than we need if we’ve doubled a few times ?

Also why start with 8 ? Or is that what Taylor said ? Start with 8 ? Multiples of 8 ? No I think it was start with 8 spaces.Why ?

How to communicate to user that we have moved the vector ? Maybe we should always just have a variable that is const that will always tell them where to find it ? I don’t think they need to know.They just call functions on the vector object and that’s all handled internally.The user shouldn’t need to care where the data is in memory, just that vector.DoStuff() is available.

Is the vector an array of elements, or an array of pointers to elements ?

!*/


class VectorData
{
public:
    VectorData() {};
    VectorData(int) {};
    ~VectorData() {};
    //int value{ 0 };
    //void print() { std::cout << this << " " << value << std::endl; }

};



class Vector
{
private:           // why cant reallocate/checksize be private?  
    int *vector;  // points to first elem

    int size;      // number of elements currently in the vector
    int max;       // maximum number of elements the vector can hold
              
public:
    Vector()
    {
        vector = new int[8];
        size = 0;
        max = 8;
    };
    ~Vector() {}; // cleanup here

    //Data *reallocate() //move to a new place
    //{
    //    Data *temp = new Data[max * 2];
    //    temp = vector; // does this carry over the size and max? 
    //    delete(vector);
    //    max = max * 2;    // max *=2;
    //    assert(max > size);
    //    return &temp[0];   // this should return pointer to the first elem in the array at the new location
    //}

    //void CheckSize(int new_size = -1)  // check size against max, realloc if necessary, and return pointer to vector  
    //{
    //    if (new_size == -1)  // why can't i make parameter default value be size? 
    //        new_size = size;

    //    if (new_size < max)
    //        return;                    // we don’t need any more space 

    //    while (max < new_size)  // get max to correct size if adding a long list ... but if we are inserting a colletion, maybe would make more sense to put everything in in order? 
    //        max = max * 2;

    //    Data* temp = new Data[max];
    //    temp = vector; // does this carry over the size and max? 
    //    delete(vector);

    //    assert(max > size);
    //}


    //int Size() const { return size; } // return the size
    //const int Max() const { return max; } // return max size

    void Push(int data)   // add element to back
    {
        //CheckSize();

        vector[size] = data; // not enough space here? 
        size++;
    }

    //void Insert(Data data, int index) // inster at index
    //{
    //    if (index > size)
    //        return;            // index isn’t in the array

    //    CheckSize();
    //    int loc = size++;
    //    while (loc != index)
    //    {
    //        vector[loc] = vector[loc - 1];
    //        loc--;
    //    }

    //    vector[index] = data;
    //}

    //void Insert(Vector* collection, int index)   //insert a collectio after an index
    //{
    //    if (index > size)
    //        return;

    //    int oldLoc = size;  // set this before changing size.. 
    //    size = size + collection->Size();
    //    CheckSize();     // not ideal bc we just moved stuff around and now we’re going to move it again
    //    int newLoc = size + 1;
    //    while (oldLoc != index)
    //    {
    //        vector[newLoc] = vector[oldLoc];
    //        oldLoc--;
    //        newLoc--;
    //    }

    //    for (int i = 0; i == collection->Size(); i++)
    //    {
    //        //vector[oldLoc] = collection[i];
    //        std::cout << &vector[oldLoc];
    //        std::cout << &collection[i];
    //            
    //        collection[i];
    //        oldLoc++; // can this be in the for loop ?
    //    }
    //}


    //void replace(Data data, int index)  // replace the data at index with data
    //{
    //    if (index > size)     // make this a helper function? 
    //        return;
    //    vector[index] = data;
    //}

    //void Pop() // delete last element
    //{
    //    if (index > size)     // make this a helper function? 
    //        return;

    //    delete vector[size];
    //    size--;
    //}
    



    //Data Get(int index) const  //get element at specified index, or last
    //{
    //    if (index > size)
    //        return;

    //    return vector[index];
    //}

    //void Remove(int index) {} //removes the element at index

    //void Clear() {} //delete contents of vector

    //void Delete() {} //delete entire vector 

    //static void Join(Data* vector1, Data* vector2) {} // join two vectors
    //


};
//
//Vector::Vector()
//    : vector(nullptr), size(0), max(8) { }
//
//
//
//

struct stuff
{
    int val;
    bool isThing; // why isn't this getting into the vector class? 

    stuff()
    {
        std::cout << "stuff constructor";
        val = 0;
        isThing = true;
    }
    ~stuff()
    {
        std::cout << "stuff destructor";
    }
};

class VectorClass
{
    stuff *arr; // is this vector only for use with this data type? 

    // capacity is the total storage 
    // capacity of the vector 
    int capacity;

    // current is the number of elements 
    // currently present in the vector 
    int current;

public:
    // Default constructor to initialise 
    // an initial capacity of 1 element and 
    // allocating storage using dynamic allocation 
    VectorClass()
    {
        arr = new stuff[8];
        capacity = 8;
        current = 0;
    }

    void push(stuff data)
    {
        arr[current] = data;
    }

    void pushX(stuff data)
    {

        // if the number of elements is equal to the capacity, 
        // that means we don't have space 
        // to accommodate more elements. 
        // We need to double the capacity 
        if (current == capacity) {
            stuff* temp = new stuff[2 * capacity];

            // copying old array elements to new array 
            for (int i = 0; i < capacity; i++) {
                temp[i] = arr[i];
            }

            // deleting previous array 
            delete[] arr;
            capacity *= 2;
            arr = temp;
        }

        // Inserting data 
        arr[current] = data;
        current++;
    }
};

    int main()
    {

        VectorClass<stuff> t; // do i need to figure out templates to do this? 

        //VectorClass v[3]; // i think this is an array of vectorClass objects.. 

        // need t

        stuff stuff;
        stuff.val = 10;

        //v->push(stuff);

        std::cout << "\n\n\n";

        //std::cout << *v.arr[0]->isThing << std::endl; 


        VectorData w[3]; // this is an array of data objects.. how do i associate it with VectorClass functions?


        //std::cout << v[1] << std::endl;
        //std::cout << v[2] << std::endl;

        
        // does the data the vector will hold have to go into the vector class? 



        //int *ptr; 
        //ptr = new int[8];

        //ptr[0] = 0;
        //ptr[1] = 1;
        //ptr[2] = 2;
        //ptr[3] = 3;
        //
        //std::cout << ptr[0] << std::endl;
        //std::cout << ptr[1] << std::endl;
        //std::cout << ptr[2] << std::endl;
        //std::cout << ptr[3] << std::endl;

        //std::cout << &ptr[0] << std::endl;
        //std::cout << &ptr[1] << std::endl;
        //std::cout << &ptr[2] << std::endl;
        //std::cout << &ptr[3] << std::endl;

        //std::cout << &ptr << std::endl;
        //std::cout << *ptr << std::endl;
        //std::cout << ptr << std::endl;


        //delete(ptr);
    }

