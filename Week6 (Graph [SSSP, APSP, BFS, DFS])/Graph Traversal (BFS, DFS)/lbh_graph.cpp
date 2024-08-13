#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Graph {
    int V;    // Number of vertices
    vector<vector<int>> adj; // Adjacency list

public:
    Graph(int V);
    void addEdge(int v, int w); // Add an edge from v to w
    void BFS(int start, vector<bool>& visited); // BFS traversal from start vertex
    void BFS_Disconnected();     // BFS that handles disconnected components
    void DFS(int v, vector<bool>& visited); // Utility function for DFS
    void DFS_Disconnected();     // DFS that handles disconnected components
};

Graph::Graph(int V) {
    this->V = V;
    adj.resize(V);
}

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w);
    adj[w].push_back(v); // If undirected graph
}

void Graph::BFS(int start, vector<bool>& visited) {
    queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int v = q.front();
        cout << v << " ";
        q.pop();

        for (int i : adj[v]) {
            if (!visited[i]) {
                visited[i] = true;
                q.push(i);
            }
        }
    }
}

void Graph::BFS_Disconnected() {
    vector<bool> visited(V, false);

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            BFS(i, visited);
            cout << endl;
        }
    }
}

void Graph::DFS(int v, vector<bool>& visited) {
    visited[v] = true;
    cout << v << " ";

    for (int i : adj[v]) {
        if (!visited[i]) {
            DFS(i, visited);
        }
    }
}

void Graph::DFS_Disconnected() {
    vector<bool> visited(V, false);

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            DFS(i, visited);
            cout << endl;
        }
    }
}

int main() {
    Graph g(10);  // Create a graph with 10 vertices

    // First component
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(3, 4);

    // Second component
    g.addEdge(5, 6);
    g.addEdge(5, 7);

    // Third component
    g.addEdge(8, 9);

    cout << "BFS for disconnected graph:\n";
    g.BFS_Disconnected();

    cout << "DFS for disconnected graph:\n";
    g.DFS_Disconnected();

    return 0;
}