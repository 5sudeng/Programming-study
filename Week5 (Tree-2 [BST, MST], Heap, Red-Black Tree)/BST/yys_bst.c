#include <stdio.h>
#include <stdlib.h>



typedef struct Node{
    int key;
    struct Node *left, *right, *parent;
} Node;// typedef를 써서,  Node라고 명칭

typedef struct BST{
    Node *root;
}BST;

// function to create a new node : C만의 기능 cpp에서 일종의 constructor
Node* createNode(int key){
    Node* newnode = (Node*) malloc(sizeof(Node)); // 동적 할당
    newnode -> key = key;
    newnode -> left = newnode-> right = newnode->parent = NULL;
    return newnode;
}


BST* createBST(){
    BST* bst = (BST*)malloc(sizeof(BST));
    bst->root = NULL;
    return bst;
}

Node* isKey(BST* bst, int key){ 
    
    Node* node = bst->root;
    while(node != NULL && key != node->key){
        if (key < node->key){
            node = node->left;
        }
        else{
            node = node->right;
        }
    }
    return node; // 없다면 NULL(root)을 반환.
}


void insert(BST*bst, int key){
    Node* y = NULL; // parent of z
    Node* x = bst->root;
    Node* z = createNode(key);

    // find parent if insert point
    while(x!=NULL){
        y = x;
        if (key < x->key){
            x = x->left;
        }
        else{
            x = x->right;
        }
    }

    z->parent = y;

    //link to y
    if (y == NULL){
        // y is still NULL, then no root
        bst->root = z;
    }
    else if (key < y->key){
        y->left = z;
    }
    else{
        y->right = z;
    }
}

void transplant(BST* bst, Node* u, Node* v){
    if (u->parent == NULL){
        // just root
        bst->root = v;
    }
    else if (u == u->parent->left){
        u->parent->left = v;
    }
    else{
        u->parent->right = v;
    }

    if (v!=NULL){
        v->parent = u->parent;
    }
}

Node* tree_minimum(Node* x){
    while(x->left!=NULL){
        x = x->left;
    }
    return x;
}
Node* tree_maximum(Node* x){
    while(x->right!=NULL){
        x = x->right;
    }
    return x;
}

void delete(BST* bst, int key){
    Node* z = isKey(bst, key);

    if (z==NULL){
        return;
    }

    if(z->left==NULL){
        transplant(bst, z, z->right);
    }
    else if(z->right == NULL){
        transplant(bst, z, z->left);
    }
    else{
        //with two children
        Node* y = tree_minimum(z->right); // 대체할 친구

        if (y != z->right){
            transplant(bst, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        //나머지 부분 
        transplant(bst, z, y);
        y->left = z->left;
        y->left->parent = y;
    }
}

void inorder_traversal(Node*node){
    
    if (node !=NULL){
        inorder_traversal(node->left);
        printf("%d", node->key);
        inorder_traversal(node->right);
    }
}
void inorder(BST*bst){
    inorder_traversal(bst->root);
    printf("\n");
}




int main() {
    // Initialize the BST with no root node
    BST* bst = createBST();

    // Insert nodes into the BST
    insert(bst, 10);
    insert(bst, 5);
    insert(bst, 15);
    insert(bst, 2);
    insert(bst, 7);
    insert(bst, 12);
    insert(bst, 17);
    insert(bst, 1);
    insert(bst, 3);
    insert(bst, 6);
    insert(bst, 8);
    insert(bst, 11);
    insert(bst, 13);
    insert(bst, 16);
    insert(bst, 18);

 
    // Test IsKey function
    printf("\nIsKey Test Cases:\n");
    printf("%d\n", isKey(bst, 10) != NULL);  // Should be 1 (true)
    printf("%d\n", isKey(bst, 5) != NULL);   // Should be 1 (true)
    printf("%d\n", isKey(bst, 20) == NULL);  // Should be 1 (true)

    // Test delete function
    printf("\nDelete Test Cases:\n");
    delete(bst, 1);  // No children
    delete(bst, 17); // One child
    delete(bst, 5);  // Two children
    delete(bst, 10); // Root with two children

 
    inorder(bst);
    return 0;
}
