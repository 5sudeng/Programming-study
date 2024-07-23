#include <stdio.h>
#include <stdlib.h>

// Node structure
typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

// Doubly linked list structure with sentinel nodes
typedef struct {
    Node* head;
    Node* tail;
    int size;
} DoublyLinkedList;

// Function to initialize the doubly linked list with sentinel nodes
void initList(DoublyLinkedList* list) {
    list->head = (Node*)malloc(sizeof(Node));
    list->tail = (Node*)malloc(sizeof(Node));
    list->head->next = list->tail;
    list->head->prev = NULL;
    list->tail->next = NULL;
    list->tail->prev = list->head;
    list->size = 0;
}

// Function to insert a node at the beginning of the list
void insertFirst(DoublyLinkedList* list, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = list->head->next;
    newNode->prev = list->head;
    list->head->next->prev = newNode;
    list->head->next = newNode;
    list->size++;
}

// Function to insert a node at the end of the list
void insertLast(DoublyLinkedList* list, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = list->tail;
    newNode->prev = list->tail->prev;
    list->tail->prev->next = newNode;
    list->tail->prev = newNode;
    list->size++;
}

// Function to insert a node before a node with a certain value
void insertValue(DoublyLinkedList* list, int target, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    Node* temp = list->head->next;
    while (temp != list->tail && temp->data != target) {
        temp = temp->next;
    }
    if (temp == list->tail) {
        printf("Target value not found\n");
        free(newNode);
        return;
    }
    newNode->next = temp;
    newNode->prev = temp->prev;
    temp->prev->next = newNode;
    temp->prev = newNode;
    list->size++;
}

// Function to delete a node by value
void deleteValue(DoublyLinkedList* list, int value) {
    Node* temp = list->head->next;
    while (temp != list->tail && temp->data != value) {
        temp = temp->next;
    }
    if (temp == list->tail) {
        return;
    }
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    free(temp);
    list->size--;
}

// Function to delete the first node
void deleteFirst(DoublyLinkedList* list) {
    if (list->head->next == list->tail) {
        return;
    }
    Node* toDelete = list->head->next;
    list->head->next = list->head->next->next;
    list->head->next->prev = list->head;
    free(toDelete);
    list->size--;
}

// Function to delete the last node
void deleteLast(DoublyLinkedList* list) {
    if (list->tail->prev == list->head) {
        return;
    }
    Node* toDelete = list->tail->prev;
    list->tail->prev = list->tail->prev->prev;
    list->tail->prev->next = list->tail;
    free(toDelete);
    list->size--;
}

// Function to get the first node's value
int getFirst(const DoublyLinkedList* list) {
    if (list->head->next == list->tail) {
        printf("List is empty\n");
        return -1;
    }
    return list->head->next->data;
}

// Function to get the last node's value
int getLast(const DoublyLinkedList* list) {
    if (list->tail->prev == list->head) {
        printf("List is empty\n");
        return -1;
    }
    return list->tail->prev->data;
}

// Function to get the size of the list
int getSize(const DoublyLinkedList* list) {
    return list->size;
}

// Function to print the elements of the list
void printList(const DoublyLinkedList* list) {
    Node* temp = list->head->next;
    while (temp != list->tail) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Function to free all nodes in the list
void freeList(DoublyLinkedList* list) {
    Node* temp = list->head;
    while (temp != NULL) {
        Node* next = temp->next;
        free(temp);
        temp = next;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

// Main function to demonstrate usage
int main() {
    DoublyLinkedList list;
    initList(&list);

    insertFirst(&list, 10);
    insertFirst(&list, 20);
    insertLast(&list, 30);
    insertLast(&list, 40);

    printf("List: ");
    printList(&list);
    printf("Size: %d\n", getSize(&list));

    printf("First element: %d\n", getFirst(&list));
    printf("Last element: %d\n", getLast(&list));

    insertValue(&list, 30, 25);
    printf("After inserting 25 before 30: ");
    printList(&list);

    deleteFirst(&list);
    printf("After deleting first element: ");
    printList(&list);

    deleteLast(&list);
    printf("After deleting last element: ");
    printList(&list);

    deleteValue(&list, 30);
    printf("After deleting value 30: ");
    printList(&list);

    printf("Final size: %d\n", getSize(&list));

    freeList(&list);
    return 0;
}