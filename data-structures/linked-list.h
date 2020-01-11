#pragma once

#include <iostream>
#include <cassert> 
#include <string>

#include <vld.h>

#include <assert.h>
#include "pch.h"

template <typename T>
struct LinkedNode
{
    LinkedNode()
    {
        next = nullptr;
    }

    ~LinkedNode(){}

    T data{};
    LinkedNode* next{ nullptr };
};

template <typename T>
class LinkedList
{
private:
    LinkedNode<T>* head;
    LinkedNode<T>* tail;
    int length;
public:
    LinkedList();
    ~LinkedList();

    int GetLength() const; // returns current length of the list

    LinkedNode<T>* GetHead() const;// returns pointer to first node
    LinkedNode<T>* GetTail() const; // returns pointer to last node

    bool InList(LinkedNode<T>*) const; // returns true if n is in the list

    LinkedNode<T>* SetHead(LinkedNode<T>*);  // Sets headand returns pointer to new head
    LinkedNode<T>* SetTail(LinkedNode<T>*);  // Sets tail and returns pointer to new tail

    LinkedNode<T>* GetNode(int) const; // Returns node at index i
   // Node<T>* GetNodeByData(T&) const; // Returns node with data pointer d

    LinkedNode<T>* const AddNodeFront(const T = {}); // Adds a new node to the front of the list and returns pointer to the new node
    LinkedNode<T>* const AddNodeBack(const T& = {});  // Adds a new node to the back of the list, with data d if provided, and returns pointer to the new node

    LinkedNode<T>* InsertNodeAfter(LinkedNode<T>* n, const T& = {}); // Adds a new node after n and returns pointer to the new node 

    bool Delete(LinkedNode<T>*); // Deletes a node from the list, returns true on success 
    bool Delete(int); // Deletes node at index i from the list, returns true on success

    void Join(LinkedList&); // copies all nodes from list l and adds them to this the end of this list

    void Clear(); // Removes all nodes from the list

   // int& operator[](int index) { _verify(index); return _array[index]; };  // access element using []

    template <typename T>
    friend std::ostream& operator<<(std::ostream& os, const LinkedList<T>& list); // ostream
};


template <typename T>
std::ostream& operator<<(std::ostream& os, const LinkedList<T>& list);

template <typename T>
std::ostream& operator<<(std::ostream& os, const LinkedList<T>& list)
{
    os << "[";

    LinkedNode<T>* temp = list.GetHead();
    int index = 0;
    while (temp)
    {
        os << temp->data << " ";
        temp = temp->next;
        index++;
    }

    os << "]";

    return os;
}

template <typename T>
LinkedList<T>::LinkedList()
    : head(nullptr), tail(nullptr), length(0) { }

template <typename T>
LinkedList<T>::~LinkedList()
{
    LinkedNode<T>* next = head;
    LinkedNode<T>* current = nullptr;

    while (next)
    {
        current = next;
        next = next->next;
        delete(current);
    }
}

template <typename T>
int LinkedList<T>::GetLength() const { return length; }

template <typename T>
LinkedNode<T>* LinkedList<T>::GetHead() const { return head; }

template <typename T>
LinkedNode<T>* LinkedList<T>::GetTail() const { return tail; }

template <typename T>
bool LinkedList<T>::InList(LinkedNode<T>* n) const
{
    if (!head)
        return false;

    LinkedNode<T>* current = head;
    while (current)
    {
        if (current == n)
            return true;

        current = current->next;
    }

    return false;
}

template <typename T>
LinkedNode<T>* LinkedList<T>::SetHead(LinkedNode<T>* n)
{
    if (!n)
        return nullptr;

    if (InList(n))
    {
        LinkedNode<T>* next = head;
        LinkedNode<T>* current = nullptr;
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

template <typename T>
LinkedNode<T>* LinkedList<T>::SetTail(LinkedNode<T>* n)
{
    if (!n)
        return nullptr;

    if (InList(n))
    {
        LinkedNode<T>* current = head;
        while (current != n)
        {
            current = current->next;
        }

        current = current->next;
        LinkedNode<T>* next = current;
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

template <typename T>
LinkedNode<T>* LinkedList<T>::GetNode(int i) const
{
    LinkedNode<T>* current = head;
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

//template <typename T>
//Node<T>* LinkedList<T>::GetNodeByData(T& d) const // this is problematic if data is an int
//{
//    Node<T>* temp = head;
//    while (temp)
//    {
//        if (&temp->data == d)
//            return temp;
//        temp = temp->next;
//    }
//    return nullptr;
//}

template <typename T>
LinkedNode<T>* const LinkedList<T>::AddNodeFront(const T d)
{
    LinkedNode<T>* newNode = new LinkedNode<T>;
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

template <typename T>
LinkedNode<T>* const LinkedList<T>::AddNodeBack(const T& d)  // maybe this shouldn't exist, it's the same as insert after tail
{
    LinkedNode<T>* newNode = new LinkedNode<T>;
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

template <typename T>
LinkedNode<T>* LinkedList<T>::InsertNodeAfter(LinkedNode<T>* n, const T& d)
{
    if (tail && n == tail)
    {
        LinkedNode<T>* newNode = new LinkedNode<T>;
        tail->next = newNode;
        tail = newNode;
        newNode->data = d;
        length++;
        return newNode;
    }

    if (head)
    {
        LinkedNode<T>* current = head;
        while (current)
        {
            if (current == n)
            {
                LinkedNode<T>* newNode = new LinkedNode<T>;
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

template <typename T>
bool LinkedList<T>::Delete(LinkedNode<T>* n)
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

    LinkedNode<T>* current = head;
    LinkedNode<T>* previous = { nullptr };
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

template <typename T>
bool LinkedList<T>::Delete(int i)
{
    LinkedNode<T>* current = head;
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

template <typename T>
void LinkedList<T>::Join(LinkedList& l)
{
    if (!l.head || !l.tail)
        return;

    this->tail->next = l.head;
    this->tail = l.tail;

    length = length + l.GetLength();

    l.head = nullptr;
    LinkedList otherlist = std::move(l);
}

template <typename T>
void LinkedList<T>::Clear()
{
    LinkedNode<T>* current = head;
    while (current)
    {
        LinkedNode<T>* next = current->next;
        delete(current);
        current = next;
    }

    length = 0;
    head = tail = nullptr;
}
