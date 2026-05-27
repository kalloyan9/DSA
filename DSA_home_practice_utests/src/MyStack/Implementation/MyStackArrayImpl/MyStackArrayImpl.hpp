#pragma once
#include "MyDynamicArray.hpp"

namespace MyStackArrayImpl
{
    template <typename T>
    struct MyStackArrayImpl
    {
        // data
        MyDynamicArray::MyDynamicArray<T> arr;
        size_t tos;

        // methods
        void push(const T &data);
        T pop();
        T peek() const;
        bool isEmpty() const;
        bool isFull() const;

        // rule of five
        MyStackArrayImpl();
        MyStackArrayImpl(const MyStackArrayImpl &other) = default;
        MyStackArrayImpl(MyStackArrayImpl &&other) noexcept = default;
        MyStackArrayImpl &operator=(const MyStackArrayImpl &other) = default;
        MyStackArrayImpl &operator=(MyStackArrayImpl &&other) noexcept = default;
        ~MyStackArrayImpl();
    };
}
