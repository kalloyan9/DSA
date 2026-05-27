#include <stdexcept>
#include "MyStackLListImpl.hpp"

namespace MyStackLListImpl
{
    MyStackLListImpl::MyStackLListImpl() : tos(0)
    {
    }

    MyStackLListImpl::~MyStackLListImpl()
    {
    }

    void MyStackLListImpl::push(const int &data)
    {
        llist.push_back(data);
        ++tos;
    }

    int MyStackLListImpl::pop()
    {
        if (isEmpty())
        {
            throw std::out_of_range("Stack is empty");
        }
        --tos;
        int data = llist[tos];
        llist.pop_back();
        return data;
    }

    int MyStackLListImpl::peek() const
    {
        if (isEmpty())
        {
            throw std::out_of_range("Stack is empty");
        }
        return llist[tos - 1];
    }

    bool MyStackLListImpl::isEmpty() const
    {
        return 0 == tos;
    }

    bool MyStackLListImpl::isFull() const
    {
        return false; // A linked list implementation of a stack is never full
    }
} // MyStackLListImpl
