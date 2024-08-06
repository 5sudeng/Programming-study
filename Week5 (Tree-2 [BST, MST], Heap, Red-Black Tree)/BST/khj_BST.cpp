#include <iostream>
#include <cstdlib>

using namespace std;

class TreeNode {
public:
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class BinaryTree {
public:
    TreeNode* root;

    BinaryTree() : root(nullptr) {}

    TreeNode* create_node(int x) {
        return new TreeNode(x);
    }

    void inorder(TreeNode* node) {
        if (node) {
            inorder(node->left);
            cout << node->val << " ";
            inorder(node->right);
        }
    }

    TreeNode* search(TreeNode* node, int key) {
        if (node == nullptr) return nullptr;
        if (key < node->val) return search(node->left, key);
        else if (key > node->val) return search(node->right, key);
        return node;
    }

    TreeNode* insert_node(TreeNode* node, int key) {
        if (node == nullptr) return create_node(key);
        if (key < node->val) node->left = insert_node(node->left, key);
        else node->right = insert_node(node->right, key);
        return node;
    }

    TreeNode* findMin(TreeNode* node) {
        while (node->left) {
            node = node->left;
        }
        return node;
    }

    TreeNode* delete_node(TreeNode* node, int key) {
        if (node == nullptr) return nullptr;
        if (node->val == key) {
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            }
            else if (node->left != nullptr && node->right == nullptr) {
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }
            else if (node->left == nullptr && node->right != nullptr) {
                TreeNode* temp = node->right;
                delete node;
                return temp;
            }
            else {
                TreeNode* temp = findMin(node->right);
                node->val = temp->val;
                node->right = delete_node(node->right, temp->val);
            }
        }
        else if (key < node->val) {
            node->left = delete_node(node->left, key);
        }
        else {
            node->right = delete_node(node->right, key);
        }
        return node;
    }

    TreeNode* modify(TreeNode* node, int data, int newdata) {
        if (node == nullptr) return nullptr;
        if (node->val == data) {
            node->val = newdata;
        } else if (data < node->val) {
            node->left = modify(node->left, data, newdata);
        } else {
            node->right = modify(node->right, data, newdata);
        }
        return node;
    }
};

int main() {
    BinaryTree tree;

    // Node insertion
    tree.root = tree.insert_node(tree.root, 50);
    tree.insert_node(tree.root, 30);
    tree.insert_node(tree.root, 20);
    tree.insert_node(tree.root, 40);
    tree.insert_node(tree.root, 70);
    tree.insert_node(tree.root, 60);
    tree.insert_node(tree.root, 80);

    cout << "Inorder traversal of the tree: ";
    tree.inorder(tree.root);
    cout << "\n";

    // Search for a value
    TreeNode* result = tree.search(tree.root, 40);
    if (result != nullptr) {
        cout << "Found value 40 in the tree.\n";
    } else {
        cout << "Value 40 not found in the tree.\n";
    }

    // Modify a value
    cout << "Modifying value 40 to 45.\n";
    tree.root = tree.modify(tree.root, 40, 45);
    cout << "Inorder traversal after modification: ";
    tree.inorder(tree.root);
    cout << "\n";

    // Delete nodes
    cout << "Deleting node with value 30 and 50.\n";
    tree.root = tree.delete_node(tree.root, 30);
    tree.root = tree.delete_node(tree.root, 50);
    cout << "Inorder traversal after deletion: ";
    tree.inorder(tree.root);
    cout << "\n";

    return 0;
}
