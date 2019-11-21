#include "pch.h"
#include<iostream>
#include "linked_list.h"
#include <assert.h>

int main()
{

    LinkedList list;

    list.GenerateTestList(60, 10);

    std::cout << "\n----------------------------------------------------------------- Identify some nodes and data";
    
    std::cout << "\nNode 0 via index: " << list.GetNode(0) << " " << list.GetNode(0)->data.val1;  
    std::cout << "\nNode 3 via index: " << list.GetNode(3) << " " << list.GetNode(3)->data.val1;

    Data* Data0 = &list.GetNode(0)->data;
    Data* Data3 = &list.GetNode(3)->data;

    std::cout << "\nNode 0 via Data address: " << list.GetNode(Data0) << " " << list.GetNode(Data0);
    std::cout << "\nNode 3 via Data address: " << list.GetNode(Data3) << " " << list.GetNode(Data3);

    std::cout << "\nHead: " << list.GetHead() << list.GetHead()->data.val1;
    std::cout << "\nTail: " << list.GetTail() << list.GetTail()->data.val1;

    std::cout << "\n----------------------------------------------------------------- Insert some nodes after x"; 

    Data myNewData = {};

    myNewData.val1 = 35;
    std::cout << "\nInsert 35 after 3: " << list.InsertNodeAfter(list.GetNode(3), myNewData);
    list.TestHeadTail();

    myNewData.val1 = 55;
    std::cout << "\nInsert 55 after 5: " << list.InsertNodeAfter(list.GetNode(5), myNewData);
    list.TestHeadTail();

    std::cout << "\n----------------------------------------------------------------- Add some nodes to front";
    
    myNewData.val1 = 200;
    std::cout << "\nAdd 200 to front: " << list.AddNodeFront(myNewData);
    list.TestHeadTail();

    myNewData.val1 = 100;
    std::cout << "\nAdd 100 to front: " << list.AddNodeFront(myNewData);
    list.TestHeadTail();

    std::cout << "\n----------------------------------------------------------------- Add some nodes to back";
 
    myNewData.val1 = 60;
    std::cout << "\nAdd 60 to back: " << list.AddNodeBack(myNewData);
    list.TestHeadTail();

    myNewData.val1 = 65;
    std::cout << "\nAdd 65 to back: " << list.AddNodeBack(myNewData);
    list.TestHeadTail();

    list.Print();

    std::cout << "\n----------------------------------------------------------------- Set new head and tail";
    
    std::cout << "\nSet head to 4...";
    list.SetHead(list.GetNode(4));

    list.Print();
    list.TestHeadTail();

    std::cout << "\nSet tail to 4...";
    list.SetTail(list.GetNode(4));

    list.Print();
    list.TestHeadTail();

    std::cout << "\nSet head to 2...";
    list.SetHead(list.GetNode(2));

    list.Print();
    list.TestHeadTail();

    std::cout << "\nSet tail to 3...";
    list.SetTail(list.GetNode(3));

    list.Print();
    list.TestHeadTail();

    list.GenerateTestList(100, 10);

    std::cout << "\n----------------------------------------------------------------- Delete some nodes";

    std::cout << "\nDelete 1 via index...";
    list.Delete(list.GetNode(1));

    list.Print();
    list.TestHeadTail();

    std::cout << "\nDelete 5 via index...";
    list.Delete(list.GetNode(5));

    list.Print();
    list.TestHeadTail();

    std::cout << "\nDelete 0 via Data address...";
    Data0 = &list.GetNode(0)->data;
    list.Delete(list.GetNode(Data0));

    list.Print();
    list.TestHeadTail();

    std::cout << "\nDelete 5 via Data address...";
    Data3 = &list.GetNode(3)->data;
    list.Delete(list.GetNode(Data3));

    list.Print();
    list.TestHeadTail();

    std::cout << "\nDelete tail...";
    list.Delete(list.GetTail());

    list.Print();
    list.TestHeadTail();

    std::cout << "\nDelete head...";
    list.Delete(list.GetHead());

    list.Print();
    list.TestHeadTail();

    std::cout << "\nDelete tail...";
    list.Delete(list.GetTail());

    list.Print();
    list.TestHeadTail();

    std::cout << "\nDelete head...";
    list.Delete(list.GetHead());

    list.GenerateTestList(40, 10);

    std::cout << "\n----------------------------------------------------------------- Join some lists";

    std::cout << "\n\nNew list to append:";
    LinkedList to_append;
    to_append.GenerateTestList(4, 1);

    std::cout << "\n\nAppend new list to old list:";
    list.Join(to_append);

    list.Print();
    list.TestHeadTail();

    list.Clear();

    std::cout << "\n----------------------------------------------------------------- Empty list tests";

    std::cout << "\nGet head, tail: " << list.GetHead() << ", " << list.GetTail();
    list.TestHeadTail();

    std::cout << "\n\nDelete nodes that don't exist in empty list:\n";

    list.Delete(list.GetNode(5));
    list.Delete(list.GetHead());
    list.Delete(list.GetTail());
    list.Delete(nullptr);

    list.TestHeadTail();

    std::cout << "\nGet node 0 via index: " << list.GetNode(0);
    std::cout << "\nGet node 3 via index: " << list.GetNode(3);
    std::cout << "\nGet node 0 via Data address: " << list.GetNode(Data0);
    std::cout << "\nGet node 3 via Data address: " << list.GetNode(Data3); 
    std::cout << "\nGet Head: " << list.GetHead();
    std::cout << "\nGet Tail: " << list.GetTail();

    list.TestHeadTail();

    std::cout << "\nSet head to 4..."<< list.SetHead(list.GetNode(4));
    std::cout << "\nSet tail to 4..." << list.SetTail(list.GetNode(4));

    list.TestHeadTail();

    std::cout << "\n\nInsert after node that doesn't exist in empty list:";

    std::cout << "\nInsert after index" << list.InsertNodeAfter(list.GetNode(5), myNewData);
    std::cout << "\nInsert after Data address" << list.InsertNodeAfter(list.GetNode(Data0));

    list.TestHeadTail();

    list.Clear();
    std::cout << "\n\nAdd to back of empty list...";
    list.AddNodeBack();

    list.Print();
    list.TestHeadTail();

    list.Clear();
    std::cout << "\n\nAdd to front of empty list...";
    list.AddNodeFront();

    list.Print();
    list.TestHeadTail();

    std::cout << "\n\nEnd of scope, call destructors...";


    return 0;

}

   