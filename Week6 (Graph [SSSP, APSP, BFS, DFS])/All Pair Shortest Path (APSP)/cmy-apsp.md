# APSP

All-Paris Shortest-Paths
: **모든 노드**부터 **다른 모든 노드**까지 가는 가장 빠른 길들을 찾는 알고리즘

- :thought_balloon: 소신발언: 이것 또한 C 프로그래밍으로 출제될 수가 없다
- C++, C, Python 코드는 지피티가 만들어주었습니다 :curly_loop:

### Algorithms
- `Floyd-Warshall` algorithm
- `Johnson`'s algorithm

## Floyd-Warshall Algorithm
- Negative-w edges :o:, but **negative-w cycles :x:**
- **`Idea`**: Use DP!!
    - for `k = 1 to n`, check whether `k` is an intermediate vertex of p,
    	- where p: shortest path from `i` to `j`j
- $O(V^3)$

**FLOYD-WARHSALL(w, n)**
```
for i = 1 to n
    for j = 1 to n
        dist[i, j] = w[i, j]
        pred[i, j] = NULL
        if (i != j and w[i, j] < inf)
            pred[i, j] = i

for k = 1 to n
    for i = 1 to n     // source
        for j = 1 to n // destination
            if (dist[i, k] + dist[k, j] < dist[i, j])
                dist[i, j] = dist[i, k] + dist[k, j]
                pred[i ,j] = pred[k, j]
```

**PRINT-APSP(pred, i, j)**
```
if i == j
    print i
else if pred[i, j] == NULL
    print "NO PATH"
else
    PRINT-APSP(pred, i, pred[i, j])
    print j
```

## Johnson's Algorithm
- Useful for sparse graphs ($E = O(V)$)
- **`Idea`**: Reweighting, and then run `Dijkstra`'s algorihtm
    $$ \hat{w}(u, v) = w(u, v) + h(u) - h(v) \geq 0 $$
    - Add a new node `s` connected with all other vertices with `w(s, v) = 0`
    - Run `Bellmna-Ford` to find shortest paths from `s` to all other vertices, let $h(v) = \delta(s, v)$ 
    - Run `Dijkstra` for all vertices
- $O(V^2logV + VE)$

**JOHNSON(G, w)**
```
Create G' where 
    G'.V = G.V + {s},
    G'.E = G.E + ((s, u) for u in G.V),
    w(s, u) = 0 for u in G.V

if Bellman-Ford(s) == False
    return "NEGATIVE CYCLE"
else
    for vertex v in G`.V:
            h(v) = delta(s, v) computed by Bellman-Ford
        for edge (u, v) in G`.E:
            w`(u, v) = w(u, v) + h(u) - h(v)
            
        D = new matrix of distances initialized to inf
        for vertex u in G.V:
            run Dijkstra(G, w`, u) to compute delta`(u, v) for all v in G.V
            for each vertex v in G.V:
                D_(u, v) = delta`(u, v) + h(v) - h(u)
return D
```