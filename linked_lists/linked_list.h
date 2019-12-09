#pragma once
#include <vld.h>

struct Data
{
public:
    int val1;
    int val2;
};

struct Node
{
    Node()   
    {
        data = {};
        next = nullptr;
    }

    ~Node() 
    { 
        std::cout << "  \n(destroy node " << this << " data.val1 " << data.val1 << ")";
        // is something supposed to be in here to free this memory?
    }

    Data data{ };
    Node* next{ nullptr };
};

class LinkedList
{
private:
    Node* head;
    Node* tail;
    int length;
public:
    LinkedList();
    ~LinkedList();

    int GetLength() const; // returns current length of the list

    Node* GetHead() const;// returns pointer to first node
    Node* GetTail() const; // returns pointer to last node

    bool InList(Node*) const; // returns true if n is in the list

    Node* SetHead(Node* n);  // Sets head to n and returns pointer to new head
    Node* SetTail(Node* n);  // Sets tail to n and returns pointer to new tail

    Node* GetNode(int) const; // Returns node at index i
    Node* GetNode(Data*) const; // Returns node with data pointer d
    
    Node* const AddNodeFront(const Data = {}); // Adds a new node to the front of the list and returns pointer to the new node
    Node* const AddNodeBack(const Data& = {});  // Adds a new node to the back of the list, with data d if provided, and returns pointer to the new node

    Node* InsertNodeAfter(Node* n, const Data& = {}); // Adds a new node after n and returns pointer to the new node 

    bool Delete(Node*); // Deletes n from the list. Returns true on success 
    bool Delete(int); // Deletes node at index i from the list, Returns true on success
  
    void Join(LinkedList&); // copies all nodes from list l and adds them to this the end of this list
  
    void Clear(); // Removes all nodes from the list
   
    void Print() const; // Prints the list 

    void GenerateTestList(int = 100, int = 10); // Clears out any current nodes and generates a test list

    void TestHeadTail(); // Verifies head and tale are the first and last items in the list, or both nullptr
   
};