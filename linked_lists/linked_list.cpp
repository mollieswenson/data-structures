#include "pch.h"
#include<iostream>
#include "linked_list.h"

struct Data
{
public:
    int val1;
    int val2;
};


struct Node
{
    ~Node() 
    {
        std::cout << "  \n(destroy node " << this << " data.val1 " << data.val1 << ")"; 
        // is there a way to refer to the LinkedList obj to which this belongs? (want to check length and null out head and tail if empty)
    }

    Data data{ };               // would this normnally be a pointer to the data obj? 
    Node* next{ nullptr };
};

class LinkedList
{
private:
    Node* head;
    Node* tail;
    int length;
public:
    LinkedList()
    {
        head = nullptr;
        tail = nullptr;
        length = 0;
    }

    ~LinkedList()
    {
        std::cout << "  \n\n(destroy list " << this << ")\n"; 
        Node* next = head;
        Node* current = nullptr;   

        while (next)
        {
            current = next;
            next = next->next;
            delete(current);
        }
    }

    const int GetLength() const { return length; } // returns current length of the list 

    Node* GetHead() const { return head; } // returns pointer to first node
    Node* GetTail() const { return tail; } // returns pointer to last node

    bool InList(Node* n) const // reuturns true if n is in the list
    {
        Node* current = head;
        while (current)
        {
            if (current == n)
                return true;
            current = current->next;
        }

        return false;
    }

    const Node* const SetHead(Node* n)      // Sets head to n and returns pointer to new head
    {
        if (!n)
            return nullptr;

        if (InList(n))
        {
            Node* next = head;
            Node* current = nullptr;
            while (next != n)             // delete anything before the new head
            {
                current = next;
                next = current->next;
                delete(current);
                length--;
                
            }

            head = n;
            return head;
        }

    }

    const Node* const SetTail(Node* n)  // Sets tail to n and returns pointer to new tail
    {
        if (!n)
            return nullptr;

        if (InList(n))
        {
            Node* current = head;
            while (current != n)
            {
                current = current->next;
            }

            current = current->next;  
            Node* next = current;
            while (next)              // delete anything after the new tail
            {
                current = next;
                next = current->next;
                delete(current);
                length--;
            }

            tail = n;
            tail->next = nullptr;
            return tail;
        }

    }

    Node* const GetNode(int i) const // Returns node at index i
    {
        Node* current = head;
        int iter = 0;
        while (current)
        {
            if (iter == i)
                return current;
            iter++;
            current = current->next;
        }
        return nullptr; 
    }

    
    Node* const GetNode(Data* d) const // Returns node with data pointer d
    {
        Node* temp = head;
        while (temp)
        {
            if (&temp->data == d) // is this right? 
                return temp;
            temp = temp->next;
        }
        return nullptr;
    }


    // Adds a new node to the front of the list and returns pointer to the new node
    const Node* const AddNodeFront(const Data d = {})
    {
        Node* newNode = new Node;
        newNode->data = d;

        if (head)
        {
            newNode->next = head;
            head = newNode;
        }
        else
        {
            head = tail = newNode;
        }

        length++;
        return newNode;
        
    }

    // Adds a new node to the back of the list, with data d if provided, and returns pointer to the new node
    const Node* const AddNodeBack(const Data& d = {})
    {
        Node* newNode = new Node;
        newNode->data = d;

        if (head)
        {
            tail->next = newNode;
            tail = newNode;
        }
        else
        {
            head = tail = newNode;
        }
   
        length++;
        return newNode;
    }

    // Adds a new node after n and returns pointer to the new node 
    Node* InsertNodeAfter(Node* n, const Data& d = {})
    {
        if (tail && n == tail)
        {          
            Node* newNode = new Node;
            tail->next = newNode;
            tail = newNode;
            newNode->data = d;
            length++;
            return newNode;
        }

        if (head)
        {
            Node* current = head;
            while (current)
            {
                if (current == n)
                {
                    Node* newNode = new Node;
                    newNode->next = current->next;
                    current->next = newNode;
                    newNode->data = d;
                    length++;
                    return newNode;
                }
                current = current->next;
            }
        }
        return nullptr; 
    }

    // Deletes n from the list. Returns true on success // ALSO DELETE BY INDEX? 
    bool Delete(Node* n)
    {
        if (!head)
            return false;

        if (length == 1) // single item list
        {
            ClearList(); 
            // or:        // better to call a function that does this, or implement here when it's simple like this? 
            // delete(n);
            // length--;
            // head = tail = nullptr;
            return true; 
        }

        if (n == head) 
        {
            SetHead(n->next); 
            // or
            // head = n->next;
            // delete(n);
            // length--; 
            return true;
        }

        if (n == tail)
            SetTail(n); 
            //Delete(length);

        Node* current = head;
        Node* previous{ nullptr };
        while (current)
        {
            if (current == n) 
            {
                previous->next = current->next; 
                delete(n);
                length--;
                return true;
            }
            previous = current;
            current = current->next;
        }

        return false; // not in the list
    }

    bool Delete(int i) // Deletes node at index i from the list, Returns true on success
    {
        Node* current = head;
        int iter = 0;
        while (current)
        {
            if (iter == i)
            {
                Delete(current);
                return true;
            }
            iter++;
            current = current->next;
        }
        return false;
    }

    // copies all nodes from list l and adds them to this the end of this list
    void JoinLists(const LinkedList& l)
    {
        if (!l.head || !l.tail)
            return;

        Node* current = l.head;
        while (current)
        {
            AddNodeBack(current->data); // sets the new tail, increments length
            current = current->next;
        }

        //// why didn't this approach to null out all the pointers of list l work?
        //Node* current = l.head; 
        //Node* next { nullptr };
        //while (current)
        //{
        //    next = current->next;
        //    current = nullptr;
        //    current = next;
        //}
    }

    // Removes all nodes from the list
    void ClearList()
    {
        Node* current = head;
        while (current)
        {
            Node* next = current->next;
            delete(current);
            current = next;
        }
        
        length = 0;
        head = tail = nullptr;
    }

    // Prints the list 
    void DisplayList() const
    {
        std::cout << "\n\nList length: " << GetLength() << "\n";

        if (!head)
            return;

        Node* temp = head;
        int index = 0;
        while (temp)
        {
            std::cout << "\nNode index " << index << "  ptr " << temp << " with Data obj ptr " << &temp->data << " data.val1 = " << temp->data.val1;
            temp = temp->next;
            index++;
        }
    }
};

int main()
{

    /////////////// Creating List, Node, Data objects

    std::cout << "\n\nCreate a list (1 - 5) with Data on each node: ";
    LinkedList list;

    for (int i = 0; i < 6; i++)
    {
        Data myData = {};
        myData.val1 = i;
        list.AddNodeBack(myData);
    }
      
    list.DisplayList();

    std::cout << "\n Get the length: "  << list.GetLength();

    Node* myNode = list.GetNode(3);

    std::cout << "\n\nGet the ptr to node at index 3: " << myNode;

    Data* myDataPtr = &myNode->data;

    std::cout << "\n\nGet the pointer to the node's Data obj (myDataPtr): " << myDataPtr << " myDataPtr->val1 = " << myDataPtr->val1;;

    std::cout << "\n\nNode index 3 " << myNode << " data ptr: " << &myNode->data << " data.val1: " << myNode->data.val1;

    std::cout << "\n\nGet a Node ptr by its Data ptr (myDataPtr): " << list.GetNode(myDataPtr) << " from Node Data: " << myNode->data.val1;

    myDataPtr->val1 = 77;

    std::cout << "\n\nChange a value in Data obj via ptr (myDataPtr->val1), then get same value through node data (myNode->data.val1): " << myNode->data.val1;

    list.DisplayList();

    std::cout << "\n\nGet head, tail:\n";

    std::cout << list.GetHead() << ", " << list.GetTail() << "\n";

    std::cout << "\nInsert Data val1 of 88 into Node after node with ptr myDataPtr: \n";

    Data myNewData = {};
    myNewData.val1 = 88;
    list.InsertNodeAfter(list.GetNode(myDataPtr), myNewData);

    std::cout << "Insert Data val1 of 99 into Node at beginning of list: ";

    myNewData.val1 = 99;
    list.AddNodeFront(myNewData);

    list.DisplayList();


    std::cout << "\n\nInsert Data val1 of 66 into Node at end of list: \n";

    myNewData.val1 = 66;
    list.AddNodeBack(myNewData);

    std::cout << "Insert empty nodes after index 1 and 5: ";

    list.InsertNodeAfter(list.GetNode(1));
    list.InsertNodeAfter(list.GetNode(5));

    list.DisplayList();

    /////////////// Deleting

    std::cout << "\n\nDelete head and tail nodes: "<< list.GetHead() << " " << list.GetTail();

    list.Delete(list.GetHead());
    list.Delete(list.GetTail());

    list.DisplayList();

    std::cout << "\n\nDelete node with myDataPtr: " << list.GetNode(myDataPtr);

    list.Delete(list.GetNode(myDataPtr));

    list.DisplayList();

    std::cout << "\n\nDelete node at index 4: " << list.GetNode(4);

    list.Delete(list.GetNode(4));

    list.DisplayList();

    std::cout << "\n\nDelete nodes that don't exist:\n\n";

    std::cout << list.Delete(list.GetNode(50)) << " GetNode(50)\n";
    std::cout << list.Delete(list.GetNode(myDataPtr)) << " GetNode(myDataPtr)\n";
    std::cout << list.Delete(nullptr) << " nullptr\n"; 

    list.DisplayList();

    /////////////// Setting head and tail 

    std::cout << "\n\nSet head and tail to nodes that don't exist: \n\n";

    std::cout << list.SetHead(list.GetNode(99)) << " GetNode(99)\n";
    std::cout << list.SetHead(list.GetNode(myDataPtr)) << " (myDataPtr)\n";

    std::cout << "\n\nGet head, tail:\n";

    std::cout << list.GetHead() << ", " << list.GetTail() << "\n";

    std::cout << list.SetTail(list.GetNode(99)) << " GetNode(99)\n";
    std::cout << list.SetTail(list.GetNode(myDataPtr)) << " GetNode(myDataPtr)\n";

    std::cout << "\n\nGet head, tail:\n";

    std::cout << list.GetHead() << ", " << list.GetTail() << "\n";

    list.DisplayList();

    std::cout << "\n\nSet node at index 3 to head (deletes everything before new head): " << list.GetNode(3);

    list.SetHead(list.GetNode(3));

    list.DisplayList();

    std::cout << "\n\nSet node at tail to head (deletes everything after new tail, creates one item list): " << list.GetNode(3);

    list.SetTail(list.GetHead());

    list.DisplayList();

    std::cout << "\n\nDelete last node: " << list.GetNode(0);

    list.Delete(list.GetNode(0));

    list.DisplayList();

    /////////////// Empty list tests

    std::cout << "\n\nDisplay head, tail of empty list:\n\n";

    std::cout << list.GetHead() << ", " << list.GetTail();

    std::cout << "\n\nDelete nodes that don't exist in empty list:\n\n";

    std::cout << list.Delete(list.GetNode(5)) << "  GetNode(5)\n";
    std::cout << list.Delete(list.GetNode(myDataPtr)) << "  GetNode(myDataPtr)\n";
    std::cout << list.Delete(nullptr) << " nullptr\n";

    std::cout << "\nGet nodes that don't exist in empty list:\n\n";

    std::cout << list.GetNode(5) << " GetNode(5)\n";
    std::cout << list.GetNode(myDataPtr) << "GetNode(myDataPtr)\n";
    std::cout << list.GetNode(nullptr) << " GetNode(nullptr)\n";

    std::cout << "\nInsert after node that doesn't exist in empty list (with, without data):\n\n";

    std::cout << list.InsertNodeAfter(list.GetNode(5), myNewData) << " GetNode(5), myNewData\n";
    std::cout << list.InsertNodeAfter(list.GetNode(myDataPtr)) << " GetNode(myDataPtr)\n";

    std::cout << "\n\nEmpty list still empty:";

    list.DisplayList();

    /////////////// Joining lists

    std::cout << "\n\nNew list a:";

    LinkedList a;
    for (int i = 0; i < 4; i++)
    {
        Data myData = {};
        myData.val1 = i;
        a.AddNodeBack(myData);
    }

    a.DisplayList();

    std::cout << "\n\nNew list b:";

    LinkedList b;
    for (int i = 4; i < 7; i++)
    {
        Data myData = {};
        myData.val1 = i;
        b.AddNodeBack(myData);
    }

    b.DisplayList();

    std::cout << "\n\nAppend list b to list a (1-6):";

    a.JoinLists(b);  

    a.DisplayList();

    /////////////// Trying to test const-correctness... not sure if this is the best way to figure this out? 
    
    std::cout << "\n\nClear all lists:";
    a.ClearList();
    b.ClearList();
    list.ClearList();




    std::cout << "\n\nEnd of scope, call destructors...";

    return 0;
}