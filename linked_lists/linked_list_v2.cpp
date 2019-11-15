#include "pch.h"
#include<iostream>
#include "linked_list_v2.h"

struct Node
{
    ~Node() 
    {
        std::cout << "  \n(destroy node " << this << " " << data << ")"; // is anything happeing here? 
    }

    int data{};
    Node *next{ nullptr };
};

class LinkedList
{
private:
    Node *head, *tail;   // shouldn't more stuff be private? 
public:
    LinkedList()
    {
        head = nullptr;
        tail = nullptr;
    }

    ~LinkedList()    //this sometimes deletes objects too early (try to use JoinLists()) 
    {
        Node *next = head;
        Node *current = nullptr;   

        while (next)
        {
            current = next;
            next = next->next;
            delete(current);
        }
    }

    Node* GetHead() { return head; } // returns pointer to first node
    Node* GetTail() { return tail; } // returns pointer to last node

    bool InList(Node *n)
    {
        Node *current = head;
        while (head)
        {
            if (current == n)
                return true;
            current = current->next;
        }

        return false;
    }

    Node* SetHead(Node* n)      // Sets head to n and returns pointer to new head
    {
        if (!n)
            return nullptr;

        if (InList(n))
        {
            Node *next = head;
            Node *current = nullptr;
            while (next != n)          //TODO.. HANDLE DELETING NODES THAT GET WIPED OUT HERE
            {
                current = next;
                next = next->next;
                delete(current);
            }

            head = n;
            return head;
        }

    }

    Node* SetTail(Node* n)  // Sets tail to n and returns pointer to new tail
    {
        if (!n)
            return nullptr;
        tail = n;
        tail->next = nullptr;
        return tail;                //TODO.. HANDLE DELETING NODES THAT GET WIPED OUT HERE
    }

    Node* GetNode(int d) // Returns first instance of a node with data d
    {
        Node* temp = head;
        while (temp)
        {
            if (temp->data == d)
                return temp;
            temp = temp->next;
        }
        return nullptr; 
    }

    // Adds a new node to the front of the list and returns pointer to the new node
    Node * AddNodeFront(int d = NULL)
    {
        Node *newNode = new Node;
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

        return newNode;  // this will get deleted by the destructor so i dont do that here.. right?
    }

    // Adds a new node to the back of the list and returns pointer to the new node
    Node * AddNodeBack(int d = NULL)
    {
        Node *newNode = new Node;

        if (head)
        {
            tail->next = newNode;
            tail = newNode;
        }
        else
        {
            head = tail = newNode;
        }

        newNode->data = d;
        return newNode; // this will get deleted by the destructor so i dont do that here.. right?
    }

    // Adds a new node after n and returns pointer to the new node 
    Node * InsertNodeAfter(Node *n, int d = NULL)
    {
        Node *newNode = new Node;
        newNode->data = d;

        if (n == tail && tail != nullptr) {
            tail->next = newNode;
            tail = newNode;
            return newNode;
        }

        if (head)
        {
            Node *current = head;
            while (current)
            {
                if (current == n)
                {
                    newNode->next = current->next;
                    current->next = newNode;
                    return newNode;
                }
                current = current->next;
            }
        }
        //delete(newNode);
        return nullptr; 
    }

    // Deletes n from the list. Returns true on success
    bool Delete(Node *n)
    {
        if (!head)
            return false;

        if (n == head && n == tail) // single item list 
        {
            delete(head);
            head = tail = nullptr; // necessary?
            return true;
        }

        Node *current = head;
        Node *previous { nullptr };
        while (current)
        {
            if (current == n)
            {
                if (!previous) // deleting head
                {
                    head = current->next;
                    delete(current);
                    return true;
                }

                if (n == tail) // delteing tail 
                {
                    previous->next = nullptr;
                    tail = previous;
                    delete(current);
                    return true;
                }
                previous->next = current->next;  // deleting something in between  
                break;
            }
            previous = current;
            current = current->next;
            
        }

        return false; // not in the list
    }

    // appends list l to this the end of this list
    void JoinLists(LinkedList l)
    {
        tail->next = l.head;
        tail = l.tail;
    }

    // Removes all nodes from the list
    void ClearList()
    {
        Node *current = head;
        while (current)
        {
            Node *next = current->next;
            delete(current);
            current = next;
        }
        
    head = tail = nullptr;
    }

    // Prints the list 
    void DisplayList()
    {
        if (!head)
            return;

        Node *temp = head; 
        while (temp)
        {
            std::cout << "\n" << temp << " " << temp->data;
            temp = temp->next;
        }
    }
};

int main()  // how tf do i set up good testing for all the ways these could go?
{
    std::cout << "\n\nCreate a list and add items to back and front (1 - 5):\n";
    
    LinkedList list;
 
    list.AddNodeBack(3);
    list.AddNodeBack(4);
    list.AddNodeBack(5);

    list.AddNodeFront(2);
    list.AddNodeFront(1);

    list.DisplayList();

    std::cout << "\n\nDisplay head, tail:\n\n";

    std::cout << list.GetHead() << ", " << list.GetTail() << "\n";

    std::cout << "\nClear list:\n";

    list.ClearList();

    // new list
    list.AddNodeBack(1);
    list.AddNodeBack(3);
    list.AddNodeBack(5);

    std::cout << "\n\nNew list (1, 3 ,5):\n";
    list.DisplayList();

    std::cout << "\n\nGet nodes with data (1 and 3):\n\n";

    std::cout << list.GetNode(1) << ", " << list.GetNode(3);

    std::cout << "\n\nInsert nodes before 1 and 3 (1 - 5):\n";

    list.InsertNodeAfter(list.GetNode(1), 2);
    list.InsertNodeAfter(list.GetNode(3), 4);

    list.DisplayList();

    ///////////// Deleting

    std::cout << "\n\nDelete head and tail nodes (2 , 3, 4):\n";

    list.Delete(list.GetHead());
    list.Delete(list.GetTail());

    list.DisplayList();

    std::cout << "\n\nDelete node 2 and 3 (4):\n";

    list.Delete(list.GetNode(2));
    list.Delete(list.GetNode(3));

    list.DisplayList();

    std::cout << "\n\nDelete nodes that don't exist (2 , 4):\n\n";

    std::cout << list.Delete(list.GetNode(5));
    std::cout << "\n" << list.Delete(nullptr);
    std::cout << "\n" << list.Delete(NULL) <<  "\n";

    list.DisplayList();

    std::cout << "\n\nDelete last node (4):\n";

    list.Delete(list.GetNode(4));

    list.DisplayList();

    ///////////// Empty list tests


    std::cout << "\n\nDisplay head, tail of empty list:\n\n";
   
    std::cout << list.GetHead() << ", " << list.GetTail();

    std::cout << "\n\nDelete nodes that don't exist in empty list:\n";

    std::cout << list.Delete(list.GetNode(5)) << ", ";
    std::cout << list.Delete(nullptr) << ", ";
    std::cout << list.Delete(NULL);

    std::cout << "\n\nGet node that doesn't exist in empty list:\n";

    std::cout << list.GetNode(1) << ", " << list.GetNode(3);

    std::cout << "\n\nInsert after node that doesn't exist in empty list :\n";

    std::cout << list.InsertNodeAfter(list.GetNode(4), 5);

    std::cout << "\n\nEmpty list still empty:\n";

    list.DisplayList();

    ///////////// Set head and tail tests

    std::cout << "\n\nNew list(1-7):\n";

    for(int i = 1; i < 8 ; i++)
        list.AddNodeBack(i);

    list.DisplayList();

    std::cout << "\n\nSet head at 3, tail at 5 (3, 4, 5):\n";

    list.SetHead(list.GetNode(3)); 
    list.SetTail(list.GetNode(5));
    list.DisplayList();

    std::cout << "\n\nDisplay head, tail:\n\n";

    std::cout << list.GetHead() << ", " << list.GetTail();

    std::cout << "\n\nSet head to tail (5):\n";

    list.SetHead(list.GetTail());

    list.DisplayList();

    
    std::cout << "\nClear list:\n";
    list.ClearList();

    std::cout << "\n\nNew list (1-5):\n";
    for (int i = 1; i < 6; i++)
        list.AddNodeBack(i);

    list.DisplayList();

    std::cout << "\n\nSet head and tail to node that doesn't exist:\n\n";

    std::cout << list.SetHead(nullptr) << "\n";
    std::cout << list.SetTail(nullptr);

    std::cout << "\n\nDisplay head, tail:\n\n";

    std::cout << list.GetHead() << ", " << list.GetTail();

    std::cout << "\n\nList unchanged:\n";

    list.DisplayList();

    std::cout << "\n\nSet tail to head (1):\n";

    list.SetTail(list.GetHead());

    list.DisplayList();

    std::cout << "\n\nNew list a (1-3):\n";

    LinkedList a;
    for (int i = 1; i < 4; i++)
        a.AddNodeBack(i);

    a.DisplayList();

    std::cout << "\n\nNew list b (4-6):\n";

    LinkedList b;
    for (int i = 4; i < 7; i++)
        b.AddNodeBack(i);

    b.DisplayList();

    // std::cout << "\n\nAppend list b to list a (1-6):\n";
    // a.JoinLists(b); // why does destructor get called on b here??
    // a.DisplayList();


    std::cout << "\n\n\n";

    return 0;
}