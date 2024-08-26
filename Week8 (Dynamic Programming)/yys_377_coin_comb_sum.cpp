#include <iostream>
#include <vector>
#include <climits>
using namespace std;




/*
Given an array of distinct integers nums and a target integer target, 
return the number of possible combinations that add up to target.
The test cases are generated so that the answer can fit in a 32-bit integer.

nums = {1,2,3}, target = 4
(1, 1, 1, 1) 
(1, 1, 2)
(1, 2, 1)
(1, 3)
(2, 1, 1)
(2, 2)
(3, 1)

dp_i : i를 만들기 위한 조합 수
for coin 
    dp_i +=dp_(i-c)

    i-c가 0이라면 그냥 더하기 1
*/


class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        
        
        // vector<int>dp(target+1, 0);
        vector<long long>dp(target+1, 0);
        dp[0] = 1;

        for(int i =1 ; i<= target; ++i){
            for(int j = 0; j<nums.size();++j){

                if (i-nums[j] >=0){
                    dp[i] =(dp[i] + dp[i-nums[j]])%INT_MAX;
                }
                
            }
        }
        return dp[target];

    }
};




int main(){

    Solution sol;
    vector<int> nums = {1,2,3};
    int target =4;
    cout<<sol.combinationSum4(nums, target)<<endl;
    return 0;
}