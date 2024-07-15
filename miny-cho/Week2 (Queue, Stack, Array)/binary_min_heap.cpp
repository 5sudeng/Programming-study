// From 2024-1 CFDS1 Lecture notes and https://www.geeksforgeeks.org/binary-heap/

#include <iostream>
using namespace std;

void swap(int *x, int *y);

// using array implementation
class MinHeap {
    int *harr;
    int capacity; 
    int heap_size;

public:
    MinHeap(int cap) {
        heap_size = 0;
        capacity = cap;
        harr = new int[capacity];
    };

    void MinHeapify(int i);

    int parent(int i) { return (i-1)/2; }
    int left(int i) { return (2*i +1); }
    int right(int i) { return (2*i +2); }

    int extractMin();
    void decreaseKey(int i, int new_val);
    int getMin() { return harr[0]; }

    void deleteKey(int i);
    void insertKey(int k);
};

void MinHeap::insertKey(int k) {
    if (heap_size == capacity) {
        cout << "\nOverflow: Could not insertKey\n";
        return;
    }

    // For structure property
    heap_size++;
    int i = heap_size - 1;
    harr[i] = k;

    // Fix min heap property
    while (i!=0 && harr[parent(i)]>harr[i]) {
        swap(&harr[i], &harr[parent(i)]);
        i = parent(i);
    }
}

// Decrease value of key at index i to new_val where new_val < harr[i]
void MinHeap::decreaseKey(int i, int new_val) {
    harr[i] = new_val;
    while (i!=0 && harr[parent(i)]>harr[i]) {
        swap(&harr[i], &harr[parent(i)]);
        i = parent(i);
    }
}

// Remove root (minimum element)
int MinHeap::extractMin() {
    if (heap_size <= 0) { return INT_MAX; }

    if (heap_size == 1) {
        heap_size--;
        return harr[0];
    }

    int root = harr[0];
    harr[0] = harr[heap_size-1];
    heap_size--;
    MinHeapify(0);
    return root;
}

void MinHeap::deleteKey(int i) {
    decreaseKey(i, INT_MIN);
    extractMin();
}

void MinHeap::MinHeapify(int i) {
    int l = left(i);
    int r = right(i);

    int smallest = i;
    if (l<heap_size && harr[l]<harr[i]) { smallest = l; }
    if (r<heap_size && harr[r]<harr[smallest]) { smallest = r; }
    if (smallest != i) {
        swap (&harr[i], &harr[smallest]);
        MinHeapify(smallest);
    }
}

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}