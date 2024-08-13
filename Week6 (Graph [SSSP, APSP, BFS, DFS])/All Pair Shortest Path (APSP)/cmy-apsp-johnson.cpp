#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

#define INF INT_MAX

void bellmanFord(int source, const vector<vector<pair<int, int>>>& graph, vector<int>& h) {
    int n = graph.size();
    fill(h.begin(), h.end(), INF);
    h[source] = 0;
    
    for (int i = 0; i < n - 1; ++i) {
        for (int u = 0; u < n; ++u) {
            for (const auto& edge : graph[u]) {
                int v = edge.first;
                int weight = edge.second;
                
                if (h[u] != INF && h[u] + weight < h[v]) {
                    h[v] = h[u] + weight;
                }
            }
        }
    }
}

void dijkstra(int source, const vector<vector<pair<int, int>>>& graph, vector<int>& dist) {
    int n = graph.size();
    fill(dist.begin(), dist.end(), INF);
    dist[source] = 0;
    
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, source});
    
    while (!pq.empty()) {
        int u = pq.top().second;
        int dist_u = pq.top().first;
        pq.pop();
        
        if (dist_u > dist[u]) continue;
        
        for (const auto& edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;
            
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
}

void johnson(const vector<vector<pair<int, int>>>& graph, vector<vector<int>>& all_distances) {
    int n = graph.size();
    vector<vector<pair<int, int>>> modified_graph = graph;
    vector<int> h(n, INF);
    
    vector<vector<pair<int, int>>> temp_graph(n + 1);
    for (int u = 0; u < n; ++u) {
        temp_graph[n].push_back({u, 0});
    }
    
    temp_graph.push_back(vector<pair<int, int>>());
    for (int u = 0; u < n; ++u) {
        for (const auto& edge : graph[u]) {
            temp_graph[u].push_back(edge);
        }
    }
    
    bellmanFord(n, temp_graph, h);
    
    for (int u = 0; u < n; ++u) {
        modified_graph[u].clear();
        for (const auto& edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;
            modified_graph[u].push_back({v, weight + h[u] - h[v]});
        }
    }
    
    all_distances.resize(n);
    for (int i = 0; i < n; ++i) {
        all_distances[i].resize(n);
        dijkstra(i, modified_graph, all_distances[i]);
        for (int j = 0; j < n; ++j) {
            if (all_distances[i][j] != INF) {
                all_distances[i][j] += h[j] - h[i];
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m; // Number of nodes and edges
    
    vector<vector<pair<int, int>>> graph(n);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w; // Edge from u to v with weight w
        graph[u - 1].push_back({v - 1, w});
    }
    
    vector<vector<int>> all_distances;
    johnson(graph, all_distances);
    
    for (const auto& distances : all_distances) {
        for (int dist : distances) {
            if (dist == INF) {
                cout << "INF ";
            } else {
                cout << dist << " ";
            }
        }
        cout << endl;
    }
    
    return 0;
}
