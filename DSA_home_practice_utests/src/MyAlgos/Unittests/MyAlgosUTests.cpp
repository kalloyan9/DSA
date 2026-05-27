#include <cassert>
#include <iostream>

#include "MyAlgos.hpp"
#include "MyAlgosUTests.hpp"

namespace MyAlgos
{
    template <typename T>
    bool isSorted(T *arr, const size_t size)
    {
        for (size_t i = 1; i < size; ++i)
        {
            if (arr[i - 1] > arr[i])
            {
                return false;
            }
        }
        return true;
    }

    int MyAlgosUTests()
    {
        {
            int values[] = {1, 2, 3, 4, 5};
            assert(MyBinarySearch(values, 5, 1) == 0);
            assert(MyBinarySearch(values, 5, 3) == 2);
            assert(MyBinarySearch(values, 5, 5) == 4);
            assert(MyBinarySearch(values, 5, 6) == -1);
            assert(MyBinarySearchRecursive(values, 0, 4, 4) == 3);
        }

        {
            char values[] = {'a', 'b', 'c', 'd', 'e'};
            assert(MyBinarySearch(values, 5, 'a') == 0);
            assert(MyBinarySearch(values, 5, 'c') == 2);
            assert(MyBinarySearch(values, 5, 'e') == 4);
            assert(MyBinarySearch(values, 5, 'z') == -1);
            assert(MyBinarySearchRecursive(values, 0, 4, 'b') == 1);
        }

        {
            double values[] = {1.1, 2.2, 3.3, 4.4};
            assert(MyBinarySearch(values, 4, 1.1) == 0);
            assert(MyBinarySearch(values, 4, 3.3) == 2);
            assert(MyBinarySearch(values, 4, 4.4) == 3);
            assert(MyBinarySearch(values, 4, 5.5) == -1);
            assert(MyBinarySearchRecursive(values, 0, 3, 2.2) == 1);
        }

        {
            int values[] = {4, 1, 3, 2, 0};
            MySelectionSort(values, 5);
            assert(isSorted(values, 5));
        }

        {
            char values[] = {'z', 'x', 'a', 'q'};
            MyInsertionSort(values, 4);
            assert(isSorted(values, 4));
        }

        {
            double values[] = {3.14, 1.41, 2.72, 1.62};
            MyBubbleSort(values, 4);
            assert(isSorted(values, 4));
        }

        {
            int values[] = {5, 2, 8, 2, 3};
            MyQuickSort(values, 0, 4);
            assert(isSorted(values, 5));
        }

        std::cout << "MyAlgos and sort tests passed (int, char, double).\n";
        return 0;
    }
} // namespace MyAlgos
