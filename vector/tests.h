#pragma once

#include <typeinfo>
#include <vld.h>
#include "vector.h"

template <typename T>
class Vector;

struct myCustomType;

template <typename T> void display(const Vector<T>& vect) { std::cout << "\n   current " << vect << " " << vect.size() << "/" << vect.capacity() << "\n"; }
void spacer() { std::cout << "\n   "; }

// for testing various types... 
template <typename T>T value(T type) { return type; }

template <> int value<int>(int i) { return 0; }
template <> double value(double i) { return 0.00; }
template <> long value(long i) { return 1000; }

template <> char value(char i) { return 'a'; }

// test modifier (T must support operator++)
template <typename T>
void testModifiers(Vector<T>& vect) 
{
    std::cout << "\n\nMODIFIERS: " << typeid(T).name();

    vect.clear();
    display(vect);

    T test{};
    test = value(test);

    spacer();
    for (size_t i = 0; i < 5; i++)
    {
        vect.push_back(test);
        std::cout << "push_back(" << test << ") ";
        test++;
    }

    spacer();
    for (size_t i = 0; i < 2; i++)
    {
        std::cout << "emplace_back() ";
        vect.emplace_back();
    }

    display(vect);

    spacer();
    for (size_t i = 0; i < 2; i++)
    {
        std::cout << "pop_back() ";
        vect.pop_back();
    }

    display(vect);

    std::cout << "\n   insert(3, " << test << ")";
    vect.insert(3, test);

    display(vect);

    std::cout << "\n   erase(3) " << vect.at(3);
    vect.erase(3);

    display(vect);

    std::cout << "\n   erase(1, 3) " << vect.at(1) << " " << vect.at(2) << " " << vect.at(3);
    vect.erase(1, 3);

    display(vect);

    std::cout << "\n   swap(0, 1) " << vect.at(0) << " " << vect.at(1);
    vect.swap(0, 1);

    display(vect);

    std::cout << "\n   assign(5, " << value(test) << ")";
    vect.assign(5, value(test));

    display(vect);


    std::cout << "\n   clear()";
    vect.clear();

    display(vect);

    test = value(test);
    spacer();
    for (size_t i = 0; i < 5; i++)
    {
        vect.push_back(test);
        std::cout << "push_back(" << test << ") ";
        test++;
    }

    display(vect);
}

// test capacity
template <typename T>
void testCapacity(Vector<T>& vect)   
{
    std::cout << "\n\nCAPACITY: " << typeid(T).name();
    size_t temp;

    vect.clear();
   
    for (size_t i = 0; i < 5; i++)
        vect.push_back(T());

    display(vect);

    std::cout << "\n   push_back() " << vect.capacity() * 4 <<  " times (4x capacity)";

    temp = vect.capacity() * 4;
    for (size_t i = 0; i < temp; i++) // increase cap
        vect.push_back(T());
        
    display(vect);

    temp = (vect.size()) - (vect.size() / 3);
    std::cout << "\n   pop_back() all but 1/3 elements";
    for (size_t i = 0; i < temp; i++) // reduce size
        vect.pop_back();

    display(vect);

    std::cout << "\n   shrink_to_fit()";
    vect.shrink_to_fit();

    display(vect);
}

// test access
template <typename T>
void testAccess(Vector<T>& vect)  // nothing should not be allowed on empty vector
{
    std::cout << "\n\nACCESS: " << typeid(T).name();

    display(vect);

    if (vect.empty()) { std::cout << "\n   Vector is empty, nothing to access!! (attempting anyway)"; }

    std::cout << "\n   operator << "; std::cout << vect;

    std::cout << "\n   front() "; std::cout << vect.front();
    std::cout << "\n   back() "; std::cout << vect.back();

    for (size_t i = 0; i < 1; i++)
        std::cout << "\n   at(" << i << ") " << vect.at(i);
        
    for (size_t i = 0; i < 1; i++)
        std::cout << "\n   [" << i << "] " << vect.at(i);

    if ((vect.data()) != nullptr)
        std::cout << "\n   data() " << vect.data();
    else    
    std::cout << "\n   data() nullptr";

    std::cout << "\n   at(size) "; std::cout << vect.at(vect.size());
    std::cout << "\n   at(size + 1) "; std::cout << vect.at(vect.size() + 1);
    std::cout << "\n   at(1000) "; std::cout << vect.at(1000);

    std::cout << "\n   begin() "; std::cout << *vect.begin();
    std::cout << "\n   end() "; std::cout << *vect.end(); 

    //it<T> it = vect.begin(); // why can't i do this here? 
    //std::cout << "\n   it: "; std::cout << *it; it++;
    //std::cout << "\n   it++: "; std::cout << *it; it++;
    //std::cout << "\n   it++: "; std::cout << *it; it++;
    //std::cout << "\n   it++: "; std::cout << *it; it++;
    //std::cout << "\n   it++: "; std::cout << *it; it++;
    //std::cout << "\n   it++: "; std::cout << *it; it++;

    //display(vect);
}
