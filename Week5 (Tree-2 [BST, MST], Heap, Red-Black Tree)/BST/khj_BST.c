#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode{
    int val;
    struct treeNode* left;
    struct treeNode* right;
} TreeNode;

TreeNode *create_node(int x) {
    TreeNode * new_node = (TreeNode*)malloc(sizeof(TreeNode));
    new_node->val = x;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}


//search
TreeNode *search(TreeNode *node, int key) {
    if (node == NULL) return NULL;
    // if (key == node->val) return node;
    if (key  < node->val) {
        return search(node->left, key);
    }
    else if (key > node->val) {
        return search(node->right, key);
    }
    return node;
}

TreeNode *insert(TreeNode *node, int key) {
    if (node == NULL) {
        return create_node(key);
    }

    if (key < node-> val) {
        node->left = insert(node->left, key);
    }
    else {
        node->right = insert(node->right ,key);
    }
    return node;
}

// //insert
// TreeNode *insert(TreeNode *node, int key) {
//     if (node == NULL) return NULL;
//     if (key < node-> val) {
//         if (node->left == NULL) {
//             node->left->val = key;
//             node->left->parent = node;
//         }
//         else {
//             node->left = insert(node->left, key);
//         }
//     }

//     else if (key > node->val) {
//         if (node->right == NULL) {
//             node->right->val = key;
//             node->right->parent = node;
//         }
//         else {
//             node->right = insert(node->right, key);
//         }
//     }
//     return node;
// }

//delete
TreeNode* findMin(TreeNode* node) {
    while (node->left) {
        node = node->left;
    }
    return node;
} 

TreeNode* delete(TreeNode* node, int key) {
    if (node == NULL) return NULL;
    
    if (node->val == key) {

        //Node has no children
        if (node->left == NULL && node->right == NULL) {
            node = NULL;
        }

        //Node has 1 child
        else if (node->left != NULL && node->right == NULL) {
            node = node->left;
        }

        else if (node->left == NULL && node->right != NULL) {
            node = node->right;
        }

        //Node has 2 children
        else {
            TreeNode* temp = findMin(node->right);
            node->val = temp->val;
            node->right = delete(node->right, temp->val);
            
        }
    }
    else if (node->val < key) {
        node->right = delete(node->right, key);
    }
    else if (node->val > key) {
        node->left =  delete(node->left, key);
    }
    // return node;

}

//Modify
TreeNode* modify(TreeNode *node, int data, int newdata) {
    if (node == NULL) return;
    if (node->val == data) {
        node->val = newdata;
    }
    else if (data < node->val) {
        modify(node->left, data, newdata);
    }
    else {
        modify(node->right, data, newdata);
    }
    return node;
}


void inorder(TreeNode* node) {
        if (node != NULL) {
            inorder(node->left);
            printf("%d ", node->val);
            inorder(node->right);
        }
    }


int main() {
    TreeNode* root = NULL;

    // Insert nodes
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);
    

    
    printf("Inorder traversal of the tree: ");
    inorder(root);
    printf("\n");

    
    // Search for a value
    TreeNode* result = search(root, 40);
    if (result != NULL) {
        printf("Found value 40 in the tree.\n");
    } else {
        printf("Value 40 not found in the tree.\n");
    }

    // Modify a value
    printf("Modifying value 40 to 45.\n");
    modify(root, 40, 45);
    printf("Inorder traversal after modification: ");
    inorder(root);
    printf("\n");


    // Delete a node
    printf("Deleting node with value 30 and 50.\n");
    delete(root, 30);
    delete(root, 50);
    // printf("Deleting node with value 20: \n");
    // delete(root, 20);
    printf("Inorder traversal after deletion: ");
    
    inorder(root);
    printf("\n");

    return 0;
}