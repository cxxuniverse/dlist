#include "../include/dlist.h"

// #include "../include/test.h"

int main()
{
    // cxc::dlist<float> list = {1, 2, 3, 4, 5, 6};
    cxc::dlist<float> list{};

    std::cout << "address of list: " << &list << std::endl;

    // list.print();

    list.insert_head(100);
    list.insert_tail(101);
    // list.print();

    list.insert_head(99);
    list.insert_head(98);
    // list.print();

    list.insert_tail(102);
    list.print();

    list.clear();
    std::cout << "after clear: " << std::endl;
    list.print();
}