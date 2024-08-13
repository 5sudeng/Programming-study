import sys

class Graph:
    def __init__(self, vertices):
        self.V = vertices
        self.graph = [[0 for column in range(vertices)] for row in range(vertices)]

    def min_distance(self, dist, sptSet):
        min_val = sys.maxsize
        min_index = -1

        # Search for the vertex with the smallest distance
        for v in range(self.V):
            if dist[v] < min_val and not sptSet[v]:
                min_val = dist[v]
                min_index = v

        return min_index

    def print_solution(self, dist):
        print("Vertex \t Distance from Source")
        for node in range(self.V):
            print(node, "\t", dist[node])

    def print_path(self, parent, vertex):
        if parent[vertex] == -1:
            print(vertex, end=" ")
            return
        self.print_path(parent, parent[vertex])
        print(vertex, end=" ")

    def dijkstra(self, src):
        dist = [sys.maxsize] * self.V  # Distance from src to all other vertices
        sptSet = [False] * self.V  # True if vertex i is included in shortest path tree
        parent = [-1] * self.V  # Array to store the constructed shortest path

        dist[src] = 0  # Distance of source vertex from itself is always 0

        for _ in range(self.V):
            u = self.min_distance(dist, sptSet)  # Pick the minimum distance vertex from the set of vertices not yet processed
            sptSet[u] = True  # Mark the picked vertex as processed

            # Update the distance value of the adjacent vertices of the picked vertex
            for v in range(self.V):
                if (self.graph[u][v] > 0 and not sptSet[v] and
                        dist[u] != sys.maxsize and dist[u] + self.graph[u][v] < dist[v]):
                    dist[v] = dist[u] + self.graph[u][v]
                    parent[v] = u  # Update parent to keep track of the path

        self.print_solution(dist)

        # Example: Print the path from source vertex 0 to vertex 8
        print("\nShortest path from 0 to 8: ", end="")
        if dist[8] != sys.maxsize:
            self.print_path(parent, 8)
        else:
            print("No path exists.")
        print()

# Example usage
g = Graph(9)
g.graph = [
    [0, 4, 0, 0, 0, 0, 0, 8, 0],
    [4, 0, 8, 0, 0, 0, 0, 11, 0],
    [0, 8, 0, 7, 0, 4, 0, 0, 2],
    [0, 0, 7, 0, 9, 14, 0, 0, 0],
    [0, 0, 0, 9, 0, 10, 0, 0, 0],
    [0, 0, 4, 14, 10, 0, 2, 0, 0],
    [0, 0, 0, 0, 0, 2, 0, 1, 6],
    [8, 11, 0, 0, 0, 0, 1, 0, 7],
    [0, 0, 2, 0, 0, 0, 6, 7, 0]
]

g.dijkstra(0)  # Source vertex is 0