#include <iostream>
using namespace std;

void printarr(const int * const arr, size_t n)
{
        for(size_t i = 0; i < n; ++i)
                cout << arr[i] << " ";
        cout << endl;
}

size_t partition(int *arr, size_t left, size_t right)
{
        size_t pivot = arr[right];
        size_t i = left; //index of smaller element

        for (size_t j = left; j <= right; ++j){
                //if current element is smaller than or equal to pivot
                if (arr[j] <= pivot){
                        ++i;
                        std::swap(arr[i], arr[j]);
                }
        }
        std::swap(arr[i + 1], arr[right]);
        return i + 1;
}

void quickSort(int *arr, size_t left, size_t right)
{
        if (left >= right)
                return;
        
        //arr[partitionIndex] is on the right place
        int partitionIndex = partition(arr, left, right);

        //separetely sort elements before and after partitionIndex
        quickSort(arr, left, partitionIndex - 1);
        quickSort(arr, partitionIndex + 1, right);

}

int main()
{
        int arr[] = {5, 3, 1, 2, 8}; //initialization
        size_t SIZE = sizeof(arr) / sizeof(arr[0]); //formula
        printarr(arr, SIZE);
        cout << "sorting...\n";
        quickSort(arr, 0, SIZE - 1);
        printarr(arr, SIZE);

        return 0;
}