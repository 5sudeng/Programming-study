#include <stdio.h>
#include <stdlib.h>

#include "cQueue.h"

QueueType* createCQueue(void) {
  QueueType* cQ;
  cQ = (QueueType*)malloc(sizeof(QueueType));
  cQ->front = 0;
  cQ->rear = 0;
  return cQ;
}

// Check whether queue is empty
int isEmpty(QueueType* cQ) {
    if (cQ->front == cQ->rear){
        printf("Circular Queue is empty!\n");
        return 1;
    }
    return 0;
}

// Check whether queue is full
int isFull(QueueType* cQ) {
    if (((cQ->rear + 1)%cQ_SIZE)==cQ->front){
        printf("Circular Queue is full!\n");
        return 1;
    }
    return 0;
}

// Push item at rear
void push(QueueType* cQ, element item) {
    if (isFull(cQ))
        return;
    cQ->rear = (cQ->rear+1)%cQ_SIZE ;
    cQ->queue[cQ->rear] = item;
}

// Return item at front and delete
element pop(QueueType* cQ) {
    if (isEmpty(cQ))
        return -1;
    cQ->front = (cQ->front+1)%cQ_SIZE ;
    return cQ->queue[cQ->front];
}

// Return item at front
element front(QueueType* cQ) {
    if (isEmpty(cQ))
        return -1;
    return cQ->queue[(cQ->front+1)%cQ_SIZE];
}

// Return item at rear
element back(QueueType* cQ) {
    if (isEmpty(cQ))
        return -1;
    return cQ->queue[cQ->rear];
}

// Print all items
void print(QueueType* cQ) {
    if (isEmpty(cQ))
        return;
    int tmp;
    tmp = cQ->front + 1;
    do{
        tmp%=cQ_SIZE;
        printf("%d ", cQ->queue[tmp]);
        tmp ++;
    } while ((tmp%cQ_SIZE)!=((cQ->rear + 1)%cQ_SIZE));
    puts("");
}
