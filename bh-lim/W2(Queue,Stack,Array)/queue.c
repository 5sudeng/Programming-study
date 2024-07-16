/*
    Method Explanations

	1.	enqueue: Adds an element to the end of the queue.
	2.	dequeue: Removes and returns the element at the front of the queue.
	3.	peek: Returns the element at the front of the queue without removing it.
	4.	is_empty: Checks if the queue is empty.
    5.	size: Returns the number of elements in the queue.
	6.	clear: Removes all elements from the queue.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int front;
    int rear;
    int size;
    int capacity;
} Queue;

// Function to initialize the queue
void initQueue(Queue *q, int initialCapacity) {
    q->data = (int *)malloc(initialCapacity * sizeof(int));
    q->front = 0;
    q->rear = -1;
    q->size = 0;
    q->capacity = initialCapacity;
}

// Function to check if the queue is empty
int isEmpty(Queue *q) {
    return q->size == 0;
}

// Function to get the size of the queue
int size(Queue *q) {
    return q->size;
}

// Function to resize the queue
void resizeQueue(Queue *q) {
    int newCapacity = q->capacity * 2;
    int *newData = (int *)malloc(newCapacity * sizeof(int));

    for (int i = 0; i < q->size; i++) {
        newData[i] = q->data[(q->front + i) % q->capacity];
    }

    free(q->data);
    q->data = newData;
    q->capacity = newCapacity;
    q->front = 0;
    q->rear = q->size - 1;
}

// Function to add an element to the queue
void enqueue(Queue *q, int element) {
    if (q->size == q->capacity) {
        resizeQueue(q);
    }
    q->rear = (q->rear + 1) % q->capacity;
    q->data[q->rear] = element;
    q->size++;
}

// Function to remove an element from the queue
int dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return -1;
    }
    int element = q->data[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size--;
    return element;
}

// Function to get the front element of the queue
int peek(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return -1;
    }
    return q->data[q->front];
}

// Function to clear the queue
void clearQueue(Queue *q) {
    q->front = 0;
    q->rear = -1;
    q->size = 0;
}

// Function to free the queue
void freeQueue(Queue *q) {
    free(q->data);
    q->data = NULL;
    q->front = q->rear = q->size = q->capacity = 0;
}

// Main function to demonstrate usage
int main() {
    Queue q;
    initQueue(&q, 2);
    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);

    printf("Front element: %d\n", peek(&q));

    printf("Dequeued: %d\n", dequeue(&q));
    printf("Front element after dequeue: %d\n", peek(&q));

    printf("Queue size: %d\n", size(&q));
    clearQueue(&q);
    printf("Queue size after clearing: %d\n", size(&q));

    freeQueue(&q);
    return 0;
}