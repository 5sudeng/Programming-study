import sys

class Graph:
    def __init__(self, vertices):
        self.V = vertices
        self.graph = [[0 for column in range(vertices)] for row in range(vertices)]

    def print_mst(self, parent):
        print("Edge \tWeight")
        for i in range(1, self.V):
            print(parent[i], "-", i, "\t", self.graph[i][parent[i]])

    def min_key(self, key, mst_set):
        # Initialize min value
        min_val = sys.maxsize
        min_index = -1

        # Find the vertex with the smallest key value that is not yet included in MST
        for v in range(self.V):
            if key[v] < min_val and not mst_set[v]:
                min_val = key[v]
                min_index = v

        return min_index

    def prim_mst(self):
        key = [sys.maxsize] * self.V  # Key values used to pick minimum weight edge
        parent = [None] * self.V  # Array to store the constructed MST
        key[0] = 0  # Make key 0 so that this vertex is picked as the first vertex
        mst_set = [False] * self.V  # To represent set of vertices included in MST
        parent[0] = -1  # First node is always the root of MST

        for _ in range(self.V):
            # Pick the minimum key vertex from the set of vertices not yet included in MST
            u = self.min_key(key, mst_set)
            mst_set[u] = True  # Add the picked vertex to the MST set

            # Update the key value and parent index of the adjacent vertices of the picked vertex
            for v in range(self.V):
                # graph[u][v] is non-zero only for adjacent vertices of u
                # mst_set[v] is false for vertices not yet included in MST
                # Update the key only if graph[u][v] is smaller than key[v]
                if self.graph[u][v] > 0 and not mst_set[v] and key[v] > self.graph[u][v]:
                    key[v] = self.graph[u][v]
                    parent[v] = u

        self.print_mst(parent)

# Example usage
g = Graph(5)
g.graph = [
    [0, 2, 0, 6, 0],
    [2, 0, 3, 8, 5],
    [0, 3, 0, 0, 7],
    [6, 8, 0, 0, 9],
    [0, 5, 7, 9, 0]
]

g.prim_mst()