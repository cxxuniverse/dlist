# Doubly Linked List

This repository contains an implementation of a doubly linked list for storing elements of dynamic types.

## Usage

```cpp

cxc::dlist<float> list = {12.2f, 3.14f, 2.2136f};
cxc::dlist<Custom_Class> custom_list = { ... }; 

```

## Features
- Supports insertion at the head and tail of the list.
- Provides a clear method to deallocate memory and reset the list.
- Supports various dynamic types.
- Easy to use with a simple and intuitive interface.

## Example

```cpp
#include "dlist.h"

int main() {
    // Create a list of integers
    cxc::dlist<int> list;

    // Insert elements at the head
    list.insert_head(1);
    list.insert_head(2);
    list.insert_head(3);

    // Insert elements at the tail
    list.insert_tail(4);
    list.insert_tail(5);
    list.insert_tail(6);

    // Print the list
    list.print();

    // Clear the list
    list.clear();

    return 0;
}

```