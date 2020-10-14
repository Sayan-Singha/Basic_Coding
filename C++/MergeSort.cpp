#include <iostream>
using namespace std;

void printArray(int *array, int n)
{
    for (int i = 0; i < n; ++i)
        cout << array[i] << " ";
    cout<<endl;
}

void merge(int *array, int low, int mid, int high)
{
    int temp[high + 1];
    int i = low;
    int j = mid + 1;
    int k = 0;

    while (i <= mid && j <= high)
    {
        if (array[i] <= array[j])
            temp[k++] = array[i++];
        else
            temp[k++] = array[j++];
    }
    while (i <= mid)
        temp[k++] = array[i++];
    while (j <= high)
        temp[k++] = array[j++];
    k--;
    while (k >= 0)
    {
        array[k + low] = temp[k];
        k--;
    }
}

void mergeSort(int *array, int low, int high)
{
    int mid;
    if (low < high)
    {
        mid = (low + high) / 2;             // Using Divide and Conquer technique
        mergeSort(array, low, mid);         // to sort the given array.
        mergeSort(array, mid + 1, high);
        merge(array, low, mid, high);       // Merge the two halves sorted.
    }
}

int main()
{
    int array[100];
    int size;
    cout << "Enter the size of array: ";
    cin >> size;
    cout << "Enter the elements of array:-" << endl;
    for(int i = 0; i < size; i++)
        cin >> array[i];

    mergeSort(array, 0, n - 1);             // Time complexity O(nlogn)

    cout << "After Merge Sort :" << std::endl;
    printArray(array, n);
    return 0;
}