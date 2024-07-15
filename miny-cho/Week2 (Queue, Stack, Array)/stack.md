# Stack
- "LIFO (Last In, First Out)"
- Pushed and popped from "back", which is `top` of the stack

## C++

``` C++
#include <stack>
stack<int> stack;
stack.push(10)
stack.push(20)
stack.pop() // 20
```

Member functions are `top`, `size`, `empty`, `swap`, etc.

## C
- Need to implement by hand

``` C
// Using array

#include<stdio.h>
#define MAX_STACK_SIZE 100
 
int stack[MAX_STACK_SIZE];
int top = -1;
 
int isEmpty() {
    return top < 0;
}

int isFull() {
    return top >= MAX_STACK_SIZE-1; 
}
 
void push(int value) {
    if (isFull() == true) { printf("Stack is full"); }
    else { stack[++top] = value; }
}
 
int pop() {
    if (isEmpty() == true) { printf("Stack is empty"); }
    else { return stack[top--]; }
}
```

또는

``` C
// Using structure, dynamic memory allocation
// Stack of students

#include <stdio.h>
#include <stdlib.h>
#define MAX_STRING 100

typedef struct{
   int student_number;
   char student_name[MAX_STRING];
   char student_address[MAX_STRING];
} student;

typedef struct{
    student * data;
    int capacity;  
    int top;
} Stack;

void init_stack(Stack *s){
    s->top=-1;
    s->capacity=1;
    s->data=(student *)malloc(sizeof(student) * s->capacity);
}

int is_empty(Stack *s){
    return s->top == -1;
}

int is_full(Stack *s){
    return s->top == (s->capacity-1);
}

void push(Stack *s, student object){
    if (is_full(s)) {
        s->capacity *= 2;
        s->data=(student *)realloc(s->data, sizeof(student) * s->capacity);
    }
    s->data[++s->top] = object;
}

student pop(Stack *s) {
    if (is_empty(s)) {
        fprintf(stderr,"UNDERFLOW\n");
        exit(1);
    }
    else return s->data[s->top--];
}

student peek(Stack *s){
    if (is_empty(s)) {
        fprintf(stderr,"UNDERFLOW\n");
        exit(1);
    }
    else return s->data[s->top];
}

int main(void) {
    Stack s;
    init_stack(&s);
    student kys = {
            201511796, "KYS", "Seoul"
    };
    student object;

    push(&s, kys);
    object = pop(&s);

    printf("student number: %d\n", object.student_number);
    printf("student name: %s\n", object.student_name);
    printf("student address: %s\n", object.student_address);

    return 0;
}

```

## Python
- 그냥 리스트를 써도 됨: `append`, `pop` 등
- 또는 `deque`, `LifoQueue`를 쓸 수 있음

``` Python
from collections import deque
stack = deque()
stack.append('a')
stack.append('b')
print(stack.pop()) # 'b'
```

``` Python
from queue import LifoQueue
stack = LifoQueue(maxsize = 10) # default = 무한
stack.put('a')
stack.put('b')
print(stack.get()) # 'b'
```

Other methods are `empty`, `full`, `qsize`, etc.

## References
- C code sourced from
    - https://minimin2.tistory.com/3 and
    - https://velog.io/@kysung95/%EC%9E%90%EB%A3%8C%EA%B5%AC%EC%A1%B0%EB%A1%A0-C%EB%A1%9C-%EC%8A%A4%ED%83%9D%EC%9D%84-%EB%A7%8C%EB%93%A4%EC%9E%90