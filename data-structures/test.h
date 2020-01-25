#pragma once

#include "test-linked-list.h"
#include "test-vector.h"
#include "test-hash-table-chaining.h"
#include "test-hash-table-linear-probing.h"
#include "test-binary-search-tree.h"

int run_tests()
{
    if (!test_vector())
        std::cout << "\n  Vector tests passed!";
    
    if (!test_linked_list())
        std::cout << "\n  Linked List tests passed!";
    
    if (!test_hash_table_chaining())
        std::cout << "\n  Hash Table Chaining tests passed!";

    if (!test_hash_table_linear_probing())
        std::cout << "\n  Hash Table Linear Probing tests passed!";

    if (!test_bst())
        std::cout << "\n  Binary Search Tree tests passed!  \n\n";

    return 0;
}