#ifndef CXC_DLIST_H
#define CXC_DLIST_H

#include "events.h"
#include "node.h"

#include <iostream>

namespace cxc
{

enum class Events
{
    INCREASE_COUNT,
    DECREASE_COUNT,
    EMPTY_COUNT
};

template <typename T> struct dlist
{
  private:
    size_t m_size = 0;
    Node<T> *head = nullptr;
    Node<T> *tail = nullptr;
    cxc::EventListener<Events> _events{};

    template <typename... Args> void init(T first, Args... rest);

    void init();

    void init_events();

    void increase();

    void decrease();

    void empty();

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
    const T &get_head();
    const T &get_tail();
    void size();
    bool is_empty();

    // search
    void find();
    void count();

    // misc
    void reverse();
    bool only_element();

    void print();
};

} // namespace cxc

#include "../src/dlist.cpp"

#endif
