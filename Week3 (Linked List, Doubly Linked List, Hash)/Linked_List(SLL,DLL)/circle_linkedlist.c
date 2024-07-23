#include <stdlib.h>
#include <stdio.h>

/* 원형 연결 리스트
    장점 : 탐색 시 head로 이동할 필요 없음
    끝이 어딘지 모르므로 무한탐색 할 가능성 있음 (while(p!=출발점) 으로 해결) */

typedef int element;
typedef struct __ListNode {
    element data;
    struct __ListNode* next;
} ListNode;

void display(ListNode *head) {
    ListNode *p = head;
    while (p != NULL) {
        printf("%d -> ", p->data);
        p = p->next;
    }
    printf("NULL\n");
}

void insert_first(ListNode** head, ListNode* new_node) {
    if (*head == NULL) {
        *head = new_node;
        new_node->next = new_node;
    } else {
        new_node->next = (*head)->next;
        (*head)->next = new_node;
    }
}

void insert_last(ListNode** head, ListNode* new_node) {
    if (*head == NULL) {
        *head = new_node;
        new_node->next = new_node;
    } else {
        new_node->next = (*head)->next;
        (*head)->next = new_node;
        *head = new_node;
    }
}