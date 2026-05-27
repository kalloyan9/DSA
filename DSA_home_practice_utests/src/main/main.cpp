#include <iostream>

#include "MyLinkedListUTests.hpp"
#include "MyDynamicArrayUTests.hpp"
#include "MyStackArrayImplUTests.hpp"
#include "MyStackLListImplUTests.hpp"

#include "MyAlgos.hpp"
#include "MyAlgosUTests.hpp"

int main()
{
    MyLinkedList::MyLinkedListUTests();
    MyDynamicArray::MyDynamicArrayUTests();
    MyStackArrayImpl::MyStackArrayImplUTests();
    MyStackLListImpl::MyStackLListImplUTests();
    MyAlgos::MyAlgosUTests();
    return 0;
}
