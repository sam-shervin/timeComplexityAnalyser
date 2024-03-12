#include <iostream>
#include <vector>
#include <ctime>
#include "../matplotlibcpp.h"
namespace plt = matplotlibcpp;
using namespace std;

int partition(vector<int> &arr, int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int> &arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

vector<double> timeComplexityAnalyzer(vector<vector<int>> elements)
{
    vector<double> timeTaken;

    for (int i = 0; i < elements.size(); i++)
    {
        clock_t tStart = clock();

        quickSort(elements[i], 0, elements[i].size() - 1);

        timeTaken.push_back((double)(clock() - tStart) / CLOCKS_PER_SEC);
    }
    return timeTaken;
}

int main()
{

    vector<double> number_of_data = {5000, 10000, 15000, 20000, 25000}; // tunable parameters

    // create nested vectors which contain data in ascending, descending, random of lengths 5000, 10000, 15000, 20000 depending on the number_of_data array
    vector<vector<int>> data;
    vector<int> ascending;
    vector<int> descending;
    vector<int> randomm;
    for (int i = 0; i < number_of_data.size(); i++)
    {
        ascending.clear();
        descending.clear();
        randomm.clear();
        for (int j = 0; j < number_of_data[i]; j++)
        {
            ascending.push_back(j);
            descending.push_back(number_of_data[i] - j);
            randomm.push_back(rand() % (int)number_of_data[i]);
        }
        data.push_back(ascending);
        data.push_back(descending);
        data.push_back(randomm);
    }

    // print the data vector
    /*
    for (int i = 0; i < data.size(); i++)
    {
        for (int j = 0; j < data[i].size(); j++)
        {
            cout << data[i][j] << " ";
        }
        cout << endl;
    }
    */

    // call timeComplexityAnalyzer function
    vector<double> timeTaken = timeComplexityAnalyzer(data);

    // print the time taken
    for (int i = 0; i < timeTaken.size(); i++)
    {
        if (i % 3 == 0)
            cout << endl;
        string dataType = (i % 3 == 0) ? "ascending" : (i % 3 == 1) ? "descending"
                                                                    : "random";
        cout << "Time taken by " << dataType << "_" << number_of_data[i / 3] << " is: " << timeTaken[i] << "sec\n";
    }

    std::vector<double> ascendingTimes, descendingTimes, randomTimes;
    for (int i = 0; i < timeTaken.size(); i++)
    {
        if (i % 3 == 0)
            ascendingTimes.push_back(timeTaken[i]);
        else if (i % 3 == 1)
            descendingTimes.push_back(timeTaken[i]);
        else
            randomTimes.push_back(timeTaken[i]);
    }
    // Plot the times
    plt::plot(number_of_data, ascendingTimes, {{"label", "ascending"}});
    plt::plot(number_of_data, descendingTimes, {{"label", "descending"}});
    plt::plot(number_of_data, randomTimes, {{"label", "random"}});

    plt::title("Time taken");
    plt::xlabel("Number of data");
    plt::ylabel("Time (sec)");

    plt::legend();
    plt::show();
}