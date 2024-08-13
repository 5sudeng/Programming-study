'''
graph traversal

DFT (Depth Frist Traversal)
1. 재귀함수 구현
2. stack  구현
'''
from collections import deque 





class directed_graph():
    def __init__(self, V : list, E: list)->None:
        self.V = V[:]
        self.neighbors = {}

        for v in V:
            self.neighbors[v] = []

        for (v, w) in E:
            self.neighbors[v].append(w)
            self.neighbors[w].append(v) #이게 있으면 undirected graph

        self.count_island = 0

    ### 재귀 함수 구현
    def __DFT_preorder_help(self, visited : list, v: int)-> None:
        '''
        visited: 현재까지 marking 된 내용
        v: traversal을 시작할 위치 (굳이 특정 노드에서 시작하지 않아도 되기에, 어떠한 노드에서 시작할 수 있게끔.)
        '''

        if not visited[v]:
            visited[v]  = True
            print(v, end= " ") # visit frist

            #then traversal it's neighbors
            for w in self.neighbors[v]:
                self.__DFT_preorder_help(visited, w)
                

    def DFT_recursive(self)-> None:

        if self.V:
            visited_l = {}
            self.count_island = 0
        
            #initialization
            for v in self.V:
                visited_l[v] = False

            #DFT:
            for v in self.V : # 모든 노드에 대해서도, 그래도 island도 거칠 수 있다.
                self.__DFT_preorder_help(visited_l, v) #연결되어 있는 것들은 여기서 한번에 해결.
                self.count_island+= 1 # counting island
                '''
                **중요부분**

                분명 밖에서 visited_l로 접근했는데, 안에서 별다른 반환이 없었는데, 내부 내용에
                직접 접근을 하게 되면서 내용이 바뀌는 모습이다.
                C, C++ 로 하려면 pointer로 직접 접근해야 함.

                기본적으로 call by reference로 작동하기 때문.
                '''

    def DFT_stack(self):

        if self.V:
            visited_l = {}
            stack = []
            self.count_island = 0

            #initialization
            for v in self.V:
                visited_l[v] = False

            #DFT
            for v in self.V:
                if not visited_l[v]:
                    stack.append(v)

                    #여기서 반복문 시작.
                    while stack:
                        current = stack.pop() #First out

                        if not visited_l[current]:
                            visited_l[current] = True
                            print(current, end = " ")

                            for w in reversed(self.neighbors[current]): # 이건 그냥 재귀함수랑 같은 순서로 하기 위함.
                                if not visited_l[w]:
                                    stack.append(w)
                    
                    
                    #연결되어 있는 경로 모두 탐색 후,
                    self.count_island+= 1 # counting island


    #1. 두 노드 connected 여부 확인
    def are_connected(self, start, end):
        visited = {v: False for v in self.V}
        return self.check_path(visited, start, end)
    
    def check_path(self,visited, start, end) -> bool:
        '''
        특정 두 노드 사이에 path가 있는지 여부 check
        재귀적으로 문제는 앞에서부터 쪼개가면서 진행
        '''

        #base case
        if start == end:
            return True
        
        visited[start] = True

        for w in self.neighbors[start]:

            if not visited[w]:
                ## 계속해서 쪼개면서 나아간다.
                if self.check_path(visited, w, end):
                    return True
            
        return False # 어디에도 걸리지 않으면
        

    # 2. 모든 노드가 연결되어 있는지 확인하는 함수
    def are_all_connected(self)-> bool:
        '''
        idea : 어디서 시작하든, 항상 visited는 모든 값들이 True로 채워져야 한다.
        '''

        for v in self.V:

            visited = {v: False for v in self.V}
            self.__DFT_preorder_help(visited, v)
            if not all(visited.values()): ## 모든 값들이 true가 아니라면, island가 존재
                return False
            
        return True


    def count_islands(self):
        return self.count_island
    

    def has_cycle(self):
        '''
        특정 노드에서 시작하는 cycle_detection 을 모든 노드에 대해 실행하면서
        하나라도 True가 나오면 True로 판단.
        '''
        visited = {v: False for v in self.V}
        rec_stack = {v : False for v in self.V} #현재 재귀 호출이 진행 중인 노드를 추적


        for v in self.V:
            if not visited[v]:
                if self.cycle_detect(v, visited, rec_stack):
                    return True
        return False




    def cycle_detect(self, node, visited, rec_stack) -> bool:
        '''
        현재 node에서 시작해서 dft를 하면서 방문한 노드를 다시 방문할 경우, cycle이 있다고 판단.
        visited vs rec_stack
        - visited 만으로 충분해보일 수 있으나,(다시 방문 여부만 판단한다면.)
        - 이것이 "cycle"인지는 다르다. 예를 들어 A-> B, B<-A는 bidirected edges이지 cycle이 아님.
        - 다시 방문일 수 있지만, 그것이 cycle이 아닐 수도 있다.
        - 그래서 현재 탐색 중인 "경로"에서 재방문이 있는지 표시하기 위한 용도가 "rec_stack"이다.
            -재귀함수가 끝났을 때, False로 다시 돌리는 것도 그 이유이다.

        c.f. graph가 directed일 때랑, undirected일 때랑 결과가 다르다.
        '''

        visited[node] = True
        rec_stack[node] = True

        for w in self.neighbors[node]:
            if not visited[w]:
                if self.cycle_detect(w, visited, rec_stack): #dft식의 재귀함수
                    return True
                
            elif rec_stack[w]: ## 현재 재귀함수 호출에 의한 불리는 node들을 추적하는데, True가 되었다는 것은 cycle이 존재
                # 현재 탐색 경로에 포함되는지를 확인하는 용도이다.
                return True
            

        rec_stack[node]= False #해당 노드와 관련된 경로 탐색이 끝났음을 표시.

                
    def has_cycle2(self):
        if self.V:
            visited = {v : False for v in self.V}

            for v in self.V:
                if not visited[v]:
                    
                    def cycle_detect2(node, visited, parent): 
                        '''
                        특정 노드에서 시작해서 DFT로 진행하면서  cycle이 있는지 
                        검사하는 함수
                        '''

                        visited[node] = True

                        for w in self.neighbors[node]:
                            if not visited[w]:
                                if cycle_detect2(w, visited, v):
                                    return True
                            elif w != parent:
                                '''
                                v-> w로 다시 왔는데, w-> v가 아닌 경우, = cycle
                                '''
                                return True
                        
                        return False
                    
                    if cycle_detect2(v, visited, -1): # 맨 처음 시작은 no parent
                        return True

        return False
        


def main():


    V = [0,1,2,3,4,5,6,7,8,9]
    E = [(0,1),(1,4),(1,5),(2,3),(4,6),(5,6),(5,7),(6,9),(7,8)]

    graph = directed_graph(V,E)
    print("DFT recursive")
    graph.DFT_recursive() # 0 1 4 6 9 5 7 8 2 3 

    print("")
    print("DFT stack")
    graph.DFT_stack() # 0 1 4 6 9 5 7 8 2 3 


    # 1. 두 노드가 연결되어 있는지 확인
    print("Are 0 and 6 connected?", graph.are_connected(0, 6))
    print("Are 0 and 3 connected?", graph.are_connected(0, 3))

    # 2. 모든 노드가 연결되어 있는지 확인
    print("Are all vertices connected?", graph.are_all_connected())

    # 3. 그래프의 분리된 섬의 개수 세기
    print("Number of disjoint islands:", graph.count_islands())

    # 4. 그래프에 사이클이 있는지 확인
    print("Does the graph have a cycle?", graph.has_cycle())

    print("Does the graph have a cycle?", graph.has_cycle2())



if __name__ == "__main__":
    main()