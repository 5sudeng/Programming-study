# Queue
- "FIFO (First In, First Out)"
- Pushed into "back" and popped from "front"

## C++

``` C++
#include <queue>
queue<int> qq;
qq.push(10);
qq.front();
qq.pop();
```

Member functions are `empty`, `size`, `front`, `back`, `push`, `pop`, etc.

## C
- Need to implement by hand

``` C
// Using structure
#include <stdbool.h>
#include <stdio.h>
#define MAX_SIZE 100

// Defining the Queue structure
typedef struct {
    int items[MAX_SIZE];
    int front;
    int rear;
} Queue;

// Function to initialize the queue
void initializeQueue(Queue* q) {
    q->front = -1;
    q->rear = 0;
}

bool isEmpty(Queue* q) { return (q->front == q->rear - 1); }

bool isFull(Queue* q) { return (q->rear == MAX_SIZE); }

void enqueue(Queue* q, int value) {
    if (isFull(q)) {
        printf("Queue is full\n");
        return;
    }
    q->items[q->rear] = value;
    q->rear++;
}

void dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return;
    }
    q->front++;
}

int peek(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return -1;
    }
    return q->items[q->front + 1];
}

void printQueue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return;
    }

    printf("Current Queue: ");
    for (int i = q->front + 1; i < q->rear; i++) {
        printf("%d ", q->items[i]);
    }
    printf("\n");
}

int main() {
    Queue q;
    initializeQueue(&q);

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    printQueue(&q);

    printf("Front element: %d\n", peek(&q));

    dequeue(&q);
    printQueue(&q);
    return 0;
}
```

## Python

``` Python
from collections import deque
q = deque([4, 5, 6])
q.append(7)
q.appendleft(3)
q.popleft() # 3
q.pop() # 7
```
- 내부적으로 linked list를 사용함
    - random access의 time complexity: `O(n)`

또는

``` Python
from queue import Queue
q = Queue()
q.put(4)
q.put(5)
q.put(6)
q.get() # 4
```
- 데이터 추가/삭제: `O(1)`
- 인덱스로 접근 불가능