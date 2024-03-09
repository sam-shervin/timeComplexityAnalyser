#include <iostream>
#include <vector>
#include <ctime>
#include <limits.h>

using namespace std;

// Structure to represent a 2D point
struct Point
{
    int x, y;
};

void merge(vector<int> &elements, int left, int mid, int right)
{
    vector<int> left_Sub_Array, right_Sub_Array;
    int no_Left_Sub, no_Right_Sub, i, index_Left_SA, index_Right_SA, index_Full_Array;
    no_Left_Sub = mid - left + 1;
    no_Right_Sub = right - mid;
    for (i = 0; i < no_Left_Sub; i++)
        left_Sub_Array.push_back(elements[left + i]);
    left_Sub_Array.push_back(INT_MAX);
    for (i = 0; i < no_Right_Sub; i++)
        right_Sub_Array.push_back(elements[mid + i + 1]);
    right_Sub_Array.push_back(INT_MAX);
    index_Left_SA = 0;
    index_Right_SA = 0;
    for (index_Full_Array = left; index_Full_Array <= right; index_Full_Array++)
    {
        if (left_Sub_Array[index_Left_SA] < right_Sub_Array[index_Right_SA])
        {
            elements[index_Full_Array] = left_Sub_Array[index_Left_SA];
            index_Left_SA++;
        }
        else
        {
            elements[index_Full_Array] = right_Sub_Array[index_Right_SA];
            index_Right_SA++;
        }
    }
}
void mergesort(vector<int> &elements, int left, int right)
{
    int mid;
    if (left == right)
        return;
    mid = (left + right) / 2;
    mergesort(elements, left, mid);
    mergesort(elements, mid + 1, right);
    merge(elements, left, mid, right);
}

// Function to compute t(n) and sort points based on specified criteria
double computeTime(vector<Point> &points, function<bool(const Point &, const Point &)> comparator)
{
    clock_t startTime = clock();
    mergeSort(points, 0, points.size() - 1, comparator);
    clock_t endTime = clock();

    return double(endTime - startTime) / CLOCKS_PER_SEC;
}

int main()
{
    vector<Point> points = {{3, 4}, {1, 2}, {5, 6}, {8, 1}, {7, 5}, {2, 9}};
    double tX, tY, tXY;

    // Sorting based on x coordinate
    tX = computeTime(points, [](const Point &a, const Point &b)
                     { return a.x <= b.x; });
    cout << "Sorted points based on x coordinate: ";
    for (const auto &point : points)
    {
        cout << "(" << point.x << ", " << point.y << ") ";
    }
    cout << endl;
    cout << "Time taken to sort based on x coordinate: " << tX << " seconds\n";

    // Sorting based on y coordinate
    tY = computeTime(points, [](const Point &a, const Point &b)
                     { return a.y <= b.y; });
    cout << "Sorted points based on y coordinate: ";
    for (const auto &point : points)
    {
        cout << "(" << point.x << ", " << point.y << ") ";
    }
    cout << endl;
    cout << "Time taken to sort based on y coordinate: " << tY << " seconds\n";

    // Sorting based on (x + y) / 2 coordinate
    tXY = computeTime(points, [](const Point &a, const Point &b)
                      { return (a.x + a.y) / 2.0 <= (b.x + b.y) / 2.0; });
    cout << "Sorted points based on (x + y) / 2 coordinate: ";
    for (const auto &point : points)
    {
        cout << "(" << point.x << ", " << point.y << ") ";
    }
    cout << endl;
    cout << "Time taken to sort based on (x + y) / 2 coordinate: " << tXY << " seconds\n";

    return 0;
}
