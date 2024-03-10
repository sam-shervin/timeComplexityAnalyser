#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

// Function to perform insertion sort
void insertionSort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 1; i < n; i++)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// Merge function for merging two sorted subarrays
void merge(vector<int> &elements, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++)
        L[i] = elements[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = elements[mid + 1 + j];

    // Merge the temporary arrays back into elements[left..right]
    int i = 0;    // Initial index of first subarray
    int j = 0;    // Initial index of second subarray
    int k = left; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            elements[k] = L[i];
            i++;
        }
        else
        {
            elements[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if any
    while (i < n1)
    {
        elements[k] = L[i];
        i++;
        k++;
    }

    // No need to copy the remaining elements of R[] since they are already in elements
}

// Modified merge-sort algorithm as described
void modifiedMergeSort(vector<int> &elements, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        // Recursively divide the left subarray
        modifiedMergeSort(elements, left, mid);
        // Sort the right subarray using insertion sort
        insertionSort(elements);
        // Merge the two sorted subarrays
        merge(elements, left, mid, right);
    }
}

int main()
{
    vector<int> elements = {12, 11, 13, 5, 6, 7};
    int n = elements.size();

    // Applying modified merge sort
    modifiedMergeSort(elements, 0, n - 1);

    cout << "Sorted array using modified merge sort: ";
    for (int i = 0; i < n; i++)
    {
        cout << elements[i] << " ";
    }
    cout << endl;

    return 0;
}
