// deque 구현
#define TRUE 1
#define FALSE 0
#define ERROR -1

typedef int boolean;
typedef int element;
typedef struct __dequeType {
    element *data;
    int front;
    int rear;
} Deque;

void init_deque(Deque *q, int dequeSize) {
    q->data = (element *)malloc(sizeof(element) * dequeSize);
    q->front = 0;
    q->rear = 0;
}
boolean is_empty(Deque *q) {
    if (q->front == q->rear) {
        return TRUE;
    } else {
        return FALSE;
    }
}
boolean is_full(Deque *q, int dequeSize) {
    if (((q->rear+1) % dequeSize) == q->front) {
        return TRUE;
    } else {
        return FALSE;
    }
}
element get_front(Deque *q, int dequeSize) {
    if (is_empty(q)) {
        printf("deque is empty.\n");
        return ERROR;
    }
    return q->data[(q->front+1) % dequeSize];
}
element get_rear(Deque *q) {
    if (is_empty(q)){
        printf("deque is empty.\n");
        return ERROR;
    }
    return q->data[q->rear];
}
void add_front(Deque *q, element data, int dequeSize) {
    if (is_full(q, dequeSize)) {
        printf("deque is full.\n");
        return;
    }

    q->data[q->front] = data;
    q->front = (q->front - 1 + dequeSize) % dequeSize;
    return;
}
void add_rear(Deque *q, element data, int dequeSize) {
    if (is_full(q, dequeSize)) {
        printf("deque is full.\n");
        return;
    }

    q->rear = (q->rear + 1) % dequeSize;
    q->data[q->rear] = data;
}
element delete_front(Deque *q, int dequeSize) {
    if (is_empty(q)) {
        printf("deque is empty.\n");
        return ERROR;
    }

    element tmp = get_front(q, dequeSize);
    q->front = (q->front + 1) % dequeSize;
    return tmp;
}
element delete_rear(Deque *q, int dequeSize) {
    if (is_empty(q)) {
        printf("deque is empty.\n");
        return ERROR;
    }

    element tmp = get_rear(q);
    q->rear = (q->rear - 1 + dequeSize) % dequeSize;
    return tmp;
}


int main() {
    Deque *result = (Deque *)malloc(sizeof(Deque));
    int dequeSize = 100;

    init_deque(result, dequeSize);

    add_front(result, 0, dequeSize);

    // rotate
    add_front(result, get_rear(result), dequeSize);
    delete_rear(result, dequeSize);


    // deque(result) -> array(answer) 로 변환
    int *answer = (int *)malloc(sizeof(int) * dequeSize);
    int i = (result->front+1) % dequeSize;
    int answerIdx = 0;
    while (i != result->rear) {
        answer[answerIdx++] = result->data[i];
        i = (i+1) % dequeSize;
    }
    answer[answerIdx] = result->data[i];

}