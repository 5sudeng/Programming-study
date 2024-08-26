#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*

Given two strings text1 and text2, return the length of their longest common subsequence. 
If there is no common subsequence, return 0.

A subsequence of a string is a new string generated from the original string with some characters (can be none) deleted without changing the relative order of the remaining characters.
상대적인 순서는 바뀌지 않은 채로, 원래의 문자열에서 일부만 제거해서 만든 문자열을 subsequence라고 부름.

For example, "ace" is a subsequence of "abcde".
A common subsequence of two strings is a subsequence that is common to both strings.


Input: text1 = "abc", text2 = "abc"
Output: 3
Explanation: The longest common subsequence is "abc" and its length is 3.


Input: text1 = "abc", text2 = "def"
Output: 0
Explanation: There is no such common subsequence, so the result is 0.


전략 :
dp_ij : 각각 i,j 번째 문자를 iterate 했을 때, common sub sequence의 최대 길이
-  한문자 추가 될 때마다, 1을 더 할지 말지 결정ㅈ
- 


*/





class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {

        int n = text1.size();
        int m = text2.size();
        vector<vector<int>> dp(n+1, vector<int>(m+1,0)); // 2d matrix

        for(int i = 1 ; i<n+1; ++i){
            for(int j = 1; j<m+1; ++j){
                if(text1[i-1] == text2[j-1]){
                    dp[i][j] = dp[i-1][j-1] +1;
                }
                else{
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }

        return dp[n][m];
        
    }
};



int main(){
    Solution sol;
    string text1 = "abcde";
    string text2 = "ace";

    cout<<sol.longestCommonSubsequence(text1, text2)<<endl;
}