#pragma once

#include <iostream>
#include <cassert> 

#include <vld.h>
#include "hash-table-linear-probing.h"
#include "test-hash-table-chaining.h" // for randon generator

int test_hash_table_linear_probing()
{
    LinearProbeHashTable<const char*, int> table;

    assert(table.GetCapacity() == 8);
    assert(table.GetSize() == 0);

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

    int val0 = 0;
    int val1 = 1;
    int val2 = 2;
    int val3 = 3;
    int val4 = 4;
    int val5 = 5;
    int val6 = 6;
    int val7 = 7;
    int val8 = 8;
    int val9 = 9;

    table.Insert(key0, val0); // insert keys and values 
    table.Insert(key1, val1);
    table.Insert(key2, val2);
    table.Insert(key3, val3);
    table.Insert(key4, val4);
    table.Insert(key5, val5);
    table.Insert(key6, val6);
    table.Insert(key7, val7);

    assert(table.Search(key0) == 0);
    assert(table.Search(key1) == 1);
    assert(table.Search(key2) == 2);
    assert(table.Search(key3) == 3);
    assert(table.Search(key4) == 4);
    assert(table.Search(key5) == 5);

    assert(table.GetCapacity() == 8);
    assert(table.GetSize() == 8);

    table.Insert(key8, val8);
    table.Insert(key9, val9);

    assert(table.GetCapacity() == 16);
    assert(table.GetSize() == 10);

    assert(table.Search(key0) == 0);
    assert(table.Search(key1) == 1);
    assert(table.Search(key2) == 2);
    assert(table.Search(key3) == 3);
    assert(table.Search(key4) == 4);
    assert(table.Search(key5) == 5);
    assert(table.Search(key6) == 6);
    assert(table.Search(key7) == 7);
    assert(table.Search(key8) == 8);
    assert(table.Search(key9) == 9);

    val0 = 1000;
    val1 = 1111;
    val5 = 5555;
    val8 = 8888;
    val9 = 9999;

    table.Update(key0, val0);
    table.Update(key1, val1);
    table.Update(key5, val5);
    table.Update(key8, val8);
    table.Update(key9, val9);

    assert(table.Search(key0) == 1000);
    assert(table.Search(key1) == 1111);
    assert(table.Search(key5) == 5555);
    assert(table.Search(key8) == 8888);
    assert(table.Search(key9) == 9999);

    table.Delete(key0);
    table.Delete(key1);
    table.Delete(key5);
    table.Delete(key8);
    table.Delete(key9);

    assert(table.GetCapacity() == 16);
    assert(table.GetSize() == 5);
    
    assert(table.Search(key2) == 2);
    assert(table.Search(key3) == 3);
    assert(table.Search(key4) == 4);
    assert(table.Search(key6) == 6);
    assert(table.Search(key7) == 7);

    table.Clear();

    assert(table.GetCapacity() == 16);
    assert(table.GetSize() == 0);

    LinearProbeHashTable<int, const char*> other_table(100);

    int keys[1000]{};
    const char* vals[1000]{};

    for (size_t i = 0; i < 1000; i++)
    {
        int key = rand();
        const char* val = genStr();
        other_table.Insert(key, val);
        keys[i] = key;
        vals[i] = val;
    }

    for (size_t i = 0; i < 1000; i++)                        // if i loop this 1000 times (all keys), then searching a different table (int_table) fails later on..
        assert(other_table.Search(keys[i]) == vals[i]);

    return 0;
}
