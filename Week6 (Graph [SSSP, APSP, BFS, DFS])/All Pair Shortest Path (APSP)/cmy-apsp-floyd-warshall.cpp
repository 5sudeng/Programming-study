#include <iostream>
#include <vector>
#include <climits>

using namespace std;

void floydWarshall(vector<vector<int>>& dist) {
    int n = dist.size();
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m; // Number of nodes and edges
    
    vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
    for (int i = 0; i < n; ++i) dist[i][i] = 0; // Distance to itself is 0
    
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w; // Edge from u to v with weight w
        dist[u - 1][v - 1] = w;
    }
    
    floydWarshall(dist);
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (dist[i][j] == INT_MAX) {
                cout << "INF ";
            } else {
                cout << dist[i][j] << " ";
            }
        }
        cout << endl;
    }
    
    return 0;
}
