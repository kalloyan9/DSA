#include <cstddef>
#include <utility>

namespace MyAlgos
{
    template <typename T>
    int MyBinarySearch(T *arr, const size_t size, const T &target)
    {
        int left = 0;
        int right = size - 1;

        while (left <= right)
        {
            int mid = left + (right / 2 - left / 2); // To avoid potential overflow

            if (target == arr[mid])
            {
                return mid; // Target found at index mid
            }
            else if (target > arr[mid])
            {
                left = mid + 1; // Search in the right half
            }
            else // target < arr[mid]
            {
                right = mid - 1; // Search in the left half
            }
        }

        return -1; // Target not found in the array
    }

    template <typename T>
    int MyBinarySearchRecursive(T *arr, const size_t left, const size_t right, const T &target)
    {
        if (left > right)
        {
            return -1; // Base case: target not found
        }

        int mid = left + (right / 2 - left / 2); // To avoid potential overflow
        if (target == arr[mid])
        {
            return mid; // Target found at index mid
        }
        else if (target > arr[mid])
        {
            return MyBinarySearchRecursive(arr, mid + 1, right, target); // Search in the right half
        }
        else // target < arr[mid]
        {
            return MyBinarySearchRecursive(arr, left, mid - 1, target); // Search in the left half
        }
    }

    template <typename T>
    // Selection sort is not stable in general because it swaps the minimum item into place,
    // which can change the relative order of equal elements.
    void MySelectionSort(T *arr, const size_t size)
    {
        for (size_t i = 0; i < size - 1; ++i)
        {
            size_t minIndex = i;
            for (size_t j = i + 1; j < size; ++j)
            {
                if (arr[j] < arr[minIndex])
                {
                    minIndex = j; // Update the index of the minimum element
                }
            }
            std::swap(arr[i], arr[minIndex]); // Swap the found minimum element with the first element
        }
    }

    template <typename T>
    // Insertion sort is stable because equal elements are moved by shifting and inserted without
    // changing their original relative order.
    void MyInsertionSort(T *arr, const size_t size)
    {
        for (size_t i = 1; i < size; ++i)
        {
            T key = arr[i];
            int j = i - 1;

            // Move elements of arr[0..i-1], that are greater than key,
            // to one position ahead of their current position
            while (j >= 0 && arr[j] > key)
            {
                arr[j + 1] = arr[j];
                --j;
            }
            arr[j + 1] = key; // Place the key in its correct position
        }
    }

    template <typename T>
    // Bubble sort is stable because it only swaps adjacent elements when they are out of order,
    // preserving the relative order of equal elements.
    void MyBubbleSort(T *arr, const size_t size)
    {
        for (size_t i = 0; i < size - 1; ++i)
        {
            for (size_t j = 0; j < size - i - 1; ++j)
            {
                if (arr[j] > arr[j + 1])
                {
                    std::swap(arr[j], arr[j + 1]); // Swap if the element found is greater than the next element
                }
            }
        }
    }

    template <typename T>
    int Partition(T *arr, const size_t left, const size_t right)
    {
        T pivot = arr[right]; // Choosing the last element as pivot
        int i = left - 1; // Index of smaller element

        for (size_t j = left; j < right; ++j)
        {
            if (arr[j] < pivot)
            {
                ++i; // Increment index of smaller element
                std::swap(arr[i], arr[j]); // Swap the elements
            }
        }
        std::swap(arr[i + 1], arr[right]); // Swap the pivot element with the element at index i + 1
        return i + 1; // Return the partitioning index
    }

    template <typename T>
    // Quick sort is not stable in general because the partitioning step can reorder equal elements.
    void MyQuickSort(T *arr, const size_t left, const size_t right)
    {
        if (left < right)
        {
            int pivotIndex = Partition(arr, left, right); // Partition the array

            if (pivotIndex > 0)
            {
                MyQuickSort(arr, left, pivotIndex - 1); // Recursively sort elements before partition
            }
            MyQuickSort(arr, pivotIndex + 1, right); // Recursively sort elements after partition
        }
    }

}
