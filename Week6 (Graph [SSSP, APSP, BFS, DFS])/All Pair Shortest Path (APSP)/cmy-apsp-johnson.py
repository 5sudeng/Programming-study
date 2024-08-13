import heapq
import sys

def bellman_ford(source, graph, n):
    h = [float('inf')] * n
    h[source] = 0
    
    for _ in range(n - 1):
        for u in range(n):
            for v, weight in graph[u]:
                if h[u] != float('inf') and h[u] + weight < h[v]:
                    h[v] = h[u] + weight
    
    return h

def dijkstra(source, graph, n):
    dist = [float('inf')] * n
    dist[source] = 0
    
    pq = [(0, source)]
    while pq:
        current_dist, u = heapq.heappop(pq)
        
        if current_dist > dist[u]:
            continue
        
        for v, weight in graph[u]:
            if dist[u] + weight < dist[v]:
                dist[v] = dist[u] + weight
                heapq.heappush(pq, (dist[v], v))
    
    return dist

def johnson(graph, n):
    modified_graph = [edges[:] for edges in graph]
    h = bellman_ford(n, modified_graph + [[]], n)
    
    for u in range(n):
        for i in range(len(modified_graph[u])):
            v, weight = modified_graph[u][i]
            modified_graph[u][i] = (v, weight + h[u] - h[v])
    
    all_distances = []
    for u in range(n):
        dist = dijkstra(u, modified_graph, n)
        all_distances.append([dist[v] + h[v] - h[u] if dist[v] < float('inf') else float('inf') for v in range(n)])
    
    return all_distances

def main():
    input = sys.stdin.read
    data = list(map(int, input().split()))
    
    n = data[0]
    m = data[1]
    
    graph = [[] for _ in range(n)]
    index = 2
    for _ in range(m):
        u = data[index] - 1
        v = data[index + 1] - 1
        w = data[index + 2]
        graph[u].append((v, w))
        index += 3
    
    all_distances = johnson(graph, n)
    
    for row in all_distances:
        print(" ".join("INF" if dist == float('inf') else str(dist) for dist in row))

if __name__ == "__main__":
    main()
