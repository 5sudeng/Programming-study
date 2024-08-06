#include <iostream>
#include <queue>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BST {
public:
    Node* root;

    BST() : root(nullptr) {}

    Node* insert(Node* node, int data) {
        if (node == nullptr) return new Node(data);
        if (data < node->data)
            node->left = insert(node->left, data);
        else if (data > node->data)
            node->right = insert(node->right, data);
        return node;
    }

    Node* search(Node* node, int data) {
        if (node == nullptr || node->data == data)
            return node;
        if (data < node->data)
            return search(node->left, data);
        return search(node->right, data);
    }

    Node* findMin(Node* node) {
        while (node && node->left != nullptr)
            node = node->left;
        return node;
    }

    Node* deleteNode(Node* node, int data) {
        if (node == nullptr) return node;
        if (data < node->data)
            node->left = deleteNode(node->left, data);
        else if (data > node->data)
            node->right = deleteNode(node->right, data);
        else {
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            Node* temp = findMin(node->right);
            node->data = temp->data;
            node->right = deleteNode(node->right, temp->data);
        }
        return node;
    }

    void inorder(Node* node) {
        if (node != nullptr) {
            inorder(node->left);
            cout << node->data << " ";
            inorder(node->right);
        }
    }

    void preorder(Node* node) {
        if (node != nullptr) {
            cout << node->data << " ";
            preorder(node->left);
            preorder(node->right);
        }
    }

    void postorder(Node* node) {
        if (node != nullptr) {
            postorder(node->left);
            postorder(node->right);
            cout << node->data << " ";
        }
    }

    void bft(Node* node) {
        if (node == nullptr) return;
        queue<Node*> q;
        q.push(node);
        while (!q.empty()) {
            Node* current = q.front();
            q.pop();
            cout << current->data << " ";
            if (current->left != nullptr) q.push(current->left);
            if (current->right != nullptr) q.push(current->right);
        }
    }
};

int main() {
    BST bst;
    bst.root = bst.insert(bst.root, 50);
    bst.root = bst.insert(bst.root, 30);
    bst.root = bst.insert(bst.root, 20);
    bst.root = bst.insert(bst.root, 40);
    bst.root = bst.insert(bst.root, 70);
    bst.root = bst.insert(bst.root, 60);
    bst.root = bst.insert(bst.root, 80);

    cout << "Inorder traversal: ";
    bst.inorder(bst.root);
    cout << endl;

    cout << "Preorder traversal: ";
    bst.preorder(bst.root);
    cout << endl;

    cout << "Postorder traversal: ";
    bst.postorder(bst.root);
    cout << endl;

    cout << "Breadth-First traversal: ";
    bst.bft(bst.root);
    cout << endl;

    cout << "\nDelete 20\n";
    bst.root = bst.deleteNode(bst.root, 20);
    cout << "Inorder traversal: ";
    bst.inorder(bst.root);
    cout << endl;

    return 0;
}