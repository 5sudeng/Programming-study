#include <stdio.h>
#include<stdlib.h> // malloc

void merge(int L[], int first, int mid, int last){
    /*
    L는 정렬할 대상
    */

    int k = first;
    int i = 0;
    int j = 0;
    int n1 = mid -first +1; // size of sub1
    int n2 = last - mid; // size of sub2

    //subarray
    int * sub1 = (int*)malloc(n1*sizeof(int));
    int * sub2 = (int*)malloc(n2*sizeof(int)); 
    // copying
    for(int i =0; i<n1; i++){
        sub1[i] = L[first  +i];
    }
    for(int j=0;j<n2; j++){
        sub2[j] = L[mid +1 +j];
    }

    //merge
    i = 0;
    j= 0;
    k = first;

    while(i<n1 && j<n2){
        if(sub1[i] <=sub2[j]){
            L[k] = sub1[i];
            i++;
        }
        else{
            L[k] = sub2[j];
            j++;
        }
        k++;
    }

    //handling remains
    while(i<n1){
        L[k] = sub1[i];
        i++;
        k++;
    }
    while(j<n2){
        L[k] = sub2[j];
        j++;
        k++;
    }

    //free dynamic arrays
    free(sub1);
    free(sub2);

    

}



void mergeSort(int L[], int first, int last){
    
    if(first<last){
        int mid = first + (last - first)/2;
        mergeSort(L, first, mid);
        mergeSort(L, mid+1, last);
        merge(L, first, mid, last);
    }
}





int main(void){

    int array[] = {7,8,5,8,3,5,9,1};
    int array_size =sizeof(array) / sizeof(array[0]);
    mergeSort(array, 0, array_size-1);

    for (int i= 0; i<array_size ; i++){
        printf("%d", array[i]);
    }
}