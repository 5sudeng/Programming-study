#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 10

typedef struct {
    int *data;
    int size;
    int capacity;
} PriorityQueue;

void initPriorityQueue(PriorityQueue *pq) {
    pq->data = (int *)malloc(INITIAL_CAPACITY * sizeof(int));
    pq->size = 0;
    pq->capacity = INITIAL_CAPACITY;
}

int isEmpty(PriorityQueue *pq) {
    return pq->size == 0;
}

void resizePriorityQueue(PriorityQueue *pq) {
    pq->capacity *= 2;
    pq->data = (int *)realloc(pq->data, pq->capacity * sizeof(int));
}

void push(PriorityQueue *pq, int value) {
    if (pq->size == pq->capacity) {
        resizePriorityQueue(pq);
    }
    pq->data[pq->size] = value;
    int i = pq->size;
    pq->size++;
    while (i > 0 && pq->data[(i - 1) / 2] < pq->data[i]) {
        int temp = pq->data[i];
        pq->data[i] = pq->data[(i - 1) / 2];
        pq->data[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

int pop(PriorityQueue *pq) {
    if (isEmpty(pq)) {
        printf("Priority Queue is empty\n");
        return -1;
    }
    int topValue = pq->data[0];
    pq->data[0] = pq->data[pq->size - 1];
    pq->size--;
    int i = 0;
    while (2 * i + 1 < pq->size) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = left;
        if (right < pq->size && pq->data[right] > pq->data[left]) {
            largest = right;
        }
        if (pq->data[i] >= pq->data[largest]) {
            break;
        }
        int temp = pq->data[i];
        pq->data[i] = pq->data[largest];
        pq->data[largest] = temp;
        i = largest;
    }
    return topValue;
}

int top(PriorityQueue *pq) {
    if (isEmpty(pq)) {
        printf("Priority Queue is empty\n");
        return -1;
    }
    return pq->data[0];
}

void freePriorityQueue(PriorityQueue *pq) {
    free(pq->data);
    pq->data = NULL;
    pq->size = pq->capacity = 0;
}


int main() {
    PriorityQueue pq;
    initPriorityQueue(&pq);

    push(&pq, 10);
    push(&pq, 20);
    push(&pq, 15);

    printf("Top element: %d\n", top(&pq));

    printf("Popped: %d\n", pop(&pq));
    printf("Top element after pop: %d\n", top(&pq));

    freePriorityQueue(&pq);
    return 0;
}
