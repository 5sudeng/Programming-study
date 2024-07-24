#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SinglyLinkedList.h"

// Create an empty linked list
linkedList_h* createLinkedList_h(void) {
  linkedList_h* L;
  L = (linkedList_h*)malloc(sizeof(linkedList_h));
  L->head = NULL;
  return L;
}

// Free all memories
void freeLinkedList(linkedList_h* L) {
  listNode* p;
  while (L->head != NULL) {
    p = L->head;
    L->head = L->head->link;
    free(p);
    p = NULL;
  }
}

// Print all nodes
void print(linkedList_h* L) {
  listNode* p;
  p = L->head;
  while (p != NULL) {
    printf("%s ", p->data);
    p = p->link;
  }
  printf("\n");
}

// Insert new node at front
void push_front(linkedList_h* L, char* x) {
  listNode* newNode;
  newNode = (listNode*)malloc(sizeof(listNode));
  strcpy(newNode->data, x);
  newNode->link = L->head;
  L->head = newNode;
}

// Insert new node at back
void push_back(linkedList_h* L, char* x) {
  listNode* newNode;
  listNode* temp;
  newNode = (listNode*)malloc(sizeof(listNode));
  strcpy(newNode->data, x);
  newNode->link = NULL;
  if (L->head == NULL) {  // Empty list
    L->head = newNode;
    return;
  }
  // Not empty
  temp = L->head;
  while (temp->link != NULL)
    temp = temp->link;  // Find last node
  temp->link = newNode;
}

// Insert new node behind pre node
void insert(linkedList_h* L, listNode* pre, char* x) {
  listNode* newNode;
  newNode = (listNode*)malloc(sizeof(listNode));
  strcpy(newNode->data, x);
  if (L->head == NULL) {  // Empty list
    newNode->link = NULL;
    L->head = newNode;
  } else if (pre == NULL) {  // Insert new node at front
    newNode->link = L->head;
    L->head = newNode;
  } else {
    newNode->link = pre->link;  // Insert new node behind pre node
    pre->link = newNode;
  }
}

// Delete node p
void erase(linkedList_h* L, listNode* p) {
  listNode* pre;
  if (L->head == NULL) return;  // Empty list
  if (L->head->link == NULL) {  // Single node in the list
    free(L->head);
    L->head = NULL;
    return;
  } else if (p == NULL)
    return;
  else if (L->head == p) { // To remove the first node
    L->head = p->link;
    free(p);
    return;
  } 
  else {
    pre = L->head;
    while (pre->link != p) {
      pre = pre->link;
    }
    pre->link = p->link;
    free(p);
  }
}

// Delete node at front
void pop_front(linkedList_h* L) {
  listNode *first, *second;
  if (L->head == NULL) return;  // Empty list
  if (L->head->link == NULL) {  // Single node in the list
    free(L->head);
    L->head = NULL;
    return;
  } else {
    first = L->head;
    second = first->link;
    L->head = second;
    free(first);
  }
}

// Delete node at back
void pop_back(linkedList_h* L) {
  listNode *pre, *old;
  if (L->head == NULL) return;  // Empty list
  if (L->head->link == NULL) {  // Single node in the list
    free(L->head);
    L->head = NULL;
    return;
  } else {
    pre = L->head;
    while (pre->link->link != NULL) {
      pre = pre->link;
    }
    old = pre->link;
    pre->link = NULL;
    free(old);
  }
}

// Search node which contains x
listNode* find(linkedList_h* L, char* x) {
  listNode* temp;
  temp = L->head;
  while (temp != NULL) {
    if (strcmp(temp->data, x) == 0)
      return temp;
    else
      temp = temp->link;
  }
  return temp;
}

// Reverse the order of nodes in list
void reverse(linkedList_h* L) {
  listNode* p;
  listNode* q;
  listNode* r;

  p = L->head;
  q = NULL;
  r = NULL;

  while (p != NULL) {
    r = q;
    q = p;
    p = p->link;
    q->link = r;
  }
  L->head = q;
}