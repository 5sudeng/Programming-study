#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Node {
public:
    int data;
    vector<Node*> children;
    Node(int val) : data(val) {}
};

// Function to add a child to a node
void addChild(Node* parent, int data) {
    parent->children.push_back(new Node(data));
}

// Function to delete a node (assumes parent is known)
void deleteNode(Node* parent, int data) {
    for (auto it = parent->children.begin(); it != parent->children.end(); ++it) {
        if ((*it)->data == data) {
            delete *it;
            parent->children.erase(it);
            return;
        }
    }
    for (auto child : parent->children) {
        deleteNode(child, data);
    }
}

// Function for breadth-first traversal
void bft(Node* root) {
    if (!root) return;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* node = q.front();
        q.pop();
        cout << node->data << " ";
        for (auto child : node->children) {
            q.push(child);
        }
    }
}

// Function for preorder traversal
void preorder(Node* root) {
    if (!root) return;
    cout << root->data << " ";
    for (auto child : root->children) {
        preorder(child);
    }
}

// Function for postorder traversal
void postorder(Node* root) {
    if (!root) return;
    for (auto child : root->children) {
        postorder(child);
    }
    cout << root->data << " ";
}

// Function to search a node
Node* search(Node* root, int data) {
    if (!root) return nullptr;
    if (root->data == data) return root;
    for (auto child : root->children) {
        Node* result = search(child, data);
        if (result) return result;
    }
    return nullptr;
}

int main() {
    Node* root = new Node(1);
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

    cout << "Breadth-First Traversal: ";
    bft(root);
    cout << endl;

    cout << "Preorder Traversal: ";
    preorder(root);
    cout << endl;

    cout << "Postorder Traversal: ";
    postorder(root);
    cout << endl;

    cout << "\nDeleting node 2 and its children\n";
    deleteNode(root, 2);

    cout << "Breadth-First Traversal: ";
    bft(root);
    cout << endl;

    return 0;
}