#include <iostream>

#include "MyLinkedListUTests.hpp"
#include "MyDynamicArrayUTests.hpp"
#include "MyStackArrayImplUTests.hpp"
#include "MyStackLListImplUTests.hpp"

#include "MyAlgos.hpp"
#include "MyAlgosUTests.hpp"
#include "MyGraphEdgeListUTests.hpp"
#include "MyGraphAdjacencyListUTests.hpp"
#include "MyGraphAdjacencyMatrixUTests.hpp"
#include "MyGenericTreeUTests.hpp"
#include "MyBSTUTests.hpp"

int main()
{
    MyLinkedList::MyLinkedListUTests();
    MyDynamicArray::MyDynamicArrayUTests();
    MyStackArrayImpl::MyStackArrayImplUTests();
    MyStackLListImpl::MyStackLListImplUTests();
    MyAlgos::MyAlgosUTests();
    MyGraph::MyGraphEdgeListUTests();
    MyGraph::MyGraphAdjacencyListUTests();
    MyGraph::MyGraphAdjacencyMatrixUTests();
    MyTrees::MyGenericTreeUTests();
    MyTrees::MyBSTUTests();
    return 0;
}
