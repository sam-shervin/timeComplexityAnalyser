#include <iostream>
#include <vector>
#include <ctime>
#include <limits.h>

using namespace std;

// Function to merge two sorted subarrays and count comparisons
int merge(vector<int> &elements, int left, int mid, int right)
{
    int comparisons = 0;
    vector<int> leftSubArray(elements.begin() + left, elements.begin() + mid + 1);
    vector<int> rightSubArray(elements.begin() + mid + 1, elements.begin() + right + 1);

    leftSubArray.push_back(INT_MAX);
    rightSubArray.push_back(INT_MAX);

    int indexLeft = 0, indexRight = 0;

    for (int i = left; i <= right; i++)
    {
        if (leftSubArray[indexLeft] <= rightSubArray[indexRight])
        {
            elements[i] = leftSubArray[indexLeft];
            indexLeft++;
        }
        else
        {
            elements[i] = rightSubArray[indexRight];
            indexRight++;
        }
        comparisons++;
    }

    return comparisons;
}

// Merge sort algorithm to sort elements and count comparisons
int mergeSort(vector<int> &elements, int left, int right)
{
    int comparisons = 0;
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        comparisons += mergeSort(elements, left, mid);
        comparisons += mergeSort(elements, mid + 1, right);
        comparisons += merge(elements, left, mid, right);
    }
    return comparisons;
}

// Function to compute the time taken for one comparison
pair<int, double> computeComparisonStatistics(int n)
{
    vector<int> elements(n);
    for (int i = 0; i < n; i++)
    {
        elements[i] = rand(); // Randomly initialize elements
    }

    clock_t startTime = clock();
    int comparisons = mergeSort(elements, 0, n - 1);
    clock_t endTime = clock();

    double timeTaken = double(endTime - startTime) / CLOCKS_PER_SEC;
    double timePerComparison = timeTaken / comparisons;

    return make_pair(comparisons, timePerComparison);
}

int main()
{
    vector<double> n = {20000, 40000, 60000, 80000, 100000, 200000, 400000, 600000, 800000, 1000000};

    for (int i = 0; i < n.size(); i++)
    {
        pair<int, double> comparisonStats = computeComparisonStatistics(n[i]);

        cout << "Number of comparisons for n = " << n[i] << ": " << comparisonStats.first << endl;
        cout << "Time taken per comparison for n = " << n[i] << ": " << comparisonStats.second << " seconds" << endl;
    }

    return 0;
}
