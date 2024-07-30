#include <stdio.h>
#include <stdlib.h>

void printArray(int *L, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", L[i]);
    }
    printf("\n");
}

/*selection sort
뒤에서 하나 선택해서 갖고오기
#O(N^2)
*/
int find_min(int *L, int start_idx, int n) {
    int smallest = start_idx;
    for (int i = start_idx + 1; i < n; i++) {
        if (L[i] < L[smallest]) smallest = i;
    }
    return smallest;
}

void selection_sort(int *L, int n) {
    for (int i = 0; i < n; i++) {
        int smallest = i;
        for (int j = i+1; j < n; j++) {
            if (L[j] < L[smallest]) smallest = j;
        }
        int temp = L[i];
        L[i] = L[smallest];
        L[smallest] = temp;
    }
}



/*insertion sort
O(N^2)
근데 거의 sorting되어있다면 O(kN)
*/
void insertion_sort(int L[], int n) {
    for (int i = 1; i <n; i++) {
        for (int j = i; j >0; j--) {
            if (L[j-1] > L[j]) {
                int temp = L[j];
                L[j] = L[j-1];
                L[j-1] = temp;
            }
            else break;
        }
    }
}




/*merge sort
O(NlogN)
*/
int *arr_slicing(int* arr, int start, int end) {
    int arr_size = end-start;
    int *slice_arr = (int*)malloc(sizeof(int)*arr_size);

    for (int i = 0; i<arr_size; i++) {
        slice_arr[i]= arr[start+i];
    }
    return slice_arr;
}



void merge(int L[], int first, int mid, int last) {
    int k = first;
    int* sub1 = arr_slicing(L, first, mid+1);
    int* sub2 = arr_slicing(L, mid+1, last+1);
    int i = 0;
    int j = 0;

    int len_sub1 = mid+1 - first;
    int len_sub2 = last+1-mid-1;

    while (i<len_sub1 && j<len_sub2) {
        if (sub1[i] <= sub2[j]) {
            L[k] = sub1[i];
            i++;
        }
        else {
            L[k] = sub2[j];
            j++;
        }
        k++;
    }

    if (i < len_sub1) {
        for (int m = k; m< last+1; m++) {
            L[m] = sub1[i];
            i++;
        }
    }
    else if (j < len_sub2) {
        for (int m = k; m < last+1; m++) {
            L[m] = sub2[j];
        }
    }


}



void mergeSortHelp(int* L, int first, int last) { 
    if (first == last) return;
    else {
        int mid = first + (last-first)/2;  
        mergeSortHelp(L, first, mid); 
        mergeSortHelp(L, mid+1, last); 
        merge(L, first, mid, last); 
    }
}



void mergeSort(int *L, int n) {
    mergeSortHelp(L, 0, n-1); 
}


/*
quick sort
pivot 값 정해서 그걸 기준으로 분할하고 swap하기
O(NlogN)
*/
void quick_sort(int *L, int start, int end) {
    if (start >= end) return;

    //pivot 초기값은 첫 번째 요소
    int pivot = start;
    int left = start+1;
    int right = end;

    while (left<=right) {
        //pivot보다 큰 데이터를 찾을때까지 반복
        while (left <= end && L[left] <=L[pivot]) {
            left+=1;
        }
        
        //pivot보다 작은 데이터를 찾을때까지 반복
        while (right>start && L[right] >= L[pivot]) {
            right -=1;
        }
   
        if (left>right)  { //엇갈렸다면 작은 right -=1 데이터와 피봇을 교체 
            int temp = L[right];
            L[right] = L[pivot];
            L[pivot] = temp;
        }
        else { //엇갈리지 않았다면 작은 데이터와 큰 데이터 교체
            int temp = L[left];
            L[left] = L[right];
            L[right] = temp;
        }
    }
    
    //분할 이후 왼쪽 부분과 오른쪽 부분에서 각각 정렬 수행
    quick_sort(L, start, right-1);
    quick_sort(L, right+1, end);
}

//quick_sort(L, 0, len(L)-1)



int main() {
    int L[] = {64, 25, 12, 22, 11};
    int n = sizeof(L) / sizeof(L[0]);

    printf("Original array: ");
    printArray(L, n);

    // Selection Sort
    selection_sort(L, n);
    printf("Sorted array with selection sort: ");
    printArray(L, n);

    // Reinitializing array for insertion sort
    int L2[] = {64, 25, 12, 22, 11};
    insertion_sort(L2, n);
    printf("Sorted array with insertion sort: ");
    printArray(L2, n);

    // Reinitializing array for merge sort
    int L3[] = {64, 25, 12, 22, 13, 18, 20, 11, 9};
    int n3 = sizeof(L3)/sizeof(L3[0]);
    mergeSort(L3, n3);
    printf("Sorted array with merge sort: ");
    printArray(L3, n3);


    int L4[] = {64, 25, 12, 22, 13, 18, 20, 11, 9};
    int n4 = sizeof(L4)/sizeof(L4[0]);
    quick_sort(L4, 0, n4-1);
    printf("Sorted array with quick sort: ");
    printArray(L4, n4);

    return 0;
}
