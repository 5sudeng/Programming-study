#include "bst.h"

#include <stdio.h>
#include <stdlib.h>

void inorder(treeNode* root) {
  if (root) {
      inorder(root->left);
      printf("%d ",root->key);
      inorder(root->right);
  }
}

// Search x from BST, return node which has x
// Otherwise, return NULL
treeNode* find(treeNode* root, element x) {
    treeNode* p;
    p = root;
    if (p == NULL)
        return NULL;
    if (x == p->key)
        return p;
    if (x < p->key)
        return find(p->left, x);
    else return find(p->right, x);
}

// Insert x, check p->key
// If x already exists, do not insert
// return root p
treeNode* insert(treeNode* p, element x) {
    treeNode *t, *q; //target //target's parent
    t = p;
    while (t != NULL){
        if (x == t->key)
            return NULL;
        q = t;
        if (x < t->key)
            t = t->left;
        else
            t = t->right;
    }
    
    treeNode* new;
    new = malloc(sizeof(treeNode));
    new->key = x;
    new->left = NULL;
    new->right = NULL;
    
    if (p == NULL)
        p = new;
    else if (x < q->key)
        q->left = new;
    else
        q->right = new;
    return p;
}

treeNode* findParent(treeNode* root, element x, treeNode* par) {
    treeNode *tmp;
    tmp = root;
    if (tmp == NULL)
        return NULL;
    if (x == tmp->key)
        return par;
    if (x < tmp->key){
        return findParent(tmp->left, x, tmp);
    }
    else return findParent(tmp->right, x, tmp);
}

treeNode* maxnode(treeNode* root, treeNode* max) {
    treeNode* tmp;
    tmp = root;
    while (1){
        max = tmp->right;
        tmp = tmp->right;
        if((tmp->right) == NULL)
            break;
    }
    return max;
}

// Delete node which has key as value
// Will be a long~function
// if 1: key not found
// if 2: terminal node
// if 3: the node has one child
// if 4: the node has two children (solution chose successor from left tree)
void erases(treeNode* root, element key) {
    treeNode *tmp, *p, *q, *max; //p:삭제 ,q:삭제할 p's parent
    p = find(root, key);
    q = findParent(root, key, NULL);
    
    // 삭제할 노드 x
    if (p == NULL)
        return;
    
    // 삭제할 노드 차수 0
    if (p->left == NULL && p->right == NULL){
        if (q==NULL)
            root = NULL;
        else if (q->left == p)
            q->left = NULL;
        else
            q->right = NULL;
    }
    
    // 삭제할 노드 차수 1
    else if (p->left == NULL || p->right == NULL){
        if (q == NULL)
            root = (root->left != NULL) ? root->left : root->right;
        else if (p->left != NULL){
            if (q->left == p)
                q->left = p->left;
            else
                q->right = p->left;
        } else {
            if (q->left == p)
                q->left = p->right;
            else
                q->right = p->right;
        }
    }
    // 삭제할 노드 차수 2
    else if ((p->left != NULL) && (p->right != NULL)){
        max = p->left;
        tmp = maxnode(p->left, max);
        p->key = tmp->key;
        erases(p->left, p->key);
    }
}
