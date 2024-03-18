#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct LCSResult
{
    int length;
    string sequence;
};

LCSResult longestCommonSubsequence(const string &s1, const string &s2)
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
    string lcs;
    int i = m, j = n;
    while (i > 0 && j > 0)
    {
        if (s1[i - 1] == s2[j - 1])
        {
            lcs = s1[i - 1] + lcs;
            --i;
            --j;
        }
        else if (dp[i - 1][j] > dp[i][j - 1])
        {
            --i;
        }
        else
        {
            --j;
        }
    }
    LCSResult result;
    result.length = dp[m][n];
    result.sequence = lcs;
    return result;
}

int main()
{
    string s1 = "apple";
    string s2 = "ball";
    LCSResult result = longestCommonSubsequence(s1, s2);
    cout << "Length of Longest Common Subsequence: " << result.length << endl;
    cout << "Longest Common Subsequence: " << result.sequence << endl;
    return 0;
}