#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int longestCommonSubsequenceLength(const string &s1, const string &s2)
{
    int m = s1.length();
    int n = s2.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= m; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (s1[i - 1] == s2[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    return dp[m][n];
}

int main()
{
    string s1 = "mango";
    string s2 = "bat";

    int length = longestCommonSubsequenceLength(s1, s2);
    cout << "Length of Longest Common Subsequence: " << length << endl;

    return 0;
}