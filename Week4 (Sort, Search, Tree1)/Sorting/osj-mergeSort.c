#include <stdio.h>
#include <stdlib.h>

void merge(char* sorted, char* data, int start, int mid, int end){
    int i = start;
    int j = mid+1;
    int k = start;

    while(i<=mid && j<=end){
        if(data[i]<=data[j]){
            sorted[k] = data[i];
            i++;
        }
        else{
            sorted[k] = data[j];
            j++;
        }
        k++;
    }
    if(i>mid){
        for(int t=j; t<=end; t++){
            sorted[k] = data[t];
            k++;
        }
    }
    else{
        for(int t=i; t<=mid; t++){
            sorted[k] = data[t];
            k++;
        }
    }
    for(int t=start; t<=end; t++){
        data[t] = sorted[t];
    }
}

void merge_sort(char* sorted, char* data, int start, int end){
    if(start<end){
        int mid = (start+end)/2;
        merge_sort(sorted, data, start, mid);
        merge_sort(sorted, data, mid+1, end);
        merge(sorted, data, start, mid, end);
    }
}


int main(){
    char data[] = "36712485";
    char* sorted_data = (char*)malloc(sizeof(char)*8);

    merge_sort(sorted_data, data, 0, 7);
    printf("%s", data);
    return 0;
}
