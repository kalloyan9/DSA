#include <iostream>

#include "MyLinkedListUTests.hpp"
#include "MyDynamicArrayUTests.hpp"
#include "MyStackArrayImplUTests.hpp"
#include "MyStackLListImplUTests.hpp"

int main()
{
    MyLinkedList::MyLinkedListUTests();
    MyDynamicArray::MyDynamicArrayUTests();
    MyStackArrayImpl::MyStackArrayImplUTests();
    MyStackLListImpl::MyStackLListImplUTests();
    return 0;
}