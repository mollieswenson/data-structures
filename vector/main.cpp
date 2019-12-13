#pragma once

#include <vector>

#include <vld.h>

#include "vector.h"

int post(int i) { return i++; }
int pre(int i) { return ++i; }

int main()
{
    // try constructors on different types.. 
    
    Vector<int> idef; // default
    Vector<int> ifil(7, 12); // fill
    Vector<int> icop(ifil); // copy
    Vector<int> iran(icop.begin(), icop.end()); // range 

    std::vector<int> diffTypeVector{ 99,88,77 };
    Vector<double> myDiffTypeIttVec(diffTypeVector.begin(), diffTypeVector.end()); // range, diff type

    Vector<double> ddef; // default
    Vector<double> dfil(4, 1.0); // fill
    Vector<double> dcop(dfil); // copy
    Vector<double> dran(dcop.begin(), dcop.end()); // range
    
    Vector<char> cdef; // default
    Vector<char> cfil(4, 'x'); // fill
    Vector<char> ccop(cfil); // copy
    Vector<char> cran(ccop.begin(), ccop.end()); // range

    // run tests on vector of char

    Vector<char> myChVec; 

    testAccess(myChVec); // empty list
    testModifiers(myChVec);
    testAccess(myChVec);
    testCapacity(myChVec);

    // run tests on vector of int

    Vector<int> myIntVec; 

    testAccess(myIntVec); // empty list
    testModifiers(myIntVec);
    testAccess(myIntVec);
    testCapacity(myIntVec);

    // tests on vector of myCustomType 
    Vector<myCustomType> myCustomVec;

    testAccess(myCustomVec); // empty list
    testCapacity(myCustomVec);
    myCustomVec.clear();
    
    std::cout << "\n\nMODIFIERS: myCustomType\n";

    for (int i = 0; i < 3; i++)
    {
        myCustomVec.push_back(myCustomType(i));
        std::cout << "\n   push_back(myCustomType(" << i<< ")";
    }

    std::cout << "\n   " << myCustomVec << std::endl;

    for (int i = 0; i < 2; i++)
    {
        myCustomVec.emplace_back();
        std::cout << "\n   emplace_back()";
    }

    std::cout << "\n   " << myCustomVec << std::endl;

    myCustomVec.insert(3,myCustomType(12));
    std::cout << "\n   insert(3, myCustomType())";

    std::cout << "\n   " << myCustomVec << std::endl;

    myCustomVec.erase(3);
    std::cout << "\n   erase(3)";

    std::cout << "\n   " << myCustomVec << std::endl;

    myCustomVec.swap(1,3);
    std::cout << "\n   swap(1,3)";

    std::cout << "\n   " << myCustomVec << std::endl;

    myCustomVec.clear();
    std::cout << "\n   clear()";

    for (int i = 0; i < 5; i++)
    {
        myCustomVec.push_back(myCustomType(i));
        std::cout << "\n   push_back(myCustomType(" << i << ")";
    }

    testAccess(myCustomVec);

    myChVec.clear();
    char c = 'a';
    for (int i = 0; i < 5; i++)
    {
        myChVec.push_back(c);
        c++;
    }

    // iterator tests -- why can't I declare an iterator in the test functions? 

    it<char> it = myChVec.begin();
    std::cout << "\n   it<char>: "; std::cout << *it; it++;
    std::cout << "\n   it++: "; std::cout << *it; it++;
    std::cout << "\n   it++: "; std::cout << *it; it++;
    std::cout << "\n   it++: "; std::cout << *it; it++;
    std::cout << "\n   it++: "; std::cout << *it; it++;
    std::cout << "\n   it++: "; std::cout << *it; it++;

    std::cout << "\n\n\n";
    return 0;
}