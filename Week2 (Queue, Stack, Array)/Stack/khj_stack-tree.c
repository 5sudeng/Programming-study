struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

#include <stdbool.h>

// 2265. Count Nodes Equal to Average of Subtree
// stack 구현
// 함수 : isEmpty(), isFull(), push(val), pop()
#define STACK_SIZE 1000
struct TreeNode* stack[STACK_SIZE];
int top = -1;
int isEmpty() {
    if (top < 0) {
        return true;
    } else {
        return false;
    }
}
int isFull() {
    if (top >= STACK_SIZE-1) {
        return true;
    } else {
        return false;
    }
}
struct TreeNode* topp() {
    return stack[top];
}
void push(struct TreeNode* val) {
    if (isFull()) {
        printf("stack is full.\n");
    } else {
        stack[++top] = val;
    }
}
struct TreeNode* pop() {
    if (isEmpty()) {
        printf("stack is empty.\n");
        return 0;
    } else {
        return stack[top--];
    }
}