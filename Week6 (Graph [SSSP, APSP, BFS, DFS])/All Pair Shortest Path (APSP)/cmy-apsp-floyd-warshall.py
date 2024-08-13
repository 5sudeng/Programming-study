def floyd_warshall(dist):
    n = len(dist)
    for k in range(n):
        for i in range(n):
            for j in range(n):
                if dist[i][k] < float('inf') and dist[k][j] < float('inf'):
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])

def main():
    import sys
    input = sys.stdin.read
    data = input().split()
    
    n = int(data[0])
    m = int(data[1])
    
    dist = [[float('inf')] * n for _ in range(n)]
    for i in range(n):
        dist[i][i] = 0
    
    index = 2
    for _ in range(m):
        u = int(data[index]) - 1
        v = int(data[index + 1]) - 1
        w = int(data[index + 2])
        dist[u][v] = w
        index += 3
    
    floyd_warshall(dist)
    
    for i in range(n):
        for j in range(n):
            if dist[i][j] == float('inf'):
                print("INF", end=" ")
            else:
                print(dist[i][j], end=" ")
        print()

if __name__ == "__main__":
    main()
