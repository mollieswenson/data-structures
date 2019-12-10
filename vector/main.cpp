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

    Vector<double> ddef; // default
    Vector<double> dfil(4, 1.0); // fill
    Vector<double> dcop(dfil); // copy
    Vector<double> dran(dcop.begin(), dcop.end()); // range
    
    Vector<char> cdef; // default
    Vector<char> cfil(4, 'x'); // fill
    Vector<char> ccop(cfil); // copy
    Vector<char> cran(ccop.begin(), ccop.end()); // range

    std::vector<int> diffTypeVector{ 99,88,77 };
    Vector<double> myDiffTypeIttVec(diffTypeVector.begin(), diffTypeVector.end());

    const char* str1 = "Hello";

    Vector<char[5]> cvdef; // default
    //Vector<char[5]> cvfil(4, str1); // fill
    //Vector<char[5]> cvcop(cvfil); // copy
    //Vector<char[5]> cvran(cvcop.begin(), cvcop.end()); // range

   // cvdef.push_back(str1);

    Vector<std::string> sdef; // default
    //Vector<std::string> sfil(4, str1); // fill
    //Vector<std::string> scop(sfil); // copy
    //Vector<char> cran(ccop.begin(), ccop.end()); // range

    sdef.push_back(str1);

    Vector<char> myChVec; 

    testAccess(myChVec); // empty list tests
    testModifiers(myChVec);
    testAccess(myChVec);
    testCapacity(myChVec);

    Vector<int> myIntVec;

    testAccess(myIntVec); // empty list tests
    testModifiers(myIntVec);
    testAccess(myIntVec);
    testCapacity(myIntVec);

    Vector<myCustomType> myCustomVec;

    //testAccess(myCustomVec); // empty list tests
    //testModifiers(myCustomVec);
    //testAccess(myCustomVec);
    //testCapacity(myCustomVec);
    
    //myCustomVec.emplace_back();

     //myCustomType a{};
     //a.num[0] = 22;

     // tests don't support types without increment operator

     // customTypeVec.push_back(a); // why is the type deleted too early?

    return 0;
}