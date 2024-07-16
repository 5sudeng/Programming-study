#include<stdio.h>



int max(int a, int b) {
    return a > b ? a : b;
}

double averageWaitingTime(int** customers, int customersSize, int* customersColSize) {



    // memory allocation
    /* 
        malloc : void*를 반환
        (sizeof(int)) 메모리 할당 타입
        customerSize*sizeof(int) 만큼 메모리를 할당한 후, pointer반환
        (int*) : type cast : void* -> int*
    */
    int * ends= (int*)malloc(customersSize * sizeof(int));
    if(ends == NULL){
        perror("Failed to allocate memory");
        return -1.0;
    }

    ends[0] = customers[0][0] + customers[0][1];
    double waits = customers[0][1];

    for (int i=0; i<customersSize - 1 ; ++i){

        // max를 직접 구현해야 함.
        ends[i+1] = max(ends[i] , customers[i+1][0]) + customers[i+1][1];
        waits += (max(ends[i] , customers[i+1][0]) - customers[i+1][0]) + customers[i+1][1];
    }

    double averageWaits = waits / customersSize;

    free(ends);
    return averageWaits;


}