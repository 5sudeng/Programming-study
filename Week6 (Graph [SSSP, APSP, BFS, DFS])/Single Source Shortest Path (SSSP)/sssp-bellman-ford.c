#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX

typedef struct {
    int u, v, weight;
} Edge;

void bellman_ford(int source, int n, int m, Edge* edges, int* distance, int* hasNegativeCycle) {
    for (int i = 1; i <= n; i++) {
        distance[i] = INF;
    }
    distance[source] = 0;
    
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int u = edges[j].u;
            int v = edges[j].v;
            int weight = edges[j].weight;
            
            if (distance[u] != INF && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
            }
        }
    }
    
    *hasNegativeCycle = 0;
    for (int j = 0; j < m; j++) {
        int u = edges[j].u;
        int v = edges[j].v;
        int weight = edges[j].weight;
        
        if (distance[u] != INF && distance[u] + weight < distance[v]) {
            *hasNegativeCycle = 1;
            return;
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    Edge* edges = malloc(sizeof(Edge) * m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].weight);
    }
    
    int* distance = malloc(sizeof(int) * (n + 1));
    int hasNegativeCycle;
    
    bellman_ford(1, n, m, edges, distance, &hasNegativeCycle);
    
    if (hasNegativeCycle) {
        printf("Negative weight cycle detected!\n");
    } else {
        for (int i = 1; i <= n; i++) {
            if (distance[i] == INF) {
                printf("INF ");
            } else {
                printf("%d ", distance[i]);
            }
        }
        printf("\n");
    }
    
    free(edges);
    free(distance);
    
    return 0;
}
