#include <cassert>
#include <iostream>
#include <string>
#include "MyDynamicArray.hpp"

namespace MyDynamicArray
{
    int MyDynamicArrayUTests()
    {
        {
            MyDynamicArray<int> array;
            assert(array.size == 0);
            assert(array.pData != nullptr);
            assert(array.capacity == MyDynamicArray<int>::initialCapacity);

            array.push_back(10);
            assert(array.size == 1);
            assert(array[0] == 10);
            assert(array.capacity == MyDynamicArray<int>::initialCapacity);

            array.push_back(20);
            array.push_back(30);
            assert(array.size == 3);
            assert(array[2] == 30);
        }

        {
            MyDynamicArray<int> array;
            const int count = 20;
            for (int i = 0; i < count; ++i)
            {
                array.push_back(i);
            }

            assert(array.size == count);
            for (int i = 0; i < count; ++i)
            {
                assert(array[i] == i);
            }
            assert(array.capacity >= array.size);
            assert(array.capacity == 32);
        }

        {
            MyDynamicArray<int> array;
            array.push_back(1);
            array.push_back(2);
            array.push_back(3);

            array.pop_back();
            assert(array.size == 2);
            assert(array[0] == 1);
            assert(array[1] == 2);

            array.pop_back();
            array.pop_back();
            assert(array.size == 0);
            assert(array.capacity == MyDynamicArray<int>::initialCapacity);

            array.pop_back();
            assert(array.size == 0);
        }

        {
            MyDynamicArray<int> source;
            source.push_back(100);
            source.push_back(200);

            MyDynamicArray<int> copy = source;
            assert(copy.size == 2);
            assert(copy[0] == 100);
            assert(copy[1] == 200);
            source[0] = 101;
            assert(copy[0] == 100);
        }

        {
            MyDynamicArray<int> a;
            a.push_back(5);
            MyDynamicArray<int> b;
            b = a;
            assert(b.size == a.size);
            assert(b[0] == 5);
        }

        // Tests for char type
        {
            MyDynamicArray<char> charArray;
            assert(charArray.size == 0);
            assert(charArray.pData != nullptr);
            assert(charArray.capacity == MyDynamicArray<char>::initialCapacity);

            charArray.push_back('a');
            charArray.push_back('b');
            charArray.push_back('c');
            assert(charArray.size == 3);
            assert(charArray[0] == 'a');
            assert(charArray[1] == 'b');
            assert(charArray[2] == 'c');

            charArray.pop_back();
            assert(charArray.size == 2);
            assert(charArray[1] == 'b');
        }

        // Tests for std::string type
        {
            MyDynamicArray<std::string> stringArray;
            assert(stringArray.size == 0);

            stringArray.push_back("hello");
            stringArray.push_back("world");
            stringArray.push_back("cpp");
            assert(stringArray.size == 3);
            assert(stringArray[0] == "hello");
            assert(stringArray[1] == "world");
            assert(stringArray[2] == "cpp");

            stringArray.pop_back();
            assert(stringArray.size == 2);
            assert(stringArray[1] == "world");

            // Test copy constructor for strings
            MyDynamicArray<std::string> stringCopy = stringArray;
            assert(stringCopy.size == 2);
            assert(stringCopy[0] == "hello");
        }

        std::cout << "MyDynamicArray tests passed (int, char, string).\n";
        return 0;
    }
} // namespace MyDynamicArray
