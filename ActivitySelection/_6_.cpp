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

// Comparator function for the priority queue based on start times (reverse order)
struct CompareStartTime
{
    bool operator()(const Activity &a, const Activity &b)
    {
        return a.start > b.start;
    }
};

// Greedy activity selector function using priority queue
vector<Activity> selectActivities(vector<Activity> &activities)
{
    vector<Activity> selectedActivities;

    // Sort activities based on start times
    sort(activities.begin(), activities.end(), [](const Activity &a, const Activity &b)
         { return a.start > b.start; });

    // Priority queue to select activities based on start times (reverse order)
    priority_queue<Activity, vector<Activity>, CompareStartTime> pq;

    for (const auto &activity : activities)
    {
        // Check if the activity is compatible with the previously selected activities
        if (pq.empty() || activity.finish <= pq.top().start)
        {
            selectedActivities.push_back(activity);
            pq.push(activity);
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

    cout << "Selected activities using iterative greedy algorithm with priority queue: " << endl;
    for (const auto &activity : selectedActivities)
    {
        cout << "(" << activity.start << ", " << activity.finish << ")" << endl;
    }

    return 0;
}
