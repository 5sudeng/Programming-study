// From 2024-1 CFDS1 Lecture notes and https://www.geeksforgeeks.org/binary-heap/

/*
computing1에서 배운 내용은 heap을 이용한 priority-queue의 구현이다.
여기서는 단순 heap(complete binary tree)에 대해서만 다룬다.
*/

#include<iostream>
#include<climits>
using namespace std;


void swap(int *x, int*y);


class MinHeap
{
    int *harr;// pionter to array in heap
    int capacity;
    int heap_size;

    public:
        MinHeap(int capacity);
        void MinHeapify(int i); // heapify a subtree with the root at given index

        int parent(int i) {return (i-1)/2;}
        int left(int i){return (2*i+1);}
        int right(int i){return (2*i +2);}
        int extractMin(); // extract the root which is the minimum element
        void decreaseKey(int i, int new_val); /// decrease key value of the key at index i to new_val

        int getMin(){return harr[0];} // retrun the minimum value at root
        void deleteKey(int i); // delete a key stored at index i
        void insertKey(int k);// inseart a new key k

};


// constructor
MinHeap::MinHeap(int cap){
    heap_size = 0;
    capacity = cap;
    harr = new int[cap];
}


//insert a new key k
void MinHeap::insertKey(int k)
{
    if (heap_size == capacity){
        cout<<"\nOverflow\n";
        return;    
    }

    // insert the new key at the end
    heap_size++;
    int i= heap_size -1;
    harr[i] = k;


    //fix the min heap property : heapify or percolate up
    while(i!=0 && harr[parent(i)] > harr[i]){
        // parent의 값이 원래 더 작으니, 그걸 위반하는 경우가 보이면 실행
        swap(&harr[i],&harr[parent(i)]);
        i = parent(i);
    }

}


void MinHeap::decreaseKey(int i, int new_val){
    // decrease value of key at index i to new val
    // assumed new_val < harr[i]

    harr[i] = new_val;
    
    //역시 그 이후, heapify: percolate up
    while(i !=0 && harr[parent(i)]> harr[i]){
        swap(&harr[i], &harr[parent(i)]);
        i = parent(i);
    }
}

int MinHeap::extractMin(){
    // method to remove minimum (or root) from min heap

    if (heap_size<=0){
        return INT_MAX;
    }
    if(heap_size ==1){
        heap_size--;
        return harr[0];
    }
    
    int root = harr[0];
    harr[0] = harr[heap_size -1]; // 맨 마지막 값으로 대체
    heap_size--;
    MinHeapify(0); // 0부터 heap property 수정 : 0이하 subtree모두 heapify

    return root;
}

void MinHeap::deleteKey(int i){
    
    // delete key at index i. 
    // index i의 key 값을 INT_MIN으로 바꾸고, extractmin() calling

    decreaseKey(i, INT_MIN);
    extractMin();
}


void MinHeap::MinHeapify(int i){
    // start with index i
    // percolate down 함수임. : 바꾸는 대상은 두 child 중 최소랑 바꿈.

    int l = left(i);
    int r = right(i);
    int smallest = i; // 바꿀 위치 선정
    if(l <heap_size && harr[l] < harr[i]){
        smallest = l;
    }
    if (r < heap_size && harr[r] < harr[smallest]){
        smallest = r;
    }

    if(smallest != i){
        // 바꾸는 대상이 원래와 다를 경우, swap
        swap(&harr[i], &harr[smallest]);
        MinHeapify(smallest); // 거기서부터 다시 재귀적으로 실행
    }
    
}

void swap(int*x, int *y){
    int temp= *x;
    *x = *y;
    *y = temp;
}



int main() 
{ 
    MinHeap h(11); 
    h.insertKey(3); 
    h.insertKey(2); 
    h.deleteKey(1); 
    h.insertKey(15); 
    h.insertKey(5); 
    h.insertKey(4); 
    h.insertKey(45); 
    cout << h.extractMin() << " "; 
    cout << h.getMin() << " "; 
    h.decreaseKey(2, 1); 
    cout << h.getMin(); 
    return 0; 
} 