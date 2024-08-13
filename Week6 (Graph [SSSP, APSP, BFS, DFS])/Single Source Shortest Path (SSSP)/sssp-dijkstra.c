#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX

typedef struct {
    int v;
    int weight;
} Edge;

typedef struct {
    Edge* edges;
    int size;
    int capacity;
} AdjacencyList;

typedef struct {
    AdjacencyList* lists;
    int numNodes;
} Graph;

typedef struct {
    int* dist;
    int* visited;
    int size;
} PriorityQueue;

void initGraph(Graph* graph, int numNodes) {
    graph->lists = malloc(sizeof(AdjacencyList) * (numNodes + 1));
    graph->numNodes = numNodes;
    for (int i = 1; i <= numNodes; i++) {
        graph->lists[i].edges = malloc(sizeof(Edge) * 10);
        graph->lists[i].size = 0;
        graph->lists[i].capacity = 10;
    }
}

void addEdge(Graph* graph, int u, int v, int weight) {
    AdjacencyList* list = &graph->lists[u];
    if (list->size >= list->capacity) {
        list->capacity *= 2;
        list->edges = realloc(list->edges, sizeof(Edge) * list->capacity);
    }
    list->edges[list->size].v = v;
    list->edges[list->size].weight = weight;
    list->size++;
}

void dijkstra(int source, Graph* graph, int* distance) {
    int n = graph->numNodes;
    PriorityQueue pq;
    pq.dist = malloc(sizeof(int) * (n + 1));
    pq.visited = malloc(sizeof(int) * (n + 1));
    pq.size = n + 1;
    
    for (int i = 1; i <= n; i++) {
        pq.dist[i] = INF;
        pq.visited[i] = 0;
    }
    pq.dist[source] = 0;
    
    while (1) {
        int u = -1;
        for (int i = 1; i <= n; i++) {
            if (!pq.visited[i] && (u == -1 || pq.dist[i] < pq.dist[u])) {
                u = i;
            }
        }
        if (u == -1 || pq.dist[u] == INF) break;
        
        pq.visited[u] = 1;
        
        for (int i = 0; i < graph->lists[u].size; i++) {
            Edge edge = graph->lists[u].edges[i];
            int v = edge.v;
            int weight = edge.weight;
            
            if (pq.dist[u] + weight < pq.dist[v]) {
                pq.dist[v] = pq.dist[u] + weight;
            }
        }
    }
    
    free(pq.dist);
    free(pq.visited);
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    Graph graph;
    initGraph(&graph, n);
    
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        addEdge(&graph, u, v, w);
    }
    
    int* distance = malloc(sizeof(int) * (n + 1));
    dijkstra(1, &graph, distance);
    
    for (int i = 1; i <= n; i++) {
        if (distance[i] == INF) {
            printf("INF ");
        } else {
            printf("%d ", distance[i]);
        }
    }
    printf("\n");
    
    free(distance);
    for (int i = 1; i <= n; i++) {
        free(graph.lists[i].edges);
    }
    free(graph.lists);
    
    return 0;
}
