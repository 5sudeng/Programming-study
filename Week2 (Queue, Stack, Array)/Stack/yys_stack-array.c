#include<stdio.h>
#include <stdbool.h>
#include<stdlib.h> // malloc
#define INITIAL_SIZE 100


int stack[INITIAL_SIZE]; //aray : 이렇게 고정된 상태면 resize를 못함.
int MAX_STACK_SIZE = INITIAL_SIZE;
// stack = (int*)malloc(MAX_STACK_SIZE*sizeof(int)); // global scope에서는 동적 할당 불가능 -> main에서 해야함.
int top = -1; // top index


int IsEmpty(){
    if(top<0){
        return true;
    }
    else{
        return false;
    }
}

int isFull(){
    if(top >=MAX_STACK_SIZE-1){
        return true;
    }
    else{
        return false;
    }
}


void push(int value){
    if (isFull() ==true){
        printf("full stack");

        
       // for resize : using dynamic allocation : malloc & realloc

    }
    else{
        stack[++top] = value; // top을 늘리면서 넣기
    }
}

int pop(){
    if (IsEmpty() == true){
        printf("empty stack");
    }
    else{
        return stack[top--];
    }
}

int main(){
    push(3);
    push(5);

    printf("%d ",pop());
    printf("%d ",pop());
    printf("%d ",pop());
 
    return 0;
}
