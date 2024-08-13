#include <stdio.h>
#include <stdlib.h>

struct Graph {
    int V;
    int** adj;
};

struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;

    graph->adj = (int**)malloc(V * sizeof(int*));
    for (int i = 0; i < V; i++) {
        graph->adj[i] = (int*)malloc(V * sizeof(int));
        for (int j = 0; j < V; j++) {
            graph->adj[i][j] = 0;
        }
    }
    return graph;
}

void addEdge(struct Graph* graph, int src, int dest) {
    graph->adj[src][dest] = 1;
    graph->adj[dest][src] = 1; // If undirected graph
}

void BFS(struct Graph* graph, int start, int* visited) {
    int* queue = (int*)malloc(graph->V * sizeof(int));
    int front = 0, rear = 0;

    visited[start] = 1;
    queue[rear++] = start;

    while (front != rear) {
        int v = queue[front++];
        printf("%d ", v);

        for (int i = 0; i < graph->V; i++) {
            if (graph->adj[v][i] == 1 && !visited[i]) {
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }
    free(queue);
}

void BFS_Disconnected(struct Graph* graph) {
    int* visited = (int*)calloc(graph->V, sizeof(int));

    for (int i = 0; i < graph->V; i++) {
        if (!visited[i]) {
            BFS(graph, i, visited);
            printf("\n");
        }
    }

    free(visited);
}

void DFS(struct Graph* graph, int v, int* visited) {
    visited[v] = 1;
    printf("%d ", v);

    for (int i = 0; i < graph->V; i++) {
        if (graph->adj[v][i] == 1 && !visited[i]) {
            DFS(graph, i, visited);
        }
    }
}

void DFS_Disconnected(struct Graph* graph) {
    int* visited = (int*)calloc(graph->V, sizeof(int));

    for (int i = 0; i < graph->V; i++) {
        if (!visited[i]) {
            DFS(graph, i, visited);
            printf("\n");
        }
    }

    free(visited);
}

int main() {
    int V = 10;
    struct Graph* graph = createGraph(V);

    // First component
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);

    // Second component
    addEdge(graph, 5, 6);
    addEdge(graph, 5, 7);

    // Third component
    addEdge(graph, 8, 9);

    printf("BFS for disconnected graph:\n");
    BFS_Disconnected(graph);

    printf("DFS for disconnected graph:\n");
    DFS_Disconnected(graph);

    // Free memory
    for (int i = 0; i < V; i++) {
        free(graph->adj[i]);
    }
    free(graph->adj);
    free(graph);

    return 0;
}