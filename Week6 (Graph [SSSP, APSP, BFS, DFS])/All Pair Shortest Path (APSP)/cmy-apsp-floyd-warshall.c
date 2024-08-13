#include <stdio.h>
#include <limits.h>

#define INF INT_MAX

void floydWarshall(int n, int dist[n][n]) {
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    if (dist[i][j] > dist[i][k] + dist[k][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m); // Number of nodes and edges
    
    int dist[n][n];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) dist[i][j] = 0;
            else dist[i][j] = INF;
        }
    }
    
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w); // Edge from u to v with weight w
        dist[u - 1][v - 1] = w;
    }
    
    floydWarshall(n, dist);
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (dist[i][j] == INF) {
                printf("INF ");
            } else {
                printf("%d ", dist[i][j]);
            }
        }
        printf("\n");
    }
    
    return 0;
}
