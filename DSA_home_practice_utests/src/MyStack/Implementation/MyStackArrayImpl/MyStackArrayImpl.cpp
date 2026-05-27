#include <stdexcept>
#include <string>
#include "MyStackArrayImpl.hpp"

namespace MyStackArrayImpl
{
    template <typename T>
    MyStackArrayImpl<T>::MyStackArrayImpl() : arr(),
                                              tos(0)
    {
    }

    template <typename T>
    MyStackArrayImpl<T>::~MyStackArrayImpl()
    {
        // Destructor for MyDynamicArray will be called automatically
    }

    template <typename T>
    void MyStackArrayImpl<T>::push(const T &data)
    {
        arr.push_back(data);
        ++tos;
    }

    template <typename T>
    T MyStackArrayImpl<T>::pop()
    {
        if (isEmpty())
        {
            throw std::out_of_range("Stack is empty");
        }
        --tos;
        T val = arr[tos];
        arr.pop_back();
        return val;
    }

    template <typename T>
    T MyStackArrayImpl<T>::peek() const
    {
        if (isEmpty())
        {
            throw std::out_of_range("Stack is empty");
        }
        return arr[tos - 1];
    }

    template <typename T>
    bool MyStackArrayImpl<T>::isEmpty() const
    {
        return (0 == tos);
    }

    template <typename T>
    bool MyStackArrayImpl<T>::isFull() const
    {
        return false; // Dynamic array can grow indefinitely
    }

    template class MyStackArrayImpl<int>;
    template class MyStackArrayImpl<char>;
    template class MyStackArrayImpl<std::string>;
}
