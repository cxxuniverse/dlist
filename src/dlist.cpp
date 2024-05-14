#ifndef DLIST_CPP
#define DLIST_CPP

#include "../include/dlist.h"
#include "dlist.h"

namespace cxc
{

/**
 * @brief Constructor for the dlist struct.
 *
 * @tparam T The type of elements stored in the list.
 * @tparam Args Variadic template parameters for initializing the list with
 * multiple values.
 * @param args The arguments used to initialize the list.
 */
template <typename T> template <typename... Args> dlist<T>::dlist(Args... args)
{
    _init(args...);
}

/**
 * @brief Helper function for initializing the dlist.
 *
 * This function recursively initializes the list with the given arguments.
 *
 * @tparam T The type of elements stored in the list.
 * @tparam Args Variadic template parameters for initializing the list with
 * multiple values.
 * @param first The first argument used to initialize the list.
 * @param rest The remaining arguments used to initialize the list.
 */
template <typename T> template <typename... Args> void dlist<T>::_init(T first, Args... rest)
{
    if (head == nullptr)
    {
        Node<T> *new_node = new Node<T>(first, nullptr, nullptr);
        head = new_node;
        tail = new_node;
    }
    else
    {
        Node<T> *new_node = new Node<T>(first, tail, nullptr);
        tail->next = new_node;
        tail = new_node;
    }

    _init(rest...);
}

/**
 * @brief Base case for the recursive initialization of the dlist.
 *
 * @tparam T The type of elements stored in the list.
 */
template <typename T> void dlist<T>::_init()
{
}

/**
 * @brief Function to print each element of the dlist.
 *
 * @tparam T The type of elements stored in the list.
 */
template <typename T> void dlist<T>::print()
{
    Node<T> *ptr = head;

    while (ptr != nullptr)
    {
        std::cout << ptr->data << std::endl;
        ptr = ptr->next;
    }
}

/**
 * @brief Inserts a new node with the specified data at the head of the doubly linked list.
 *
 * This function inserts a new node with the specified data at the head of the doubly linked list.
 *
 * @tparam T The type of data stored in the nodes.
 * @param data The data to be stored in the new node.
 */
template <typename T> void dlist<T>::insert_head(T data)
{
    insert_head(Node<T>::create(data, nullptr, nullptr));
}

/**
 * @brief Inserts the given node at the head of the doubly linked list.
 *
 * This function inserts the given node at the head of the doubly linked list.
 *
 * @tparam T The type of data stored in the nodes.
 * @param node Pointer to the node to be inserted.
 */
template <typename T> void dlist<T>::insert_head(Node<T> *node)
{
    if (head != nullptr)
    {
        head->prev = node;
        node->next = head;
        node->prev = nullptr;
        head = node;
        return;
    }

    node->prev = nullptr;
    node->next = nullptr;
    head = node;
    tail = node;
}

/**
 * @brief Inserts a new node with the specified data at the tail of the doubly linked list.
 *
 * This function inserts a new node with the specified data at the tail of the doubly linked list.
 *
 * @tparam T The type of data stored in the nodes.
 * @param data The data to be stored in the new node.
 */
template <typename T> void dlist<T>::insert_tail(T data)
{
    insert_tail(Node<T>::create(data, nullptr, nullptr));
}

/**
 * @brief Inserts the given node at the tail of the doubly linked list.
 *
 * This function inserts the given node at the tail of the doubly linked list.
 *
 * @tparam T The type of data stored in the nodes.
 * @param node Pointer to the node to be inserted.
 */
template <typename T> void dlist<T>::insert_tail(Node<T> *node)
{
    tail->next = node;
    node->prev = tail;
    node->next = nullptr;

    tail = node;
}

/**
 * @brief Clears the doubly linked list.
 *
 * This function deallocates memory for all nodes in the doubly linked list
 * and sets the head and tail pointers to nullptr, effectively clearing the list.
 *
 * @tparam T The type of data stored in the nodes.
 */
template <typename T> void dlist<T>::clear()
{
    if (head == nullptr)
        return;

    Node<T> *ptr = head;

    while (ptr != nullptr)
    {
        Node<T> *tmp = ptr->next;
        delete ptr;
        ptr = tmp;
    }

    head = nullptr;
    tail = nullptr;
}

} // namespace cxc

#endif