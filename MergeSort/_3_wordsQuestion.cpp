#include <iostream>
#include <vector>
#include <ctime>
#include <limits.h>
#include <algorithm>
#include "../matplotlibcpp.h"

namespace plt = matplotlibcpp;
using namespace std;

void merge(vector<string> &elements, int left, int mid, int right)
{
    vector<string> left_Sub_Array, right_Sub_Array;
    int no_Left_Sub, no_Right_Sub, i, index_Left_SA, index_Right_SA, index_Full_Array;
    no_Left_Sub = mid - left + 1;
    no_Right_Sub = right - mid;
    for (i = 0; i < no_Left_Sub; i++)
        left_Sub_Array.push_back(elements[left + i]);
    left_Sub_Array.push_back("zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz"); // INT_MAX_STRING
    for (i = 0; i < no_Right_Sub; i++)
        right_Sub_Array.push_back(elements[mid + i + 1]);
    right_Sub_Array.push_back("zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz");
    index_Left_SA = 0;
    index_Right_SA = 0;
    for (index_Full_Array = left; index_Full_Array <= right; index_Full_Array++)
    {
        if (left_Sub_Array[index_Left_SA] <= right_Sub_Array[index_Right_SA])
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

void mergeSort(vector<string> &elements, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSort(elements, left, mid);
        mergeSort(elements, mid + 1, right);
        merge(elements, left, mid, right);
    }
}

vector<double> timeComplexityAnalyzer(vector<vector<string>> elements)
{
    vector<double> timeTaken;

    for (int a = 0; a < elements.size(); a++)
    {
        clock_t tStart = clock();

        mergeSort(elements[a], 0, elements[a].size() - 1);

        timeTaken.push_back((double)(clock() - tStart) / CLOCKS_PER_SEC);
    }
    return timeTaken;
}

int main()
{
    // take some random example words and sort them, display the result
    vector<string> words = {"A", "AAb", "a", "banana", "apple", "Orange", "Grape", "pear", "Pineapple", "watermelon"};
    // sort the words
    mergeSort(words, 0, words.size() - 1);
    // display the sorted words
    for (int i = 0; i < words.size(); i++)
    {
        cout << words[i] << endl;
    }

    vector<double> number_of_data = {20000, 40000, 60000, 80000, 100000}; // tunable parameters

    // create nested vectors which contain data in ascending, descending, random of lengths 5000, 10000, 15000, 20000 depending on the number_of_data array
    vector<vector<string>> data;
    vector<string> ascending;
    vector<string> descending;
    vector<string> randomm;
    for (int i = 0; i < number_of_data.size(); i++)
    {
        ascending.clear();
        descending.clear();
        randomm.clear();
        for (int j = 0; j < number_of_data[i]; j++)
        {
            ascending.push_back("word" + to_string(j));
            descending.push_back("word" + to_string((int)number_of_data[i] - j));
            randomm.push_back("word" + to_string(rand() % (int)number_of_data[i]));
        }
        data.push_back(ascending);
        data.push_back(descending);
        data.push_back(randomm);
    }

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
    plt::figure(1);
    plt::plot(number_of_data, ascendingTimes);
    plt::title("Time taken (ascending)");
    plt::xlabel("Number of data");
    plt::ylabel("Time (sec)");
    plt::show();

    plt::figure(2);
    plt::plot(number_of_data, descendingTimes);
    plt::title("Time taken (descending)");
    plt::xlabel("Number of data");
    plt::ylabel("Time (sec)");
    plt::show();

    plt::figure(3);
    plt::plot(number_of_data, randomTimes);
    plt::title("Time taken (random)");
    plt::xlabel("Number of data");
    plt::ylabel("Time (sec)");
    plt::show();

    return 0;
}
