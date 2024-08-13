import sys

INF = sys.maxsize

class Edge:
    def __init__(self, src, dest, weight):
        self.src = src
        self.dest = dest
        self.weight = weight

class Graph:
    def __init__(self, vertices):
        self.V = vertices
        self.edges = []

    def add_edge(self, u, v, w):
        self.edges.append(Edge(u, v, w))

    def print_path(self, parent, vertex):
        if parent[vertex] == -1:
            print(vertex, end=" ")
            return
        self.print_path(parent, parent[vertex])
        print(vertex, end=" ")

    def bellman_ford(self, vertices, src):
        dist = [INF] * vertices
        parent = [-1] * vertices
        dist[src] = 0

        for _ in range(vertices - 1):
            for edge in self.edges:
                u = edge.src
                v = edge.dest
                weight = edge.weight
                if dist[u] != INF and dist[u] + weight < dist[v]:
                    dist[v] = dist[u] + weight
                    parent[v] = u

        for edge in self.edges:
            u = edge.src
            v = edge.dest
            weight = edge.weight
            if dist[u] != INF and dist[u] + weight < dist[v]:
                print("Graph contains negative weight cycle")
                return None, None

        return dist, parent

    def dijkstra(self, graph, src):
        dist = [INF] * self.V
        sptSet = [False] * self.V
        parent = [-1] * self.V
        dist[src] = 0

        for _ in range(self.V):
            u = -1
            for i in range(self.V):
                if not sptSet[i] and (u == -1 or dist[i] < dist[u]):
                    u = i

            sptSet[u] = True

            for v in range(self.V):
                if not sptSet[v] and graph[u][v] != INF and dist[u] != INF and dist[u] + graph[u][v] < dist[v]:
                    dist[v] = dist[u] + graph[u][v]
                    parent[v] = u

        return dist, parent

    def johnson(self):
        new_vertex_count = self.V + 1
        original_edges = self.edges[:]
        for i in range(self.V):
            self.edges.append(Edge(self.V, i, 0))

        h, _ = self.bellman_ford(new_vertex_count, self.V)
        if h is None:
            return

        reweighted_graph = [[INF] * self.V for _ in range(self.V)]
        for edge in original_edges:
            reweighted_graph[edge.src][edge.dest] = edge.weight + h[edge.src] - h[edge.dest]

        for u in range(self.V):
            dist, parent = self.dijkstra(reweighted_graph, u)
            print(f"\nShortest distances from vertex {u}:")
            for v in range(self.V):
                if dist[v] != INF:
                    dist[v] = dist[v] + h[v] - h[u]
                    print(f"Distance to vertex {v} is {dist[v]}")
                    print("Path: ", end="")
                    self.print_path(parent, v)
                    print()
                else:
                    print(f"No path to vertex {v}")

# Example usage
g = Graph(5)
g.add_edge(0, 1, -1)
g.add_edge(0, 3, 2)
g.add_edge(1, 2, 4)
g.add_edge(1, 3, 3)
g.add_edge(1, 4, 2)
g.add_edge(2, 4, 1)
g.add_edge(3, 4, 5)

g.johnson()