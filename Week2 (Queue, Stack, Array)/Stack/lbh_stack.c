/*
    Method Explanations

    1.	push: Adds an element to the top of the stack. If the stack is full, it calls the resize method to double the capacity.
	2.	pop: Removes and returns the top element of the stack. If the stack is empty, it prints an error message and returns -1.
	3.	peek: Returns the top element of the stack without removing it. If the stack is empty, it prints an error message and returns -1.
	4.	clear: Clears the stack by resetting top to -1.
	5.	resize: Doubles the capacity of the stack, copies the elements to the new array, and updates the capacity.
	6.	get_size: Returns the current size of the stack.
*/

#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 10

typedef struct {
    int *data;
    int top;
    int capacity;
} Stack;

// Function to initialize the stack
void initStack(Stack *stack) {
    stack->data = (int *)malloc(INITIAL_CAPACITY * sizeof(int));
    stack->top = -1;
    stack->capacity = INITIAL_CAPACITY;
}

// Function to check if the stack is empty
int isEmpty(Stack *stack) {
    return stack->top == -1;
}

// Function to check if the stack is full
int isFull(Stack *stack) {
    return stack->top == stack->capacity - 1;
}

// Function to resize the stack
void resizeStack(Stack *stack) {
    stack->capacity *= 2;
    stack->data = (int *)realloc(stack->data, stack->capacity * sizeof(int));
}

// Function to push an element onto the stack
void push(Stack *stack, int value) {
    if (isFull(stack)) {
        resizeStack(stack);
    }
    stack->data[++stack->top] = value;
}

// Function to pop an element from the stack
int pop(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        return -1;
    }
    return stack->data[stack->top--];
}

// Function to peek at the top element of the stack
int peek(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        return -1;
    }
    return stack->data[stack->top];
}

// Function to clear the stack
void clearStack(Stack *stack) {
    stack->top = -1;
}

// Function to free the stack
void freeStack(Stack *stack) {
    free(stack->data);
    stack->data = NULL;
    stack->top = stack->capacity = 0;
}

// Main function to demonstrate usage
int main() {
    Stack stack;
    initStack(&stack);

    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);

    printf("Top element: %d\n", peek(&stack));

    printf("Popped: %d\n", pop(&stack));
    printf("Top element after pop: %d\n", peek(&stack));

    push(&stack, 40);
    printf("Top element after pushing 40: %d\n", peek(&stack));

    printf("Stack size: %d\n", stack.top + 1);
    clearStack(&stack);
    printf("Stack size after clearing: %d\n", stack.top + 1);

    freeStack(&stack);
    return 0;
}