#pragma once

#include <vld.h>
#include "linked-list.h"

struct Data { int val1; }; // custom data type

template <typename T>
void Print(LinkedList<T>& list);

template <typename T>
void GenerateTestList(LinkedList<T>& list, int max, int mult);

template <typename T>
void TestHeadTail(LinkedList<T>& list);

int test_linked_list() // run all vector tests
{
    // ================================ Char List

    LinkedList<char> charlist;

    char c = 'a';

    for (size_t i = 0; i < 10; i++, c++)
        charlist.AddNodeBack(c);

    c = 'a';
    for (size_t i = 0; i < 10; i++, c++)
        assert(charlist.GetNode((int)i)->data == c);

    assert(charlist.GetHead()->data == charlist.GetNode(0)->data); // head points to first node
    assert(charlist.GetHead()->data == 'a'); // access expected data

    assert(charlist.GetTail()->data == charlist.GetNode(9)->data); // tail points to last node
    assert(charlist.GetTail()->data == 'j'); // access expected data

    LinkedNode<char>* ptr = charlist.GetNode(4); // get node by its index

    assert(ptr->data == 'e'); // access expected data
    assert(charlist.InList(ptr)); // expected to be in list

    charlist.Delete(ptr); // delete node by Node ptr 
    charlist.Delete(0); // delete node by index

    assert(!charlist.InList(ptr)); // not in list

    charlist.AddNodeFront('a'); // add a node to front
    charlist.InsertNodeAfter(charlist.GetNode(3), 'e'); // insert a node 
    charlist.AddNodeBack('k'); // add a node to back

    charlist.SetHead(charlist.GetNode(2)); // set head
    charlist.SetTail(charlist.GetNode(5)); // set tail

    c = 'c';
    for (size_t i = 0; i < 6; i++, c++)
        assert(charlist.GetNode((int)i)->data == c);

    // ================================ Custom List
    
    LinkedList<Data> custom_list;

    Data testData = {};
    int data = 100;

    for (int i = 0; i < 100; i++, data += 100) // populate list
    {
        testData.val1 = data;
        custom_list.AddNodeBack(testData);
    }

    data = 100;
    for (int i = 0; i < 99; i++, data += 100) // access expected values
        assert(custom_list.GetNode(i)->data.val1 == data);

    assert(custom_list.GetLength() == 100); // length 100 

    assert(custom_list.GetHead() == custom_list.GetNode(0)); // head points to first node
    assert(custom_list.GetTail() == custom_list.GetNode(99)); // tail points to last node

    assert(custom_list.InList(custom_list.GetNode(50)) == true); // an index within range is in the list
    assert(custom_list.InList(custom_list.GetNode(500)) == false); // an index out of range is not in the list

    custom_list.SetHead(custom_list.GetNode(50)); // set head to index 50
    custom_list.SetTail(custom_list.GetNode(9));  // set tail to index 9 

    assert(custom_list.GetLength() == 10); // length 10

    data = 5100;
    for (int i = 0; i < 10; i++, data += 100) // access expected values
        assert(custom_list.GetNode(i)->data.val1 == data);

    testData.val1 = 33;
    custom_list.AddNodeFront(testData); // add a node to front

    testData.val1 = 99;
    custom_list.AddNodeBack(testData); // add a node to back

    testData.val1 = 55;
    custom_list.InsertNodeAfter(custom_list.GetNode(5), testData); // add a node in middle

    testData.val1 = 66;
    custom_list.InsertNodeAfter(custom_list.GetNode(5), testData); // add another node in middle

    assert(custom_list.GetLength() == 14); // length 14

    assert(custom_list.GetHead() == custom_list.GetNode(0)); // head points to first node
    assert(custom_list.GetTail() == custom_list.GetNode(13)); // tail points to last node

    custom_list.Delete(custom_list.GetNode(0)); // delete first node
    custom_list.Delete(custom_list.GetNode(5)); // delete middle node
    custom_list.Delete(custom_list.GetNode(11)); // delete last node
    custom_list.Delete(custom_list.GetNode(1)); // delete node by index

    assert(custom_list.GetLength() == 10); // length 10

    assert(custom_list.GetHead() == custom_list.GetNode(0)); // head points to first node
    assert(custom_list.GetTail() == custom_list.GetNode(9)); // tail points to last node

    custom_list.Clear(); // clear list

    assert(custom_list.GetLength() == 0); // length 0
    assert(custom_list.GetHead() == nullptr); // head is nullptr
    assert(custom_list.GetTail() == nullptr); // tail is nullptr

    data = 10;
    for (int i = 0; i < 10; i++, data += 10) // re-populate list
    {
        testData.val1 = data;
        custom_list.AddNodeBack(testData);
    }

    LinkedList<Data> secondList; // second list

    data = 15;
    for (int i = 0; i < 10; i++, data += 5) // populate second list
    {
        testData.val1 = data;
        secondList.AddNodeBack(testData);
    }

    LinkedNode<Data>* n = secondList.GetNode(0); // save this for later   -------------

    custom_list.Join(secondList); // join list and secondList

    assert(custom_list.GetLength() == 20); // length 20

    assert(custom_list.GetHead() == custom_list.GetNode(0)); // head points to first node
    assert(custom_list.GetTail() == custom_list.GetNode(19)); // tail points to last node

    assert(custom_list.GetTail() == secondList.GetTail()); // new tail is second list tail
    assert(custom_list.InList(n)); // node from second list is in the first list now

    return 0;
}

template <typename T>
void Print(LinkedList<T>& list)
{
    std::cout << "\n\nList length: " << list.GetLength() << "\n";

    if (!list.GetHead())
        return;

    LinkedNode<T>* temp = list.GetHead();
    int index = 0;
    while (temp)
    {
        std::cout << "\nNode [" << index << "] data: " << temp->data;
        temp = temp->next;
        index++;
    }
    std::cout << "\n";
}

template <typename T>
void GenerateTestList(LinkedList<T>& list, int max, int mult) 
{
    list.Clear();

    for (int i = 0; i < max; i += mult)
    {
        Data myData = {};
        myData.val1 = i;
        list.AddNodeBack(myData);
    }

    Print(list);
}

template <typename T>
void TestHeadTail(LinkedList<T>& list)
{
    assert((!list.GetHead() && !list.GetTail()) || (list.GetHead() && list.GetTail()));

    if (!list.GetHead())
    {
        std::cout << "\nHead and tail passed: " << list.GetHead() << " " << list.GetTail();
        return;
    }

    assert(list.GetTail()->next == nullptr);

    LinkedNode* current = list.GetHead();
    while (current->next)
        current = current->next;

    assert(current == list.GetTail());

    std::cout << "\nHead and tail passed: " << list.GetHead()->data.val1 << " " << list.GetTail()->data.val1 << "\n";

    return;
}
