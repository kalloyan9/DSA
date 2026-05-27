#pragma once
#include "MyLinkedList.hpp"

namespace MyStackLListImpl
{
    struct MyStackLListImpl
    {
        // data
        MyLinkedList::MyLinkedList llist;
        size_t tos;

        // methods
        void push(const int &data);
        int pop();
        int peek() const;
        bool isEmpty() const;
        bool isFull() const;

        // rule of five
        MyStackLListImpl();
        MyStackLListImpl(const MyStackLListImpl &other) = default;
        MyStackLListImpl(MyStackLListImpl &&other) noexcept = default;
        MyStackLListImpl &operator=(const MyStackLListImpl &other) = default;
        MyStackLListImpl &operator=(MyStackLListImpl &&other) noexcept = default;
        ~MyStackLListImpl();
    };
}