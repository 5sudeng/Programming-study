#include <stdio.h>
 
int partition (int arr[], int p, int r){
    int low, high;
    int pivot = arr[p]; // pivot 값 설정
 
    low = p + 1; // low 는 pivot의 바로 다음 위치에서부터
    high = r; // high는 전달된 끝지점
 
    while(low <= high){
        while(arr[low] < pivot) low++; // pivot 보다 작은 값이 나올때마다 이동
        while(arr[high] > pivot) high--; // pivot 보다 큰 값이 나올때마다 이동
 
        if (low <= high){ // low와 high 가 중단된 지점이 서로 위치가 역전된 지점이 아니라면
            int temp = arr[low];    // low 와 high 의 값 변경
            arr[low] = arr[high];
            arr[high] = temp;
        }
    }
 
    // 피벗과 high 위치 교환
    int temp = arr[p];
    arr[p] = arr[high];
    arr[high] = temp;
 
    return high; // 피벗 위치 반환
 
}
 
void quick_sort(int arr[], int left, int right){
    if (left < right){
        int pivot = partition(arr, left, right);
 
        quick_sort(arr, left, pivot-1); // 피벗을 기준으로 왼쪽 배열 정렬
        quick_sort(arr, pivot+1, right); // 피벗 기준으로 오른쪽 배열 정렬
    }
}
int main (){
    int arr [] = {3, 2, 1, 5, 7, 9, 6};
 
    quick_sort(arr, 0, sizeof(arr)/sizeof(arr[0])-1);
 
    for (int i = 0 ; i < sizeof(arr)/sizeof(arr[0]) ; i++){
        printf("%d ", arr[i]);
    }
}