#ifndef TEST_TPP
#define TEST_TPP

#include "../include/test.h"

namespace cxc
{

template <typename T> void Test<T>::print()
{
    std::cout << "hello from test\n";
}

} // namespace cxc

#endif