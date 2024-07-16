#include <iostream> 
#include <climits> 
#include <queue>
#include <cmath>
// #include <stack>
using namespace std; 

struct Node {
    int val;
    Node * left = nullptr;
    Node * right = nullptr;
    Node * parent = nullptr;
};
  

// A class for Min Heap 
class MaxHeap 
{ 
    Node * root;
    Node * last_node;
    int heapsize;

public: 
    // Constructor 
    MaxHeap();
    // Returns the node pointer that includes the maximum value (root node)
    Node * getMax();
    // Inserts a new key 'k' 
    void enqueue(int k); 
    // Delete the maxmium value (root node)
    void dequeue();
    void printHeap();
    void swap(Node * a, Node * b);
}; 




MaxHeap::MaxHeap(){
        root = nullptr;        
}  

Node * MaxHeap::getMax(){
    return root;
}

void MaxHeap::printHeap(){
    Node * currNode = root;
    queue<Node*> q;

    q.push(root);
    std::cout << "Print Heap: ";
    while (!q.empty() && q.front()){
        std::cout << q.front()->val << " ";
        if (q.front()->left){
            q.push(q.front()->left);
        }

        if (q.front()->right){
            q.push(q.front()->right);
        }

        q.pop();
    }
    std::cout << std::endl;
}

void MaxHeap::swap(Node * a, Node * b){
    int temp = a->val;
    a->val = b->val;
    b->val = temp;
}


// Inserts a new key 'k' 
void MaxHeap::enqueue(int k) 
{ 
    
    /* 
    1. insert node to last(왼쪽부터 채우기)
    2. percolate up : swap with parent , terminate when the node reaches root or  parent >= item
    */
   Node * new_node = new Node();
   new_node -> val = k;
   

   if(!root){
    root = new_node;
    last_node = root;
    heapsize = 1;
   }

   else{

    //traverse 하는데 이진 트리 특성 이용해서.
    //finding insert point : by binary (complete binary tree)
    /*
    특정 노드 인덱스 i
    부모 노드 인덱스 : (i-1)/2
    왼쪽 자식 : 2*i+ 1
    오른쪽 자시 : 2*i +2
    */
    // int insert_index = heapsize;//있다고 생각하고. 그 위를 찾을려고 하는 것.
    // stack<int> path;
    // while(insert_index>0){
    //     path.push(insert_index); //from last node to root
    //     insert_index = (insert_index-1)/2; //parent node input
    // } //bottom : 특정 노드 -> top : root

    // //from root 부터 내려오기 : 내려올때, 최대한 가쪽으로
    // Node * insert_point = root;
    // while(path.size() >1){
    //     int next = path.top();
    //     path.pop();

    //     if(next%2 ==1){
    //         //left;
    //         if(insert_point -> left){
    //             insert_point  = insert_point -> left;
    //         }
    //     }
    //     else{
    //         //right
    //         if(insert_point->right){
    //             insert_point = insert_point->right;
    //         }
    //     }
    // }

    //다른 더 효율적인 방식
    int binary = log2(heapsize+1);
    Node* insert_point = root;
    for (int i = binary -1; i>=1; --i){ // root 제외, 넣을 곳 바로 직전까지
        
        if((heapsize +1) & (1<<i)){ // if true : then right
            insert_point = insert_point -> right;
        }
        else{
            insert_point = insert_point -> left;
        }
        

    }


    if (!insert_point->left){
        insert_point->left = new_node;
    }
    else{
        insert_point->right = new_node;
    }

 
    // insert할때 왼쪽만 비는 경우는 없다.
    new_node-> parent = insert_point; // 연결
    last_node = new_node;




    //percolate up : from insert point
    //swap with parent , terminate when the node reaches root or  parent >= item
    Node * curr_node = last_node;
    while((curr_node->parent != nullptr) && (curr_node->val > curr_node->parent->val) ){ // not root node and parent < item
        //then value swap with parent
        swap(curr_node, curr_node->parent);
        curr_node = curr_node->parent;
    }

    ++heapsize;
   }
   
    

} 

// Removes the root node and heapify
void MaxHeap::dequeue(){
    
    if(!root) return;
    
    //value swap with last node
    swap(root, last_node);

    //remove last_node
    // 지우기 전에 정리해주기: 초기화 
    if(!last_node-> parent){// root node
        root = nullptr;
    }
    else{
        if(last_node->parent->left  == last_node){
            last_node->parent->left = nullptr;
        }
        else{
            last_node->parent->right = nullptr;
        }
    }
    delete last_node; // pointer 지우기
    --heapsize;


    //last node pointer 위치 찾아주기. : last_node = leafnode without child
    if (heapsize == 0)
    {
        last_node = nullptr;
        return;
    }

    int binary = log2(heapsize); // traverse 횟수 = height
    Node* new_last_node = root;
    for (int i = binary -1; i>=0; --i){ // 완전 last 노드까지 내려가기
        if ((heapsize) & (1<<i)){ // 1가지고 i 만큼 shifting(left)
            new_last_node = new_last_node-> right;
        }
        else{
            new_last_node = new_last_node->left;
        }
    }
    last_node= new_last_node;


    //percolate down
    Node * curr_node = root;
    while (curr_node->left || curr_node->right) {
    // 왼쪽은 있을 때 근데, 왼쪽이 더 큼.
        if (curr_node->left && (!curr_node->right || curr_node->left->val >= curr_node->right->val)) {
        
        //오로지 바꾸는 경우
            if (curr_node->val < curr_node->left->val) {
                swap(curr_node, curr_node->left);
                curr_node = curr_node->left;

            } 
            else {// 그 외는 
                break; 
            }
        //오른쪽 살아잇으면 왼쪽도 있는 거임.(둘다 있는 경우)
        } 
        else if (curr_node->right) {
        
            if (curr_node->val < curr_node->right->val) {
            
                swap(curr_node, curr_node->right);
                curr_node = curr_node->right;
            } 
            else {
                break; 
            }
        } 
        else {//모두 없는 경우임.
            break; 
        }
    }



    



}
