#include <stdio.h>
#include <stdlib.h> // for malloc

//node structure
typedef struct linkedNode{
    int val;
    struct LinkedNode*next;
} LinkedNode; // 이러면 struct LinkedNode가 아닌 LinkedNode만 적으면 됌.

//queue structure

typedef struct Queue{
    LinkedNode* front;
    LinkedNode* rear;
    int size;
} Queue;

//make node
LinkedNode* createNode(int value){
    LinkedNode* newnode =  (LinkedNode*)malloc(sizeof(LinkedNode)); // dynamically new node
    newnode->val = value;
    newnode->next =NULL;

    return newnode;
}


//initialization the queue
void initializeQueue(Queue* q){ // pointer로 직접 접근 (참고로 call by reference를 지원하지 않음.)
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
}


int getSize(Queue* q){
    return q->size;

}

int isEmpty(Queue* q){ // boolean을 반환하지만 정수로 변환해서 반환하게 됨. 마찬가지로 쓸대도, 0이 아닌 모든 값은 true로 판정된다.
    return q->size == 0;
}


//get first
int first(Queue* q){
    if (isEmpty(q)){
        printf("empty queue\n");
        return -1;
    }
    return (*q).front->val; // q->front->val과 동치임.
}

void enqueue(Queue*q, int value){
    LinkedNode* newnode = createNode(value);

    if (isEmpty(q)){
        q->front = q->rear = newnode;
    }
    else{
        q->rear->next = newnode;
        q->rear = newnode;
    }
    q->size++;
}

int dequeue(Queue* q){
    if (isEmpty(q)){
        printf("empty queue\n");
        return -1;
    }
    else{
        LinkedNode* node = q->front;
        int value = node->val;

        if (q->size == 1){
            q->front = q->rear= NULL;
        }
        else{
            q->front = q->front->next;
        }

        q->size--;
        free(node); // release node
        return value;

    }
}

void clear(Queue*q){
    while (!isEmpty(q)){
        dequeue(q); // 계속해서 빼내기.
    }
}

void printQueue(Queue*q){
    if(isEmpty(q)){
        printf("empty queue\n");
    }
    else{
        LinkedNode*temp = q->front;
        while(temp){ // untill temp is not NULL
            printf("value : %d\n", temp->val);
            temp = temp->next;
        }
    }
}



void testQueue() {
    Queue q;
    initializeQueue(&q);

    // Test isEmpty and getSize on empty queue
    printf("Initial empty queue test passed: %s\n", isEmpty(&q) ? "True" : "False");
    printf("Initial queue size: %d\n", getSize(&q));

    // Test enqueue
    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    printQueue(&q);  // Expected: 10 -> 20 -> 30 -> None

    // Test first
    printf("First element: %d\n", first(&q));

    // Test isEmpty and getSize after enqueues
    printf("Queue is empty: %s\n", isEmpty(&q) ? "True" : "False");
    printf("Queue size: %d\n", getSize(&q));

    // Test dequeue
    printf("Dequeue: %d\n", dequeue(&q));
    printf("Dequeue: %d\n", dequeue(&q));
    printQueue(&q);  // Expected: 30 -> None

    // Test dequeue until empty
    printf("Dequeue: %d\n", dequeue(&q));
    printf("Dequeue: %d\n", dequeue(&q));  // Expected empty queue message
    printQueue(&q);  // Expected: empty queue

    // Test clear
    enqueue(&q, 40);
    enqueue(&q, 50);
    clear(&q);
    printQueue(&q);  // Expected: empty queue
    printf("Queue is empty after clear: %s\n", isEmpty(&q) ? "True" : "False");
    printf("Queue size after clear: %d\n", getSize(&q));

    printf("All tests passed.\n");
}

// Main function to run test cases
int main() {
    testQueue();
    return 0;
}




