#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>

using namespace std;

enum Color { RED, BLACK };

// RBNode 클래스
class RBNode {
public:
    int key;
    Color color;
    RBNode* left;
    RBNode* right;
    RBNode* parent;

    RBNode(int key) : key(key), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}

    friend ostream& operator<<(ostream& os, const RBNode& node) {
        os << node.key;
        return os;
    }
};

class RedBlackTree {
private:
    RBNode* root;
    RBNode* EXT; // 외부 노드

    void left_rotate(RBNode* x) {
        RBNode* y = x->right; // x의 오른쪽 자식
        x->right = y->left; // y의 왼쪽 자식 T2를 x의 오른쪽 자식으로 설정

        if (y->left != EXT) {
            y->left->parent = x; // T2의 부모를 x로 설정
        }

        y->parent = x->parent; // y의 부모를 x의 부모로 설정

        if (x->parent == nullptr) {
            root = y; // x가 루트 노드인 경우 y를 새로운 루트로 설정
        } else if (x == x->parent->left) {
            x->parent->left = y; // x가 왼쪽 자식인 경우 y를 x의 부모의 왼쪽 자식으로 설정
        } else {
            x->parent->right = y; // x가 오른쪽 자식인 경우 y를 x의 부모의 오른쪽 자식으로 설정
        }

        y->left = x; // x를 y의 왼쪽 자식으로 설정
        x->parent = y; // x의 부모를 y로 설정
    }

    void right_rotate(RBNode* x) {
        RBNode* y = x->left; // x의 왼쪽 자식
        x->left = y->right; // y의 오른쪽 자식 T2를 x의 왼쪽 자식으로 설정

        if (y->right != EXT) {
            y->right->parent = x; // T2의 부모를 x로 설정
        }

        y->parent = x->parent; // y의 부모를 x의 부모로 설정

        if (x->parent == nullptr) {
            root = y; // x가 루트 노드인 경우 y를 새로운 루트로 설정
        } else if (x == x->parent->right) {
            x->parent->right = y; // x가 오른쪽 자식인 경우 y를 x의 부모의 오른쪽 자식으로 설정
        } else {
            x->parent->left = y; // x가 왼쪽 자식인 경우 y를 x의 부모의 왼쪽 자식으로 설정
        }

        y->right = x; // x를 y의 오른쪽 자식으로 설정
        x->parent = y; // x의 부모를 y로 설정
    }

    void insert_fix(RBNode* n) {
        RBNode* pn = nullptr;
        RBNode* gn = nullptr;
        RBNode* un = nullptr;

        while (n->parent != nullptr && n->parent->color == RED) {
            pn = n->parent; // n의 부모
            gn = pn->parent; // n의 조부모

            if (pn == gn->left) {
                un = gn->right; // 삼촌 노드

                if (un != nullptr && un->color == RED) {
                    // Case 1: 삼촌이 RED인 경우
                    gn->color = RED;
                    pn->color = BLACK;
                    un->color = BLACK;
                    n = gn; // 조부모를 기준으로 다시 균형 맞추기
                } else {
                    if (n == pn->right) {
                        // Case 2: n이 부모의 오른쪽 자식인 경우
                        left_rotate(pn);
                        n = pn;
                        pn = n->parent;
                    }

                    // Case 3: n이 부모의 왼쪽 자식인 경우
                    pn->color = BLACK;
                    gn->color = RED;
                    right_rotate(gn);
                }
            } else {
                un = gn->left; // 삼촌 노드

                if (un != nullptr && un->color == RED) {
                    // Case 1: 삼촌이 RED인 경우
                    gn->color = RED;
                    pn->color = BLACK;
                    un->color = BLACK;
                    n = gn; // 조부모를 기준으로 다시 균형 맞추기
                } else {
                    if (n == pn->left) {
                        // Case 2: n이 부모의 왼쪽 자식인 경우
                        right_rotate(pn);
                        n = pn;
                        pn = n->parent;
                    }

                    // Case 3: n이 부모의 오른쪽 자식인 경우
                    pn->color = BLACK;
                    gn->color = RED;
                    left_rotate(gn);
                }
            }
        }

        root->color = BLACK; // 루트 노드는 항상 BLACK
    }

    void transplant(RBNode* u, RBNode* v) {
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        if (v != nullptr) {
            v->parent = u->parent;
        }
    }

    RBNode* minimum(RBNode* node) {
        while (node->left != EXT) {
            node = node->left;
        }
        return node;
    }

    void delete_fix(RBNode* x) {
        while (x != root && x->color == BLACK) {
            if (x == x->parent->left) {
                RBNode* w = x->parent->right;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    left_rotate(x->parent);
                    w = x->parent->right;
                }
                if (w->left->color == BLACK && w->right->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->right->color == BLACK) {
                        w->left->color = BLACK;
                        w->color = RED;
                        right_rotate(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    left_rotate(x->parent);
                    x = root;
                }
            } else {
                RBNode* w = x->parent->left;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    right_rotate(x->parent);
                    w = x->parent->left;
                }
                if (w->right->color == BLACK && w->left->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->left->color == BLACK) {
                        w->right->color = BLACK;
                        w->color = RED;
                        left_rotate(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    right_rotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }

public:
    RedBlackTree() {
        EXT = new RBNode(-1);
        EXT->color = BLACK;
        root = EXT;
    }

    RBNode* get_root() {
        return root;
    }

    void preorder_traverse(RBNode* cur, function<void(RBNode*)> func) {
        if (cur == EXT) return;
        func(cur);
        preorder_traverse(cur->left, func);
        preorder_traverse(cur->right, func);
    }

    void inorder_traverse(RBNode* cur, function<void(RBNode*)> func) {
        if (cur == EXT) return;
        inorder_traverse(cur->left, func);
        func(cur);
        inorder_traverse(cur->right, func);
    }


    int tree_height(RBNode* node) {
        if (node == EXT) return -1;
        int left_height = tree_height(node->left);
        int right_height = tree_height(node->right);
        return max(left_height, right_height) + 1;
    }

    int node_count(RBNode* node) {
        if (node == EXT) return 0;
        return 1 + node_count(node->left) + node_count(node->right);
    }

    int black_height(RBNode* node) {
        if (node == EXT) return 0;
        int left_black_height = black_height(node->left);
        int right_black_height = black_height(node->right);
        if (node->color == BLACK) {
            return max(left_black_height, right_black_height) + 1;
        } else {
            return max(left_black_height, right_black_height);
        }
    }

    void insert(int key) {
        RBNode* new_node = new RBNode(key);
        new_node->left = EXT;
        new_node->right = EXT;

        RBNode* cur = root;

        if (root == EXT) {
            root = new_node;
            root->color = BLACK;
            root->parent = nullptr;
            return;
        }

        RBNode* parent = nullptr;

        while (cur != EXT) {
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

        insert_fix(new_node);
    }

    RBNode* search(int key) {
        RBNode* cur = root;
        while (cur != EXT && cur->key != key) {
            if (key < cur->key) {
                cur = cur->left;
            } else {
                cur = cur->right;
            }
        }
        return cur;
    }

    void delete_node(int key) {
        RBNode* node = search(key);
        if (node == EXT) return;

        RBNode* y = node;
        RBNode* x;
        Color y_original_color = y->color;

        if (node->left == EXT) {
            x = node->right;
            transplant(node, node->right);
        } else if (node->right == EXT) {
            x = node->left;
            transplant(node, node->left);
        } else {
            y = minimum(node->right);
            y_original_color = y->color;
            x = y->right;
            if (y->parent == node) {
                x->parent = y;
            } else {
                transplant(y, y->right);
                y->right = node->right;
                y->right->parent = y;
            }
            transplant(node, y);
            y->left = node->left;
            y->left->parent = y;
            y->color = node->color;
        }

        delete node;

        if (y_original_color == BLACK) {
            delete_fix(x);
        }
    }

    void print_node(RBNode* node) {
        if (node) {
            cout << "node: " << node->key << ", ";
            if (node->color == RED) {
                cout << "color: RED, ";
            } else {
                cout << "color: BLACK, ";
            }
            if (node->left) {
                cout << "left: " << node->left->key << ", ";
            }
            if (node->right) {
                cout << "right: " << node->right->key << ", ";
            }
            if (node->parent) {
                cout << "parent: " << node->parent->key;
            }
            cout << endl;
        }
    }
};


int main() {
    RedBlackTree rbt;

    for (int i = 0; i < 10; ++i) {
        rbt.insert(i);
    }

    rbt.preorder_traverse(rbt.get_root(), [&](RBNode* node) { rbt.print_node(node); });
    cout << string(100, '*') << endl;

    // 삭제 테스트
    rbt.delete_node(3);
    rbt.delete_node(7);

    rbt.preorder_traverse(rbt.get_root(), [&](RBNode* node) { rbt.print_node(node); });
    cout << string(100, '*') << endl;

    return 0;
}

