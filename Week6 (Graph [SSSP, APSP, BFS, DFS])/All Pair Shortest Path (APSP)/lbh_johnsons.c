#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define INF INT_MAX

struct Edge {
    int src, dest, weight;
};

struct Graph {
    int V, E;
    struct Edge* edges;
};

void printPath(int parent[], int vertex) {
    if (parent[vertex] == -1) {
        printf("%d ", vertex);
        return;
    }
    printPath(parent, parent[vertex]);
    printf("%d ", vertex);
}

int BellmanFord(struct Graph* graph, int vertices, int src, int dist[], int parent[]) {
    for (int i = 0; i < vertices; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }
    dist[src] = 0;

    for (int i = 1; i <= vertices - 1; i++) {
        for (int j = 0; j < graph->E; j++) {
            int u = graph->edges[j].src;
            int v = graph->edges[j].dest;
            int weight = graph->edges[j].weight;
            if (dist[u] != INF && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
            }
        }
    }

    for (int j = 0; j < graph->E; j++) {
        int u = graph->edges[j].src;
        int v = graph->edges[j].dest;
        int weight = graph->edges[j].weight;
        if (dist[u] != INF && dist[u] + weight < dist[v]) {
            printf("Graph contains a negative weight cycle\n");
            return 0;
        }
    }
    return 1;
}

void Dijkstra(int** graph, int V, int src, int dist[], int parent[]) {
    int* sptSet = (int*)calloc(V, sizeof(int));

    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        sptSet[i] = 0;
        parent[i] = -1;
    }
    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int min = INF, u = -1;

        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && dist[v] <= min) {
                min = dist[v];
                u = v;
            }
        }

        sptSet[u] = 1;

        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && graph[u][v] != INF && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    free(sptSet);
}

void Johnson(struct Graph* graph) {
    int V = graph->V;
    int new_vertex_count = V + 1;
    int original_edges_count = graph->E;
    int new_edges_count = original_edges_count + V;
    struct Edge* original_edges = graph->edges;
    struct Edge* newEdges = (struct Edge*)malloc(new_edges_count * sizeof(struct Edge));

    for (int i = 0; i < original_edges_count; i++) {
        newEdges[i] = original_edges[i];
    }
    for (int i = 0; i < V; i++) {
        newEdges[original_edges_count + i].src = V;
        newEdges[original_edges_count + i].dest = i;
        newEdges[original_edges_count + i].weight = 0;
    }

    int* dist = (int*)malloc(new_vertex_count * sizeof(int));
    int* parent = (int*)malloc(new_vertex_count * sizeof(int));
    int* h = (int*)malloc(V * sizeof(int));
    struct Graph newGraph = {new_vertex_count, new_edges_count, newEdges};

    if (!BellmanFord(&newGraph, new_vertex_count, V, dist, parent)) {
        free(newEdges);
        free(dist);
        free(parent);
        free(h);
        return;
    }

    for (int i = 0; i < V; i++) {
        h[i] = dist[i];
    }

    int** reweightedGraph = (int**)malloc(V * sizeof(int*));
    for (int i = 0; i < V; i++) {
        reweightedGraph[i] = (int*)malloc(V * sizeof(int));
        for (int j = 0; j < V; j++) {
            reweightedGraph[i][j] = INF;
        }
    }

    for (int i = 0; i < original_edges_count; i++) {
        int u = original_edges[i].src;
        int v = original_edges[i].dest;
        if (original_edges[i].weight != INF) {
            int weight = original_edges[i].weight + h[u] - h[v];
            reweightedGraph[u][v] = weight;
        }
    }

    for (int u = 0; u < V; u++) {
        Dijkstra(reweightedGraph, V, u, dist, parent);
        printf("\nShortest distances from vertex %d:\n", u);
        for (int v = 0; v < V; v++) {
            if (dist[v] != INF) {
                // Reconstruct the original distance using the h-values
                dist[v] = dist[v] + h[v] - h[u];
                printf("Distance to vertex %d is %d\n", v, dist[v]);
                printf("Path: ");
                printPath(parent, v);
                printf("\n");
            } else {
                printf("No path to vertex %d\n", v);
            }
        }
    }

    for (int i = 0; i < V; i++) {
        free(reweightedGraph[i]);
    }
    free(reweightedGraph);
    free(newEdges);
    free(dist);
    free(parent);
    free(h);
}

int main() {
    int V = 5;
    struct Graph graph = {V, 7, NULL};
    struct Edge edges[] = {
        {0, 1, -1},
        {0, 3, 2},
        {1, 2, 4},
        {1, 3, 3},
        {1, 4, 2},
        {2, 4, 1},
        {3, 4, 5}
    };
    graph.edges = edges;

    Johnson(&graph);

    return 0;
}