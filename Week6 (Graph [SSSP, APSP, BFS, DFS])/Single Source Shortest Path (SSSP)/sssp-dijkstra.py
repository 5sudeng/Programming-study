import heapq
import sys

def dijkstra(source, graph, n):
    distance = [float('inf')] * (n + 1)
    distance[source] = 0
    pq = [(0, source)]
    
    while pq:
        dist_u, u = heapq.heappop(pq)
        
        if dist_u > distance[u]:
            continue
        
        for v, weight in graph[u]:
            if distance[u] + weight < distance[v]:
                distance[v] = distance[u] + weight
                heapq.heappush(pq, (distance[v], v))
    
    return distance

def main():
    input = sys.stdin.read
    data = input().split()
    
    n = int(data[0])
    m = int(data[1])
    
    graph = [[] for _ in range(n + 1)]
    
    index = 2
    for _ in range(m):
        u = int(data[index])
        v = int(data[index + 1])
        w = int(data[index + 2])
        graph[u].append((v, w))
        index += 3
    
    distance = dijkstra(1, graph, n)
    
    for i in range(1, n + 1):
        if distance[i] == float('inf'):
            print("INF", end=" ")
        else:
            print(distance[i], end=" ")
    print()

if __name__ == "__main__":
    main()
