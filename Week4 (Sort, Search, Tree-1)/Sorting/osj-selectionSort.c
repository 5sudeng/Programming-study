// Implement selection sort in C

// Consider the python implementation
// def selection_sort(L:list) -> None:
//     for i in range(len(L)):
//         smallest = i
//         for j in range(i+1, len(L)):
//             if L[j]<L[smallest]:
//                 smallest = j
//         L[i], L[smallest] = L[smallest], L[i]

// Header: void selection_sort(int L[], int size)

#include <stdio.h>

void swap(int *num1, int *num2){
    int temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}

void selection_sort(int L[], int size){
    for(int i=0; i<size; i++){
        int smallest = i;
        for(int j=i+1; j<size; j++){
            if(L[j]<L[smallest]){
                smallest = j;
            }
        }
        // int temp = L[i];
        // L[i] = L[smallest];
        // L[smallest] = temp;
        swap(&L[i], &L[smallest]);
    }
}

int main(){
    int i;
    int size = 5;
    int list[5] = {9, 6, 7, 3, 5};

    selection_sort(list, size); // 리스트라 주소로 안주고 바꿔도 알아서 잘바뀜

    for(i=0; i<size; i++){
        printf("%d\n", list[i]);
    }
    return 0;

}