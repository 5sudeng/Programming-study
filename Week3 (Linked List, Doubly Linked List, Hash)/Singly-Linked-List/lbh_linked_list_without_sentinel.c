#include <stdio.h>
#include <stdlib.h>

// Node structure
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Singly linked list structure
typedef struct {
    Node* head;
    int size;
} LinkedList;

// Function to initialize the linked list
void initList(LinkedList* list) {
    list->head = NULL;
    list->size = 0;
}

// Function to insert a node at the beginning of the list
void insertFirst(LinkedList* list, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = list->head;
    list->head = newNode;
    list->size++;
}

// Function to insert a node at the end of the list
void insertLast(LinkedList* list, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;
    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node* temp = list->head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    list->size++;
}

// Function to insert a node before a node with a certain value
void insertValue(LinkedList* list, int target, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    Node* temp = list->head;
    Node* prev = NULL;
    while (temp != NULL && temp->data != target) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Target value not found\n");
        free(newNode);
        return;
    }
    newNode->next = temp;
    if (prev == NULL) {
        list->head = newNode;
    } else {
        prev->next = newNode;
    }
    list->size++;
}

// Function to delete a node by value
void deleteValue(LinkedList* list, int value) {
    Node* temp = list->head;
    Node* prev = NULL;
    while (temp != NULL && temp->data != value) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        return;
    }
    if (prev == NULL) {
        list->head = temp->next;
    } else {
        prev->next = temp->next;
    }
    free(temp);
    list->size--;
}

// Function to delete the first node
void deleteFirst(LinkedList* list) {
    if (list->head == NULL) {
        return;
    }
    Node* toDelete = list->head;
    list->head = list->head->next;
    free(toDelete);
    list->size--;
}

// Function to delete the last node
void deleteLast(LinkedList* list) {
    if (list->head == NULL) {
        return;
    }
    Node* temp = list->head;
    Node* prev = NULL;
    while (temp->next != NULL) {
        prev = temp;
        temp = temp->next;
    }
    if (prev == NULL) {
        list->head = NULL;
    } else {
        prev->next = NULL;
    }
    free(temp);
    list->size--;
}

// Function to get the first node's value
int getFirst(const LinkedList* list) {
    if (list->head == NULL) {
        printf("List is empty\n");
        return -1;
    }
    return list->head->data;
}

// Function to get the last node's value
int getLast(const LinkedList* list) {
    if (list->head == NULL) {
        printf("List is empty\n");
        return -1;
    }
    Node* temp = list->head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    return temp->data;
}

// Function to get the size of the list
int getSize(const LinkedList* list) {
    return list->size;
}

// Function to print the elements of the list
void printList(const LinkedList* list) {
    Node* temp = list->head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Function to free all nodes in the list
void freeList(LinkedList* list) {
    Node* temp = list->head;
    while (temp != NULL) {
        Node* next = temp->next;
        free(temp);
        temp = next;
    }
    list->head = NULL;
    list->size = 0;
}

// Main function to demonstrate usage
int main() {
    LinkedList list;
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