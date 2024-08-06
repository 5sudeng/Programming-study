#include <stdio.h>
#include <stdlib.h>

typedef enum { RED, BLACK } Color;

typedef struct RBNode {
    int key;
    Color color;
    struct RBNode* left;
    struct RBNode* right;
    struct RBNode* parent;
} RBNode;

RBNode* create_node(int key) {
    RBNode* node = (RBNode*)malloc(sizeof(RBNode));
    node->key = key;
    node->color = RED;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    return node;
}


typedef struct {
    RBNode* root;
    RBNode* EXT; // 외부 노드
} RedBlackTree;

RedBlackTree* create_tree() {
    RedBlackTree* tree = (RedBlackTree*)malloc(sizeof(RedBlackTree));
    tree->EXT = create_node(-1);
    tree->EXT->color = BLACK;
    tree->root = tree->EXT;
    return tree;
}

void left_rotate(RedBlackTree* tree, RBNode* x) {
    RBNode* y = x->right; // x의 오른쪽 자식
    x->right = y->left; // y의 왼쪽 자식 T2를 x의 오른쪽 자식으로 설정

    if (y->left != tree->EXT) {
        y->left->parent = x; // T2의 부모를 x로 설정
    }

    y->parent = x->parent; // y의 부모를 x의 부모로 설정

    if (x->parent == NULL) {
        tree->root = y; // x가 루트 노드인 경우 y를 새로운 루트로 설정
    } else if (x == x->parent->left) {
        x->parent->left = y; // x가 왼쪽 자식인 경우 y를 x의 부모의 왼쪽 자식으로 설정
    } else {
        x->parent->right = y; // x가 오른쪽 자식인 경우 y를 x의 부모의 오른쪽 자식으로 설정
    }

    y->left = x; // x를 y의 왼쪽 자식으로 설정
    x->parent = y; // x의 부모를 y로 설정
}

void right_rotate(RedBlackTree* tree, RBNode* x) {
    RBNode* y = x->left; // x의 왼쪽 자식
    x->left = y->right; // y의 오른쪽 자식 T2를 x의 왼쪽 자식으로 설정

    if (y->right != tree->EXT) {
        y->right->parent = x; // T2의 부모를 x로 설정
    }

    y->parent = x->parent; // y의 부모를 x의 부모로 설정

    if (x->parent == NULL) {
        tree->root = y; // x가 루트 노드인 경우 y를 새로운 루트로 설정
    } else if (x == x->parent->right) {
        x->parent->right = y; // x가 오른쪽 자식인 경우 y를 x의 부모의 오른쪽 자식으로 설정
    } else {
        x->parent->left = y; // x가 왼쪽 자식인 경우 y를 x의 부모의 왼쪽 자식으로 설정
    }

    y->right = x; // x를 y의 오른쪽 자식으로 설정
    x->parent = y; // x의 부모를 y로 설정
}

void insert_fix(RedBlackTree* tree, RBNode* n) {
    RBNode* pn = NULL;
    RBNode* gn = NULL;
    RBNode* un = NULL;

    while (n->parent != NULL && n->parent->color == RED) {
        pn = n->parent; // n의 부모
        gn = pn->parent; // n의 조부모

        if (pn == gn->left) {
            un = gn->right; // 삼촌 노드

            if (un != NULL && un->color == RED) {
                // Case 1: 삼촌이 RED인 경우
                gn->color = RED;
                pn->color = BLACK;
                un->color = BLACK;
                n = gn; // 조부모를 기준으로 다시 균형 맞추기
            } else {
                if (n == pn->right) {
                    // Case 2: n이 부모의 오른쪽 자식인 경우
                    left_rotate(tree, pn);
                    n = pn;
                    pn = n->parent;
                }

                // Case 3: n이 부모의 왼쪽 자식인 경우
                pn->color = BLACK;
                gn->color = RED;
                right_rotate(tree, gn);
            }
        } else {
            un = gn->left; // 삼촌 노드

            if (un != NULL && un->color == RED) {
                // Case 1: 삼촌이 RED인 경우
                gn->color = RED;
                pn->color = BLACK;
                un->color = BLACK;
                n = gn; // 조부모를 기준으로 다시 균형 맞추기
            } else {
                if (n == pn->left) {
                    // Case 2: n이 부모의 왼쪽 자식인 경우
                    right_rotate(tree, pn);
                    n = pn;
                    pn = n->parent;
                }

                // Case 3: n이 부모의 오른쪽 자식인 경우
                pn->color = BLACK;
                gn->color = RED;
                left_rotate(tree, gn);
            }
        }
    }

    tree->root->color = BLACK; // 루트 노드는 항상 BLACK
}

void transplant(RedBlackTree* tree, RBNode* u, RBNode* v) {
    if (u->parent == NULL) {
        tree->root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v != NULL) {
        v->parent = u->parent;
    }
}

RBNode* minimum(RBNode* node, RBNode* EXT) {
    while (node->left != EXT) {
        node = node->left;
    }
    return node;
}

void delete_fix(RedBlackTree* tree, RBNode* x) {
    while (x != tree->root && x->color == BLACK) {
        if (x == x->parent->left) {
            RBNode* w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                left_rotate(tree, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    right_rotate(tree, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                left_rotate(tree, x->parent);
                x = tree->root;
            }
        } else {
            RBNode* w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                right_rotate(tree, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    left_rotate(tree, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                right_rotate(tree, x->parent);
                x = tree->root;
            }
        }
    }
    x->color = BLACK;
}

void insert(RedBlackTree* tree, int key) {
    RBNode* new_node = create_node(key);
    new_node->left = tree->EXT;
    new_node->right = tree->EXT;

    RBNode* cur = tree->root;

    if (tree->root == tree->EXT) {
        tree->root = new_node;
        tree->root->color = BLACK;
        tree->root->parent = NULL;
        return;
    }

    RBNode* parent = NULL;

    while (cur != tree->EXT) {
        parent = cur;
        if (key < cur->key) {
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }

    new_node->parent = parent;
    if (key < parent->key) {
        parent->left = new_node;
    } else {
        parent->right = new_node;
    }

    insert_fix(tree, new_node);
}

RBNode* search(RedBlackTree* tree, int key) {
    RBNode* cur = tree->root;
    while (cur != tree->EXT && cur->key != key) {
        if (key < cur->key) {
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }
    return cur;
}

void delete_node(RedBlackTree* tree, int key) {
    RBNode* node = search(tree, key);
    if (node == tree->EXT) return;

    RBNode* y = node;
    RBNode* x;
    Color y_original_color = y->color;

    if (node->left == tree->EXT) {
        x = node->right;
        transplant(tree, node, node->right);
    } else if (node->right == tree->EXT) {
        x = node->left;
        transplant(tree, node, node->left);
    } else {
        y = minimum(node->right, tree->EXT);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == node) {
            x->parent = y;
        } else {
            transplant(tree, y, y->right);
            y->right = node->right;
            y->right->parent = y;
        }
        transplant(tree, node, y);
        y->left = node->left;
        y->left->parent = y;
        y->color = node->color;
    }

    free(node);

    if (y_original_color == BLACK) {
        delete_fix(tree, x);
    }
}

void print_node(RBNode* node) {
    if (node) {
        printf("node: %d, ", node->key);
        if (node->color == RED) {
            printf("color: RED, ");
        } else {
            printf("color: BLACK, ");
        }
        if (node->left) {
            printf("left: %d, ", node->left->key);
        }
        if (node->right) {
            printf("right: %d, ", node->right->key);
        }
        if (node->parent) {
            printf("parent: %d", node->parent->key);
        }
        printf("\n");
    }
}

void preorder_traverse(RedBlackTree* tree, RBNode* cur, void (*func)(RBNode*)) {
    if (cur == tree->EXT) return;
    func(cur);
    preorder_traverse(tree, cur->left, func);
    preorder_traverse(tree, cur->right, func);
}

void inorder_traverse(RedBlackTree* tree, RBNode* cur, void (*func)(RBNode*)) {
    if (cur == tree->EXT) return;
    inorder_traverse(tree, cur->left, func);
    func(cur);
    inorder_traverse(tree, cur->right, func);
}

int tree_height(RedBlackTree* tree, RBNode* node) {
    if (node == tree->EXT) return -1;
    int left_height = tree_height(tree, node->left);
    int right_height = tree_height(tree, node->right);
    return left_height > right_height ? left_height + 1 : right_height + 1;
}

int node_count(RedBlackTree* tree, RBNode* node) {
    if (node == tree->EXT) return 0;
    return 1 + node_count(tree, node->left) + node_count(tree, node->right);
}

int black_height(RedBlackTree* tree, RBNode* node) {
    if (node == tree->EXT) return 0;
    int left_black_height = black_height(tree, node->left);
    int right_black_height = black_height(tree, node->right);
    if (node->color == BLACK) {
        return left_black_height > right_black_height ? left_black_height + 1 : right_black_height + 1;
    } else {
        return left_black_height > right_black_height ? left_black_height : right_black_height;
    }
}

int main() {
    RedBlackTree* rbt = create_tree();

    for (int i = 0; i < 10; ++i) {
        insert(rbt, i);
    }

    preorder_traverse(rbt, rbt->root, print_node);
    printf("%s\n", "****************************************************************************************************");

    // 삭제 테스트
    delete_node(rbt, 3);
    delete_node(rbt, 7);

    preorder_traverse(rbt, rbt->root, print_node);
    printf("%s\n", "****************************************************************************************************");

    return 0;
}

