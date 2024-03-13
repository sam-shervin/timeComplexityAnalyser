// Given a set 'S' of 'n' activities, implement the recursive greedy algorithm
// to select a subset of activities from S by selecting the task that finishes first.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent an activity
struct Activity
{
    int start, finish;
};

// Comparator function to sort activities based on their finish times
bool activityCompare(const Activity &a, const Activity &b)
{
    return (a.finish < b.finish);
}

// Recursive greedy activity selector function
void selectActivities(vector<Activity> &activities, int n, int k)
{
    // Sort activities based on finish times
    sort(activities.begin(), activities.end(), activityCompare);

    // The first activity always gets selected
    cout << "Selected activity: (" << activities[k].start << ", " << activities[k].finish << ")" << endl;

    // Find the next activity that finishes after the current one starts
    int m = k + 1;
    while (m < n && activities[m].start < activities[k].finish)
    {
        m++;
    }

    // If there are more activities, select them recursively
    if (m < n)
    {
        selectActivities(activities, n, m);
    }
}

int main()
{
    vector<Activity> activities = {{1, 2}, {3, 4}, {0, 6}, {5, 7}, {8, 9}, {5, 9}};
    int n = activities.size();

    cout << "Activities: " << endl;
    for (const auto &activity : activities)
    {
        cout << "(" << activity.start << ", " << activity.finish << ")" << endl;
    }

    cout << "Selected activities using recursive greedy algorithm: " << endl;
    selectActivities(activities, n, 0);

    return 0;
}
