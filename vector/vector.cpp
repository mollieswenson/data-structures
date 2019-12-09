#include "pch.h"
#include <iostream>
#include <array>         // do i even need this? 
#include <cassert> 
#include <vector>
#include <vld.h>
#include <typeinfo> 

#include "tests.h"

struct myCustomType  // test data type that allocates its own memory 
{
    int* num = nullptr;
    int cnt{3};

    myCustomType() { num = new int[cnt] {}; std::cout << "\n   myCustomType constructor " << num; }
    myCustomType(int n) { cnt = n; myCustomType(); std::cout << "\n   myCustomType(n) constructor " << num; } // how to create Vector of a type with args (use this constructor)? 
    ~myCustomType() { std::cout << "\n   myCustomType destructor " << num; delete[] num; }
    friend std::ostream& operator<<(std::ostream& os, const myCustomType& t);
};

std::ostream& operator<<(std::ostream& os, const myCustomType& t) // ostream for myCustomType
{
    for (size_t i = 0; i < t.cnt ; i++)
        os << t.num[i] << " ";

    return os;
}

// implement the std::vector-like class with dynamic array: https://en.cppreference.com/w/cpp/container/vector
// did not include allocators.. i don't understand why they are part of the class if the purpose of the container is to manage memory for you
//  i tried to use size_t in place of int everywhere, but kept getting illegal indirection when dereferencing and not engough info to debug

template <typename T> class Vector
{
private:
    T* array;
    size_t next_empty{ 0 };
    size_t base{ 8 };
    size_t array_cap{ base };   // right place to initialize these? initializer list? 

    size_t calc_cap(int sz)
    {
        int temp = base;
        while (temp < sz)
            temp *= 2;       // base(2) rate of growth. should it be base^2?

        return temp;
    }

    void reallocate(int cap)
    {
        cap = calc_cap(cap);

        T* temp = new T[array_cap = cap];
        for (size_t i = 0; i < next_empty; i++)
            temp[i] = array[i];

        delete[] array;
        array = temp;
        std::cout << "\n   reallocated to array_capacity " << array_cap;
    }

    void manage_capacity()
    {
        assert(array_cap >= next_empty);
        if (array_cap == next_empty)       
            reallocate(array_cap * 2);
    }

    bool verify_exists(const int index) const // returns true if index exists 
    {
        if (-1 < index < next_empty)
            return true;

        try { array[index]; throw std::out_of_range("Exception: That index doesnt exist");}
        catch (std::out_of_range& e) { std::cout << e.what(); }
    }

public:

    /////////////////////////////////////////////////////////////////////////// MEMBERS

    Vector() // defualt constructor
    {
        std::cout << "\n\n============\nVector<" << typeid(T).name() << "> default constructor...\n";
        array = new T[array_cap]{};
    }

    Vector(int size, T val) // fill constructor 
    {
        std::cout << "\n\n============\nVector<" << typeid(T).name() << "> fill constructor...\n";
        array_cap = calc_cap(size);
        array = new T[array_cap]{};

        for (size_t i = 0; i < size; i++)
            push_back(val);
    }

    template<typename it> // range constructor
    Vector<T>(it first, it last)
    {
        std::cout << "\n\n============\nVector<" << typeid(T).name() << "> range constructor...\n";

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

    Vector(const Vector &v) // copy constructor that takes another vector 
    {
        std::cout << "\n\n============\nVector<" << typeid(T).name() << ">  copy constructor...\n";

        array_cap = calc_cap(v.next_empty);
        array = new T[array_cap]{};

        for (size_t i = 0; i < v.size(); i++)
            push_back(v.at(i));
    }

    ~Vector() 
    {
        std::cout << "\nVector <" << typeid(T).name() << ">  destructor"; 
        delete[] array; // each element gets destroyed by its own destructor, right?
    }

    Vector& operator=(Vector& rhs) // assignment operator
    {
        if (this == &rhs)
            return *this;
        return rhs; 
    }

    void assign(const int count, const T& value) // replaces elements in the Vector with value
    {
        clear();
        if(array_cap < count) { reallocate(calc_cap(count)); }
            
        for (size_t i = 0; i < count; i++)
            push_back(value);
    }


    /////////////////////////////////////////////////////////////////////////// ELEMENT ACCESS
    

    T& at(const size_t index) const  // access specified element
    { 
        if (verify_exists(index))
            return array[index];

        T empty{};
        return empty; // why can't i return T{}? 
    } 

    T& operator[](size_t index) { return at(index); } // access specified element  

    template <typename T> friend std::ostream& operator<<(std::ostream& os, const Vector<T>& v); // ostream operator

    T& front() const
    { 
        if (verify_exists(0))
            return array[0];

        T empty{};
        return empty;

    } // access the first element
    T& back() const
    { 
        if (verify_exists(next_empty - 1))
            return array[next_empty - 1];

        T empty{};
        return empty;
    } // access the last element
  
    T* data() const { return array; } // direct access to the underlying array 


    /////////////////////////////////////////////////////////////////////////// ITERATORS 

    // i don't know how these work

    /////////////////////////////////////////////////////////////////////////// CAPACITY  (excluded std::max_size and reserve)

    const bool empty() const { return (next_empty == 0); } // returns true if empty
    size_t size() const { return next_empty; } // returns current number of elements
    size_t capacity() const { return array_cap; } // returns max elements before resize

    void shrink_to_fit()  // reduce capacity to fit size
    {
        if (calc_cap(next_empty) < array_cap)
            reallocate(calc_cap(next_empty));
    }

    /////////////////////////////////////////////////////////////////////////// MODIFIERS
    
    void clear() // clears the contents
    {
        while (next_empty)
            pop_back();
    }

    void insert(const size_t pos, const T val) // inserts val before pos
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

    template<typename it> 
    void insert(it first, it last, const Vector<T> coll) // inserts a range of elements at a position 
    {
        return;
    }

    template<typename it, typename args>  // construct an element in a specified position
    void emplace(it pos, args&&)
    {
        return;
    }

    void erase(const size_t first, const size_t last)   // erases range of specified elements  -- something's broken in hhere
    {
        if (verify_exists(last) && verify_exists(first)) 
        {
            for (size_t i = first; i < last; i++)
            {
                erase(i);
            }
        }
    }

    void erase(const size_t pos)   // erases a specified element
    {
        if (verify_exists(pos))
        {
            for (size_t i = pos; i < size(); i++)
                array[i] = array[i + 1];

            next_empty--;
        }
    }

    void push_back(const T m) // adds element at end
    {
        manage_capacity();
        array[next_empty] = m;
        next_empty++;
    }

    void emplace_back() // construct element in place
    {
        manage_capacity();
        array[next_empty] = T{};
        next_empty++;
    }

    void pop_back() // remove last elelement
    {
        if (next_empty)
        {
            array[next_empty - 1] = T{};
            next_empty--;
        }
    }

    void swap(size_t a, size_t b) // swaps elements a and b
    {
        if (verify_exists(a) && verify_exists(b))
        {
            T temp = array[a];
            array[a] = array[b];
            array[b] = temp;
        }
    }

    void swap(Vector& other) // swaps elements of this Vector with elements of other Vector 
    {
        return;
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& v)
{
    // how to handle this when we have some type that doesn't work here?
    os << "[ ";

    for (size_t i = 0; i < v.next_empty; i++)
    {
            os << v.array[i] << " ";
    }
        
    os << "]";
    return os;
}

int main()
{
    ////////////////////////// default constuctor
    Vector<char> myVec;

    testAccess(myVec); // empty list tests
    testModifiers(myVec);
    testAccess(myVec);
    testCapacity(myVec);

    //////////////////////////// fill constructor 

    Vector<int> mySizeValVec(4, 10);
    std::cout << mySizeValVec << std::endl;

    testModifiers(mySizeValVec);
    testAccess(mySizeValVec);
    testCapacity(mySizeValVec);

    //////////////////////////// range constructor, same type
    std::vector<size_t> sameTypeVector{ 1,2,3 };
    Vector<size_t> mySameTypeIttVec(sameTypeVector.begin(), sameTypeVector.end());
    std::cout << mySameTypeIttVec << std::endl;

    testModifiers(mySameTypeIttVec);
    testAccess(mySameTypeIttVec);
    testCapacity(mySameTypeIttVec);

    //////////////////////////// range constructor, different type
    std::vector<int> diffTypeVector{ 1,2,3 };
    Vector<double> myDiffTypeIttVec(diffTypeVector.begin(), diffTypeVector.end());
    std::cout << myDiffTypeIttVec << std::endl;

    testModifiers(myDiffTypeIttVec);
    testAccess(myDiffTypeIttVec);
    testCapacity(myDiffTypeIttVec);

    ////////////////////////// copy constructor
    Vector<char> myCopyVec(myVec);
    std::cout << myCopyVec << std::endl;

    testModifiers(myCopyVec);
    testAccess(myCopyVec);
    testCapacity(myCopyVec);

    ////////////////////////// Assignment Operator
    Vector<char> myAssgnVec;
    std::cout << "\n   assignment operator" << std::endl;
    myAssgnVec = myCopyVec;

    testModifiers(myAssgnVec);
    testAccess(myAssgnVec);
    testCapacity(myAssgnVec);
    
        ////////////////////////// annoying types
    Vector<std::string> myStrVec;

    testModifiers(myAssgnVec);
    testAccess(myAssgnVec);
    testCapacity(myAssgnVec);

    ////////////////////////// vector of custom data type that also allocates memory 
    Vector<myCustomType> customTypeVec;

    myCustomType a{};
    a.num[0] = 22;

    // tests don't support types without increment operator
    
    // customTypeVec.push_back(a); // why is the type deleted too early?
    
    return 0;
}