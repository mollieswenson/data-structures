#pragma once

#include <vld.h>
#include "vector.h"

struct myCustomType  // user-defined data type
{
    char letter;
    int number;

    myCustomType() { }
    myCustomType(char c, int n) { letter = c; number = n; }
    ~myCustomType() {  }
};

int test_vector() // run all vector tests
{
    Vector<int> vector; // default constructor

    assert(vector.size() == 0); // size 0 (empty)

    int ValT = 100;
    for (size_t i = 0; i < 5; i++, ValT += 100) // add some elems
        vector.push_back(ValT);

    assert(vector.size() == 5); // size 5

    assert(vector.data() != nullptr); // the vector data is not a nullptr

    assert(vector.front() == 100); // access expected values
    assert(vector.back() == 500);

    ValT = 100;
    for (size_t i = 0; i < 5; i++, ValT += 100) // access expected values
        assert(vector.at(i) == ValT && vector.at(i) == vector[i]);

    vector.emplace_back(); // construct in place at end
    vector.emplace_back();

    assert(vector.at(5) == 0); // emplace_back elements init to zero
    assert(vector.at(6) == 0);

    vector.at(5) = 600;
    vector.at(6) = 700;

    assert(vector.at(5) == 600); // access expected values
    assert(vector.at(6) == 700);

    vector.swap(1, 6); // swap elem 1 and 6

    assert(vector.at(1) == 700); // access expected values
    assert(vector.at(6) == 200);

    vector.erase(1); // erase some elements by index
    vector.erase(0);

    vector.pop_back(); // pop some elements off back
    vector.pop_back();

    ValT = 300;
    for (size_t i = 0; i < 3; i++, ValT += 100) // access expected values 
        assert(vector[i] == ValT);

    assert(vector.capacity() == 8); // capacity 8
    assert(vector.size() == 3); // size 3

    vector.insert(0, 0);
    vector.insert(1, 100);
    vector.insert(2, 200);

    ValT = 0;
    for (size_t i = 0; i < 5; i++, ValT += 100) // access expected values via []
        assert(vector[i] == ValT);
   
    assert(vector.capacity() == 8); // capacity 8
    assert(vector.size() == 6); // size 6
     
    vector.push_back(600); // add some elements (expect capacity resize)
    vector.push_back(700);
    vector.push_back(800);
    vector.push_back(900);

    assert(vector.capacity() == 16); // capacity 16
    assert(vector.size() == 10); // size 10

    ValT = 1000;
    for (size_t i = 0; i < 990; i++, ValT+= 100) // increase to 1000 elemes
        vector.push_back(ValT);

    assert(vector.capacity() == 1024); // capacity 1024
    assert(vector.size() == 1000); // size 1000

    vector.erase(0, 499); // range erase first half of elems

    vector.erase(400, 499); // range erase 100 elems from the end

    ValT = 50000;
    for (size_t i = 0; i < 400; i++, ValT += 100) // access expected values
        assert(vector.at(i) == ValT);

    vector.shrink_to_fit(); // shrink to fit 400 elems

    assert(vector.capacity() == 512); // capacity 512
    assert(vector.size() == 400); // size 400

    Iterator<int> iterator = vector.begin(); ValT = 50000;
    for (size_t i = 0; i < 400; i++, ValT += 100, iterator++) // access expected values via iterator 
        assert(vector.at(i) == *iterator);

    Iterator<int> iterator_end = vector.end(); // end iterator is out of bounds (will assert if you try to access it)

    //Iterator<int> iterator_end = vector.end(); // iterator at end
    //
    //assert(vector.at(399) == *iterator_end); // access expected values via iterator 
        
    vector.assign(1000, 888); // assign 1000 elements with ValT 888

    for (size_t i = 0; i < 1000; i++) // access expected values
        assert(vector.at(i) == 888);

    vector.clear(); // clear elements

    assert(vector.size() == 0); // size 0

    for (size_t i = 0; i < 200; i++) // repop vector
        vector.push_back((int)i);

    Vector<int> copy_vector(vector); // copy constructor -----------

    assert(copy_vector.size() == 200);  // size 200
    assert(copy_vector.capacity() == 256);  // capacity 256

    for (size_t i = 0; i < 200; i++) // access expected values, verify copies
        assert(copy_vector.at(i) == vector.at(i));

    Iterator<int> range_iterator_begin = vector.begin(); // iterator at begin

    Iterator<int> range_iterator_end = vector.begin(); // set up iterator at end
    for (size_t i = 0; i < 25; i++) 
        range_iterator_end++;
    
    // RANGE CONSTRUCTOR BROKEN 
    // 
    //Vector<int> range_vector(range_iterator_begin, range_iterator_end);  // range constructor via iterators (index 0 - 24) -----------
    //
    //assert(range_vector.size() == 25);  // size 25
    //assert(range_vector.capacity() == 32);  // capacity 32

    //for (size_t i = 0; i < 25; i++) // access expected values, verify copies
    //    assert(range_vector.at(i) == vector.at(i));
    
    Vector<int> fill_vector(100, 4); // fill constructor (100 elements with ValT 4) -----------

    assert(fill_vector.size() == 100);  // size 4
    assert(fill_vector.capacity() == 128);  // capacity

    for (size_t i = 0; i < 100; i++) // access expected values
        assert(fill_vector.at(i) == 4);

    Vector<int> assign_vector = vector; //assignment operator 

    for (size_t i = 0; i < 200; i++) // access expected values, verify copies
        assert(assign_vector.at(i) == vector.at(i));

    Vector<myCustomType> custom_vector; // custom type

    char c = 'a'; int n = 100;
    for (size_t i = 0; i < 30; i++, c++, n += 100)
        custom_vector.push_back(myCustomType(c, n));

    c = 'a'; n = 100;
    for (size_t i = 0; i < 30; i++, c++, n += 100)
        assert((custom_vector.at(i)).letter == c);

    return 0;
}


