############ Vertex와 Edge가 주어진 경우 #################
##### Undirected Graph #########
class undi_graph():
    def __init__(self, V:list, E:list) -> None:
        self.V = V[:]
        self.neighbor = {}
        for v in V:
            self.neighbor[v] = []
        for (v, w) in E:
            self.neighbor[v].append(w)
            self.neighbor[w].append(v)   # For undirected graph

    ### add edge형식인경우 앞부분만 밑처럼 바꾸기
    # graph.add_edge(0, 1)
    # graph.add_edge(0, 2)
    # graph.add_edge(1, 3)
    # graph.add_edge(2, 3)
    # graph.add_edge(3, 4)

# class UndiGraph:
#     def __init__(self, V):
#         self.V = V
#         self.neighbor = {v: [] for v in V}

#     def add_edge(self, v, w):
#         self.neighbor[v].append(w)
#         self.neighbor[w].append(v)  # For undirected graph


    def BFS(self, root):
        if root is None:
            return
        visited = {v: False for v in self.V}
        q = [root]
        visited[root] = True

        while q:
            curNode = q.pop(0)
            print(curNode, end=' ')
            for v in self.neighbor[curNode]:
                if not visited[v]:
                    q.append(v)
                    visited[v] = True

        for k in self.V:
            if not visited[k]:
                q.append(k)
                visited[k] = True
                while q:
                    curNode = q.pop(0)
                    print(curNode, end=' ')
                    for v in self.neighbor[curNode]:
                        if not visited[v]:
                            q.append(v)
                            visited[v] = True


if __name__ == "__main__":
    vertices = [1, 2, 3, 4, 5, 6, 7, 8]
    edges = [
    (1, 2), (1, 3), 
    (2, 1), (2, 8),
    (3, 1), (3, 4), (3, 5),
    (4, 3), (4, 5),
    (5, 3), (5, 4),
    (6, 7),
    (7, 6),
    (8, 2)
    ]

    # Create the graph
    graph = undi_graph(vertices, edges)

    # Perform BFS starting from vertex 1
    print("BFS starting from vertex 1:")
    graph.BFS(1)


####### directed graph #########
class dir_graph():
    def __init__(self, V:list, E:list) -> None:
        self.V = V[:]
        self.neighbor = {v: [] for v in V}
        for (v, w) in E:
            self.neighbor[v].append(w)


    def BFS(self, root):
        if root is None:
            return
        
        visited = {v: False for v in self.V}
        q = [root]
        visited[root] = True

        while q:
            curNode = q.pop(0)
            print(curNode, end=' ')
            for v in self.neighbor[curNode]:
                if not visited[v]:
                    q.append(v)
                    visited[v] = True

        for k in self.V:
            if not visited[k]:
                q.append(k)
                visited[k] = True
                while q:
                    curNode = q.pop(0)
                    print(curNode, end=' ')
                    for v in self.neighbor[curNode]:
                        if not visited[v]:
                            q.append(v)
                            visited[v] = True


if __name__ == "__main__":
    vertices = [1, 2, 3, 4, 5, 6, 7, 8]
    edges = [
    (1, 2), (1, 3),
    (2, 8),
    (3, 4), (3, 5),
    (4, 5),
    (6, 7), (6, 8),
    (7, 8)
    ]

    # Create the graph
    graph = dir_graph(vertices, edges)

    # Perform BFS starting from vertex 1
    print("BFS starting from vertex 1:")
    graph.BFS(1)





############### 그래프 자체로 주어졌을 경우 #################
### Undirected graph, Directed graph 모두 표현 가능 ###########
#queue 쓰기
from collections import deque


num_nodes = 8 
def bfs_helper(graph, node, visited):
    queue = deque([node])
    visited[node] = True

    while queue:
        v = queue.popleft()  # 데크에 삽입된 순서대로 노드 하나 꺼내기
        print(v, end=' ')
        for i in graph[v]:
            if not visited[i]:
                queue.append(i)
                visited[i] = True



# 시작 노드 안넣어두기
# def bfs(graph, num_nodes):
#     visited = [False] * (num_nodes + 1)
    
#     for node in range(1, num_nodes + 1):
#         if not visited[node]:
#             bfs_helper(graph, node, visited)


# 시작 위치 지명하기
def bfs(graph, num_nodes, start_node):
    visited = [False] * (num_nodes + 1)
    bfs_helper(graph, start_node, visited)

    for node in range(1, num_nodes + 1):
        if not visited[node]:
            bfs_helper(graph, node, visited)




#Directed
graph = [
    [],
    [2,3],
    [8],
    [4,5],
    [5],
    [],
    [7,8],
    [8],
    []
]
# 1 2 3 8 4 5 6 7

#Undirected
# graph = [
#     [],
#     [2, 3],
#     [1, 8],
#     [1, 4, 5],
#     [3, 5],
#     [3, 4],
#     [7],
#     [6],
#     [2]
# ]
# 1 2 3 8 4 5 6 7


# bfs(graph, num_nodes)
bfs(graph, num_nodes, 1)
