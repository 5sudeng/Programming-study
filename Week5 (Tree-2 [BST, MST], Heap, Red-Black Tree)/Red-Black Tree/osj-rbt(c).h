#ifndef RBTREE_H
#define RBTREE_H

#include <stddef.h>

typedef enum color_t {
    RBTREE_RED,
    RBTREE_BLACK
} color_t;

typedef int key_t;

typedef struct node_t {
    key_t key;
    struct node_t *parent;
    struct node_t *left;
    struct node_t *right;
    color_t color;
} node_t;

typedef struct rbtree {
    node_t *root;
    node_t *nil;
} rbtree;

rbtree *new_rbtree(void);
void delete_rbtree(rbtree *t);
void left_rotate(rbtree *t, node_t *x);
void right_rotate(rbtree *t, node_t *x);
void rb_insert_fixup(rbtree *t, node_t *z);
node_t *rbtree_insert(rbtree *t, const key_t key);
node_t *rbtree_find(const rbtree *t, const key_t key);
node_t *rbtree_min(const rbtree *t);
node_t *rbtree_max(const rbtree *t);
int rbtree_erase(rbtree *t, node_t *z);
int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n);

#endif // RBTREE_H
