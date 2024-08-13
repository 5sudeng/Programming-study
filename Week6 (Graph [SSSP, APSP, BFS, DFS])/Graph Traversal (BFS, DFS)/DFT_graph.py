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
            self.neighbor[w].append(v)

    # 만약 addEdge 형태라면
    # def __init__(self, directed=False):
    #     self.neighbor = {}
    #     self.directed = directed

    # def addVertex(self, v):
    #     if v not in self.neighbor:
    #         self.neighbor[v] = []

    # def addEdge(self, v, w):
    #     if v not in self.neighbor:
    #         self.addVertex(v)
    #     if w not in self.neighbor:
    #         self.addVertex(w)
        
    #     self.neighbor[v].append(w)
    #     if not self.directed:
    #         self.neighbor[w].append(v)
        
    #preorder        
    def __DFTHelp(self, visited:list, v:int) ->None:
        if not visited[v]:
            visited[v] = True
            print(v)
            for w in self.neighbor[v]:
                self.__DFTHelp(visited, w)
            for w in self.V:
                if not visited[w]:
                    self.__DFTHelp(visited, w)



    
    # 시작 노드 지정 안할경우
    # def DFT(self) -> None:
    #     if self.V:
    #         visited = {}
    #         for v in self.V:
    #             visited[v] = False
    #         for v in self.V:
    #             self.__DFTHelp(visited, v)



    # 시작 노드 지정해줄 경우
    def DFT(self, start_node: str) -> None:
        visited = {v: False for v in self.V}
        self.__DFTHelp(visited, start_node)
        

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
    # 1 2 8 3 4 5 6 7


    # Create the graph
    graph = undi_graph(vertices, edges)

    # Perform BFS starting from vertex 'A'
    print("DFT starting from vertex 1:")
    graph.DFT(1)


####### directed graph #########
class dir_graph():
    def __init__(self, V:list, E:list) -> None:
        self.V = V[:]
        self.neighbor = {v: [] for v in V}
        for (v, w) in E:
            self.neighbor[v].append(w)

    def __DFTHelp(self, visited:list, v:int) ->None:
        if not visited[v]:
            visited[v] = True
            print(v)
            for w in self.neighbor[v]:
                self.__DFTHelp(visited, w)
            for w in self.V:
                if not visited[w]:
                    self.__DFTHelp(visited, w)




    # 시작 노드 지정 안할경우
    # def DFT(self) -> None:
    #     if self.V:
    #         visited = {}
    #         for v in self.V:
    #             visited[v] = False
    #         for v in self.V:
    #             self.__DFTHelp(visited, v)
     


    # 시작 노드 지정할 경우    
    def DFT(self, start_node: str) -> None:
        visited = {v: False for v in self.V}
        self.__DFTHelp(visited, start_node)
        print()


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

    # Perform BFS starting from vertex 'A'
    print("DFT starting from vertex 1:")
    graph.DFT(1)  #1 2 8 3 4 5 6 7 



############### 그래프 자체로 주어졌을 경우 #################
### Undirected graph, Directed graph 모두 표현 가능 ###########
from collections import deque

def dfs(graph, node, visited):
    # 현재 노드를 방문 처리
    visited[node] = True
    print(node, end=' ')

    # 현재 노드와 연결된 다른 노드를 재귀적으로 방문
    for neighbor in graph[node]:
        if not visited[neighbor]:
            dfs(graph, neighbor, visited)

    for node in range(1, len(graph)):  # 인덱스 1부터 시작
        if not visited[node]:
            dfs(graph, node, visited)


#Directed
# graph = [
#     [],
#     [2,3],
#     [8],
#     [4,5],
#     [5],
#     [],
#     [7,8],
#     [8],
#     []
# ]
# 1 2 8 3 4 5 6 7

#Undirected
graph = [
    [],
    [2, 3],
    [1, 8],
    [1, 4, 5],
    [3, 5],
    [3, 4],
    [7],
    [6],
    [2]
]
# 1 2 8 3 4 5 6 7
visited = [False]*9
dfs(graph, 1, visited)
