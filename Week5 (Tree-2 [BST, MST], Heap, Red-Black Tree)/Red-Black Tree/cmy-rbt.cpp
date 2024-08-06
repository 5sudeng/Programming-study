#include <iostream>
using namespace std;

const string RED = "RED";
const string BLACK = "BLACK";

class Node {
public:
    int data;
    string color;
    Node *left, *right, *parent;
    Node(int data) : data(data), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RBTree {
private:
    Node *root;

protected:
    void rotateLeft(Node *root, Node *x);
    void rotateRight(Node *root, Node *x);
    void fixInsertRBTree(Node *root, Node *pt);
    Node* BSTInsert(Node *root, Node *pt);

    void fixDeleteRBTree(Node *root, Node *x);
    void transplant(Node *root, Node *u, Node *v);
    void deleteNode(Node *root, Node *z);
    Node* treeMinimum(Node *x);

    Node* searchTreeHelper(Node* root, int key);

public:
    RBTree() { root = nullptr; }
    void insert(const int &n);
    void deleteValue(const int &n);
    void search(const int &key);
};

void RBTree::rotateLeft(Node *root, Node *x) {
    Node *y = x->right;
    x->right = y->left;
    if (x->right != nullptr)
        x->right->parent = x;

    y->parent = x->parent;
    if (x->parent == nullptr)
        this->root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}
void RBTree::rotateRight(Node *root, Node *x) {
    Node *y = x->left;
    x->left = y->right;
    if (x->left != nullptr)
        x->left->parent = x;

    y->parent = x->parent;
    if (x->parent == nullptr)
        this->root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->right = x;
    x->parent = y;
}
void RBTree::fixInsertRBTree(Node *root, Node *pt) {
    if (!pt->parent) { 
        root->color = BLACK;
        return;
    } else if (!pt->parent->parent) { 
        root->color = BLACK;
        pt->color = RED;
        return;
    }

    while ((pt != root) && (pt->parent->color == RED)) {
        if (pt->parent == pt->parent->parent->left) {
            Node *y = pt->parent->parent->right;
            if (y && y->color==RED) { // Case 1
                pt->parent->color = BLACK;
                y->color = BLACK;
                pt->parent->parent->color=RED;
                pt = pt->parent->parent;
            } else {
                if (pt == pt->parent->right) {
                    pt = pt->parent;
                    rotateLeft(root, pt);
                }
                pt->parent->color = BLACK;
                pt->parent->parent->color = RED;
                rotateRight(root, pt->parent->parent);
            }
        } else {
            // "right" and "left" exchanged
            Node *y = pt->parent->parent->left;
            if (y && y->color==RED) { 
                pt->parent->color = BLACK;
                y->color = BLACK;
                pt->parent->parent->color=RED;
                pt = pt->parent->parent;
            } else {
                if (pt == pt->parent->left) {
                    pt = pt->parent;
                    rotateRight(root, pt);
                }
                pt->parent->color = BLACK;
                pt->parent->parent->color = RED;
                rotateLeft(root, pt->parent->parent);
            }
        }
    }
    
    while (root -> parent) {
        root = root->parent;
    }
    root->color = BLACK;
}
Node* RBTree::BSTInsert(Node* root, Node *pt) {
    if (root == nullptr)
        return pt;

    if (pt->data < root->data) {
        root->left = BSTInsert(root->left, pt);
        root->left->parent = root;
    } else if (pt->data > root->data) {
        root->right = BSTInsert(root->right, pt);
        root->right->parent = root;
    }

    return root;
}
void RBTree::insert(const int &data) {
    Node *pt = new Node(data);
    root = BSTInsert(root, pt);
    fixInsertRBTree(root, pt);
}


void RBTree::transplant(Node *root, Node *u, Node *v) {
    if (u->parent == nullptr) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v != nullptr) {
        v->parent = u->parent;
    }
}
Node* RBTree::treeMinimum(Node *x) {
    while (x->left != nullptr)
        x = x->left;
    return x;
}
void RBTree::deleteNode(Node *root, Node *z) {
    Node *y = z;
    string yOriginalColor = y->color;
    Node *x;

    if (z->left == nullptr) {
        x = z->right;
        transplant(root, z, z->right);
    } else if (z->right == nullptr) {
        x = z->left;
        transplant(root, z, z->left);
    } else {
        y = treeMinimum(z->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y != z->right) {
            transplant(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if (yOriginalColor == BLACK) {
        fixDeleteRBTree(root, x);
    }
}
void RBTree::fixDeleteRBTree(Node *root, Node *x) {
    while (x != this->root && x->color == BLACK) {
        if (x == x->parent->left) {
            Node *s = x->parent->right;
            if (s->color == RED) {
                s->color = BLACK;
                x->parent->color = RED;
                rotateLeft(root, x->parent);
                s = x->parent->right;
            }

            if (s->left->color == BLACK && s->right->color == BLACK) {
                s->color = RED;
                x = x->parent;
            } else {
                if (s->right->color == BLACK) {
                    s->left->color = BLACK;
                    s->color = RED;
                    rotateRight(root, s);
                    s = x->parent->right;
                }

                s->color = x->parent->color;
                x->parent->color = BLACK;
                s->right->color = BLACK;
                rotateLeft(root, x->parent);
                x = root;
            }
        } else {
            Node *s = x->parent->left;
            if (s->color == RED) {
                s->color = BLACK;
                x->parent->color = RED;
                rotateRight(root, x->parent);
                s = x->parent->left;
            }

            if (s->left->color == BLACK && s->right->color == BLACK) {
                s->color = RED;
                x = x->parent;
            } else {
                if (s->left->color == BLACK) {
                    s->right->color = BLACK;
                    s->color = RED;
                    rotateLeft(root, s);
                    s = x->parent->left;
                }

                s->color = x->parent->color;
                x->parent->color = BLACK;
                s->left->color = BLACK;
                rotateRight(root, x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}
void RBTree::deleteValue(const int &data) {
    Node *z = searchTreeHelper(root, data);
    if (z == nullptr) {
        cout << "Value not found in the tree." << endl;
        return;
    }
    deleteNode(root, z);
}




Node* RBTree::searchTreeHelper(Node* root, int key) {
    if (root == nullptr || root->data == key)
        return root;

    if (key < root->data)
        return searchTreeHelper(root->left, key);
    else
        return searchTreeHelper(root->right, key);
}
void RBTree::search(const int &key) {
    Node* current = searchTreeHelper(root, key);
    if (current != nullptr) {
        cout << "Found node with key: " << key << endl;
    } else {
        cout << "Node with key " << key << " not found" << endl;
    }
}