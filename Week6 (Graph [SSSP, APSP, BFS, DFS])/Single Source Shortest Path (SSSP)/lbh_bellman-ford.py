class Graph:
    def __init__(self, vertices):
        self.V = vertices
        self.edges = []

    def add_edge(self, u, v, w):
        self.edges.append([u, v, w])

    def print_solution(self, dist):
        print("Vertex \t Distance from Source")
        for i in range(self.V):
            print(f"{i}\t\t{dist[i]}")

    def print_path(self, parent, vertex):
        if parent[vertex] == -1:
            print(vertex, end=" ")
            return
        self.print_path(parent, parent[vertex])
        print(vertex, end=" ")

    def bellman_ford(self, src):
        dist = [float("Inf")] * self.V
        parent = [-1] * self.V

        dist[src] = 0

        # Relax all edges V - 1 times
        for _ in range(self.V - 1):
            for u, v, w in self.edges:
                if dist[u] != float("Inf") and dist[u] + w < dist[v]:
                    dist[v] = dist[u] + w
                    parent[v] = u

        # Check for negative-weight cycles
        for u, v, w in self.edges:
            if dist[u] != float("Inf") and dist[u] + w < dist[v]:
                print("Graph contains negative weight cycle")
                return

        self.print_solution(dist)

        # Example: Print the path from vertex 0 to vertex 3
        print("\nShortest path from 0 to 3: ", end="")
        if dist[3] != float("Inf"):
            self.print_path(parent, 3)
        else:
            print("No path exists.")
        print()

# Example usage
g = Graph(5)
g.add_edge(0, 1, -1)
g.add_edge(0, 2, 4)
g.add_edge(1, 2, 3)
g.add_edge(1, 3, 2)
g.add_edge(1, 4, 2)
g.add_edge(3, 2, 5)
g.add_edge(3, 1, 1)
g.add_edge(4, 3, -3)

g.bellman_ford(0)