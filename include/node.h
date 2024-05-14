#pragma once

namespace cxc
{

template <typename T> struct Node
{
    T data;
    Node *prev;
    Node *next;

    Node(T _data, Node *_prev, Node *_next) : data(_data), prev(_prev), next(_next)
    {
    }

    static Node *create(T data, Node *prev, Node *next)
    {
        return new Node(data, prev, next);
    }
};

} // namespace cxc