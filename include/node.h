#pragma once

namespace cxc
{

template <typename T> struct Node
{
    T data;
    Node *prev;
    Node *next;

    Node(T _data, Node *_prev = nullptr, Node *_next = nullptr) : data(_data), prev(_prev), next(_next)
    {
    }

    static Node *create(T data, Node *prev = nullptr, Node *next = nullptr)
    {
        return new Node(data, prev, next);
    }
};

} // namespace cxc