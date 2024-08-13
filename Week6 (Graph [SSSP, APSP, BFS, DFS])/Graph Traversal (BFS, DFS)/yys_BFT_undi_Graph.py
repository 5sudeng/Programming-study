from collections import deque
'''
BFT : Breadth-First-Traversal
해당 노드에서 sibling(혹은 연결된 모든 neighbors)을 탐색 후, 그 다음 level로 넘어간다.
여기서 level 따지는 법은, 시작한 노드에서 몇개의 edge를 거쳐서 해당 노드를 도달하는 가이다.

this is for undirected graph

'''





class undi_graph():
    def __init__(self, V: list, E:list) -> None :
        self.V = V[:]
        self.neighbors = {}

        for v in V:
            self.neighbors[v] = []

        for(v,w) in E:
            self.neighbors[v].append(w)
            self.neighbors[w].append(v)


    def BFT(self)-> None:
        if self.V:
            visited ={v: False for v in self.V}


        q = deque()
        for v in self.V:
            
            if not visited[v]:
                q.append(v)


                #각 node에 대해 bfs를 진행하는 부분.
                while q:

                    v = q.popleft() # First in, First out

                    #check visited
                    if not visited[v]:
                        visited[v] = True
                        print(v, end = " ")

                        for w in self.neighbors[v]:
                            if not visited[w]:
                                q.append(w)


    #1. shortest path in undirected unweighted graph
    def bfs_shortest_path(self, start, goal)-> list:
        '''
        bfs로 진행하면서 경로 내에 goal이 있다면 가장 먼저 goal에 도달한 path가 shortest path임을 보장한다.
        '''
        if start== goal:
            return [start]
        
        visited = {v: False for v in self.V}
        q = deque([[start]])


        while q: 
            path = q.popleft()
            node = path[-1] ## 가장 최근 node로부터 더 확장해나가는 느낌.

            # 방문을 하지 않았다면
            if not visited[node]:
                visited[node] = True

                for w in self.neighbors[node]:
                    new_path = list(path)
                    new_path.append(w)
                    q.append(new_path)

                    if w == goal:
                        return new_path ## 순환하다 goal이 나타난다면
        return []



    #2.check connectivity
    def are_all_connected(self) -> bool:
        '''
        BFS를 진행하면서 새롭게 visit할 때마다 counting
        그 counting이 vertex와 모두 같다면 모두 connected
        
        '''

        if not self.V :
            return False
        
        visited = {v : False for v in self.V}
        count = 0
        
        # for v in self.V:
        #     q = deque()
        #     q.append(v) # 여기서 연결되지 않아도 모든 node 추가 되게끔.() : 그래서 이 방법은 안됨. 그냥 하나만 가지고 해야함.

        #     ##v와 연결된 모든 vertex를 순회할 것임.
        #     while q:
        #         node = q.popleft()

        #         #traversal 진행여부 여기서 판단.
        #         if not visited[node] : 
        #             visited[node] = True
        #             count +=1
        #             for w in self.neighbors[node]:
        #                 if not visited[w]:
        #                     q.append(w)

        q = deque()
        q.append(self.V[0]) # 하나만 가지고 BFS 일단 진행, 그래야 다 연결된 것만 보니까, 연결 안된 것은 for문으로 해결했음.
        while q:
            node = q.popleft()

            #traversal 진행여부 여기서 판단.
            if not visited[node] : 
                visited[node] = True
                count +=1
                for w in self.neighbors[node]:
                    if not visited[w]:
                        q.append(w)
        
        return count == len(self.V)

    #3. count island
    
    def count_islands(self) -> int:
        if self.V:
            visited ={v: False for v in self.V}

            island_count = 0
        else:
            return 0 
        
        for v in self.V:
            # q = deque()
            # q.append(v) # 모든 것이 한번씩 queue에 들어갔다 나오는 것이 아님.
            
            if not visited[v]: #그 다음 for문 iteration에 대해 연결이 되지 않은 것만 queue를 형성.
                # 대표자 한명에 대해서 새롭게 dequeu 재정의
                q = deque([v])
                island_count +=1 #그때 count


            while q:
                v = q.popleft() # First in, First out

                #check visited
                if not visited[v]:
                    visited[v] = True
                    print(v, end = " ")

                for w in self.neighbors[v]:
                    if not visited[w]:
                        q.append(w)

        return island_count
    
    #4. cycle detection
    

    def cycle_detection(self)-> bool:
        if self.V:
            visited ={v: False for v in self.V}
            parent = {v: None for v in self.V} # 경로 내 바로 직전 parent를 추적

        else:
            return False

        for v in self.V:
            
            #모든 vertex가 아닌 각 island별로 돌리기 위해서.
            if not visited[v]:
                q = deque([v])


            #각 node에 대해 bfs를 진행하는 부분.
            while q:

                v = q.popleft() # First in, First out

                #check visited
                if not visited[v]:
                    visited[v] = True
                    

                    for w in self.neighbors[v]:
                        if not visited[w]:
                            q.append(w)
                            parent[w] = v
                        
                        elif parent[v] !=w: 
                            '''
                            ## v-> w 왔는데, 이미 재방문이고, 
                            w->v가 아니라면!(즉 bidirected가 아니라면)
                            '''
                            
                            return True

        


def main():


    V = [0,1,2,3,4,5,6,7,8,9]
    E = [(0,1),(1,4),(1,5),(2,3),(4,6),(5,6),(5,7),(6,9),(7,8)]

    graph = undi_graph(V,E) # 0 1 4 5 6 7 9 8 2 3


    print("BFT Graph Traversal")
    graph.BFT()
    print("\n")

    print("Shortest Path from 0 to 9:", graph.bfs_shortest_path(0, 9))

    print("Are all nodes connected?", graph.are_all_connected())

    print("Number of islands:", graph.count_islands())

    print("Does the graph have a cycle?", graph.cycle_detection())



if __name__ == "__main__":
    main()