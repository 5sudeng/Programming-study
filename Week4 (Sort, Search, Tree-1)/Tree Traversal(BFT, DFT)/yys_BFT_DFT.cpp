#include <iostream>
#include <queue>
using namespace std;

class TreeNode{
    public:
        int val;
        TreeNode* left;
        TreeNode* right;
        TreeNode(int x) : val(x), left(nullptr), right(nullptr){

        }
        ~TreeNode(){
            delete left;
            delete right;
        }
};


class Tree{
    private:
        TreeNode* root;

    public:
        Tree(TreeNode * root=nullptr): root(root){

        }
        ~Tree(){
            delete root;//이렇게 하면 root 부터 child 모두 재귀적으로 삭제
        }

        void visit(TreeNode * node){
            cout<<node->val<<" ";
        }


        void BFT(){
            if (root == nullptr){
                return;
            }

            queue<TreeNode*> q;
            q.push(root);

            while(!q.empty()){
                TreeNode* curNode = q.front();
                q.pop();

                visit(curNode);
                if (curNode->left !=nullptr){
                    q.push(curNode->left);
                }
                if (curNode->right!=nullptr){
                    q.push(curNode->right);
                }
            }
        }

        void DFT_preorderhelp(TreeNode* curNode){
            if (curNode == nullptr){
                return;
            }
            visit(curNode);
            DFT_preorderhelp(curNode->left);
            DFT_preorderhelp(curNode->right);
        }

        void DFT_preorder(){
            DFT_preorderhelp(root);
        }
        
        void DFT_inorderhelp(TreeNode* curNode){
            if (curNode == nullptr){
                return;
            }
            DFT_inorderhelp(curNode->left);
            visit(curNode);
            DFT_inorderhelp(curNode->right);
            
        }

        void DFT_inorder(){
            DFT_inorderhelp(root);
        }

        void DFT_postorderhelp(TreeNode* curNode){
            if (curNode == nullptr){
                return;
            }
            DFT_postorderhelp(curNode->left);
            DFT_postorderhelp(curNode->right);
            visit(curNode);
            
        }

        void DFT_postorder(){
            DFT_postorderhelp(root);
        }
};


int main(){

    TreeNode* node1 = new TreeNode(1);
    TreeNode* node2 = new TreeNode(2);
    TreeNode* node3 = new TreeNode(3);
    TreeNode* node4 = new TreeNode(4);
    TreeNode* node5 = new TreeNode(5);
    
    node1->left = node2;
    node1->right = node3;
    node2->left = node4;
    node2->right = node5;

    Tree tree(node1);

    cout<<"BFT"<<endl;
    tree.BFT();
    cout<<endl;
    cout<<"preorder"<<endl;
    tree.DFT_preorder();
    cout<<endl;
    cout<<"inorder"<<endl;
    tree.DFT_inorder();
    cout<<endl;
    cout<<"postorder"<<endl;
    tree.DFT_postorder();


     //이렇게 하면 root 부터 child 모두 재귀적으로 삭제
     //delete tree를 안해도 되는게, tree는 동적할당이 아니다. 
     //main을 벗어나면 tree가 destructor 가 발동되는데, 그때, root가 delete되면서 자식노드들 모두 free됨.

    return -1;
}