#pragma once

#include "test-linked-list.h"
#include "test-vector.h"
#include "test-hash-table.h"

int run_tests()
{
    if (!test_vector())
        std::cout << "\n  Vector tests passed!";
    
    if (!test_linked_list())
        std::cout << "\n  Linked List tests passed!";
    
    if (!test_hash_table())
        std::cout << "\n  Hash Table tests passed! \n\n";

    return 0;
}