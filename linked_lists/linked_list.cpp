#include "pch.h"
#include<iostream>
#include "linked_list.h"
#include <assert.h>

LinkedList::LinkedList()
    : head(nullptr), tail(nullptr), length(0) { }

LinkedList::~LinkedList()
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

int LinkedList::GetLength() const { return length; }

Node* LinkedList::GetHead() const { return head; }
Node* LinkedList::GetTail() const { return tail; }

bool LinkedList::InList(Node* n) const
{
    if (!head)
        return false;

    Node* current = head;
    while (current)
    {
        if (current == n)
            return true;

        current = current->next;
    }

    return false;
}

Node* LinkedList::SetHead(Node* n)
{
    if (!n)
        return nullptr;

    if (InList(n))
    {
        Node* next = head;
        Node* current = nullptr;
        while (next != n)
        {
            current = next;
            next = current->next;
            delete(current);
            length--;      
        }

        head = n;
        return head;
    }

    return nullptr;
}

Node* LinkedList::SetTail(Node* n)
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
        while (next)
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

    return nullptr;
}

Node* LinkedList::GetNode(int i) const
{
    Node* current = head;
    int iter = 0;
    while (current && current->next)
    {
        if (iter == i)
            return current;
        iter++;
        current = current->next;
    }
    return nullptr; 
}

Node* LinkedList::GetNode(Data* d) const
{
    Node* temp = head;
    while (temp)
    {
        if (&temp->data == d)
            return temp;
        temp = temp->next;
    }
    return nullptr;
}

Node* const LinkedList::AddNodeFront(const Data d)
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

Node* const LinkedList::AddNodeBack(const Data& d)  // maybe this shouldn't exist, it's the same as insert after tail 
{
    Node* newNode = new Node; // I think this is the source of a memory leak.. don't these get destroyed by the list destructor? 
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

Node* LinkedList::InsertNodeAfter(Node* n, const Data& d)
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

bool LinkedList::Delete(Node* n) 
{
    if (!head)
        return false;

    if (n == head) 
    {
        head = n->next;
        delete(n);
        length--;
        return true;
    }

    Node* current = head;
    Node* previous = { nullptr };
    while (current)
    {
        if (current == n)
        {
            previous->next = current->next;
            delete(n);
            length--;

            if (current == tail)
                tail = previous;

            return true;
        }
        previous = current;
        current = current->next;
    }

    return false;
}

bool LinkedList::Delete(int i)
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

void LinkedList::Join(LinkedList& l)
{
    if (!l.head || !l.tail)
        return;

    this->tail->next = l.head; 
    this->tail = l.tail;

    l.head = nullptr;   // this is so the next line doesn't delete the stuff we are stealing... is this the right way to do this? 
    LinkedList otherlist = std::move(l);    // move the entire list to this object.. 
                                            // we don't expect any nodes to be deleted here, right? 
}

void LinkedList::Clear()
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

void LinkedList::Print() const
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
    std::cout << "\n";
}

void LinkedList::GenerateTestList(int max, int mult)
{
    Clear();

    for (int i = 0; i < max; i += mult)
    {
        Data myData = {};
        myData.val1 = i;
        AddNodeBack(myData);
    }

    Print();
}


void LinkedList::TestHeadTail()
{
    assert((!GetHead() && !GetTail()) || (GetHead() && GetTail()));

    if (!GetHead())
    {
        std::cout << "\nHead and tail passed: " << GetHead() << " " << GetTail();
        return;
    }

    assert(GetTail()->next == nullptr);

    Node* current = GetHead();
    while (current->next)
        current = current->next;

    assert(current == GetTail());

    std::cout << "\nHead and tail passed: " << GetHead()->data.val1 << " " << GetTail()->data.val1 << "\n";


    return;

}
