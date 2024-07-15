// From 2024-1 CFDS1 HW3 Prob1

#include <iostream>
#include <climits>
#include <queue>
#include <cmath>
using namespace std;

// using tree-based implementation
struct Node {
    int val;
    Node * left = nullptr;
    Node * right = nullptr;
    Node * parent = nullptr;
};

class MinHeap {
    Node * root;
    Node * last_node;
    int heap_size;

public:
    MinHeap() {
        root = nullptr;
        heap_size = 0;
    };
    Node * getMin();
    void enqueue(int k);
    void dequeue();
    void printHeap();
    void swap(Node * a, Node * b);
}; 

Node * MinHeap::getMin() { return root; }

void MinHeap::printHeap() {
    Node * currNode = root;
    queue<Node*> q;

    q.push(root);
    cout << "Print Heap: ";
    while (!q.empty() && q.front()) {
        cout << q.front()->val << " ";
        if (q.front()->left) { q.push(q.front()->left); }
        if (q.front()->right) { q.push(q.front()->right); }
        q.pop();
    }
    cout << endl;
}

void MinHeap::swap(Node * a, Node * b){
    int temp = a->val;
    a->val = b->val;
    b->val = temp;
}

void MinHeap::enqueue(int k) {
    Node * newNode = new Node;
    newNode->val = k;
    newNode->left = newNode->right = newNode->parent = nullptr;

    if (!root) {
        root = newNode;
        last_node = newNode;
    } else {
        int path = heap_size + 1;
        int bit = 1 << (int)log2(path);

        Node * temp = root;
        while (bit>1) {
            bit >>=1;
            if (path & bit) {
                if (!temp->right) { break; }
                temp = temp->right;
            } else {
                if (!temp->left) { break; }
                temp = temp->left;
            }
        }

        newNode->parent = temp;
        if (!(path&1)) { temp->left = newNode; }
        else { temp->right = newNode; }
        last_node = newNode;

        // Restore heap property
        Node* currNode = last_node;
        while ((currNode->parent) && (currNode->parent->val > currNode->val)) {
            swap(currNode, currNode->parent);
            currNode = currNode->parent;
        }
    }
    heap_size++;
}

void MinHeap::dequeue() {
    if (!root) { return; }

    if (root == last_node) {
        delete root;
        root = nullptr; last_node = nullptr;
        heap_size--;
        return;
    }

    swap(root, last_node);
    if (last_node->parent->left == last_node) {
        last_node->parent->left = nullptr;
    } else {
        last_node->parent->right = nullptr;
    }
    delete last_node;

    int path = heap_size - 1;
    int bit = 1 << (int)log2(path);

    Node * temp = root;
    while (bit>1) {
        bit >>= 1;
        if (path & bit) {
            if (!temp->right) { break; }
            temp = temp->right;
        } else {
            if (!temp->left) { break; }
            temp = temp->left;
        }
    }
    last_node = temp;
    heap_size--;

    // Restore heap property
    if (!root) { return; }
    Node * currNode = root;
    while (currNode->left || currNode->right) {
        Node * smaller = nullptr;
        if (currNode->left && currNode->right) {
            smaller = (currNode->left->val < currNode->right->val) ? currNode->left : currNode->right;
        } else if (currNode->left) {
            smaller = currNode->left;
        } else {
            smaller = currNode->right;
        }
        
        if (smaller && currNode->val > smaller->val) {
            swap(currNode, smaller);
            currNode = smaller;
        } else { break; }
    }

}