V = 4
INF = 99999

# Function to print the solution matrix
def print_solution(dist):
    print("The following matrix shows the shortest distances between every pair of vertices:")
    for i in range(V):
        for j in range(V):
            if dist[i][j] == INF:
                print("INF", end=" ")
            else:
                print(dist[i][j], end=" ")
        print()

# Function to print the shortest path
def print_path(pred, i, j):
    if i != j:
        print_path(pred, i, pred[i][j])
    print(j, end=" ")

# Floyd-Warshall algorithm with path reconstruction
def floyd_warshall(graph):
    dist = [[graph[i][j] for j in range(V)] for i in range(V)]
    pred = [[-1 if graph[i][j] == INF or i == j else i for j in range(V)] for i in range(V)]

    for k in range(V):
        for i in range(V):
            for j in range(V):
                if dist[i][k] + dist[k][j] < dist[i][j]:
                    dist[i][j] = dist[i][k] + dist[k][j]
                    pred[i][j] = pred[k][j]

    print_solution(dist)

    # Example: Print the path from vertex 0 to vertex 3
    print("\nShortest path from 0 to 3: ", end="")
    if pred[0][3] != -1:
        print_path(pred, 0, 3)
    else:
        print("No path exists.")
    print()

# Define the graph as an adjacency matrix
graph = [[0,   5,  INF, 10],
         [INF, 0,   3, INF],
         [INF, INF, 0,   1],
         [INF, INF, INF, 0]]

# Run the Floyd-Warshall algorithm
floyd_warshall(graph)