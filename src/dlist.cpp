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
    if (is_empty())
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
 * @brief Checks if the list is empty.
 *
 * @tparam T The type of data stored in the list.
 * @return true if the list is empty, false otherwise.
 */
template <typename T> bool dlist<T>::is_empty()
{
    return head == nullptr || tail == nullptr;
}

/**
 * @brief Checks if the list contains only one element.
 *
 * @tparam T The type of data stored in the list.
 * @return true if the list contains only one element, false otherwise.
 */
template <typename T> bool dlist<T>::only_element()
{
    return head == tail;
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
    if (!is_empty())
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
    if (is_empty())
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

/**
 * @brief Inserts a new node with the specified data at the appropriate position in the list.
 *
 * This function inserts a new node with the specified data at the appropriate position in the list.
 * If the list is not empty, the data is inserted at the tail of the list.
 * If the list is empty, the data is inserted at the head of the list.
 *
 * @tparam T The type of data stored in the list.
 * @param data The data to be stored in the new node.
 */
template <typename T> void dlist<T>::insert(T data)
{
    if (!is_empty())
    {
        insert_tail(data);
    }
    else
    {
        insert_head(data);
    }
}

/**
 * @brief Removes the node at the head of the list.
 *
 * If the list is not empty, the head pointer is updated to point to the next node.
 * If the removed node was the only node in the list, both head and tail pointers are set to nullptr.
 *
 * @tparam T The type of data stored in the list.
 */
template <typename T> void dlist<T>::remove_head()
{
    if (is_empty())
        return;

    Node<T> *tmp = head;

    if (head->next != nullptr)
    {
        head = tmp->next;

        delete tmp;
    }
    else
    {
        head = nullptr;
        tail = nullptr;

        delete tmp;
    }
}

/**
 * @brief Removes the node at the tail of the list.
 *
 * If the list is not empty and contains more than one element,
 * the tail pointer is updated to point to the previous node.
 *
 * @tparam T The type of data stored in the list.
 */
template <typename T> void dlist<T>::remove_tail()
{
    if (is_empty())
        return;

    // If there's only one element, remove it by calling remove_head
    if (only_element())
    {
        remove_head();
        return;
    }

    Node<T> *tmp = tail;

    tail = tmp->prev;
    tail->next = nullptr;

    delete tmp;
}

/**
 * @brief Reverses the order of nodes in the list.
 *
 * If the list is not empty and contains more than one element,
 * this function reverses the order of nodes in the list.
 *
 * @tparam T The type of data stored in the list.
 */
template <typename T> void dlist<T>::reverse()
{
    if (is_empty() || only_element())
        return;

    // swap tail's next and prev
    tail->next = tail->prev;
    tail->prev = nullptr;

    // beginning from the tail
    Node<T> *current = tail->next;

    while (current != nullptr)
    {
        Node<T> *prev = current->prev;
        current->prev = current->next;
        current->next = prev;

        current = current->next;
    }

    // swap head and tail
    Node<T> *tmp_head = head;
    head = tail;
    tail = tmp_head;
}

} // namespace cxc

#endif