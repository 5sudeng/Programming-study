#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RED 1
#define BLACK 0

typedef struct Node {
    int data;
    int color; // Use int for color: RED = 1, BLACK = 0
    struct Node *left, *right, *parent;
} Node;

typedef struct {
    Node *root;
} RBTree;

// Helper function to create a new node
Node* createNode(int data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->color = RED; // New nodes are always RED
    newNode->left = newNode->right = newNode->parent = NULL;
    return newNode;
}

// Rotate left around node x
void rotateLeft(RBTree *tree, Node *x) {
    Node *y = x->right;
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;

    y->parent = x->parent;
    if (x->parent == NULL) {
        tree->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
}

// Rotate right around node x
void rotateRight(RBTree *tree, Node *x) {
    Node *y = x->left;
    x->left = y->right;
    if (y->right != NULL)
        y->right->parent = x;

    y->parent = x->parent;
    if (x->parent == NULL) {
        tree->root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }

    y->right = x;
    x->parent = y;
}

// Fix the Red-Black Tree properties after insertion
void fixInsertRBTree(RBTree *tree, Node *pt) {
    while (pt != tree->root && pt->parent->color == RED) {
        if (pt->parent == pt->parent->parent->left) {
            Node *y = pt->parent->parent->right;
            if (y != NULL && y->color == RED) { // Case 1
                pt->parent->color = BLACK;
                y->color = BLACK;
                pt->parent->parent->color = RED;
                pt = pt->parent->parent;
            } else {
                if (pt == pt->parent->right) {
                    pt = pt->parent;
                    rotateLeft(tree, pt);
                }
                pt->parent->color = BLACK;
                pt->parent->parent->color = RED;
                rotateRight(tree, pt->parent->parent);
            }
        } else {
            Node *y = pt->parent->parent->left;
            if (y != NULL && y->color == RED) { // "right" and "left" exchanged
                pt->parent->color = BLACK;
                y->color = BLACK;
                pt->parent->parent->color = RED;
                pt = pt->parent->parent;
            } else {
                if (pt == pt->parent->left) {
                    pt = pt->parent;
                    rotateRight(tree, pt);
                }
                pt->parent->color = BLACK;
                pt->parent->parent->color = RED;
                rotateLeft(tree, pt->parent->parent);
            }
        }
    }
    tree->root->color = BLACK;
}

// Insert a new node into the tree
void insert(RBTree *tree, int data) {
    Node *pt = createNode(data);
    Node *y = NULL;
    Node *x = tree->root;

    while (x != NULL) {
        y = x;
        if (pt->data < x->data) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    pt->parent = y;
    if (y == NULL) {
        tree->root = pt;
    } else if (pt->data < y->data) {
        y->left = pt;
    } else {
        y->right = pt;
    }

    fixInsertRBTree(tree, pt);
}

// Transplant function used in deletion
void transplant(RBTree *tree, Node *u, Node *v) {
    if (u->parent == NULL) {
        tree->root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v != NULL) {
        v->parent = u->parent;
    }
}

// Find the minimum node in a subtree
Node* treeMinimum(Node *x) {
    while (x->left != NULL)
        x = x->left;
    return x;
}

// Fix the Red-Black Tree properties after deletion
void fixDeleteRBTree(RBTree *tree, Node *x) {
    while (x != tree->root && x->color == BLACK) {
        if (x == x->parent->left) {
            Node *s = x->parent->right;
            if (s->color == RED) {
                s->color = BLACK;
                x->parent->color = RED;
                rotateLeft(tree, x->parent);
                s = x->parent->right;
            }
            if ((s->left == NULL || s->left->color == BLACK) &&
                (s->right == NULL || s->right->color == BLACK)) {
                s->color = RED;
                x = x->parent;
            } else {
                if (s->right == NULL || s->right->color == BLACK) {
                    if (s->left != NULL) {
                        s->left->color = BLACK;
                    }
                    s->color = RED;
                    rotateRight(tree, s);
                    s = x->parent->right;
                }
                s->color = x->parent->color;
                x->parent->color = BLACK;
                if (s->right != NULL) {
                    s->right->color = BLACK;
                }
                rotateLeft(tree, x->parent);
                x = tree->root;
            }
        } else {
            Node *s = x->parent->left;
            if (s->color == RED) {
                s->color = BLACK;
                x->parent->color = RED;
                rotateRight(tree, x->parent);
                s = x->parent->left;
            }
            if ((s->right == NULL || s->right->color == BLACK) &&
                (s->left == NULL || s->left->color == BLACK)) {
                s->color = RED;
                x = x->parent;
            } else {
                if (s->left == NULL || s->left->color == BLACK) {
                    if (s->right != NULL) {
                        s->right->color = BLACK;
                    }
                    s->color = RED;
                    rotateLeft(tree, s);
                    s = x->parent->left;
                }
                s->color = x->parent->color;
                x->parent->color = BLACK;
                if (s->left != NULL) {
                    s->left->color = BLACK;
                }
                rotateRight(tree, x->parent);
                x = tree->root;
            }
        }
    }
    x->color = BLACK;
}

// Delete a node from the tree
void deleteNode(RBTree *tree, Node *z) {
    Node *y = z;
    int yOriginalColor = y->color;
    Node *x;

    if (z->left == NULL) {
        x = z->right;
        transplant(tree, z, z->right);
    } else if (z->right == NULL) {
        x = z->left;
        transplant(tree, z, z->left);
    } else {
        y = treeMinimum(z->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y != z->right) {
            transplant(tree, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(tree, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if (yOriginalColor == BLACK) {
        fixDeleteRBTree(tree, x);
    }
}

// Search for a node in the tree
Node* searchTreeHelper(Node *root, int key) {
    if (root == NULL || root->data == key)
        return root;

    if (key < root->data)
        return searchTreeHelper(root->left, key);
    else
        return searchTreeHelper(root->right, key);
}

// Delete a value from the tree
void deleteValue(RBTree *tree, int data) {
    Node *z = searchTreeHelper(tree->root, data);
    if (z == NULL) {
        printf("Value not found in the tree.\n");
        return;
    }
    deleteNode(tree, z);
}

// Search for a key in the tree
void search(RBTree *tree, int key) {
    Node *current = searchTreeHelper(tree->root, key);
    if (current != NULL) {
        printf("Found node with key: %d\n", key);
    } else {
        printf("Node with key %d not found\n", key);
    }
}

// Main function to test the Red-Black Tree
int main() {
    RBTree tree;
    tree.root = NULL;

    insert(&tree, 10);
    insert(&tree, 20);
    insert(&tree, 30);
    insert(&tree, 15);
    insert(&tree, 25);

    search(&tree, 15);
    deleteValue(&tree, 15);
    search(&tree, 15);

    return 0;
}
