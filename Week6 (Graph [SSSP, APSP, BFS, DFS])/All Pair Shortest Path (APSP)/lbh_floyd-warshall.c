#include <stdio.h>
#define INF 99999
#define V 4

// Function to print the solution matrix
void printSolution(int dist[][V]) {
    printf("The following matrix shows the shortest distances between every pair of vertices:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF)
                printf("%7s", "INF");
            else
                printf("%7d", dist[i][j]);
        }
        printf("\n");
    }
}

// Function to print the shortest path
void printPath(int pred[][V], int i, int j) {
    if (i != j)
        printPath(pred, i, pred[i][j]);
    printf("%d ", j);
}

// Floyd-Warshall algorithm with path reconstruction
void floydWarshall(int graph[][V]) {
    int dist[V][V], pred[V][V];
    int i, j, k;

    // Initialize the solution and predecessor matrices
    for (i = 0; i < V; i++) {
        for (j = 0; j < V; j++) {
            dist[i][j] = graph[i][j];
            if (graph[i][j] != INF && i != j)
                pred[i][j] = i;
            else
                pred[i][j] = -1;
        }
    }

    // Compute shortest paths
    for (k = 0; k < V; k++) {
        for (i = 0; i < V; i++) {
            for (j = 0; j < V; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    pred[i][j] = pred[k][j];
                }
            }
        }
    }

    // Print the shortest distance matrix
    printSolution(dist);

    // Example: Print the path from vertex 0 to vertex 3
    printf("\nShortest path from 0 to 3: ");
    if (pred[0][3] != -1) {
        printPath(pred, 0, 3);
    } else {
        printf("No path exists.");
    }
    printf("\n");
}

int main() {
    int graph[V][V] = { {0,   5,  INF, 10},
                        {INF, 0,   3, INF},
                        {INF, INF, 0,   1},
                        {INF, INF, INF, 0} };

    floydWarshall(graph);
    return 0;
}