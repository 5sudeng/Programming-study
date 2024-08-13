import sys

class Vertex:
    color = 'WHITE'
    dist = sys.maxsize
    pi = -1
    adj = []

    def __init__(self):
        self.color = 'WHITE'
        self.dist = sys.maxsize
        self.pi = -1
        self.adj = []

class Graph:
    vertices = []

    def __init__(self, numVertex: int):
        self.vertices = [Vertex() for i in range(numVertex)]
    
    def BFS(self, s: int):
        self.vertices[s].color = 'GRAY'
        self.vertices[s].dist = 0
        self.vertices[s].pi = -1

        Q = []
        Q.append(s)

        while len(Q) != 0:
            u = Q.pop(0)

            for v in self.vertices[u].adj:
                if self.vertices[v].color == 'WHITE':
                    self.vertices[v].color = 'GRAY'
                    self.vertices[v].dist = self.vertices[u].dist + 1
                    self.vertices[v].pi = u
                    Q.append(v)
            
            self.vertices[u].color = 'BLACK'

def main():
    # [#11] p.9 graph example
    numVertex = 9
    graph = Graph(numVertex)

    graph.vertices[0].adj = [1, 2, 5]
    graph.vertices[1].adj = [0, 3, 4]
    graph.vertices[2].adj = [0, 3]
    graph.vertices[3].adj = [1, 2, 7]
    graph.vertices[4].adj = [1, 5, 7]
    graph.vertices[5].adj = [0, 4, 6, 8]
    graph.vertices[6].adj = [5, 7, 8]
    graph.vertices[7].adj = [3, 4, 6]
    graph.vertices[8].adj = [5, 6]

    graph.BFS(1)

    for i in range(numVertex):
        print('Vertex', i, ': Distance =', graph.vertices[i].dist, ', Parent =', graph.vertices[i].pi)


if __name__ == '__main__':
    main()