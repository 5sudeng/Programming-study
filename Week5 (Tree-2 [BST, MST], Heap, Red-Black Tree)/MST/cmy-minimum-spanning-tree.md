# Minimum Spanning Tree
When you want to find a way to **connect every node** in a graph in the **least-cost** possible way
- Spanning tree of undirected, connected, weighted graph with minimum total weight, $w(T) = \sum_{(u, v)\in T}w(u, v)$

## Prim's algorithm
- cost가 가장 작은 node 골라서 (**Greedy!**) 인접한 애들과 모두 `relax` 진행 
- $O((E+V)logV) = O(ElogV)$
```
Initialize connection cost of each node to “inf” and “unmark” them
Choose one node v, and set cost[v]=0, prev[v]=0
While there are unmarked nodes
    select unmarked node u with minimum cost
    for each unmarked node x adjacent to u
        if w(u, x) < cost(x)
            cost(x) = w(u, x)
            prev(x) = u
    mark u
```

### Implementation
``` C++
#include <iostream>
#include <vector>
#include <climits>
#include <cstring> // for memset

using namespace std;

#define INF INT_MAX

void primsAlgorithm(const vector<vector<int>>& graph) {
    int n = graph.size(); // Number of nodes
    vector<int> cost(n, INF);
    vector<int> prev(n, -1);
    vector<bool> marked(n, false);
    
    // Choose the first node
    cost[0] = 0;
    
    for (int i = 0; i < n - 1; ++i) {
        int u = -1;
        for (int j = 0; j < n; ++j) {
            if (!marked[j] && (u == -1 || cost[j] < cost[u])) {
                u = j;
            }
        }

        // Mark the selected node
        marked[u] = true;

        // Update the cost and previous node for adjacent nodes
        for (int v = 0; v < n; ++v) {
            if (graph[u][v] && !marked[v] && graph[u][v] < cost[v]) {
                cost[v] = graph[u][v];
                prev[v] = u;
            }
        }
    }

    // Print the results
    for (int i = 1; i < n; ++i) {
        cout << "Edge: " << prev[i] << " - " << i << ", Cost: " << cost[i] << endl;
    }
}
```

``` C
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define INF INT_MAX
#define V 5 // Number of vertices

void primsAlgorithm(int graph[V][V]) {
    int cost[V];
    int prev[V];
    bool marked[V];

    // Initialize all costs to infinity and marked to false
    for (int i = 0; i < V; ++i) {
        cost[i] = INF;
        prev[i] = -1;
        marked[i] = false;
    }

    // Choose the first node
    cost[0] = 0;

    for (int i = 0; i < V - 1; ++i) {
        int u = -1;

        // Find the minimum cost unmarked node
        for (int j = 0; j < V; ++j) {
            if (!marked[j] && (u == -1 || cost[j] < cost[u])) {
                u = j;
            }
        }

        // Mark the selected node
        marked[u] = true;

        // Update the cost and previous node for adjacent nodes
        for (int v = 0; v < V; ++v) {
            if (graph[u][v] && !marked[v] && graph[u][v] < cost[v]) {
                cost[v] = graph[u][v];
                prev[v] = u;
            }
        }
    }

    // Print the results
    for (int i = 1; i < V; ++i) {
        printf("Edge: %d - %d, Cost: %d\n", prev[i], i, cost[i]);
    }
}
```

``` Python
def prims_algorithm(graph):
    n = len(graph)  # Number of nodes
    cost = [sys.maxsize] * n
    prev = [-1] * n
    marked = [False] * n

    # Choose the first node
    cost[0] = 0

    for _ in range(n - 1):
        u = min((i for i in range(n) if not marked[i]), key=lambda x: cost[x])

        # Mark the selected node
        marked[u] = True

        # Update the cost and previous node for adjacent nodes
        for v in range(n):
            if graph[u][v] and not marked[v] and graph[u][v] < cost[v]:
                cost[v] = graph[u][v]
                prev[v] = u

    # Print the results
    for i in range(1, n):
        print(f"Edge: {prev[i]} - {i}, Cost: {cost[i]}")
```

## Kruskal's algorithm
- edge 기준으로 오름차순 정렬하고, 순서대로 뽑아서 떨어져 있으면 연결
- `disjoint-set` data structure를 이용해야 함
- $O(ElogE)$, but since $|E| \leq |V|^2, log|E| = O(logV)$ &rarr; $O(ElogV)$
```
A = empty set
for each v in G.V
    MAKE-SET(v)
create a single list of edges in G.E
sort list of edges in ascending order by weight w
for each edge (u, v) from sorted list
    if FIND-SET(u) != FIND-SET(v)
        A = A U {(u, v)}
        UNION(u, v)
return A
```


### Implementation
``` C++
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v, weight;
    bool operator<(const Edge& e) const {
        return weight < e.weight;
    }
};

class DisjointSet {
public:
    DisjointSet(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int find(int u) {
        if (parent[u] != u) {
            parent[u] = find(parent[u]); // Path compression
        }
        return parent[u];
    }

    void unionSets(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);

        if (rootU != rootV) {
            if (rank[rootU] > rank[rootV]) {
                parent[rootV] = rootU;
            } else if (rank[rootU] < rank[rootV]) {
                parent[rootU] = rootV;
            } else {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    }

private:
    vector<int> parent;
    vector<int> rank;
};

vector<Edge> kruskal(int n, vector<Edge>& edges) {
    DisjointSet ds(n);
    vector<Edge> mst;

    sort(edges.begin(), edges.end());

    for (const auto& edge : edges) {
        int u = edge.u;
        int v = edge.v;

        if (ds.find(u) != ds.find(v)) {
            mst.push_back(edge);
            ds.unionSets(u, v);
        }
    }

    return mst;
}
```

``` C
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int u, v, weight;
} Edge;

typedef struct {
    int *parent;
    int *rank;
    int size;
} DisjointSet;

DisjointSet* createDisjointSet(int n) {
    DisjointSet *ds = (DisjointSet *)malloc(sizeof(DisjointSet));
    ds->parent = (int *)malloc(n * sizeof(int));
    ds->rank = (int *)malloc(n * sizeof(int));
    ds->size = n;

    for (int i = 0; i < n; ++i) {
        ds->parent[i] = i;
        ds->rank[i] = 0;
    }
    return ds;
}

int find(DisjointSet *ds, int u) {
    if (ds->parent[u] != u) {
        ds->parent[u] = find(ds, ds->parent[u]);
    }
    return ds->parent[u];
}

void unionSets(DisjointSet *ds, int u, int v) {
    int rootU = find(ds, u);
    int rootV = find(ds, v);

    if (rootU != rootV) {
        if (ds->rank[rootU] > ds->rank[rootV]) {
            ds->parent[rootV] = rootU;
        } else if (ds->rank[rootU] < ds->rank[rootV]) {
            ds->parent[rootU] = rootV;
        } else {
            ds->parent[rootV] = rootU;
            ds->rank[rootU]++;
        }
    }
}

int compareEdges(const void *a, const void *b) {
    return ((Edge *)a)->weight - ((Edge *)b)->weight;
}

void kruskal(int n, Edge edges[], int e_count) {
    DisjointSet *ds = createDisjointSet(n);
    qsort(edges, e_count, sizeof(Edge), compareEdges);

    for (int i = 0; i < e_count; ++i) {
        Edge edge = edges[i];
        int u = edge.u;
        int v = edge.v;

        if (find(ds, u) != find(ds, v)) {
            printf("Edge: %d - %d, Weight: %d\n", u, v, edge.weight);
            unionSets(ds, u, v);
        }
    }

    free(ds->parent);
    free(ds->rank);
    free(ds);
}
```

``` Python
class DisjointSet:
    def __init__(self, n):
        self.parent = list(range(n))
        self.rank = [0] * n

    def find(self, u):
        if self.parent[u] != u:
            self.parent[u] = self.find(self.parent[u])  # Path compression
        return self.parent[u]

    def union(self, u, v):
        rootU = self.find(u)
        rootV = self.find(v)

        if rootU != rootV:
            if self.rank[rootU] > self.rank[rootV]:
                self.parent[rootV] = rootU
            elif self.rank[rootU] < self.rank[rootV]:
                self.parent[rootU] = rootV
            else:
                self.parent[rootV] = rootU
                self.rank[rootU] += 1

def kruskal(n, edges):
    ds = DisjointSet(n)
    mst = []

    edges.sort(key=lambda e: e[2])  # Sort by weight

    for u, v, weight in edges:
        if ds.find(u) != ds.find(v):
            mst.append((u, v, weight))
            ds.union(u, v)

    for u, v, weight in mst:
        print(f"Edge: {u} - {v}, Weight: {weight}")
    return mst
```