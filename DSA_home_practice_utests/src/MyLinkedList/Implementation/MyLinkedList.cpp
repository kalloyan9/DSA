#include <iostream>
#include "MyLinkedList.hpp"

// Node implementation
Node::Node(const int &_data)
{
    this->data = _data;
    this->pNext = nullptr;
}

Node::~Node()
{
    // nothing to do, no dynamic memory allocated in Node
}

namespace MyLinkedList
{
    // MyLinkedList implementation
    MyLinkedList::MyLinkedList()
    {
        this->pHead = nullptr;
        this->size = 0;
    }

    MyLinkedList::MyLinkedList(const MyLinkedList &other)
    {
        this->pHead = nullptr;
        this->size = 0;
        Node *pCurr = other.pHead;
        Node *pTail = nullptr;
        while (nullptr != pCurr)
        {
            Node *pNew = new Node(pCurr->data);
            if (nullptr == this->pHead)
            {
                this->pHead = pNew;
            }
            else
            {
                pTail->pNext = pNew;
            }
            pTail = pNew;
            pCurr = pCurr->pNext;
            ++this->size;
        }
    }

    MyLinkedList::MyLinkedList(MyLinkedList &&other) noexcept
    {
        this->pHead = other.pHead;
        this->size = other.size;
        other.pHead = nullptr;
        other.size = 0;
    }

    MyLinkedList &MyLinkedList::operator=(const MyLinkedList &other)
    {
        if (this == &other)
            return *this;

        // clear current list
        Node *pTemp = this->pHead;
        Node *pNext = nullptr;
        while (nullptr != pTemp)
        {
            pNext = pTemp->pNext;
            delete pTemp;
            pTemp = pNext;
        }

        this->pHead = nullptr;
        this->size = 0;

        // copy
        Node *pCurr = other.pHead;
        Node *pTail = nullptr;
        while (nullptr != pCurr)
        {
            Node *pNew = new Node(pCurr->data);
            if (nullptr == this->pHead)
            {
                this->pHead = pNew;
            }
            else
            {
                pTail->pNext = pNew;
            }
            pTail = pNew;
            pCurr = pCurr->pNext;
            ++this->size;
        }

        return *this;
    }

    MyLinkedList &MyLinkedList::operator=(MyLinkedList &&other) noexcept
    {
        if (this == &other)
            return *this;

        // clear current list
        Node *pTemp = this->pHead;
        Node *pNext = nullptr;
        while (nullptr != pTemp)
        {
            pNext = pTemp->pNext;
            delete pTemp;
            pTemp = pNext;
        }

        this->pHead = other.pHead;
        this->size = other.size;
        other.pHead = nullptr;
        other.size = 0;

        return *this;
    }

    MyLinkedList::~MyLinkedList()
    {
        Node *pTemp = pHead;
        Node *pNext = nullptr;
        while (nullptr != pTemp)
        {
            pNext = pTemp->pNext;
            delete pTemp;
            pTemp = pNext;
        }
        size = 0;
    }

    void MyLinkedList::push_back(const int &_data)
    {
        Node *newNode = new Node(_data);

        if (nullptr == pHead)
        {
            pHead = newNode;
        }
        else
        {
            Node *pTemp = pHead;
            while (nullptr != pTemp->pNext)
            {
                pTemp = pTemp->pNext;
            }
            pTemp->pNext = newNode;
        }
        ++size;
    }

    void MyLinkedList::pop_back()
    {
        Node *pTemp = pHead;
        if (size > 1)
        {
            while (nullptr != pTemp->pNext->pNext)
            {
                pTemp = pTemp->pNext;
            }
            delete pTemp->pNext;
            pTemp->pNext = nullptr;
            --size;
        }
        else if (size == 1)
        {
            delete pHead;
            pHead = nullptr;
            --size;
        }
        else
        {
            // do nothing, list is empty
        }
    }

    void MyLinkedList::print()
    {
        Node *pTemp = pHead;
        while (nullptr != pTemp)
        {
            std::cout << pTemp->data << " ";
            pTemp = pTemp->pNext;
        }
        std::cout << std::endl;
    }

    const int &MyLinkedList::operator[](size_t index) const
    {
        if (index >= size)
        {
            throw std::out_of_range("Index out of range");
        }
        Node *pTemp = pHead;
        for (size_t i = 0; i < index; ++i)
        {
            pTemp = pTemp->pNext;
        }
        return pTemp->data;
    }

} // namespace MyLinkedList
