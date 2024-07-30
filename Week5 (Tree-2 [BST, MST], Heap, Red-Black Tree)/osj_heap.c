#include "heap.h"

#include <stdio.h>
#include <stdlib.h>

// Create an empty heap
heapType* createHeap(void) {
  heapType* h = (heapType*)malloc(sizeof(heapType));
  h->heap_size = 0;
  return h;
}

// Insert node that has item to heap
void push(heapType* h, int item) {
    h->heap_size += 1;
    int i = h->heap_size;
    while (1){
        if (i==1)
            break;
        if (item <= h->heap[i/2])
            break;
        h->heap[i] = h->heap[i/2];
        i = i/2;
    }
    h->heap[i] = item;
}

// Return root
int top(heapType* h) {
    if (h->heap_size == 0)
        return -1;
    return h->heap[1];
}

// Remove root
void pop(heapType* h) {
    if (h->heap_size == 0)
        return;
    int temp = h->heap[h->heap_size];
    h->heap_size -= 1;
    int i=1, j=2;
    while (j <= h->heap_size){
        if (j < h->heap_size){
            if (h->heap[j] < h->heap[j+1])
                j++;
        }
        if (temp >= h->heap[j])
            break;
        else{
            h->heap[i] = h->heap[j];
            i = j;
            j *= 2;
        }
    }
    h->heap[i] = temp;
}

// Print
void print(heapType* h) {
    for(int i=1;i<=h->heap_size;i++)
        printf("%d ", h->heap[i]);
    puts("");
}

// Return number of elements
int size(heapType* h) {
    return h->heap_size;
}
