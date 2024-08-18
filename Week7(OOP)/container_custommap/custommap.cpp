
#include <iostream>
#include <string>
#include <functional>
#include <vector>

using namespace std;


/*
map 기본 특징.
1. key value pairs
2. key : unique
3. sorted based on their keys, ascending order
4. balanced binary search tree구조, red-black tree
5. logarithmic time complexity
6. 항상 height가 최소가 되도록.
7. hash, heap과 다름.


Binary Search Tree 구조를 띄고 있음.
*/



template <typename K, typename V > //Fill in the empty templates and implement the definition of the class and each member functions
class TreeNode {

    private: 
        K key;
        V value;
        TreeNode<K,V>* left;
        TreeNode<K,V>* right;
        

    public:
        TreeNode(K key, V value)
            : key(key), value(value), left(nullptr), right(nullptr){}
        
        ~TreeNode(){
        }

        K& get_key() {return key;}
        V& get_value() {return value;}
        TreeNode<K,V>* get_right()  {return right;} // const 로 선언하면 받아올 수가 없음.
        TreeNode<K,V>* get_left()  {return left;}
        
        void set_key( K k){key = k;}
        void set_value( V v){value = v;}
        void set_left( TreeNode<K,V>* l){left = l;}
        void set_right( TreeNode<K,V>* r){right = r;}


        bool is_External() const{ return left ==nullptr && right ==nullptr;}
        bool has_child() const{ return left !=nullptr || right !=nullptr;}
        bool is_Internal() const{ return !is_External();}
        bool no_child() const{return !has_child();}
        

};

template <typename K, typename V, typename Compare = std::less<K> > //Fill in the empty templates and implement the definition of the class and each member functions
class CustomMap {
    public :
        TreeNode<K,V>* root;
        Compare comp;
        int n; // number of nodes
        

        CustomMap()
            :root(nullptr), n(0){}

        ~CustomMap(){
            delete root;
        }

        TreeNode<K,V>* get_root(){return root;}

        Compare get_compare(){return comp;}
        


        TreeNode<K,V>* insert_help(TreeNode<K,V>* node, K& key, V& value){
            if (node == nullptr){
                TreeNode<K,V>* new_node = new TreeNode<K,V>(key, value);
                return new_node;
            }
            if(node->get_key() == key){
                return node;
            }

            if (key < node->get_key()){
                node ->set_left(insert_help(node->get_left(), key, value));
            }
            else{
                node -> set_right(insert_help(node->get_right(), key, value));
            }
            return node;
        }

        void insert( K key,  V value){
            root = insert_help(root , key, value);
        }

        void print_help(TreeNode<K,V>* node){
            if (node ==nullptr){
                return;
            }
            print_help(node->get_left());
            cout<<node->get_key()<<":"<<node->get_value()<<endl;
            print_help(node->get_right());
        }
        
        void print_map(){
            //from root
            print_help(root);
            
            
        }

        TreeNode<K,V>* find_right_max(TreeNode<K,V>* node){
            if (node->get_right() == nullptr){
                return node;
            }
            else{
                return find_right_max(node->get_right());
            }
        }

        TreeNode<K,V>* deleteKey_help(TreeNode<K,V>* node, K& key){
            
            if (node == nullptr){//didn't find
                return nullptr;
            }

            if (node->get_key() > key){
                node->set_left(deleteKey_help(node->get_left(), key));
            }
            else if(node->get_key() < key){
                node -> set_right(deleteKey_help(node->get_right(), key));
            }
            else{ // when we find node

                if ((node->get_left() == nullptr) &&(node->get_right() == nullptr)){ // no child
                        delete node;
                        node = nullptr;
                        
                }
                else if((node->get_left() != nullptr) &&(node->get_right() == nullptr)){ // only left
                        //delete node and get left child as node
                        TreeNode<K,V>* temp = node;
                        node = node->get_left();
                        delete temp;
                
                }
                else if ((node->get_left() == nullptr) &&(node->get_right() != nullptr)){// only right
                        //delete node and get right child as node
                        TreeNode<K,V>* temp = node;
                        node = node->get_right();
                        delete temp;

                }
                else{ // two child
                    //find left largest node
                    TreeNode<K,V>* leftlargest = find_right_max(node->get_left());
                    node->set_key(leftlargest->get_key());
                    node->set_value(leftlargest->get_value());
                    node->set_left(deleteKey_help(node->get_left(), leftlargest->get_key()));


                }
            }
            return node;
        }
        void deleteKey(K key){
            root = deleteKey_help(root, key);
        }
        

        TreeNode<K,V>* find_help(TreeNode<K,V>* node, K& key){

            if (node == nullptr){
                return nullptr;
            }

            if (node->get_key() == key){
                return node;
            }

            if (node->get_key() < key){
                return find_help(node->get_right(), key);
            }
            else{
                return find_help(node->get_left(), key);
            }
            return node;

        }
        TreeNode<K,V>* find(K key){
            return find_help(root, key);
        }


        V get_value(K key){
            TreeNode<K,V>* temp = find(key);
            if(temp == nullptr){
                return V();
            }
            else{
                return temp->get_value();
            }
        }

        V& operator[](const K key){
            
            
            if (find(key) == nullptr){
                insert(key, V()); // 없을 경우 초기화
             
            }
            return find(key)->get_value(); // if exist
        
        }
};



int main(void) {
    CustomMap<int, string> map;
    map.insert(5, "Five");
    map.insert(3, "Three");
    map.insert(8, "Eight");
    map.insert(10, "Ten");
    map.print_map();
}