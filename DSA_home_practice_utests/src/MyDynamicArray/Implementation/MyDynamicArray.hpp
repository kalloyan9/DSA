#pragma once
#include <cstddef>

namespace MyDynamicArray
{
    template <typename T>
    struct MyDynamicArray
    {
        // shared global constants
        static const size_t growthFactor = 2;
        static const size_t initialCapacity = 8;

        // data
        T *pData;
        size_t size;
        size_t capacity;

        // methods
        void push_back(const T &_data);
        void pop_back();
        T &operator[](size_t _index);
        const T &operator[](size_t _index) const;

        // utility
        void print();
        void resize(size_t _newCapacity);
        void clear();
        void swap(MyDynamicArray &other) noexcept;

        // rule of five
        MyDynamicArray();
        MyDynamicArray(const MyDynamicArray &other);
        MyDynamicArray(MyDynamicArray &&other) noexcept;
        MyDynamicArray &operator=(const MyDynamicArray &other);
        MyDynamicArray &operator=(MyDynamicArray &&other) noexcept;
        ~MyDynamicArray();
    };
} // MyDynamicArray
