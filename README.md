# Data Structures

These are the C++ data structures I wrote as a practice exercise.

## Vector

Container implementation with standard operations for element access/modifiers and size/capacity. Also has iterators, type templates, fill/range/copy constructors, destructor. Container manages capacity and reallocates to larger size as needed. Allocates and frees memory with no leaks. Tests that assert expected results after all operations

* [vector.h](https://github.com/mollieswenson/data-structures/blob/master/data-structures/vector.h)
* [test-vector.h](https://github.com/mollieswenson/data-structures/blob/master/data-structures/test-vector.h)

## Linked List

Node and container implementation with standard operations for element access and modifiers. Also has type templates, operator overloads, constructor with initialization list, destructor. Allocates and frees memory with no leaks. Tests that assert expected results after all operations

* [linked-list.h](https://github.com/mollieswenson/data-structures/blob/master/data-structures/linked-list.h)
* [test-linked-list.h](https://github.com/mollieswenson/data-structures/blob/master/data-structures/test-linked-list.h)

## Hash Table, Chaining

Node and container implementation with standard operations for element access/modifiers and size/capacity. Also has iterators, type templates, operator overloads, overloaded constructor, destructor, hash function struct for key type overrides, int and char type hash function impls, assert for unsupported key type. Container manages capacity and reallocates to larger size when load factor > 1. Allocates and frees memory with no leaks. Tests that assert expected results after all operations

* [hash-table-chaining.h](https://github.com/mollieswenson/data-structures/blob/master/data-structures/hash-table-chaining.h)
* [hash-function.h](https://github.com/mollieswenson/data-structures/blob/master/data-structures/hash-function.h)
* [test-hash-table-chaining.h](https://github.com/mollieswenson/data-structures/blob/master/data-structures/test-hash-table-chaining.h)

## Hash Table, Linear Probing

Node and container implementation with standard operations for element access/modifiers and size/capacity. Also has iterators, type templates, operator overloads, overloaded constructor, destructor, hash function struct for key type overrides, int and char type hash function impls, assert for unsupported key type. Container manages capacity and reallocates to larger size when load factor > 1. Allocates and frees memory with no leaks. Tests that assert expected results after all operations

* [hash-table-linear-probing.h](https://github.com/mollieswenson/data-structures/blob/master/data-structures/hash-table-linear-probing.h)
* [hash-function.h](https://github.com/mollieswenson/data-structures/blob/master/data-structures/hash-function.h)
* [test-hash-table-linear-probing.h](https://github.com/mollieswenson/data-structures/blob/master/data-structures/test-hash-table-linear-probing.h)

## Binary Search Tree

Node and container implementation with standard operations for element access/modifiers and size/capacity. Also has iterators, type templates, operator overloads, overloaded constructor, destructor. Tests that assert expected results after all operations

* [binary-search-tree.h](https://github.com/mollieswenson/data-structures/blob/master/data-structures/binary-search-tree.h)
* [test-binary-search-tree.h](https://github.com/mollieswenson/data-structures/blob/master/data-structures/test-binary-search-tree.h), []()

## Red-black Tree

Node and self-balancing tree implementation with standard operations for element access/modifiers and size/capacity. Also has iterators, type templates, operator overloads, overloaded constructor, destructor. Tests that assert expected results after all operations 

* [red-black-tree.h](https://github.com/mollieswenson/data-structures/blob/master/data-structures/red-black-tree.h)
* [red-black-tree-node.h](https://github.com/mollieswenson/data-structures/blob/master/data-structures/red-black-tree-node.h)
* [test-red-black-tree.h](https://github.com/mollieswenson/data-structures/blob/master/data-structures/test-red-black-tree.h)
