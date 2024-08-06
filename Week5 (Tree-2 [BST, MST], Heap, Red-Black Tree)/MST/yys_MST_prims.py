import heapq

def min_distance(points):
    num = len(points)
    distance = 0
    count = 0
    marked = [False] * num


    pq = [] # (cost, vertex)
    heapq.heappush(pq, (0, 0)) # first node, no cost
    while(count < num):
        cost, i = heapq.heappop(pq)

        if (marked[i]):
            continue

        marked[i] = True
        distance +=cost
        count +=1 

        ## node i에 대해 각 점에 대한 distance 계산
        for k in range(num):
            if (not marked[k]):
                d = abs(points[i][0]- points[k][0]) + abs(points[i][1] - points[k][1])
                heapq.heappush(pq, (d,k))
        
    return distance


def main():
    points = [[3,12],[-2, 5], [-4, 1]]
    print(min_distance(points))

if __name__== "__main__":
    main()