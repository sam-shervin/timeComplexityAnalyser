#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;
struct details
{
    int low;
    int high;
    int sum;
};
details find_maximum_subarray(const vector<int> &a)
{
    int n = a.size();
    int max_left = 0, max_right = 0, max_sum = INT_MIN, curr_sum = 0;
    for (int i = 0; i < n; i++)
    {
        curr_sum = a[i];
        if (curr_sum > max_sum)
        {
            max_sum = curr_sum;
            max_left = i;
            max_right = i;
        }
        for (int j = i + 1; j < n; j++)
        {
            curr_sum += a[j];
            if (curr_sum > max_sum)
            {
                max_sum = curr_sum;
                max_left = i;
                max_right = j;
            }
        }
    }
    details d;
    d.low = max_left;
    d.high = max_right;
    d.sum = max_sum;
    return d;
}
int main()
{
    int arr[] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    vector<int> A(arr, arr + n);
    details ans = find_maximum_subarray(A);
    cout << "The Starting index is: " << ans.low << endl;
    cout << "The End index is: " << ans.high << endl;
    cout << "The Maximum Sum of Subarray is: " << ans.sum << endl;
    return 0;
}