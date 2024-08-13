INF = 1e+9

def extendSP(L_r_1, W, L_r, n: int):
    for i in range(n):
        for j in range(n):
            for k in range(n):
                if L_r[i][j] > L_r_1[i][k] + W[k][j]:
                    L_r[i][j] = L_r_1[i][k] + W[k][j]

def slowAPSP(W, L_0, n: int):
    L = [[INF for i in range(n)] for i in range(n)]

    L = L_0
    for r in range(n-1):
        M = [[INF for i in range(n)] for i in range(n)]
        extendSP(L, W, M, n)
        L = M
    
    return L

def fasterAPSP(W, n: int):
    L = [[INF for i in range(n)] for i in range(n)]

    L = W
    r = 1
    while r < n-1:
        M = [[INF for i in range(n)] for i in range(n)]
        extendSP(L, L, M, n)
        r *= 2
        L = M
    
    return L

def main():
    n = 4
    W = [
        [0, 3, 8, INF],
        [INF, 0, 4, 11],
        [INF, INF, 0, 7],
        [4, INF, INF, 0]
    ]
    L_0 = [
        [0, INF, INF, INF],
        [INF, 0, INF, INF],
        [INF, INF, 0, INF],
        [INF, INF, INF, 0]
    ]

    result = slowAPSP(W, L_0, n)
    print("[Slow] All Pairs SHortest Path matrix:")
    for i in range(n):
        for j in range(n):
            if result[i][j] == INF:
                print("INF", end=' ')
            else:
                print(result[i][j], end=' ')
        print()
    
    print()
    result = fasterAPSP(W, n)
    print("[Faster] All Pairs SHortest Path matrix:")
    for i in range(n):
        for j in range(n):
            if result[i][j] == INF:
                print("INF", end=' ')
            else:
                print(result[i][j], end=' ')
        print()


if __name__ == "__main__":
    main()