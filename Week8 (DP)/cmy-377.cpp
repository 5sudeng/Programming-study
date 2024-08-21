#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int coinCombinations(vector<int>& nums, int target) {
    vector<long long int> dp(target+1, 0);
    dp[0] = 1;
    for (int i=1; i<=target; ++i) {
        for (auto num : nums) {
            if (i-num>=0 && dp[i]<INT_MAX) { 
                dp[i] += (long long int)dp[i-num]; 
            }
        }
    }
    return dp[target];
}

int main(){
    int x = 4;
    vector<int> coins = {3,2,1};
    std::cout << coinCombinations(coins, x) << std::endl;
    return 0;
}
