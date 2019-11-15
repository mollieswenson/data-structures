#include "pch.h"
#include<iostream>

struct Node
{
    int data { NULL };
    Node *next { nullptr };
};

class LinkedList
{
private:
    Node *head, *tail;
public:
    LinkedList()
    {
        head = NULL;
        tail = NULL;
    }

    Node* GetHead() { return head; }
    Node* GetTail() { return tail; }

    Node* GetNodeWithData(int d) // returns first instance of a node with data d
    {
        std::cout << "\nGetNodeWithData(" << d << ") ";
        Node* temp = head;

        while (temp != NULL)
        {
            if (temp->data == d)
                return temp;
            temp = temp->next;
        }
        return NULL; // head was null, no list
    }

    void AddNodeFront(int d)
    {
        std::cout << "\nAddNodeFront(" << d << ") ";
        Node *newNode = new Node;   // pointer to new Node
        newNode->data = d;   // add the data
        
        if (!head)  // empty list
        {
            head = newNode;
            tail = newNode;
            return;
        }
        
        newNode->next = head; // new head node next points to prev head ptr
        head = newNode; // new list head
    }

    void AddNodeBack(int d)
    {
        std::cout << "\nAddNodeBack(" << d << ") ";
        Node *newNode = new Node;   // pointer to new Node
        newNode->data = d;   // add the data

        if (tail)  // list exists, head and tail will only ever exist together.. 
        {
            tail->next = newNode;   // new nodes are initialized with null next
            tail = newNode;
            return;
        }
        std::cout << "calls AddNodeFront() for empty list handling...";
        AddNodeFront(d); // takes care of no list logic 
    }

    void InsertNodeAfter(Node *node, int d)
    {
        std::cout << "\nInsertNodeAfter(" << node << ", " << d << ") ";
        Node *newNode = new Node;   // pointer to new Node
        newNode->data = d;   // add the data

        // traverse list until we find node 
        Node *current = head;
        while (current->next)
        {
            if (current->data == d)
            {
                newNode->next = current->next;
                current->next = newNode;
                newNode = current;
                return;

            }

            current = current->next;
        }

        delete newNode;
    }

    void DeleteNodeAfter(Node *head)
    {
        std::cout << "";
    }

    void DeleteList(Node *head)
    {
        std::cout << "";
    }

    void JoinLists(Node *head)
    {
        std::cout << "";
    }

    void DisplayList()
    {
        std::cout << "\nDisplayList() ";
        if (!head) // if head doesn't point anywhere, no list
            return;

        Node *temp = head;  // iterator 
        while (temp != NULL)
        {
            std::cout << temp->data << "(";
            std::cout << temp << ") ";
            temp = temp->next;
        } 
    }

    

};

int main()  // how tf do i set up good testing for all the ways these could go?
{
    std::cout << "first: " << "\n---------------";

    LinkedList first;
    first.DisplayList();
    std::cout << first.GetNodeWithData(3);

    first.AddNodeBack(3);
    first.DisplayList();

    std::cout << first.GetNodeWithData(3);

    first.AddNodeBack(4);
    first.AddNodeFront(2);
    first.AddNodeBack(5);
    first.AddNodeFront(1);
    first.DisplayList();

    for (int i = 1; i < 6; i++)
    {
        std::cout << first.GetNodeWithData(i);
    }

    


    std::cout << "\n\nsecond: " << "\n---------------";

    LinkedList second;
    second.AddNodeFront(3);
    second.DisplayList();

    second.AddNodeBack(5);
    second.AddNodeBack(6);
    second.AddNodeFront(2);
    second.DisplayList();

    second.InsertNodeAfter(second.GetNodeWithData(3),4);

    std::cout << std::endl;

    return 0;
}