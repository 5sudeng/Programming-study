#include <iostream>
#include<vector>
#include<vector>
using namespace std;


class Solution {
public:
    double averageWaitingTime(vector<vector<int>>& customers) {


        /* 
        [[a,b], [c, d]]
        end time of ith customer : e_i
        wating time of (i+1)th customer :  w_(i+1)
        
        e0 = a_0+t_0 초기값
        w0 = t_0

        if arrival_(i+1) > e_i 
            -> e_(i+1) = arrival_(i+1) + time(i+1)
            -> w_(i+1) = time_(i+1)
        else: 
            -> e_(i+1) = e_i + time_(i+1)
            -> w_(i+1) = (e_i-arrival_(i+1)) + time_(i+1)
        */

       int n = customers.size();
       vector<int>ends(n,0);
       vector<int>waits(n,0);
       ends[0] = customers[0][0] + customers[0][1];
       waits[0] = customers[0][1];


       for (int i = 0; i<n-1; ++i){


        if (customers[i+1][0] > ends[i]){
            ends[i+1] = customers[i+1][0] + customers[i+1][1];
            waits[i+1] = customers[i+1][1];
        }
        else{ // 도착시간보다 늦게 끝났을 때
            ends[i+1] = ends[i]+ customers[i+1][1];
            waits[i+1] = (ends[i] - customers[i+1][0]) + customers[i+1][1];
        }
     
       }

       //average
       double s = 0;
       for (int i = 0; i<n; ++i){
        s +=(double) waits[i];
       }
       return s/n;


    }
};


int main()

{
    vector<vector<int>> customers = {{1,2},{2,5},{4,3}};

    Solution sol;
    cout<<sol.averageWaitingTime(customers)<<endl;

}