#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

string longestCommonSubsequence(const string &str1, const string &str2, int &length)
{
    int m = str1.length();
    int n = str2.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= m; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (str1[i - 1] == str2[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    int i = m, j = n;
    string lcs;
    while (i > 0 && j > 0)
    {
        if (str1[i - 1] == str2[j - 1])
        {
            lcs = str1[i - 1] + lcs;
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
    length = dp[m][n];
    return lcs;
}

int main()
{
    string str1 = "ABCBDAB";
    string str2 = "BDCABB";
    int length;

    string lcs = longestCommonSubsequence(str1, str2, length);
    cout << "Longest Common Subsequence: " << lcs << endl;
    cout << "Length of LCS: " << length << endl;
    return 0;
}