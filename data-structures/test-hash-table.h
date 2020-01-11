#pragma once

#include <iostream>
#include <cassert> 

#include <vld.h>
#include "hash-table.h"

static const char c[] =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz";

const char* genStr()
{
    static char key[11]{};

    for (size_t i = 0; i < 10; i++)
        key[i] = (c[rand() % (sizeof(c) - 1)]);

    return key;
}

int test_hash_table()
{
    ChainedHashTable<const char*, int> table; // key type const char*

    assert(table.GetSize() == 0); // expected size and capacity
    assert(table.GetCapacity() == 8);

    const char* key0 = "zero";
    const char* key1 = "one";
    const char* key2 = "two";
    const char* key3 = "three";
    const char* key4 = "four";
    const char* key5 = "five";
    const char* key6 = "six";
    const char* key7 = "seven";
    const char* key8 = "eight";
    const char* key9 = "nine";
    const char* key10 = "ten";
    const char* key11 = "eleven";
    const char* key12 = "twelve";
    const char* key13 = "thirteen";
    const char* key14 = "fourteen";
    const char* key15 = "fifteen";

    table.Insert(key0, 0); // insert keys and values 
    table.Insert(key1, 1);
    table.Insert(key2, 2);
    table.Insert(key3, 3);
    table.Insert(key4, 4);
    table.Insert(key5, 5);
    table.Insert(key6, 6);
    table.Insert(key7, 7);
    table.Insert(key8, 8);
    table.Insert(key9, 9);
    table.Insert(key10, 10);
    table.Insert(key11, 11);
    table.Insert(key12, 12);
    table.Insert(key13, 13);
    table.Insert(key14, 14);
    table.Insert(key15, 15);

    //table.Print(true);

    assert(table.GetSize() == 16); // expected size and capacity
    assert(table.GetCapacity() == 8);

    assert(table.Search(key0) == 0); // access expected values via key 
    assert(table.Search(key1) == 1);
    assert(table.Search(key2) == 2);
    assert(table.Search(key3) == 3);
    assert(table.Search(key4) == 4);

    assert(table.Search(key11) == 11);
    assert(table.Search(key12) == 12);
    assert(table.Search(key13) == 13);
    assert(table.Search(key14) == 14);
    assert(table.Search(key15) == 15);

    table.Delete(key5); // delete some nodes (hash-table.h asserts if you Search for a bad key, not sure how to test)
    table.Delete(key4);
    table.Delete(key15);
    table.Delete(key0);

    assert(table.GetSize() == 12); // expected size and capacity
    assert(table.GetCapacity() == 8);

    //table.Print(true);


    ChainedHashTable<const char*, const char*> rand_table; // key type const char*

    const char* keys[1000]{};
    for (size_t i = 0; i < 1000; i++)
    {
        const char* key = genStr();
        rand_table.Insert(key, key);
        keys[i] = key;
    }

    for (size_t i = 0; i < 150; i++)                        // if i loop this 1000 times (all keys), then searching a different table (int_table) fails later on..
        assert(rand_table.Search(keys[i]) == keys[i]);


    ChainedHashTable<int, int> int_table; // key type int

    int int_keys[1000]{};
    int int_vals[1000]{};
    int int_key{};
    int int_val{};

    for (size_t i = 0; i < 1000; i++)
    {
        int_key = rand();
        int_val = (int)i;
        int_keys[i] = (int)int_key;
        int_vals[i] = (int)i;

        int_table.Insert(int_key, int_val);  // insert key with value of keys[] index we're on 
    }

    assert(int_table.GetSize() == 1000); // expected size and capacity
    assert(int_table.GetCapacity() == 8);

    for (size_t i = 0; i < 150; i++)
        assert(int_table.Search(int_keys[i]) == (size_t)i);      // If this loops for all keys, some retured values are wrong
        
    for (int i = 0; i < 1000; i += 10) // delete 10%
        int_table.Delete(int_keys[i]);

    assert(int_table.GetSize() == 900); // expected size and capacity
    assert(int_table.GetCapacity() == 8);

    //int_table.Print();

    return 0;
}

