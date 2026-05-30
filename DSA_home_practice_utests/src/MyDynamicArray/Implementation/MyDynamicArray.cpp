#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#include "MyDynamicArray.hpp"

namespace MyDynamicArray
{
    template <typename T>
    MyDynamicArray<T>::MyDynamicArray()
        : pData(new T[MyDynamicArray::initialCapacity]),
          size(0),
          capacity(MyDynamicArray::initialCapacity)
    {
    }

    template <typename T>
    MyDynamicArray<T>::MyDynamicArray(const MyDynamicArray &other)
        : pData(new T[other.capacity]),
          size(other.size),
          capacity(other.capacity)
    {
        for (size_t i = 0; i < size; ++i)
        {
            pData[i] = other.pData[i];
        }
    }

    template <typename T>
    MyDynamicArray<T>::MyDynamicArray(MyDynamicArray &&other) noexcept
        : pData(other.pData),
          size(other.size),
          capacity(other.capacity)
    {
        other.pData = nullptr;
        other.size = 0;
        other.capacity = 0;
    }

    template <typename T>
    void MyDynamicArray<T>::swap(MyDynamicArray &other) noexcept
    {
        std::swap(pData, other.pData);
        std::swap(size, other.size);
        std::swap(capacity, other.capacity);
    }

    template <typename T>
    MyDynamicArray<T> &MyDynamicArray<T>::operator=(const MyDynamicArray &other)
    {
        if (this != &other)
        {
            MyDynamicArray temp(other);
            swap(temp);
        }
        return *this;
    }

    template <typename T>
    MyDynamicArray<T> &MyDynamicArray<T>::operator=(MyDynamicArray &&other) noexcept
    {
        if (this != &other)
        {
            delete[] pData;
            pData = other.pData;
            size = other.size;
            capacity = other.capacity;
            other.pData = nullptr;
            other.size = 0;
            other.capacity = 0;
        }
        return *this;
    }

    template <typename T>
    MyDynamicArray<T>::~MyDynamicArray()
    {
        delete[] pData;
        pData = nullptr;
        size = 0;
        capacity = 0;
    }

    template <typename T>
    void MyDynamicArray<T>::clear()
    {
        size = 0;
    }

    template <typename T>
    void MyDynamicArray<T>::push_back(const T &_data)
    {
        if (size >= capacity)
        {
            resize(capacity * MyDynamicArray::growthFactor);
        }

        pData[size] = _data;
        ++size;
    }

    template <typename T>
    void MyDynamicArray<T>::resize(size_t _newCapacity)
    {
        if (_newCapacity <= capacity)
        {
            return;
        }

        T *pNewData = new T[_newCapacity];
        for (size_t i = 0; i < size; ++i)
        {
            pNewData[i] = pData[i];
        }
        delete[] pData;
        pData = pNewData;
        capacity = _newCapacity;
    }

    template <typename T>
    void MyDynamicArray<T>::pop_back()
    {
        if (size > 0)
        {
            --size;
        }
    }

    template <typename T>
    T &MyDynamicArray<T>::operator[](size_t _index)
    {
        if (_index >= size)
        {
            throw std::out_of_range("Index out of range");
        }
        return pData[_index];
    }

    template <typename T>
    const T &MyDynamicArray<T>::operator[](size_t _index) const
    {
        if (_index >= size)
        {
            throw std::out_of_range("Index out of range");
        }
        return pData[_index];
    }

    template <typename T>
    void MyDynamicArray<T>::print()
    {
        std::cout << "MyDynamicArray (size: " << size << ", capacity: " << capacity << "): ";
        for (size_t i = 0; i < size; ++i)
        {
            std::cout << pData[i] << " ";
        }
        std::cout << std::endl;
    }

    template class MyDynamicArray<int>;
    template class MyDynamicArray<char>;
    template class MyDynamicArray<std::string>;
} // MyDynamicArray
