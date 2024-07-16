#include <iostream>
#include<vector>
#include<vector>
using namespace std;

//같은 로직이지만 더 쉽게 쓴 코드



class Solution {
public:
    double averageWaitingTime(vector<vector<int>>& customers) {



       int n = customers.size();
       vector<int>ends(n,0);
       ends[0] = customers[0][0] + customers[0][1];
       double waits = customers[0][1]; // 초기값



       for (int i = 0; i<n-1; ++i){

       // max(ends[i] , customers[i+1][0]) : start time
        ends[i+1] = max(ends[i] , customers[i+1][0]) + customers[i+1][1];
        waits += (max(ends[i] , customers[i+1][0])- customers[i+1][0]) + customers[i+1][1];
       }
    }
};


int main()

{
    vector<vector<int>> customers = {{1,2},{2,5},{4,3}};

    Solution sol;
    cout<<sol.averageWaitingTime(customers)<<endl;

}