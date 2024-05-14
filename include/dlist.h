#ifndef DLIST_H
#define DLIST_H

#include "node.h"

#include <iostream>

namespace cxc
{

template <typename T> struct dlist
{
  private:
    Node<T> *head = nullptr;
    Node<T> *tail = nullptr;

    template <typename... Args> void _init(T first, Args... rest);

    void _init();

  public:
    template <typename... Args> dlist(Args... args);

    //  inseration / deletion

    void insert_head(T data);
    void insert_head(Node<T> *new_head);

    void insert_tail(T data);
    void insert_tail(Node<T> *new_tail);

    void insert(T data);
    void insert_at(int position, T data);

    void remove_head();
    void remove_tail();
    void remove_at();
    void clear();

    // accessors
    T get_head();
    T get_tail();
    void size();
    bool is_empty();

    // search
    void find();
    void count();

    // misc
    void reverse();

    void print();
};

} // namespace cxc

#include "../src/dlist.cpp"

#endif
