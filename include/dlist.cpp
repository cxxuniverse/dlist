#ifndef CXC_DLIST_TPP
#define CXC_DLIST_TPP

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
    init_events();
    init(args...);
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
template <typename T> template <typename... Args> void dlist<T>::init(T first, Args... rest)
{
    if (is_empty())
    {
        Node<T> *new_node = new Node<T>(first, nullptr, nullptr);
        head = new_node;
        tail = new_node;

        _events.trigger(Events::INCREASE_COUNT);
    }
    else
    {
        Node<T> *new_node = new Node<T>(first, tail, nullptr);
        tail->next = new_node;
        tail = new_node;

        _events.trigger(Events::INCREASE_COUNT);
    }

    init(rest...);
}

/**
 * @brief Base case for the recursive initialization of the dlist.
 *
 * @tparam T The type of elements stored in the list.
 */
template <typename T> void dlist<T>::init()
{
}

/**
 * @brief Increases the count of elements in the list.
 *
 * @tparam T The type of elements stored in the list.
 */
template <typename T> void dlist<T>::increase()
{
    m_size++;
}

/**
 * @brief Decreases the count of elements in the list.
 *
 * @tparam T The type of elements stored in the list.
 */
template <typename T> void dlist<T>::decrease()
{
    m_size--;
}

/**
 * @brief Sets the count of elements to zero.
 *
 * @tparam T The type of elements stored in the list.
 */
template <typename T> void dlist<T>::empty()
{
    m_size = 0;
}

/**
 * @brief Initializes event handlers for the doubly linked list.
 *
 * @tparam T The type of elements stored in the list.
 */
template <typename T> void dlist<T>::init_events()
{
    _events.add(Events::EMPTY_COUNT, [this]() { empty(); });
    _events.add(Events::INCREASE_COUNT, [this]() { increase(); });
    _events.add(Events::DECREASE_COUNT, [this]() { decrease(); });
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
 * @brief Inserts a new node with the specified data at the head of the doubly
 * linked list.
 *
 * This function inserts a new node with the specified data at the head of the
 * doubly linked list.
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

        _events.trigger(Events::INCREASE_COUNT);
    }
    else
    {
        node->prev = nullptr;
        node->next = nullptr;
        head = node;
        tail = node;

        _events.trigger(Events::INCREASE_COUNT);
    }
}

/**
 * @brief Inserts a new node with the specified data at the tail of the doubly
 * linked list.
 *
 * This function inserts a new node with the specified data at the tail of the
 * doubly linked list.
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

    _events.trigger(Events::INCREASE_COUNT);
}

/**
 * @brief Clears the doubly linked list.
 *
 * This function deallocates memory for all nodes in the doubly linked list
 * and sets the head and tail pointers to nullptr, effectively clearing the
 * list.
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

    _events.trigger(Events::EMPTY_COUNT);
}

/**
 * @brief Inserts a new node with the specified data at the appropriate position
 * in the list.
 *
 * This function inserts a new node with the specified data at the appropriate
 * position in the list. If the list is not empty, the data is inserted at the
 * tail of the list. If the list is empty, the data is inserted at the head of
 * the list.
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
 * If the list is not empty, the head pointer is updated to point to the next
 * node. If the removed node was the only node in the list, both head and tail
 * pointers are set to nullptr.
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

        _events.trigger(Events::DECREASE_COUNT);
    }
    else
    {
        head = nullptr;
        tail = nullptr;

        delete tmp;

        _events.trigger(Events::DECREASE_COUNT);
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

    _events.trigger(Events::DECREASE_COUNT);
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

/**
 * @brief Returns a reference to the data stored in the head node of the list.
 *
 * If the list is empty, a std::runtime_error is thrown.
 *
 * @tparam T The type of data stored in the list.
 * @return A const reference to the data stored in the head node.
 * @throws std::runtime_error if the list is empty.
 */
template <typename T> const T &dlist<T>::get_head()
{
    if (is_empty())
        throw std::runtime_error("List is empty, cannot access head data.");

    return head->data;
}

/**
 * @brief Returns a reference to the data stored in the tail node of the list.
 *
 * If the list is empty, a std::runtime_error is thrown.
 *
 * @tparam T The type of data stored in the list.
 * @return A const reference to the data stored in the tail node.
 * @throws std::runtime_error if the list is empty.
 */
template <typename T> const T &dlist<T>::get_tail()
{
    if (is_empty())
        throw std::runtime_error("List is empty, cannot access tail data.");

    return tail->data;
}

/**
 * @brief Returns the size of the doubly linked list.
 *
 * @tparam T The type of elements stored in the list.
 * @return The size of the list.
 */
template <typename T> const size_t &dlist<T>::size()
{
    return m_size;
}

/**
 * @brief Checks if a given position is valid within the doubly linked list.
 *
 * @param position The position to check.
 * @return true if the position is valid, false otherwise.
 */
template <typename T> bool dlist<T>::valid_position(size_t position)
{
    return position <= m_size - 1;
}

/**
 * @brief Removes the node at the specified position from the doubly linked
 * list.
 *
 * @param position The position of the node to remove.
 * @throws std::runtime_error if the position is invalid or out of bounds.
 */
template <typename T> void dlist<T>::remove_at(size_t position)
{
    if (!valid_position(position))
        throw std::runtime_error("[Error] remove_at: position is invalid or out of bounds.");

    if (position == 0)
    {
        remove_head();
    }
    else if (position == m_size - 1)
    {
        remove_tail();
    }
    else
    {
        auto prev = std::next(begin(), position - 1);
        auto current = std::next(begin(), position);
        auto next = std::next(begin(), position + 1);

        prev.get_addr()->next = next.get_addr();
        next.get_addr()->prev = prev.get_addr();

        delete current.get_addr();

        _events.trigger(Events::DECREASE_COUNT);
    }
}

/**
 * @brief Inserts a new node with the given data at the specified position in
 * the doubly linked list.
 *
 * @param position The position at which to insert the new node.
 * @param data The data to be stored in the new node.
 * @throws std::runtime_error if the position is invalid or out of bounds.
 */
template <typename T> void dlist<T>::insert_at(size_t position, T data)
{
    if (!valid_position(position))
        throw std::runtime_error("[Error] insert_at: position is invalid or out of bounds.");

    if (position == 0)
    {
        insert_head(data);
    }
    else if (position == m_size - 1)
    {
        insert_tail(data);
    }
    else
    {
        auto prev = std::next(begin(), position - 1);
        auto next = std::next(begin(), position);

        Node<T> *new_node = new Node(data, prev.get_addr(), next.get_addr());

        prev.get_addr()->next = new_node;
        next.get_addr()->prev = new_node;

        _events.trigger(Events::INCREASE_COUNT);
    }
}

/**
 * @brief Get the node at the specified position.
 *
 * @param position The position of the node to retrieve.
 * @return Node<T>* Pointer to the node at the specified position.
 * @throw std::runtime_error If the position is invalid or out of bounds.
 */
template <typename T> Node<T> *dlist<T>::get_node(size_t position)
{
    if (!valid_position(position))
        throw std::runtime_error("[Error] get: position is invalid or out of bounds.");

    if (position == 0)
    {
        return head;
    }
    else if (position == m_size - 1)
    {
        return tail;
    }
    else
    {
        auto it = std::next(begin(), position);
        return it.get_addr();
    }
}

/**
 * @brief Change the data of the node at the specified position.
 *
 * @param position The position of the node to change.
 * @param data The new data for the node.
 * @throw std::runtime_error If the position is invalid or out of bounds.
 */
template <typename T> void dlist<T>::change(size_t position, T data)
{
    if (!valid_position(position))
        throw std::runtime_error("[Error] change: position is invalid or out of bounds");

    auto it = std::next(begin(), position);

    it.get_addr()->data = data;
}

} // namespace cxc

#endif