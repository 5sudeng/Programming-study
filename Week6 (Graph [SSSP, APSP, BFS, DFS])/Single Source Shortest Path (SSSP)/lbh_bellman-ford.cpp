#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct Edge {
    int src, dest, weight;
};

// Function to print the final shortest distances
void printSolution(const vector<int>& dist) {
    cout << "Vertex \t Distance from Source\n";
    for (int i = 0; i < dist.size(); i++)
        cout << i << " \t " << dist[i] << endl;
}

// Function to print the shortest path from source to vertex
void printPath(const vector<int>& parent, int vertex) {
    if (parent[vertex] == -1) {
        cout << vertex << " ";
        return;
    }
    printPath(parent, parent[vertex]);
    cout << vertex << " ";
}

// Bellman-Ford algorithm with path reconstruction
void BellmanFord(const vector<Edge>& edges, int V, int E, int src) {
    vector<int> dist(V, INT_MAX);
    vector<int> parent(V, -1);

    dist[src] = 0;

    // Relax all edges |V| - 1 times
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int weight = edges[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
            }
        }
    }

    // Check for negative-weight cycles
    for (int i = 0; i < E; i++) {
        int u = edges[i].src;
        int v = edges[i].dest;
        int weight = edges[i].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            cout << "Graph contains negative weight cycle\n";
            return;
        }
    }

    printSolution(dist);

    // Example: Print the path from vertex 0 to vertex 3
    cout << "\nShortest path from 0 to 3: ";
    if (dist[3] != INT_MAX) {
        printPath(parent, 3);
    } else {
        cout << "No path exists.";
    }
    cout << endl;
}

int main() {
    vector<Edge> edges = {
        {0, 1, -1}, {0, 2, 4}, {1, 2, 3}, {1, 3, 2}, {1, 4, 2},
        {3, 2, 5}, {3, 1, 1}, {4, 3, -3}
    };

    BellmanFord(edges, 5, 8, 0);

    return 0;
}