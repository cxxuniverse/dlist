#include "../include/dlist.h"

// #include "../include/test.h"

int main()
{
    // cxc::dlist<float> list = {1, 2, 3, 4, 5, 6};
    cxc::dlist<float> list{};

    std::cout << "address of list: " << &list << std::endl;

    list.insert(1000);
    list.insert(1001);
    list.insert_head(999);
    list.insert(1002);
    list.print();

    std::cout << "remove heads & tails" << std::endl;
    list.remove_head();
    list.remove_head();
    list.remove_tail();
    list.remove_tail();
    list.print();
}