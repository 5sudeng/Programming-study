//
//  main.c
//  dfsbfs
//
//  Created by Sujeong Oh.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROW 1001
#define COL 1001

int matrix[ROW][COL];
int visited[ROW] = {0};

int stack_top = -1;
int stack_size = ROW;
int stack[ROW];

int front = 0;
int rear = 0;
int queue[ROW];

int size_stack(void) {
  if (stack_top <= 0)
    return 0;
  else
    return stack_top + 1;
}

int empty_stack(void) {
  if (stack_top == -1)
    return 1;
  else
    return 0;
}

int full_stack(void) {
  if (stack_top == stack_size - 1)
    return 1;
  else
    return 0;
}

void push_stack(int item) {
  if (full_stack()) {
    return;
  } else {
    *(stack + ++stack_top) = item;
  }
}

int pop_stack(void) {
  if (empty_stack()) {
    return 0;
  } else {
    return *(stack + stack_top--);
  }
}

int top_stack(void) {
  if (empty_stack()) {
    return 0;
  } else {
    return *(stack + stack_top);
  }
}

void dfs(int start, int max) {
    for(int i=0;i<max;i++)
        visited[i] = 0;
    visited[start] = 1;
    printf("%d ", start);
    while (empty_stack()!=1){
        for(int i=0;i<COL;i++){
            if(matrix[start][i]==1){
                if(visited[i]==0){
                    push_stack(start);
                    visited[i] = 1;
                    printf("%d ", i);
                    start = i;
                } else
                    start = pop_stack();
            }
        }
    }
}

int empty_queue(void) {
  if (front == rear) {
    return 1;
  } else
    return 0;
}

int full_queue(void) {
  if (((rear + 1) % ROW) == front) {
    return 1;
  } else
    return 0;
}

void push_queue(int item) {
  if (full_queue())
    return;
  else {
    rear = (rear + 1) % ROW;
    queue[rear] = item;
  }
}

int pop_queue(void) {
  if (empty_queue()) {
    return -1;
  } else {
    front = (front + 1) % ROW;
    return queue[front];
  }
}

int front_queue(void) {
  if (empty_queue()) {
    return -1;
  }

  else
    return queue[(front + 1) % ROW];
}

void bfs(int start, int max) {
    for(int i=0;i<max;i++)
        visited[i] = 0;
    visited[start] = 1;
    visited[start] = 1;
    while (empty_queue()!=1){
        while (empty_stack()!=1){
            for(int i=0;i<COL;i++){
                if(matrix[start][i]==1){
                    if(visited[i]==0){
                        visited[i] = 1;
                        printf("%d ", i);
                        push_queue(i);
                    }
                }
            }
    }
        start = pop_queue();
}
}

int main(void) {
  int i, N, M, V, first, second;
  //int j = 0;

  scanf("%d", &N);
  rewind(stdin);
  scanf("%d", &M);
  rewind(stdin);
  scanf("%d", &V);
  rewind(stdin);

  for (i = 0; i < M; i++) {
    scanf("%d", &first);
    rewind(stdin);
    scanf("%d", &second);
    rewind(stdin);
    matrix[first][second] = 1;
    matrix[second][first] = 1;
  }

  dfs(V, N);
  for (i = 0; i < ROW; i++)
    visited[i] = 0;
  //memset(visited, 0, sizeof(visited));
  printf("\n");
  bfs(V, N);
}
