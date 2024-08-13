from collections import defaultdict, deque


class Graph:
    def __init__(self):
        self.graph = defaultdict(list)

    def add_edge(self, v, w):
        self.graph[v].append(w)
        self.graph[w].append(v)  # If undirected graph

    def bfs(self, start, visited):
        queue = deque([start])
        visited.add(start)

        while queue:
            v = queue.popleft()
            print(v, end=" ")

            for neighbor in self.graph[v]:
                if neighbor not in visited:
                    visited.add(neighbor)
                    queue.append(neighbor)

    def bfs_disconnected(self):
        visited = set()

        for vertex in self.graph:
            if vertex not in visited:
                self.bfs(vertex, visited)
                print()

    def dfs_util(self, v, visited):
        visited.add(v)
        print(v, end=" ")

        for neighbor in self.graph[v]:
            if neighbor not in visited:
                self.dfs_util(neighbor, visited)

    def dfs_disconnected(self):
        visited = set()

        for vertex in self.graph:
            if vertex not in visited:
                self.dfs_util(vertex, visited)
                print()


if __name__ == "__main__":
    g = Graph()

    # First component
    g.add_edge(0, 1)
    g.add_edge(0, 2)
    g.add_edge(1, 3)
    g.add_edge(2, 3)
    g.add_edge(3, 4)

    # Second component
    g.add_edge(5, 6)
    g.add_edge(5, 7)

    # Third component
    g.add_edge(8, 9)

    print("BFS for disconnected graph:")
    g.bfs_disconnected()

    print("DFS for disconnected graph:")
    g.dfs_disconnected()