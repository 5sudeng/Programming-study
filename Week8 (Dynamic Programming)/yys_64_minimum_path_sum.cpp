#include <iostream>
#include <vector>
using namespace std;



/*
Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right, 
which minimizes the sum of all numbers along its path/

Note: You can only move either down or right at any point in time.

최단 경로 찾기 문제? with weighted -> single source shortest path problem : Dijkstra's or Bellman Ford

grid = [[1,3,1],[1,5,1],[4,2,1]]
output = 7
*/

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        
        /*
        dp_ij = ij 위치까지 갔을 때의 최소 값.
        */

        int n = grid.size();
        int m = grid[0].size();

        vector<vector<int>> dp(n, vector<int>(m,0));

        for (int i =0; i<n; ++i){//행
            for (int j= 0; j<m; ++j){//열

                if (i == 0 && j == 0){
                    dp[i][j] =grid[i][j];
                }
                else{
                //해당 위치 도달하는데 든 최소 비용 값
                // 전 단계에서 오른쪽으로 왔는지 아래로 내려왔는지 판단.
                    if (j==0){
                        dp[i][j] =grid[i][j] + dp[i-1][j];
                    }

                    else if (i == 0){
                        dp[i][j]  = grid[i][j] + dp[i][j-1];
                    }
                    else{
                        dp[i][j] = grid[i][j] + min(dp[i-1][j], dp[i][j-1]);
                    }

                    
                }
       
            }
       }
       return dp[n-1][m-1];
       
    }
};


int main(){

    vector<vector<int>> grid = {{1,3,1},{1,5,1},{4,2,1}};
    Solution sol;
    cout<<sol.minPathSum(grid)<<endl;

    return 0;
}