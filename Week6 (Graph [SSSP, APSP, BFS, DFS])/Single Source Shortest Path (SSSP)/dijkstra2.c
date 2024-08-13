#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int v;
    int w;
} Edge;

typedef struct {
    int V;
    int **adj;
    int *dist;
} Graph;

Graph* createGraph(int V) {
    Graph *graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->adj = (int**)malloc((V + 1) * sizeof(int*));  // 인접 리스트 배열 초기화
    for (int i = 0; i <= V; i++) {
        graph->adj[i] = (int*)malloc(0);  // 초기에는 크기 0의 배열
    }
    graph->dist = (int*)malloc((V + 1) * sizeof(int));  // 거리 배열 초기화
    for (int i = 0; i <= V; i++) {
        graph->dist[i] = INT_MAX;  // 무한대로 초기화
    }
    return graph;
}

void addEdge(Graph *graph, int u, int v, int w) {
    int *edge = (int*)malloc(2 * sizeof(int));
    edge[0] = v;
    edge[1] = w;
    
    int size = _msize(graph->adj[u]) / sizeof(int);
    graph->adj[u] = (int*)realloc(graph->adj[u], (size + 2) * sizeof(int));
    graph->adj[u][size] = v;
    graph->adj[u][size + 1] = w;
}

int minDistance(int *dist, int *sptSet, int V) {
    int min = INT_MAX, min_index;
    for (int v = 0; v <= V; v++) {
        if (sptSet[v] == 0 && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

void dijkstra(Graph *graph, int source) {
    int *sptSet = (int*)malloc((graph->V + 1) * sizeof(int));  // 최단 경로 트리 집합

    for (int i = 0; i <= graph->V; i++) {
        graph->dist[i] = INT_MAX;
        sptSet[i] = 0;
    }

    graph->dist[source] = 0;

    for (int count = 0; count < graph->V; count++) {
        int u = minDistance(graph->dist, sptSet, graph->V);  // 최소 거리 노드 선택
        sptSet[u] = 1;

        int size = _msize(graph->adj[u]) / sizeof(int);
        for (int i = 0; i < size; i += 2) {
            int v = graph->adj[u][i];
            int w = graph->adj[u][i + 1];
            if (!sptSet[v] && graph->dist[u] != INT_MAX && graph->dist[u] + w < graph->dist[v]) {
                graph->dist[v] = graph->dist[u] + w;
            }
        }
    }

    for (int i = 1; i <= graph->V; i++) {
        printf("Node %d: %d\n", i, graph->dist[i]);
    }

    free(sptSet);
}

int main() {
    int V = 5;
    Graph *g = createGraph(V);
    addEdge(g, 1, 2, 8);
    addEdge(g, 1, 3, 2);
    addEdge(g, 2, 4, 10);
    addEdge(g, 3, 4, 1);
    addEdge(g, 3, 5, 7);
    addEdge(g, 4, 5, 9);
    addEdge(g, 5, 3, 7);

    int source = 1;
    dijkstra(g, source);

    for (int i = 0; i <= V; i++) {
        free(g->adj[i]);
    }
    free(g->adj);
    free(g->dist);
    free(g);

    return 0;
}
