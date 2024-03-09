#include <iostream>
#include <vector>
#include <ctime>
#include <limits.h>
#define INT_MAX 99999
using namespace std;

// Structure to represent a 2D point
struct Point
{
    int x, y;
    Point operator+(const Point &other) const
    {
        Point result;
        if (this->x == INT_MAX || other.x == INT_MAX || this->y == INT_MAX || other.y == INT_MAX)
        {
            result.x = INT_MAX;
            result.y = INT_MAX;
        }
        else
        {
            result.x = this->x + other.x;
            result.y = this->y + other.y;
        }
        return result;
    }
    Point operator/(const Point &other) const
    {
        Point result;
        if (this->x == INT_MAX || other.x == INT_MAX || this->y == INT_MAX || other.y == INT_MAX)
        {
            result.x = INT_MAX;
            result.y = INT_MAX;
        }
        else
        {
            result.x = this->x + other.x;
            result.y = this->y + other.y;
        }
        return result;
    }
};

void merge(vector<Point> &elements, int left, int mid, int right, int criteria)
{
    vector<Point> left_Sub_Array, right_Sub_Array;
    int no_Left_Sub, no_Right_Sub, i, index_Left_SA, index_Right_SA, index_Full_Array;
    no_Left_Sub = mid - left + 1;
    no_Right_Sub = right - mid;
    for (i = 0; i < no_Left_Sub; i++)
        left_Sub_Array.push_back(elements[left + i]);
    left_Sub_Array.push_back({99999, 99999});
    for (i = 0; i < no_Right_Sub; i++)
        right_Sub_Array.push_back(elements[mid + i + 1]);
    right_Sub_Array.push_back({99999, 99999});
    index_Left_SA = 0;
    index_Right_SA = 0;
    for (index_Full_Array = left; index_Full_Array <= right; index_Full_Array++)
    {
        if ((criteria == 1) ? (left_Sub_Array[index_Left_SA].x < right_Sub_Array[index_Right_SA].x) : (criteria == 2) ? (left_Sub_Array[index_Left_SA].y < right_Sub_Array[index_Right_SA].y)
                                                                                                                      : (((left_Sub_Array[index_Left_SA].x + left_Sub_Array[index_Left_SA].y) / 2.0) < ((right_Sub_Array[index_Right_SA].x + right_Sub_Array[index_Right_SA].y) / 2)))
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
void mergesort(vector<Point> &elements, int left, int right, int criteria)
{
    int mid;
    if (left == right)
        return;
    mid = (left + right) / 2;
    mergesort(elements, left, mid, criteria);
    mergesort(elements, mid + 1, right, criteria);
    merge(elements, left, mid, right, criteria);
}

// Function to compute t(n) and sort points based on specified criteria
double computeTime(vector<Point> &points, int criteria)
{
    clock_t startTime = clock();
    mergesort(points, 0, points.size() - 1, criteria);
    clock_t endTime = clock();

    return double(endTime - startTime) / CLOCKS_PER_SEC;
}

// print the sorted array
void printArray(vector<Point> &elements)
{
    for (int i = 0; i < elements.size(); i++)
    {
        cout << "(" << elements[i].x << ", " << elements[i].y << ")" << endl;
    }
}
int main()
{
    vector<Point> points = {{3, 4}, {1, 2}, {5, 6}, {8, 1}, {7, 5}, {2, 9}};
    double tX, tY, tXY;

    // Compute t(n) for sorting based on x-coordinate and print result

    tX = computeTime(points, 1);
    cout << "t(n) for sorting based on x-coordinate: " << tX << " seconds" << endl;
    printArray(points);

    // Compute t(n) for sorting based on y-coordinate and print result
    tY = computeTime(points, 2);
    cout << "t(n) for sorting based on y-coordinate: " << tY << " seconds" << endl;
    printArray(points);

    // Compute t(n) for sorting based on average of x and y coordinates and print result
    tXY = computeTime(points, 3);
    cout << "t(n) for sorting based on average of x and y coordinates: " << tXY << " seconds" << endl;
    printArray(points);

    return 0;
}
