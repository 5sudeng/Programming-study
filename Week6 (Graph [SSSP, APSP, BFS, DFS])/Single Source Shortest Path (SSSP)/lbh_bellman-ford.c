#include <stdio.h>
#include <limits.h>

// Define the maximum number of vertices and edges
#define MAX_VERTICES 5
#define MAX_EDGES 8

struct Edge {
    int src, dest, weight;
};

// Function to print the final shortest distances
void printSolution(int dist[], int n) {
    printf("Vertex \t Distance from Source\n");
    for (int i = 0; i < n; i++)
        printf("%d \t %d\n", i, dist[i]);
}

// Function to print the shortest path from source to a vertex
void printPath(int parent[], int vertex) {
    if (parent[vertex] == -1) {
        printf("%d ", vertex);
        return;
    }
    printPath(parent, parent[vertex]);
    printf("%d ", vertex);
}

// Bellman-Ford algorithm with path reconstruction
void BellmanFord(struct Edge edges[], int V, int E, int src) {
    int dist[MAX_VERTICES];
    int parent[MAX_VERTICES];

    // Step 1: Initialize distances and parent array
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        parent[i] = -1;
    }
    dist[src] = 0;

    // Step 2: Relax all edges |V| - 1 times
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

    // Step 3: Check for negative-weight cycles
    for (int i = 0; i < E; i++) {
        int u = edges[i].src;
        int v = edges[i].dest;
        int weight = edges[i].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            printf("Graph contains negative weight cycle\n");
            return;
        }
    }

    // Print the shortest distance matrix
    printSolution(dist, V);

    // Example: Print the path from vertex 0 to vertex 3
    printf("\nShortest path from 0 to 3: ");
    if (dist[3] != INT_MAX) {
        printPath(parent, 3);
    } else {
        printf("No path exists.");
    }
    printf("\n");
}

int main() {
    struct Edge edges[MAX_EDGES] = {
        {0, 1, -1}, {0, 2, 4}, {1, 2, 3}, {1, 3, 2}, {1, 4, 2},
        {3, 2, 5}, {3, 1, 1}, {4, 3, -3}
    };

    int V = 5; // Number of vertices
    int E = 8; // Number of edges

    BellmanFord(edges, V, E, 0);

    return 0;
}