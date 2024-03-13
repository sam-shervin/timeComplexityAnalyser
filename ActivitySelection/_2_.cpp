// Given a set 'S' of 'n' activities, implement the iterative
// greedy algorithm to select a subset of activities from S by
// selecting the task that finishes first.

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

// Iterative greedy activity selector function
vector<Activity> selectActivities(vector<Activity> &activities)
{
    vector<Activity> selectedActivities;

    // Sort activities based on finish times
    sort(activities.begin(), activities.end(), activityCompare);

    selectedActivities.push_back(activities[0]); // Select the first activity

    // Iterate through the remaining activities
    for (int i = 1; i < activities.size(); ++i)
    {
        // If the current activity starts after the finish time of the last selected activity, select it
        if (activities[i].start >= selectedActivities.back().finish)
        {
            selectedActivities.push_back(activities[i]);
        }
    }

    return selectedActivities;
}

int main()
{
    vector<Activity> activities = {{1, 2}, {3, 4}, {0, 6}, {5, 7}, {8, 9}, {5, 9}};

    cout << "Activities: " << endl;
    for (const auto &activity : activities)
    {
        cout << "(" << activity.start << ", " << activity.finish << ")" << endl;
    }

    vector<Activity> selectedActivities = selectActivities(activities);

    cout << "Selected activities using iterative greedy algorithm: " << endl;
    for (const auto &activity : selectedActivities)
    {
        cout << "(" << activity.start << ", " << activity.finish << ")" << endl;
    }

    return 0;
}
