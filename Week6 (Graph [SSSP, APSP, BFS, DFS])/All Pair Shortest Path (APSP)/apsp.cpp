#include <iostream>
#include <vector>
#include <climits>

using namespace std;

#define INF 1000000000

void extendSP(const vector<vector<int>>& L_r_1, const vector<vector<int>>& W, vector<vector<int>>& L_r, int n) {
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            for (int k=0; k<n; k++) {
                if (L_r[i][j] > L_r_1[i][k] + W[k][j]) {
                    L_r[i][j] = L_r_1[i][k] + W[k][j];
                }
            }
        }
    }
}




vector<vector<int>> slowAPSP(const vector<vector<int>>& W, const vector<vector<int>>& L_0, int n) {
    vector<vector<int>> L(n, vector<int>(n, INF));
    
    L = L_0;
    for (int r=0; r<n-1; r++) {
        vector<vector<int>> M(n, vector<int>(n, INF));
        extendSP(L, W, M, n);
        L = M;
    }

    return L;
}




vector<vector<int>> fasterAPSP(const vector<vector<int>>& W, int n) {
    vector<vector<int>> L(n, vector<int>(n, INF));

    L = W;
    int r = 1;
    while (r < n - 1) {
        vector<vector<int>> M(n, vector<int>(n, INF));
        extendSP(L, L, M, n);
        r *= 2;
        L = M;
    }

    return L;
}




int main() {
    int n = 4;
    vector<vector<int>> W = {
        {0, 3, 8, INF},
        {INF, 0, 4, 11},
        {INF, INF, 0, 7},
        {4, INF, INF, 0}
    };
    vector<vector<int>> L_0 = {
        {0, INF, INF, INF},
        {INF, 0, INF, INF},
        {INF, INF, 0, INF},
        {INF, INF, INF, 0}
    };

    vector<vector<int>> result = slowAPSP(W, L_0, n);
    cout << "[Slow] All Pairs Shortest Path matrix:\n";
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            if (result[i][j] == INF) {
                cout << "INF ";
            } else {
                cout << result[i][j] << " ";
            }
        }
        cout << endl;
    }

    result = fasterAPSP(W, n);
    cout << "\n[Faster] All Pairs Shortest Path matrix:\n";
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            if (result[i][j] == INF) {
                cout << "INF ";
            } else {
                cout << result[i][j] << " ";
            }
        }
        cout << endl;
    }

    return 0;
}