//
//  main.c
//  stack.c
//
//  Created by Sujeong Oh on 2022/12/15.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int stack[10000];
int stack_top = -1;
int n;

int size(void)
{
    if (stack_top == -1){
        return 0;
    } else
        return stack_top+1 ;
}

int empty(void)
{
    if(stack_top == -1)
        return 1;
    else
        return 0;
}

int full(void)
{
    if (stack_top == n-1)
        return 1;
    else
        return 0;
}

void push(int item)
{
    if (empty())
        stack[0] = item;
    else if (full())
        return;
    else
        stack[stack_top+1] = item;
    stack_top++;
}

int pop(void)
{
    if(empty()) {
        return -1;
    } else {
        int pop = stack[stack_top];
        stack_top--;
        return pop;
    }
}

int top(void)
{
    if(empty()) {
        return -1;
    } else {
        return stack[stack_top];
    }
}

int main(void)
{
    char ins[5];
    int item;
    int res[10000];
    scanf("%d", &n);
    
    int cnt = 0;
    for(int i=0;i<n;i++){
        scanf("%s", ins);
        if (strcmp(ins, "push") == 0){
            scanf("%d", &item);
            push(item);
            continue;}
        else if (strcmp(ins, "pop") == 0){
            res[cnt] = pop();
            cnt++;
            continue;}
        else if (strcmp(ins,"size") == 0){
            res[cnt] = size();
            cnt++;
            continue;}
        else if (strcmp(ins,"empty") == 0){
            res[cnt] = empty();
            cnt++;
            continue;}
        else if (strcmp(ins, "top") == 0){
            res[cnt] = top();
            cnt++;
            continue;}
    }
    
    for(int i=0;i<cnt;i++){
        printf("%d", res[i]);
        if (i != cnt-1)
            puts("");
    }
}
