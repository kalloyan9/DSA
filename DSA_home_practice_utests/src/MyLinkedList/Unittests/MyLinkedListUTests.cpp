#include <cassert>
#include <iostream>
#include "MyLinkedList.hpp" // or better: move MyLinkedList/Node to header and include that

namespace MyLinkedList
{
    int MyLinkedListUTests()
    {
        {
            MyLinkedList list;
            assert(list.size == 0);
            assert(list.pHead == nullptr);

            list.push_back(10);
            assert(list.size == 1);
            assert(list.pHead != nullptr);
            assert(list.pHead->data == 10);
            assert(list.pHead->pNext == nullptr);

            list.push_back(20);
            assert(list.size == 2);
            assert(list.pHead->data == 10);
            assert(list.pHead->pNext != nullptr);
            assert(list.pHead->pNext->data == 20);
            assert(list.pHead->pNext->pNext == nullptr);

            list.push_back(30);
            assert(list.size == 3);
            assert(list.pHead->pNext->pNext->data == 30);
        }

        {
            MyLinkedList list;
            list.push_back(1);
            list.push_back(2);
            list.push_back(3);

            list.pop_back();
            assert(list.size == 2);
            assert(list.pHead != nullptr);
            assert(list.pHead->data == 1);
            assert(list.pHead->pNext != nullptr);
            assert(list.pHead->pNext->data == 2);
            assert(list.pHead->pNext->pNext == nullptr);

            list.pop_back();
            assert(list.size == 1);
            assert(list.pHead->data == 1);
            assert(list.pHead->pNext == nullptr);

            list.pop_back();
            assert(list.size == 0);
            assert(list.pHead == nullptr);

            // pop from empty list must not crash or change state
            list.pop_back();
            assert(list.size == 0);
            assert(list.pHead == nullptr);
        }

        {
            MyLinkedList list;
            for (int i = 0; i < 50; ++i)
                list.push_back(i);

            assert(list.size == 50);
            list.pop_back();
            assert(list.size == 49);
            assert(list.pHead->data == 0);
            assert(list.pHead->pNext->pNext->pNext->pNext->data == 4);

            for (int i = 0; i < 49; ++i)
                list.pop_back();

            assert(list.size == 0);
            assert(list.pHead == nullptr);
        }

        std::cout << "All simple tests passed.\n";
        return 0;
    }
} // namespace MyLinkedList
