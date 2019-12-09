#pragma once
#include <typeinfo>

template <typename T> class Vector;
struct myCustomType;

template <typename T> void display(Vector<T>& vect) { std::cout << "\n   current " << vect << " " << vect.size() << "/" << vect.capacity() << "\n"; }
void spacer() { std::cout << "\n   "; }

template <typename T>
T value(T type)
{
    if (typeid(T) == typeid(char)) { return 'a'; }
    if (typeid(T) == typeid(int) || typeid(T) == typeid(size_t)) { return 0; }
    if (typeid(T) == typeid(double)) { return 1.1; }       // is there a way to find out if any type has a ++ and << operators? 

    return type;
}



template <typename T>
void testModifiers(Vector<T>& vect) // test modifier; elem type must support operator++
{
    std::cout << "\n\nMODIFIERS";

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

template <typename T>
void testCapacity(Vector<T>& vect)   // test capacity; elem must support operator++
{
    std::cout << "\n\nCAPACITY";
    T test{};
    test = value(test);
    size_t temp;

    vect.clear();
   
    for (size_t i = 0; i < 5; i++)
    {
        vect.push_back(test);
        test++;
    }

    display(vect);

    std::cout << "\n   push_back() " << vect.capacity() * 4 <<  " times (4x capacity)";

    temp = vect.capacity() * 4;
    for (size_t i = 0; i < temp; i++) // increase cap
    {
        vect.push_back(test);
        test++;
    }
        
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

template <typename T>
void testAccess(T& vect) // test access; must handle exceptions 
{
    std::cout << "\n\nACCESS";
    size_t tests{2};

    display(vect);

    if (vect.empty()) { std::cout << "\n   Vector is empty, nothing to access!! (attempting anyway)"; }

    std::cout << "\n   operator << "; std::cout << vect;

    std::cout << "\n   front() "; std::cout << vect.front();
    std::cout << "\n   back() "; std::cout << vect.back();

    for (size_t i = 0; i < tests; i++)
    {
        std::cout << "\n   at(" << i << ") "; std::cout << vect.at(i);
    }
        
    for (size_t i = 0; i < tests; i++)
    {
        std::cout << "\n   [" << i << "] ";  std::cout << vect[i];
    }
        
    std::cout << "\n   data() " << vect.data();

    std::cout << "\n   at(size) "; std::cout << vect.at(vect.size());
    std::cout << "\n   at(size + 1) "; std::cout << vect.at(vect.size() + 1);
    std::cout << "\n   at(1000) "; std::cout << vect.at(1000);

    display(vect);
}


template <typename T>
void testMemberVals(const Vector<T>& vect)   // print member vals
{
    std::cout << "\n\nMEMBERS";
    std::cout << "\n   empty() = " << vect.empty();
    std::cout << "\n   size() = " << vect.size();
    std::cout << "\n   capacity() = " << vect.capacity();

    std::cout << "\n   result " << vect;
}