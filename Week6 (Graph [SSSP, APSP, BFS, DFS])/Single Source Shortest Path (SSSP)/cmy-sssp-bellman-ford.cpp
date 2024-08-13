#include <iostream>
#include <vector>
#include <climits>

using namespace std;

bool bellman_ford(int source, const vector<tuple<int, int, int>>& edges, vector<int>& distance) {
    int n = distance.size();
    fill(distance.begin(), distance.end(), INT_MAX);
    distance[source] = 0;
    
    for (int i = 1; i < n - 1; ++i) {
        for (const auto& edge : edges) {
            int u, v, w;
            tie(u, v, w) = edge;
            if (distance[u] != INT_MAX && distance[u] + w < distance[v]) {
                distance[v] = distance[u] + w;
            }
        }
    }
    
    for (const auto& edge : edges) {
        int u, v, w;
        tie(u, v, w) = edge;
        if (distance[u] != INT_MAX && distance[u] + w < distance[v]) {
            return false; // Negative weight cycle detected
        }
    }
    
    return true; // No negative weight cycle
}

int main() {
    int n, m;
    cin >> n >> m; // Number of nodes and edges
    
    vector<tuple<int, int, int>> edges;
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w; // Edge from u to v with weight w
        edges.emplace_back(u, v, w);
    }
    
    vector<int> distance(n + 1);
    if (bellman_ford(1, edges, distance)) {
        for (int i = 1; i <= n; ++i) {
            if (distance[i] == INT_MAX) {
                cout << "INF ";
            } else {
                cout << distance[i] << " ";
            }
        }
        cout << endl;
    } else {
        cout << "Negative weight cycle detected!" << endl;
    }
    
    return 0;
}
