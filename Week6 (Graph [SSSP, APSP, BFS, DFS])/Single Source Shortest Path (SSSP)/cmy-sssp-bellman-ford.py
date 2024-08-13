import sys

def bellman_ford(source, edges, n):
    distance = [float('inf')] * (n + 1)
    distance[source] = 0
    
    for _ in range(n - 1):
        for u, v, weight in edges:
            if distance[u] != float('inf') and distance[u] + weight < distance[v]:
                distance[v] = distance[u] + weight
    
    # Check for negative weight cycles
    for u, v, weight in edges:
        if distance[u] != float('inf') and distance[u] + weight < distance[v]:
            return None  # Negative weight cycle detected
    
    return distance

def main():
    input = sys.stdin.read
    data = input().split()
    
    n = int(data[0])
    m = int(data[1])
    
    edges = []
    index = 2
    for _ in range(m):
        u = int(data[index])
        v = int(data[index + 1])
        w = int(data[index + 2])
        edges.append((u, v, w))
        index += 3
    
    distance = bellman_ford(1, edges, n)
    
    if distance is None:
        print("Negative weight cycle detected!")
    else:
        for i in range(1, n + 1):
            if distance[i] == float('inf'):
                print("INF", end=" ")
            else:
                print(distance[i], end=" ")
        print()

if __name__ == "__main__":
    main()
