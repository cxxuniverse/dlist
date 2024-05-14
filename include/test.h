#pragma once

#include <iostream>

namespace cxc
{

template <typename T> struct Test
{
    T x;
    T y;

    void print();
};

} // namespace cxc

#include "../src/test.cpp"