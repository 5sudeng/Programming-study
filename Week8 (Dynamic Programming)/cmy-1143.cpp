#include <iostream>
#include <string>
#include <vector>

using namespace std;

int longestCommonSubsequence(string text1, string text2) {
        int m = text1.size(), n = text2.size();
        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));

        for (int i=1; i<=m; ++i) {
            for (int j=1; j<=n; ++j) {
                if (text1[i-1] == text2[j-1]) {
                    dp[i][j] = dp[i-1][j-1] + 1;
                } else {
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }
        return dp[m][n];
    }


int main() {

    // Test case 1
    string text1_1 = "abcde";
    string text2_1 = "ace";
    int result1 = longestCommonSubsequence(text1_1, text2_1);
    cout << "The length of the longest common subsequence for \"" << text1_1 << "\" and \"" << text2_1 << "\" is: " << result1 << endl;

    // Test case 2
    string text1_2 = "abc";
    string text2_2 = "abc";
    int result2 = longestCommonSubsequence(text1_2, text2_2);
    cout << "The length of the longest common subsequence for \"" << text1_2 << "\" and \"" << text2_2 << "\" is: " << result2 << endl;

    // Test case 3
    string text1_3 = "abc";
    string text2_3 = "def";
    int result3 = longestCommonSubsequence(text1_3, text2_3);
    cout << "The length of the longest common subsequence for \"" << text1_3 << "\" and \"" << text2_3 << "\" is: " << result3 << endl;

    return 0;
}
