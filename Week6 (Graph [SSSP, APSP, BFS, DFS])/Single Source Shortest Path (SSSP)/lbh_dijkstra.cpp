#include <iostream>
#include <vector>
#include <climits>
using namespace std;

#define V 9  // Number of vertices in the graph

// Function to find the vertex with the minimum distance value, from the set of vertices not yet included in the shortest path tree
int minDistance(vector<int>& dist, vector<bool>& sptSet) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++) {
        if (!sptSet[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

// Function to print the constructed distance array
void printSolution(vector<int>& dist) {
    cout << "Vertex \t Distance from Source\n";
    for (int i = 0; i < V; i++)
        cout << i << " \t " << dist[i] << endl;
}

// Function to print the shortest path from source to a vertex
void printPath(vector<int>& parent, int vertex) {
    if (parent[vertex] == -1) {
        cout << vertex << " ";
        return;
    }
    printPath(parent, parent[vertex]);
    cout << vertex << " ";
}

// Function to implement Dijkstra's algorithm with path reconstruction
void dijkstra(vector<vector<int>>& graph, int src) {
    vector<int> dist(V, INT_MAX);  // dist[i] will hold the shortest distance from src to i
    vector<bool> sptSet(V, false);  // sptSet[i] will be true if vertex i is included in shortest path tree
    vector<int> parent(V, -1);  // Array to store the constructed shortest path

    dist[src] = 0;  // Distance of the source vertex from itself is always 0

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet);  // Pick the minimum distance vertex from the set of vertices not yet processed
        sptSet[u] = true;  // Mark the picked vertex as processed

        // Update dist value of the adjacent vertices of the picked vertex
        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;  // Update parent to keep track of the path
            }
        }
    }

    printSolution(dist);  // Print the constructed distance array

    // Example: Print the path from source vertex 0 to vertex 8
    cout << "\nShortest path from 0 to 8: ";
    if (dist[8] != INT_MAX) {
        printPath(parent, 8);
    } else {
        cout << "No path exists.";
    }
    cout << endl;
}

int main() {
    // Graph represented as an adjacency matrix
    vector<vector<int>> graph = {
        {0, 4, 0, 0, 0, 0, 0, 8, 0},
        {4, 0, 8, 0, 0, 0, 0, 11, 0},
        {0, 8, 0, 7, 0, 4, 0, 0, 2},
        {0, 0, 7, 0, 9, 14, 0, 0, 0},
        {0, 0, 0, 9, 0, 10, 0, 0, 0},
        {0, 0, 4, 14, 10, 0, 2, 0, 0},
        {0, 0, 0, 0, 0, 2, 0, 1, 6},
        {8, 11, 0, 0, 0, 0, 1, 0, 7},
        {0, 0, 2, 0, 0, 0, 6, 7, 0}
        };
    dijkstra(graph, 0);  // Source vertex is 0

    return 0;
}