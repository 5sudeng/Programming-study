// C++ 코드를 지피티에게 번역해달라 함

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void swap(int *x, int *y);

// Using array implementation
struct MinHeap {
    int *harr;
    int capacity;
    int heap_size;
};

// Function prototypes
void MinHeapify(struct MinHeap *heap, int i);
int parent(int i);
int left(int i);
int right(int i);
void insertKey(struct MinHeap *heap, int k);
void decreaseKey(struct MinHeap *heap, int i, int new_val);
int extractMin(struct MinHeap *heap);
void deleteKey(struct MinHeap *heap, int i);
int getMin(struct MinHeap *heap);

// Constructor for MinHeap
struct MinHeap *createMinHeap(int cap) {
    struct MinHeap *heap = (struct MinHeap *)malloc(sizeof(struct MinHeap));
    heap->heap_size = 0;
    heap->capacity = cap;
    heap->harr = (int *)malloc(cap * sizeof(int));
    return heap;
}

// Utility function to swap two integers
void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

// Get index of parent of node at index i
int parent(int i) {
    return (i - 1) / 2;
}

// Get index of left child of node at index i
int left(int i) {
    return (2 * i + 1);
}

// Get index of right child of node at index i
int right(int i) {
    return (2 * i + 2);
}

// Insert a new key 'k'
void insertKey(struct MinHeap *heap, int k) {
    if (heap->heap_size == heap->capacity) {
        printf("\nOverflow: Could not insertKey\n");
        return;
    }

    // Insert the new key at the end
    int i = heap->heap_size;
    heap->heap_size++;
    heap->harr[i] = k;

    // Maintain heap property
    while (i != 0 && heap->harr[parent(i)] > heap->harr[i]) {
        swap(&heap->harr[i], &heap->harr[parent(i)]);
        i = parent(i);
    }
}

// Decrease value of key at index i to new_val
void decreaseKey(struct MinHeap *heap, int i, int new_val) {
    heap->harr[i] = new_val;
    while (i != 0 && heap->harr[parent(i)] > heap->harr[i]) {
        swap(&heap->harr[i], &heap->harr[parent(i)]);
        i = parent(i);
    }
}

// Remove minimum element (root) from MinHeap
int extractMin(struct MinHeap *heap) {
    if (heap->heap_size <= 0)
        return INT_MAX;

    if (heap->heap_size == 1) {
        heap->heap_size--;
        return heap->harr[0];
    }

    // Store the minimum value, and remove it from heap
    int root = heap->harr[0];
    heap->harr[0] = heap->harr[heap->heap_size - 1];
    heap->heap_size--;
    MinHeapify(heap, 0);

    return root;
}

// Delete key at index i
void deleteKey(struct MinHeap *heap, int i) {
    decreaseKey(heap, i, INT_MIN);
    extractMin(heap);
}

// Maintain heap property at node i
void MinHeapify(struct MinHeap *heap, int i) {
    int l = left(i);
    int r = right(i);
    int smallest = i;

    if (l < heap->heap_size && heap->harr[l] < heap->harr[i])
        smallest = l;

    if (r < heap->heap_size && heap->harr[r] < heap->harr[smallest])
        smallest = r;

    if (smallest != i) {
        swap(&heap->harr[i], &heap->harr[smallest]);
        MinHeapify(heap, smallest);
    }
}

// Return the minimum key (root) from MinHeap
int getMin(struct MinHeap *heap) {
    return heap->harr[0];
}
