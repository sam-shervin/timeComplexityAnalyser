#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// Structure to represent an activity
struct Activity
{
    int start, finish;
};

// Comparator function for the priority queue based on finish times
struct CompareFinishTime
{
    bool operator()(const Activity &a, const Activity &b)
    {
        return a.finish > b.finish;
    }
};

// Recursive greedy activity selector function using priority queue
void selectActivities(vector<Activity> &activities, priority_queue<Activity, vector<Activity>, CompareFinishTime> &selectedActivities, int k)
{
    // Base case: If no more activities remaining
    if (k == activities.size())
        return;

    // Select the activity that finishes first
    selectedActivities.push(activities[k]);

    // Find the next activity that starts after the current one finishes
    int m = k + 1;
    while (m < activities.size() && activities[m].start < activities[k].finish)
    {
        m++;
    }

    // Recur for the remaining activities
    selectActivities(activities, selectedActivities, m);
}

int main()
{
    vector<Activity> activities = {{1, 2}, {3, 4}, {0, 6}, {5, 7}, {8, 9}, {5, 9}};
    priority_queue<Activity, vector<Activity>, CompareFinishTime> selectedActivities;

    cout << "Activities: " << endl;
    for (const auto &activity : activities)
    {
        cout << "(" << activity.start << ", " << activity.finish << ")" << endl;
    }

    // Sort activities based on finish times
    sort(activities.begin(), activities.end(), [](const Activity &a, const Activity &b)
         { return a.finish < b.finish; });

    // Call the recursive greedy algorithm
    selectActivities(activities, selectedActivities, 0);

    cout << "Selected activities using recursive greedy algorithm with priority queue: " << endl;
    while (!selectedActivities.empty())
    {
        Activity act = selectedActivities.top();
        selectedActivities.pop();
        cout << "(" << act.start << ", " << act.finish << ")" << endl;
    }

    return 0;
}
