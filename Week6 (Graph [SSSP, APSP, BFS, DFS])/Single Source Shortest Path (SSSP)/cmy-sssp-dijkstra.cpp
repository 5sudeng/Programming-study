#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

void dijkstra(int source, const vector<vector<pair<int, int>>>& graph, vector<int>& distance) {
    int n = graph.size();
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    fill(distance.begin(), distance.end(), INT_MAX);
    distance[source] = 0;
    pq.push({0, source});
    
    while (!pq.empty()) {
        int u = pq.top().second;
        int dist_u = pq.top().first;
        pq.pop();
        
        if (dist_u > distance[u]) continue;
        
        for (const auto& edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;
            
            if (distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                pq.push({distance[v], v});
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m; // Number of nodes and edges
    
    vector<vector<pair<int, int>>> graph(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w; // Edge from u to v with weight w
        graph[u].push_back({v, w});
    }
    
    vector<int> distance(n + 1);
    dijkstra(1, graph, distance);
    
    for (int i = 1; i <= n; ++i) {
        if (distance[i] == INT_MAX) {
            cout << "INF ";
        } else {
            cout << distance[i] << " ";
        }
    }
    cout << endl;
    
    return 0;
}
