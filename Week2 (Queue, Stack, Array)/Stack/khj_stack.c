// stack 구현

#include <stdlib.h>
#include <limits.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define ERROR -1

typedef int boolean;
typedef int element;
typedef struct __ArrayStackType {
    element *array;
    int top;
    int capacity;
} Stack;

Stack* createStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (!stack)
        return NULL;
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (element*)malloc(sizeof(element) * stack->capacity);
    return stack;
}

boolean isEmpty(Stack* stack) {
    if (stack->top == -1) {
        return TRUE;
    } else {
        return FALSE;
    }
}

boolean isFull(Stack* stack) {
    if (stack->top == stack->capacity-1) {
        return TRUE;
    } else {
        return FALSE;
    }
}

element top(Stack* stack) {
    if (isEmpty(stack))
        return INT_MIN;
    return stack->array[stack->top];
}

void push(Stack* stack, element data) {
    if (isFull(stack))
        printf("Stack is full.\n");
    else {
        // top을 1 증가시키고, data를 top에 저장
        stack->array[++stack->top] = data;
    }
}

element pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty.\n");
        return INT_MIN;
    } else {
        // top의 값을 가져오고, top을 1 감소시키기
        return stack->array[stack->top--];
    }
        
}

element peek(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty.\n");
        return INT_MIN;
    } else {
        return stack->array[stack->top];
    }
}


int main() {
    Stack *stack = createStack(3);
    push(stack, 1);
    push(stack, 2);
    push(stack, 3);
    push(stack, 4);

    printf("%d poped from stack.\n", pop(stack));
}