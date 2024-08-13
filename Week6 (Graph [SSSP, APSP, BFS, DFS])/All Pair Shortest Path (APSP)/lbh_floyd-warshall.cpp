#include <iostream>
#include <vector>
#define INF 99999
#define V 4

using namespace std;

// Function to print the solution matrix
void printSolution(const vector<vector<int>>& dist) {
    cout << "The following matrix shows the shortest distances between every pair of vertices:\n";
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF)
                cout << "INF" << " ";
            else
                cout << dist[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to print the shortest path
void printPath(const vector<vector<int>>& pred, int i, int j) {
    if (i != j)
        printPath(pred, i, pred[i][j]);
    cout << j << " ";
}

// Floyd-Warshall algorithm with path reconstruction
void floydWarshall(vector<vector<int>>& graph) {
    vector<vector<int>> dist = graph;
    vector<vector<int>> pred(V, vector<int>(V, -1));

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (graph[i][j] != INF && i != j)
                pred[i][j] = i;
        }
    }

    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    pred[i][j] = pred[k][j];
                }
            }
        }
    }

    printSolution(dist);

    // Example: Print the path from vertex 0 to vertex 3
    cout << "\nShortest path from 0 to 3: ";
    if (pred[0][3] != -1) {
        printPath(pred, 0, 3);
    } else {
        cout << "No path exists.";
    }
    cout << endl;
}

int main() {
    vector<vector<int>> graph = { {0,   5,  INF, 10},
                                  {INF, 0,   3, INF},
                                  {INF, INF, 0,   1},
                                  {INF, INF, INF, 0} };

    floydWarshall(graph);
    return 0;
}