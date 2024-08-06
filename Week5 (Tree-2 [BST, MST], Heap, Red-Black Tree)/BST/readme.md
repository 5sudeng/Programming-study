# Binary Search Tree - CMY

![BST](https://img1.daumcdn.net/thumb/R1280x0/?scode%3Dmtistory2%26fname%3Dhttps%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FbCe3QD%2Fbtq2ytHuN1Z%2FAi82KHYBlgY01j9hbwjOO1%2Fimg.png)

- Rooted binary tree with two properties

  - For every node $x$, $x$'s value is unique in the **whole** tree
  - Every node in the **left** subtree has value **less** than $x$'s value and every node in the **right** subtree has value **greater** than $x$'s value

- Operations
  - `search()`
  - `insert(int x)`
  - `delete(int x)`

```Python
class TreeNode():
    def __init__(self, x: int):
        self.val = x
        self.left = None
        self.right = None

class BST():
    def __init__(self):
        self.root = None

    def __searchHelp(self, curNode: TreeNode, x: int) -> TreeNode:
        if not curNode:
            return None

        if x == curNode.val:
            return curNode
        elif x < curNode.val:
            return self.__searchHelp(curNode.left, x)
        else:
            return self.__searchHelp(curNode.right, x)
    def search(self, x: int):
        return self.__searchHelp(self.root, x)

    def __insertHelp(self, curnode: TreeNode, x: int) -> TreeNode:
        if not curNode:
            return TreeNode(x)

        if x < curNode.val:
            curNode.left = self.__inesrtHelp(curNode.left, x)
        elif x > curNode.val:
            curNode.right = self.__insertHelp(curnode.right, x)
        return curNode
    def insert(self, x: int):
        self.root = self.__insertHelp(self.root, x)

    def __findMax(self, curNode:TreeNode) -> int:
        if curNode.right == None:
            return curNode.val
        else:
            return self.__findMax(curNode.right)
    def __deleteHelp(self, curNode: TreeNode, x: int) -> TreeNode:
        if not curNode:
            return curNode

        if x < curNode.val:
            curNode.left = self.__deleteHelp(curNode.left, x)
        elif x > curNode.val:
            curNode.right = self.__deleteHelp(curNode.right, x)
        else:
            # No child
            if curNode.left == None and curNode.right == None:
                return None

            # One child
            elif curNode.left and curNode.right == None:
                return curNode.left
            elif curNode.left == None and curNode.right:
                return curNode.right

            # Two children
            else:
                leftLargest = self.__findMax(curNode.left)
                curNode.left = self.__deleteHelp(curNode.left, leftLargest)
                curNode.val = leftLargest

        return curNode
    def delete(self, x: int) -> None:
        self.root = self.__deleteHelp(self.root, x)

```

```C
// C program to implement binary search tree
#include <stdio.h>
#include <stdlib.h>

// Define a structure for a binary tree node
struct BinaryTreeNode {
	int key;
	struct BinaryTreeNode *left, *right;
};

// Function to create a new node with a given value
struct BinaryTreeNode* newNodeCreate(int value)
{
	struct BinaryTreeNode* temp
		= (struct BinaryTreeNode*)malloc(
			sizeof(struct BinaryTreeNode));
	temp->key = value;
	temp->left = temp->right = NULL;
	return temp;
}

struct BinaryTreeNode* searchNode(struct BinaryTreeNode* root, int target)
{
	if (root == NULL || root->key == target) {
		return root;
	}
	if (root->key < target) {
		return searchNode(root->right, target);
	}
	return searchNode(root->left, target);
}

struct BinaryTreeNode* insertNode(struct BinaryTreeNode* node, int value)
{
	if (node == NULL) {
		return newNodeCreate(value);
	}
	if (value < node->key) {
		node->left = insertNode(node->left, value);
	}
	else if (value > node->key) {
		node->right = insertNode(node->right, value);
	}
	return node;
}

void postOrder(struct BinaryTreeNode* root) {
	if (root != NULL) {
		postOrder(root->left);
		postOrder(root->right);
		printf(" %d ", root->key);
	}
}

void inOrder(struct BinaryTreeNode* root) {
	if (root != NULL) {
		inOrder(root->left);
		printf(" %d ", root->key);
		inOrder(root->right);
	}
}

void preOrder(struct BinaryTreeNode* root) {
	if (root != NULL) {
		printf(" %d ", root->key);
		preOrder(root->left);
		preOrder(root->right);
	}
}

struct BinaryTreeNode* findMin(struct BinaryTreeNode* root) {
	if (root == NULL) {
		return NULL;
	}
	else if (root->left != NULL) {
		return findMin(root->left);
	}
	return root;
}

struct BinaryTreeNode* delete (struct BinaryTreeNode* root, int x) {
	if (root == NULL)
		return NULL;

	if (x > root->key) {
		root->right = delete (root->right, x);
	}
	else if (x < root->key) {
		root->left = delete (root->left, x);
	}
	else {
		if (root->left == NULL && root->right == NULL) {
			free(root);
			return NULL;
		}
		else if (root->left == NULL || root->right == NULL) {
			struct BinaryTreeNode* temp;
			if (root->left == NULL) {
				temp = root->right;
			}
			else {
				temp = root->left;
			}
			free(root);
			return temp;
		}
		else {
			struct BinaryTreeNode* temp = findMin(root->right);
			root->key = temp->key;
			root->right = delete (root->right, temp->key);
		}
	}
	return root;
}
```

```C++
#include <iostream>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    Node(int item) {
        key = item;
        left = NULL;
        right = NULL;
    }
};

Node* search(Node* root, int key) {
    if (root == NULL || root->key == key)
        return root;

    if (root->key < key)
        return search(root->right, key);
    return search(root->left, key);
}

Node* insert(Node* node, int key) {
      if (node == NULL)
        return new Node(key);

    if (node->key == key)
        return node;

    if (node->key < key)
        node->right = insert(node->right, key);

    else
        node->left = insert(node->left, key);

    return node;
}

Node* getSuccessor(Node* curr)
{
    curr = curr->right;
    while (curr != NULL && curr->left != NULL)
        curr = curr->left;
    return curr; // leftmost node from right subtree
}

Node* delNode(Node* root, int x)
{
    if (root == NULL)
        return root;

    if (root->key > x)
        root->left = delNode(root->left, x);
    else if (root->key < x)
        root->right = delNode(root->right, x);

    else {
        // 0 children or only right child
        if (root->left == NULL) {
            Node* temp = root->right;
            delete root;
            return temp;
        }

        // only left child
        if (root->right == NULL) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        // 2 children
        Node* succ = getSuccessor(root);
        root->key = succ->key;
        root->right = delNode(root->right, succ->key);
    }
    return root;
}

void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
    }
}
```
