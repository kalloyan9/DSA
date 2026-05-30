#include <iostream>
#include <utility>
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

    namespace
    {
        Node *cloneList(const Node *head)
        {
            if (head == nullptr)
            {
                return nullptr;
            }

            Node *newHead = new Node(head->data);
            Node *newTail = newHead;
            const Node *current = head->pNext;
            while (current != nullptr)
            {
                newTail->pNext = new Node(current->data);
                newTail = newTail->pNext;
                current = current->pNext;
            }
            return newHead;
        }

        void destroyList(Node *head)
        {
            while (head != nullptr)
            {
                Node *next = head->pNext;
                delete head;
                head = next;
            }
        }
    }

    MyLinkedList::MyLinkedList(const MyLinkedList &other)
        : pHead(cloneList(other.pHead)), size(other.size)
    {
    }

    MyLinkedList::MyLinkedList(MyLinkedList &&other) noexcept
        : pHead(other.pHead), size(other.size)
    {
        other.pHead = nullptr;
        other.size = 0;
    }

    MyLinkedList &MyLinkedList::operator=(const MyLinkedList &other)
    {
        if (this != &other)
        {
            MyLinkedList temp(other);
            swap(temp);
        }
        return *this;
    }

    MyLinkedList &MyLinkedList::operator=(MyLinkedList &&other) noexcept
    {
        if (this != &other)
        {
            destroyList(pHead);
            pHead = other.pHead;
            size = other.size;
            other.pHead = nullptr;
            other.size = 0;
        }
        return *this;
    }

    void MyLinkedList::swap(MyLinkedList &other) noexcept
    {
        std::swap(pHead, other.pHead);
        std::swap(size, other.size);
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
