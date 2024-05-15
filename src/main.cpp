#include "dlist.h"

#include <algorithm>

int main()
{
    cxc::dlist<float> list_1 = {1, 2, 3, 4, 5, 6};
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

    std::cout << "reverse order:" << std::endl;
    list.insert(1000);
    list.insert(1001);
    list.insert_head(999);
    list.insert(1002);
    list.reverse();
    list.print();
    list.reverse();
    list.insert_head(666);
    list.print();

    std::cout << "Head: " << list.get_head() << std::endl;
    std::cout << "Tail: " << list.get_tail() << std::endl;
    std::cout << "size: " << list.size() << std::endl;

    std::cout << *(list.begin()) << std::endl;

    for (float value : list)
    {
        std::cout << value << std::endl;
    }

    std::for_each(list.begin(), list.end(), [](float value) { std::cout << "value: " << value << std::endl; });

    cxc::dlist<float>::Iterator it = list.begin();

    while (it != list.end())
    {
        std::cout << "while: " << *it << std::endl;
        ++it;
    }

    list.reverse();

    for (auto it = list.begin(); it != list.end(); it++)
    {
        std::cout << "for: " << *it << std::endl;
    }

    float val = 1002;
    it = std::find(list.begin(), list.end(), val);

    // Check if the element was found
    if (it != list.end())
    {
        // Element found
        // std::cout << "Value " << *it << " found." << std::endl;
        std::cout << "Value " << *it << " found at position: " << std::distance(list.begin(), it) << std::endl;
    }
    else
    {
        std::cout << "not found\n";
    }
}