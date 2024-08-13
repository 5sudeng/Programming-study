import sys
import math
import queue


class Graph:
    def __init__(self, V):
        self.V = V
        self.adj = [[] for _ in range(V+1)]  #source가 0이라면 in range(V)
        self.dist = {i: math.inf for i in range(V+1)} # source가 0이라면 in range(V)

    def addEdge(self,u,v,w):
        self.adj[u].append((v,w))

    def dijkstra(self, source):
        pq = queue.PriorityQueue()
        S = []
        self.dist[source] = 0
        pq.put((0, source))

        while(not pq.empty()):
            u_d, u = pq.get()
            S.append(u)

            for i in range(len(self.adj[u])):
                v = self.adj[u][i][0]
                w = self.adj[u][i][1]

                if v not in S:
                    if self.dist[v] > self.dist[u]+w:
                        self.dist[v] = self.dist[u] + w
                        pq.put((w, v))

        for i in range(1, self.V+1):
            #source가 0이라면 range(self.V)
            print("Node ", i, ":", self.dist[i])




def main():
    g = Graph(5)
    g.addEdge(1, 2, 8)
    g.addEdge(1, 3, 2)
    g.addEdge(2, 1, 8)
    g.addEdge(2, 4, 10)
    g.addEdge(3, 1, 2)
    g.addEdge(3, 4, 1)
    g.addEdge(3, 5, 7)
    g.addEdge(4, 2, 10)
    g.addEdge(4, 5, 9)
    g.addEdge(5, 3, 7)
    g.addEdge(5, 4, 9)


    source = 1
    g.dijkstra(source)




if __name__ == "__main__":
    main()    