#include <iostream>
#include <vector>
using namespace std;


void printArray(vector<int> &L) {
    for (int i = 0; i < L.size(); i++) {
        cout << L[i] << " ";
    }
    cout<<endl;
}

/*selection sort
뒤에서 하나 선택해서 갖고오기
#O(N^2)
*/

int find_min(vector<int> &L, int start_idx) {
    int smallest = start_idx;
    for (int i = start_idx + 1; i < L.size(); i++) {
        if (L[i] < L[smallest]) smallest = i;
    }
    return smallest;
}

void selection_sort(vector<int> &L) {
    for (int i = 0; i < L.size(); i++) {
        int smallest = i;
        for (int j = i+1; j < L.size(); j++) {
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
void insertion_sort(vector<int> &L) {
    for (int i = 1; i <L.size(); i++) {
        for (int j = i; j >0; j--) {
            if (L[j-1] > L[j]) {
                swap(L[j], L[j-1]);
            }
            else break;
        }
    }
}




/*merge sort
O(NlogN)
*/
vector<int> arr_slicing(vector<int> &arr, int start, int end) {
    int arr_size = end-start;
    vector<int> slice_arr;

    for (int i = 0; i<arr_size; i++) {
        slice_arr.push_back(arr[start+i]);
    }
    return slice_arr;
}



void merge(vector<int> &L, int first, int mid, int last) {
    int k = first;    
    vector<int> sub1 = vector<int> (L.begin() + first, L.begin()+mid+1); //or arr_slicing(L, first, mid+1);
    vector<int> sub2 = vector<int> (L.begin()+mid+1, L.end()+1); //or arr_slicing(L, mid+1, last+1);
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



void mergeSortHelp(vector<int> &L, int first, int last) { 
    if (first == last) return;
    else {
        int mid = first + (last-first)/2;  
        mergeSortHelp(L, first, mid); 
        mergeSortHelp(L, mid+1, last); 
        merge(L, first, mid, last); 
    }
}



void mergeSort(vector<int> &L) {
    mergeSortHelp(L, 0, L.size()-1); 
}



/*
quick sort
pivot 값 정해서 그걸 기준으로 분할하고 swap하기
O(NlogN)
*/
void quick_sort(vector<int> &L, int start, int end) {
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
            swap(L[right], L[pivot]);
        }
        else { //엇갈리지 않았다면 작은 데이터와 큰 데이터 교체
            swap(L[left], L[right]);
        }
    }
    
    //분할 이후 왼쪽 부분과 오른쪽 부분에서 각각 정렬 수행
    quick_sort(L, start, right-1);
    quick_sort(L, right+1, end);
}

//quick_sort(L, 0, len(L)-1)


int main() {
    vector<int> L = {64, 25, 12, 22, 11};
    
    cout<<"Original array: ";
    printArray(L);

    // Selection Sort
    selection_sort(L);
    cout<<"Sorted array with selection sort: ";
    printArray(L);

    // Reinitializing array for insertion sort
    vector<int> L2 = {64, 25, 12, 22, 11};
    insertion_sort(L2);
    cout<<"Sorted array with insertion sort: ";
    printArray(L2);

    // Reinitializing array for merge sort
    vector<int> L3 = {64, 25, 12, 22, 13, 18, 20, 11, 9};
    mergeSort(L3);
    cout<<"Sorted array with merge sort: ";
    printArray(L3);

    vector<int> L4 = {64, 25, 12, 22, 13, 18, 20, 11, 9};
    quick_sort(L4, 0, L4.size()-1);
    cout<<"Sorted array with quick sort: ";
    printArray(L4);

    return 0;
}