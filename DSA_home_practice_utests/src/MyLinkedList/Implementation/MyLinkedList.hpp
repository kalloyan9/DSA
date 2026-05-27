#pragma once
#include <cstddef>

struct Node
{
    // data
    int data;
    Node *pNext;

    // ctor/dtor
    Node(const int &_data);
    ~Node();
};

namespace MyLinkedList
{
    struct MyLinkedList
    {
        // data
        Node *pHead;
        size_t size;

        // methods
        void push_back(const int &_data);
        void pop_back();
        void print();
        const int &operator[](size_t index) const;

        // ctor/dtor
        // rule of five
        MyLinkedList();
        MyLinkedList(const MyLinkedList &other);
        MyLinkedList(MyLinkedList &&other) noexcept;
        MyLinkedList &operator=(const MyLinkedList &other);
        MyLinkedList &operator=(MyLinkedList &&other) noexcept;
        ~MyLinkedList();
    };
} // namespace MyLinkedList
