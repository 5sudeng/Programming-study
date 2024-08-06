#include <stdio.h>
#include <stdlib.h>

#define MAX_CHILDREN 10

typedef struct Node {
    int data;
    struct Node* children[MAX_CHILDREN];
    int child_count;
} Node;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->child_count = 0;
    for (int i = 0; i < MAX_CHILDREN; i++) {
        newNode->children[i] = NULL;
    }
    return newNode;
}

// Function to add a child to a node
void addChild(Node* parent, int data) {
    if (parent->child_count < MAX_CHILDREN) {
        parent->children[parent->child_count++] = createNode(data);
    } else {
        printf("Cannot add more children to node with data %d\n", parent->data);
    }
}

// Function to delete a node (assumes parent is known)
void deleteNode(Node* parent, int data) {
    for (int i = 0; i < parent->child_count; i++) {
        if (parent->children[i]->data == data) {
            free(parent->children[i]);
            for (int j = i; j < parent->child_count - 1; j++) {
                parent->children[j] = parent->children[j + 1];
            }
            parent->child_count--;
            return;
        }
    }
    for (int i = 0; i < parent->child_count; i++) {
        deleteNode(parent->children[i], data);
    }
}

// Function for breadth-first traversal
void bft(Node* root) {
    if (!root) return;

    Node** queue = (Node**)malloc(sizeof(Node*) * 100);
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        Node* node = queue[front++];
        printf("%d ", node->data);
        for (int i = 0; i < node->child_count; i++) {
            queue[rear++] = node->children[i];
        }
    }

    free(queue);
}

// Function for preorder traversal
void preorder(Node* root) {
    if (!root) return;
    printf("%d ", root->data);
    for (int i = 0; i < root->child_count; i++) {
        preorder(root->children[i]);
    }
}

// Function for postorder traversal
void postorder(Node* root) {
    if (!root) return;
    for (int i = 0; i < root->child_count; i++) {
        postorder(root->children[i]);
    }
    printf("%d ", root->data);
}

// Function to search a node
Node* search(Node* root, int data) {
    if (!root) return NULL;
    if (root->data == data) return root;
    for (int i = 0; i < root->child_count; i++) {
        Node* result = search(root->children[i], data);
        if (result) return result;
    }
    return NULL;
}

int main() {
    Node* root = createNode(1);
    addChild(root, 2);
    addChild(root, 3);
    addChild(root, 4);

    Node* child = search(root, 2);
    if (child) {
        addChild(child, 5);
        addChild(child, 6);
    }

    child = search(root, 3);
    if (child) {
        addChild(child, 7);
    }

    printf("Breadth-First Traversal: ");
    bft(root);
    printf("\n");

    printf("Preorder Traversal: ");
    preorder(root);
    printf("\n");

    printf("Postorder Traversal: ");
    postorder(root);
    printf("\n");

    printf("\nDeleting node 2 and its children\n");
    deleteNode(root, 2);

    printf("Breadth-First Traversal: ");
    bft(root);
    printf("\n");

    return 0;
}