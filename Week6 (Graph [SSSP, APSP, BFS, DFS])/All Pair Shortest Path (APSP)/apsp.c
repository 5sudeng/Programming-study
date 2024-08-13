#include <stdio.h>
#include <limits.h>

#define INF 1000000000

void extendSP(int L_r_1[][4], int W[][4], int L_r[][4], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                if (L_r[i][j] > L_r_1[i][k] + W[k][j]) {
                    L_r[i][j] = L_r_1[i][k] + W[k][j];
                }
            }
        }
    }
}

void slowAPSP(int W[][4], int L_0[][4], int n, int L[][4]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            L[i][j] = L_0[i][j];
        }
    }

    for (int r = 0; r < n - 1; r++) {
        int M[4][4];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                M[i][j] = INF;
            }
        }
        extendSP(L, W, M, n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                L[i][j] = M[i][j];
            }
        }
    }
}

void fasterAPSP(int W[][4], int n, int L[][4]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            L[i][j] = W[i][j];
        }
    }

    int r = 1;
    while (r < n - 1) {
        int M[4][4];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                M[i][j] = INF;
            }
        }
        extendSP(L, L, M, n);
        r *= 2;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                L[i][j] = M[i][j];
            }
        }
    }
}

int main() {
    int n = 4;
    int W[4][4] = {
        {0, 3, 8, INF},
        {INF, 0, 4, 11},
        {INF, INF, 0, 7},
        {4, INF, INF, 0}
    };
    int L_0[4][4] = {
        {0, INF, INF, INF},
        {INF, 0, INF, INF},
        {INF, INF, 0, INF},
        {INF, INF, INF, 0}
    };

    int result_slow[4][4];
    slowAPSP(W, L_0, n, result_slow);
    printf("[Slow] All Pairs Shortest Path matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (result_slow[i][j] == INF) {
                printf("INF ");
            } else {
                printf("%d ", result_slow[i][j]);
            }
        }
        printf("\n");
    }

    int result_faster[4][4];
    fasterAPSP(W, n, result_faster);
    printf("\n[Faster] All Pairs Shortest Path matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (result_faster[i][j] == INF) {
                printf("INF ");
            } else {
                printf("%d ", result_faster[i][j]);
            }
        }
        printf("\n");
    }

    return 0;
}
