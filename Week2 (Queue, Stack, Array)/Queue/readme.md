# Queue

- "FIFO (First In, First Out)"
- Pushed into "back" and popped from "front"

## C++

```C++
#include <queue>
queue<int> qq;
qq.push(10);
qq.front();
qq.pop();
```

Member functions are `empty`, `size`, `front`, `back`, `push`, `pop`, etc.

## C

- Need to implement by hand

```C
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

```Python
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

```Python
from queue import Queue
q = Queue()
q.put(4)
q.put(5)
q.put(6)
q.get() # 4
```

- 데이터 추가/삭제: `O(1)`
- 인덱스로 접근 불가능

---

let's go through an example where enqueue and dequeue operations happen together. This will help demonstrate how the `front` and `rear` pointers move in a circular queue with array resizing.

### Initial Setup

Let's start with a queue of capacity 4:

```
Queue: [_, _, _, _]
front: 0, rear: -1 (initial rear index set to -1)
size: 0
```

### Enqueue and Dequeue Operations

1. **Enqueue 10:**

   ```
   Queue: [10, _, _, _]
   front: 0, rear: 0
   size: 1
   ```

2. **Enqueue 20:**

   ```
   Queue: [10, 20, _, _]
   front: 0, rear: 1
   size: 2
   ```

3. **Dequeue (removing 10):**

   ```
   Queue: [_, 20, _, _]
   front: 1, rear: 1
   size: 1
   ```

4. **Enqueue 30:**

   ```
   Queue: [_, 20, 30, _]
   front: 1, rear: 2
   size: 2
   ```

5. **Enqueue 40:**

   ```
   Queue: [_, 20, 30, 40]
   front: 1, rear: 3
   size: 3
   ```

6. **Dequeue (removing 20):**

   ```
   Queue: [_, _, 30, 40]
   front: 2, rear: 3
   size: 2
   ```

7. **Enqueue 50:**

   ```
   Queue: [50, _, 30, 40]
   front: 2, rear: 0 (wrap around)
   size: 3
   ```

8. **Enqueue 60 (queue is full, so resize happens):**

   - **Allocate new array** with double the capacity (8 in this case):

     ```
     New Queue: [_, _, _, _, _, _, _, _]
     ```

   - **Copy elements in order from old queue to new queue:**
     ```
     New Queue: [30, 40, 50, 60, _, _, _, _]
     front: 0
     rear: 3
     size: 4
     ```

### Continuing Enqueue and Dequeue

9. **Dequeue (removing 30):**

   ```
   New Queue: [_, 40, 50, 60, _, _, _, _]
   front: 1
   rear: 3
   size: 3
   ```

10. **Enqueue 70:**

    ```
    New Queue: [_, 40, 50, 60, 70, _, _, _]
    front: 1
    rear: 4
    size: 4
    ```

11. **Enqueue 80:**

    ```
    New Queue: [_, 40, 50, 60, 70, 80, _, _]
    front: 1
    rear: 5
    size: 5
    ```

12. **Dequeue (removing 40):**

    ```
    New Queue: [_, _, 50, 60, 70, 80, _, _]
    front: 2
    rear: 5
    size: 4
    ```

13. **Dequeue (removing 50):**

    ```
    New Queue: [_, _, _, 60, 70, 80, _, _]
    front: 3
    rear: 5
    size: 3
    ```

14. **Enqueue 90:**

    ```
    New Queue: [_, _, _, 60, 70, 80, 90, _]
    front: 3
    rear: 6
    size: 4
    ```

15. **Enqueue 100:**
    ```
    New Queue: [_, _, _, 60, 70, 80, 90, 100]
    front: 3
    rear: 7
    size: 5
    ```

### Summary of Front and Rear Movement

- **Enqueue** operations move the `rear` pointer forward, wrapping around when it reaches the end of the array.
- **Dequeue** operations move the `front` pointer forward, also wrapping around as necessary.
- When the queue becomes full and another enqueue operation is performed, the array is resized, and elements are copied in order from the old array to the new array.
  - **`front`** is reset to 0.
  - **`rear`** is set to the last index of the copied elements (`size - 1`).

This example demonstrates how enqueue and dequeue operations interact, how the circular nature of the queue works, and how resizing maintains the correct order of elements.
