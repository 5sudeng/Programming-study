#include <iostream>
#include <vector>

using namespace std;

int minPathSum(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();
    vector<vector<int>> dp(m, vector<int>(n, 0));
    for (int i=0; i<m; ++i) {
        for (int j=0; j<n; ++j) {
            if (i==0 && j==0) { dp[i][j] = grid[0][0]; }
            else if (i>0 && j==0) { dp[i][j] = grid[i][j] + dp[i-1][j]; }
            else if (i==0 && j>0) { dp[i][j] = grid[i][j] + dp[i][j-1]; }
            else {
                dp[i][j] = grid[i][j] + min(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    return dp[m-1][n-1];
}


int main() {

    // Test case 1
    vector<vector<int>> grid1 = {{1, 3, 1}, {1, 5, 1}, {4, 2, 1}};
    int result1 = minPathSum(grid1);
    cout << "The minimum path sum for grid1 is: " << result1 << endl;

    // Test case 2
    vector<vector<int>> grid2 = {{1, 2, 3}, {4, 5, 6}};
    int result2 = minPathSum(grid2);
    cout << "The minimum path sum for grid2 is: " << result2 << endl;

    // Additional test cases
    vector<vector<int>> grid3 = {{7, 3, 8, 1}, {5, 6, 7, 2}, {3, 4, 5, 6}, {2, 3, 1, 4}};
    int result3 = minPathSum(grid3);
    cout << "The minimum path sum for grid3 is: " << result3 << endl;

    return 0;
}