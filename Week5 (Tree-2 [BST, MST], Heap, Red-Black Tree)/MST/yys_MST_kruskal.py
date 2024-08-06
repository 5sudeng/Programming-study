class UnionFind:
    def __init__(self, size):

        # 각 node의 set 대표들. 각 parent's rank
        self.parent = list(range(size))
        self.rank = [0]* size

    def find(self, i):
        # find i's set parent

        if self.parent[i] !=i:
            self.parent[i] = self.find(self.parent[i])
        return self.parent[i]
    
    def union(self, x, y):
        #두 node set의 union
        #rank가 큰 쪽으로 합치기, 만약 같다면 합치고 rank 늘려주기
        #여기서 rank 는 "힘" "크기" 정도로 이해하자

        rootX = self.find(x)
        rootY = self.find(y)

        if rootX != rootY:
            if self.rank[x] > self.rank[y]:
                self.parent[rootY] = rootX
            elif self.rank[x] < self.rank[y]:
                self.parent[rootX] = rootY
            else:
                self.parent[rootY] = rootX
                self.rank[rootX] +=1


def minDistance(points):
    num = len(points)
    edges = []

    #make edge list
    for i in range(num):
        for j in range(i+1, num):
            cost = abs(points[i][0]- points[j][0]) + abs(points[i][1] - points[j][1])
            edges.append((cost, i, j))
    
    ## sorting edge list
    edges.sort()

    uf = UnionFind(num)
    distance = 0
    edges_used = 0

    for cost, u, v in edges:
        if uf.find(u) != uf.find(v):
            uf.union(u, v)
            distance += cost
            edges_used +=1
            if edges_used == num-1:
                break

    return distance






if __name__ == "__main__":
    points = [[3, 12], [-2, 5], [-4, 1]]
    print(minDistance(points))