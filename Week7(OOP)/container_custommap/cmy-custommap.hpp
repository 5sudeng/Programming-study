#include <iostream>
#include <string>
#include <functional>
#include <queue>

using namespace std;

template < typename K, typename V > //Fill in the empty templates and implement the definition of the class and each member functions
class TreeNode {
private:
    K key;
    V value;
    TreeNode* left;
    TreeNode* right;

public:
    TreeNode<K,V>(K k, V v) : key(k), value(v) { left = nullptr; right = nullptr; }

    void set_key(K k) { key = k; }
    K get_key() { return key; }

    void set_value(V v) { value = v; }
    V& get_value() { return value; }

    void set_left(TreeNode<K,V>* leftNode) { left = leftNode; }
    TreeNode<K,V>* get_left() { return left; }

    void set_right(TreeNode<K,V>* rightNode) { right = rightNode; }
    TreeNode<K,V>* get_right() { return right; }
};

template < typename K, typename V, typename Compare = std::less<K> > //Fill in the empty templates and implement the definition of the class and each member functions
class CustomMap {
public:
    TreeNode<K,V>* root;
    Compare object;

    CustomMap() { root = nullptr; }

    TreeNode<K,V>* get_root() { return root; }
    Compare get_compare() { return object; }

    void insert(K key, V value) {
        TreeNode<K,V>* newNode = new TreeNode<K,V>(key, value);
        if (!root) { root = newNode; }
        else {
            TreeNode<K,V>* curr = root;
            TreeNode<K,V>* parent = nullptr;

            while (curr) {
                parent = curr;
                if (object(key, curr->get_key())) {
                    curr = curr->get_left();
                } else {
                    curr = curr->get_right();
                }
            }
            if (object(key, parent->get_key())) { parent->set_left(newNode); }
            else { parent->set_right(newNode); }
        }
    }

    void print_map() {
        queue<TreeNode<K,V>*> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode<K,V>* curr = q.front(); q.pop();

            if (curr->get_left()) { q.push(curr->get_left()); }
            if (curr->get_right()) { q.push(curr->get_right()); }

            cout << curr->get_key() << ":" << curr->get_value() << endl;
        }
    }

    void deleteKey(K key) {
        if (!root) { return; }
        
        TreeNode<K,V>* curr = root;
        TreeNode<K,V>* parent = nullptr;
        while (curr) {
            parent = curr;
            if (object(key, curr->get_key())) {
                curr = curr->get_left();
            } else if (object(curr->get_key(), key)) {
                curr = curr->get_right();
            } else { // found the node to delete
                
                // no children
                if (!curr->get_left() && !curr->get_right()) {
                    if (curr == root) {
                        root = nullptr;
                    } else if (curr == parent->get_left()) {
                        parent->set_left(nullptr);
                    } else {
                        parent->set_right(nullptr);
                    }
                    delete curr;
                
                // one child
                } else if (!curr->get_left()) {
                    if (curr == root) {
                        root = curr->get_right();
                    } else if (curr == parent->get_left()) {
                        parent->set_left(curr->get_right());
                    } else {
                        parent->set_right(curr->get_right());
                    }
                    delete curr;

                } else if (!curr->get_right()) {
                    if (curr == root) {
                        root = curr->get_left();
                    } else if (curr == parent->get_left()) {
                        parent->set_left(curr->get_left());
                    } else {
                        parent->set_right(curr->get_left());
                    }
                    delete curr;

                // two children    
                } else {
                    TreeNode<K,V>* succParent = curr;
                    TreeNode<K,V>* succ = curr->get_right();
                    while (succ->get_left()) {
                        succParent = succ;
                        succ = succ->get_left();
                    }

                    if (succParent != curr) {
                        succParent->set_left(succ->get_right());
                    } else {
                        succParent->set_right(succ->get_right());
                    }

                    // copy key and value from the successor node to current node
                    curr->set_key(succ->get_key());
                    curr->set_value(succ->get_value());
                    delete succ; 
                }
                return;
            }
        }
    }

    V get_value(K key) {
        if (!root) { insert(key, V()); return root->get_value(); }

        TreeNode<K,V>* curr = root;
        while (curr) {
            if (object(key, curr->get_key())) {
                curr = curr->get_left();
            } else if (object(curr->get_key(), key)) {
                curr = curr->get_right();
            } else {
                return curr->get_value();
            }
        }
        return V();
    }

    V& operator[](K key) {
        if (!root) { insert(key, V()); return root->get_value(); }

        TreeNode<K,V>* curr = root;
        TreeNode<K,V>* parent = nullptr;
        while (curr) {
            parent = curr;
            if (object(key, curr->get_key())) {
                curr = curr->get_left();
            } else if (object(curr->get_key(), key)) {
                curr = curr->get_right();
            } else {
                return curr->get_value();
            }
        }

        TreeNode<K,V>* newNode = new TreeNode<K,V>(key, V());
        if (object(key, parent->get_key())) {
            parent->set_left(newNode);
        } else {
            parent->set_right(newNode);
        }

        return newNode->get_value();
    }
};
