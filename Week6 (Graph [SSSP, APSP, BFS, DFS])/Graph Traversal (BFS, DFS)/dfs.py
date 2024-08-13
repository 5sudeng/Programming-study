class Vertex:
    color = 'WHITE'
    pi = -1
    discover = 0
    finish = 0
    adj = []

    def __init__(self):
        self.color = 'WHITE'
        self.pi = -1
        self.discover = 0
        self.finish = 0
        self.adj = []

class Graph:
    vertices = []

    def __init__(self, numVertex: int):
        self.vertices = [Vertex() for i in range(numVertex)]


    def DFS_VISIT(self, u: int, time: int, finishStack):
        time = time + 1
        self.vertices[u].discover = time
        self.vertices[u].color = 'GRAY'

        for v in self.vertices[u].adj:
            if self.vertices[v].color == 'WHITE':
                self.vertices[v].pi = u
                time = self.DFS_VISIT(v, time, finishStack)
        
        time = time + 1
        self.vertices[u].finish = time
        self.vertices[u].color = 'BLACK'
        finishStack.append(u)

        return time



    def DFS(self):
        time = 0
        finishStack = []

        for i in range(len(self.vertices)):
            if self.vertices[i].color == 'WHITE':
                time = self.DFS_VISIT(i, time, finishStack)
        
        return finishStack



    def TopologicalSort(self):
        result = []
        finishStack = []

        finishStack = self.DFS()

        while len(finishStack) != 0:
            result.append(finishStack.pop())
        
        return result


def main():
    # [#11] p.21 graph example
    numVertex = 6
    graph = Graph(numVertex)

    graph.vertices[0].adj = [1, 3]
    graph.vertices[1].adj = [4]
    graph.vertices[2].adj = [4, 5]
    graph.vertices[3].adj = [1]
    graph.vertices[4].adj = [3]
    graph.vertices[5].adj = [5]

    graph.DFS()

    for i in range(numVertex):
        print('Vertex', i, ': Discover =', graph.vertices[i].discover, ', Finish =', graph.vertices[i].finish)


    # [#11] p.30 graph example
    # numVertex = 9
    # graph = Graph(numVertex)

    # graph.vertices[0].adj = [1, 7]
    # graph.vertices[1].adj = [2, 7]
    # graph.vertices[2].adj = [5]
    # graph.vertices[3].adj = [2, 4]
    # graph.vertices[4].adj = [5]
    # graph.vertices[5].adj = []
    # graph.vertices[6].adj = [7]
    # graph.vertices[7].adj = []
    # graph.vertices[8].adj = []

    # sortedVertices = graph.TopologicalSort()

    # for i in range(numVertex):
    #     print('Vertex', i, ': Discover =', graph.vertices[i].discover, ', Finish =', graph.vertices[i].finish)

    # print('Topological Sort:', end=' ')
    # for vertex in sortedVertices:
    #     print(vertex, end=' ')
    # print()


if __name__ == '__main__':
    main()