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

    template <typename... Args> void init(T first, Args... rest);

    void init();

    void init_events();

    void increase();

    void decrease();

    void empty();

  public:
    cxc::EventListener<Events> _events{};
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
    const size_t &size();
    bool is_empty();

    // search

    // misc
    void reverse();
    bool only_element();

    void print();

    /**
     * @brief Iterator class for traversing a doubly linked list.
     *
     * This class provides an iterator for traversing a doubly linked list.
     * It can be used with both STL and custom functions to iterate over the elements
     * of the list.
     *
     * @tparam T The type of elements stored in the doubly linked list.
     */
    struct Iterator
    {
        // Define iterator traits required by standard library algorithms (important!)
        using pointer = T *;
        using value_type = T;
        using reference = T &;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::bidirectional_iterator_tag;

      private:
        Node<T> *current;

      public:
        Iterator(Node<T> *ptr) : current(ptr)
        {
        }

        // Iterator()
        // {
        // }

        T &operator*() const
        {
            return current->data;
        }

        Iterator &operator++()
        {
            current = current->next;
            return *this;
        }

        Iterator &operator--()
        {
            current = current->prev;
            return *this;
        }

        Iterator operator++(int)
        {
            Iterator tmp = *this;
            current = current->next;
            return tmp;
        }

        Iterator operator--(int)
        {
            Iterator tmp = *this;
            current = current->prev;
            return tmp;
        }

        bool operator==(const Iterator &other) const
        {
            return current == other.current;
        }

        bool operator!=(const Iterator &other) const
        {
            return current != other.current;
        }
    };

    /**
     * @brief Returns an iterator pointing to the first element in the list.
     *
     * @return An iterator pointing to the first element in the list.
     */
    Iterator begin()
    {
        return Iterator(head);
    }

    /**
     * @brief Returns an iterator referring to the past-the-end element in the list.
     *
     * @return An iterator referring to the past-the-end element in the list.
     */
    Iterator end()
    {
        return Iterator(nullptr);
    }
};

} // namespace cxc

#include "../src/dlist.cpp"

#endif
