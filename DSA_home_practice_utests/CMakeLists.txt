cmake_minimum_required(VERSION 3.10)
project(cpp_test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRCS
    src/main/main.cpp
    src/MyLinkedList/Implementation/MyLinkedList.cpp
    src/MyLinkedList/Unittests/MyLinkedListUTests.cpp
    src/MyDynamicArray/Implementation/MyDynamicArray.cpp
    src/MyDynamicArray/Unittests/MyDynamicArrayUTests.cpp
    src/MyStack/Implementation/MyStackArrayImpl/MyStackArrayImpl.cpp
    src/MyStack/Implementation/MyStackArrayImpl/Unittests/MyStackArrayImplUTests.cpp
    src/MyStack/Implementation/MyStackLListImpl/MyStackLListImpl.cpp
    src/MyStack/Implementation/MyStackLListImpl/Unittests/MyStackLListImplUTests.cpp
    src/MyAlgos/Unittests/MyAlgosUTests.cpp
    src/MyGraph/Unittests/MyGraphEdgeListUTests.cpp
    src/MyGraph/Unittests/MyGraphAdjacencyListUTests.cpp
    src/MyGraph/Unittests/MyGraphAdjacencyMatrixUTests.cpp
    src/MyTrees/MyGenericTree/Unittests/MyGenericTreeUTests.cpp
)

add_executable(main ${SRCS})

target_include_directories(main PRIVATE
    src/MyLinkedList/Implementation
    src/MyDynamicArray/Implementation
    src/MyStack/Implementation/MyStackArrayImpl
    src/MyStack/Implementation/MyStackLListImpl
    src/MyLinkedList/Unittests
    src/MyDynamicArray/Unittests
    src/MyStack/Implementation/MyStackArrayImpl/Unittests
    src/MyStack/Implementation/MyStackLListImpl/Unittests
    src/MyAlgos
    src/MyAlgos/Unittests
    src/MyGraph/Implementation
    src/MyGraph/Unittests
    src/MyTrees/MyGenericTree/Implementation
    src/MyTrees/MyGenericTree/Unittests
)

target_compile_options(main PRIVATE -Wall -Wextra -g)
