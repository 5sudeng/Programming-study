#include <stdio.h>
#include<stdlib.h>
#define MAX_SIZE 10


struct NODE
{
    struct NODE * next; //NODE type pointer
    int data;
};
int node_cnt = 0;
struct NODE* top = NULL;


int stack_full(){
    if (node_cnt >= MAX_SIZE)
        return 1;
    return 0;
}

int stack_empty(){
    if (node_cnt = 0){
        return 1;
    }
    return 0;
}

void push(int n){

    // 헷갈리지말자! : 지금 여기서 구현하는 것은 linked list로 구현이라, 전체 메모리 크기를 고려를 안해도 되지만,
    // 구현 상, max_size를 정해두었으므로 한번 집고 넘어가는 것임.
    // array구현이었다면, resize가 필요함.

    
    if(!stack_full()){

        //new node
        struct NODE* newnode = malloc(sizeof(struct NODE));
        if (newnode == NULL){
            return; //메모리 할당이 안되었다면.
        }
        newnode->data = n;
        newnode->next = NULL;

        node_cnt++;
        if(top=!NULL){
            //top에 뭐가 있다면. 옮겨놓기.
            newnode->next =top;
        }
        top = newnode; // 어떠한 경우라도, 항상 top은 새로운 친구.
    }

  



}

void pop(){

    
    if (!stack_empty()){
        //top 부분을 빼오고, top-> next로 대체
        struct Node * temp  = top;
        int value = top->data;
        top = top->next;

        free(temp);
        node_cnt--;
        return value;
        
    }
    //if empty, do nothing
    return;

}

void print_stack(){
    if(stack_empty())
    {
        printf("stack empty\n");
    }
    else{
        struct NODE* temp;
        temp = top;
        while(temp){
            printf("%d", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }

}


int main()
{
    for(int i = 0; i<10 ; i++){
        push(i);
    }

    print_stack();
}



