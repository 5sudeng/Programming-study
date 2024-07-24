#include <stdio.h>
#include <stdlib.h>

// Node structure
typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

// Doubly linked list structure
typedef struct {
    Node* head;
    Node* tail;
    int size;
} DoublyLinkedList;

// Function to initialize the doubly linked list
void initList(DoublyLinkedList* list) {
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

// Function to insert a node at the beginning of the list
void insertFirst(DoublyLinkedList* list, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = list->head;
    newNode->prev = NULL;
    if (list->head != NULL) {
        list->head->prev = newNode;
    } else {
        list->tail = newNode; // If list was empty, new node is also the tail
    }
    list->head = newNode;
    list->size++;
}

// Function to insert a node at the end of the list
void insertLast(DoublyLinkedList* list, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;
    newNode->prev = list->tail;
    if (list->tail != NULL) {
        list->tail->next = newNode;
    } else {
        list->head = newNode; // If list was empty, new node is also the head
    }
    list->tail = newNode;
    list->size++;
}

// Function to insert a node before a node with a certain value
void insertValue(DoublyLinkedList* list, int target, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    Node* temp = list->head;
    while (temp != NULL && temp->data != target) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Target value not found\n");
        free(newNode);
        return;
    }
    newNode->next = temp;
    newNode->prev = temp->prev;
    if (temp->prev != NULL) {
        temp->prev->next = newNode;
    } else {
        list->head = newNode; // Inserting before the first node
    }
    temp->prev = newNode;
    list->size++;
}

// Function to delete a node by value
void deleteValue(DoublyLinkedList* list, int value) {
    Node* temp = list->head;
    while (temp != NULL && temp->data != value) {
        temp = temp->next;
    }
    if (temp == NULL) {
        return; // Value not found
    }
    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    } else {
        list->head = temp->next; // Node to be deleted is head
    }
    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    } else {
        list->tail = temp->prev; // Node to be deleted is tail
    }
    free(temp);
    list->size--;
}

// Function to delete the first node
void deleteFirst(DoublyLinkedList* list) {
    if (list->head == NULL) {
        return;
    }
    Node* toDelete = list->head;
    list->head = list->head->next;
    if (list->head != NULL) {
        list->head->prev = NULL;
    } else {
        list->tail = NULL; // List became empty
    }
    free(toDelete);
    list->size--;
}

// Function to delete the last node
void deleteLast(DoublyLinkedList* list) {
    if (list->tail == NULL) {
        return;
    }
    Node* toDelete = list->tail;
    list->tail = list->tail->prev;
    if (list->tail != NULL) {
        list->tail->next = NULL;
    } else {
        list->head = NULL; // List became empty
    }
    free(toDelete);
    list->size--;
}

// Function to get the first node's value
int getFirst(const DoublyLinkedList* list) {
    if (list->head == NULL) {
        printf("List is empty\n");
        return -1;
    }
    return list->head->data;
}

// Function to get the last node's value
int getLast(const DoublyLinkedList* list) {
    if (list->tail == NULL) {
        printf("List is empty\n");
        return -1;
    }
    return list->tail->data;
}

// Function to get the size of the list
int getSize(const DoublyLinkedList* list) {
    return list->size;
}

// Function to print the elements of the list
void printList(const DoublyLinkedList* list) {
    Node* temp = list->head;
    while (temp != NULL) {
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