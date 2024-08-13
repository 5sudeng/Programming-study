# SSSP

Single-Source Shortest-Paths
: **하나의 출발점**부터 **하나의 도착점**까지 가는 가장 빠른 길을 찾는 알고리즘

- Subpaths of shortest paths are shortest paths
- Shortest path cannot contain cycle &rarr; Any shortest path contains at most `|V|-1` edges
- :thought_balloon: 소신발언: 이거는 C 프로그래밍으로 출제될 수가 없다
- C++, C, Python 코드는 지피티가 만들어주었습니다 :curly_loop:

### Algorithms
- Shortest paths for unweighted graphs
- `Dijkstra`'s algorithm
- `Bellman-Ford` algorithm
- Shortest paths for DAGs

## Shortest Paths for Unweighted Graphs
- use the idea of `BFS`!!

**bfsShortestPaths(Graph G, Vertex source)**
```
toVisit.enqueue(source)
source.dist = 0
source.pred = NULL
while (toVisit is not empty) {
    current = toVisit.dequeue()
    for (v  : current.outNeighbors()) {
        if (v is not yet visited) {
            v.dist = current.dist + 1
            v.pred = current
            toVisit.enqueue(v)
            mark v as visited
        }
    }
}
```

## Dijkstra's Algorithm
- Generalization of BFS to **weighted** graphs
- **`Idea`**
    - Repeatedly select vertex `u` from $V-S$ that is *lightest* &rarr; **Greedy!!**
    where, S: set of vertices whose final shortest-path weights from source s have been determined
    - Add `u` into S
    - Relax all edges leaving `u`
- $O(VlogV + ElogV) = O(ElogV)$ with priority queue
- :boom: Cannot handle **negative edges**

**Dijkstra(Graph G, Vertex source)**
```
INITIALIZE-SINGLE-SOURCE(G, s)
S = NULL
Q = NULL
for (u : G.V) { INSERT(Q, u) }
while (Q is not empty) {
    u = EXTRACT-MIN(Q)
    for (v : u.outNeighbors()) {
        if (u.dist + weight(u, v) < v.dist) {
            v.dist = u.dist + weight(u, v)
            v.pred = u
            DECREASE-KEY(Q, v, v.dist)
        }
    }
}
```

## Bellman-Ford Algorithm
- Slower than `Dijkstra`'s algorithm, but able to handle **negative edges**
- Returns Boolean value indicating whethere there is a negative-weight cycle reachable from the source
- **`Idea`**: relax each edge $|V|-1$ times
- $O(VE)$

**BELLMAN-FORD(G, W, s)**
```
INITIALIZE-SINGLE-SOURCE(G, s)
for (i=1 to |G.V|-1) {
    for (each edge (u, v) : G.E) {
        RELAX(u, v, w)
    }
}
for (each edge (u, v) : G.E) {
    if (v.d > u.d + w(u, v)) // i.e. if one more relaxing is possible
        return FALSE
}
return TRUE
```

## Shortest Paths for DAGs
- Shortest paths are always well defined in DAG
- **`Idea`**: Relax edges according to **topological order** of vertices
- $O(V+E)$

**DAG-SHORTEST-PATHS(G, w, s)**
```
topologically sort the vertices of G
INITIALIZE-SIGLE-SOURCE(G, s)
for (vertex u taken in topologically sorted order) {
    for (vertex v in u.neighbors()) {
        RELAX(u, v, w)
    }
}
```