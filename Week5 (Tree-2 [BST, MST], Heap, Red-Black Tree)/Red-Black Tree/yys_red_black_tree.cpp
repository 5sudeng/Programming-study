#include <iostream>
#include <string>
using namespace std;

/*
reference : https://gist.github.com/gowoonsori/a725e29ef1880f0592fe5760f4908c6b
*/


enum Color
{
    RED, BLACK
};

//노드
struct node
{
    int key;
    node *left = nullptr;
    node *right = nullptr;
    node *parent = nullptr;
    Color color = BLACK;
};

typedef node *NodePtr; // typedef : 기존 데이터 타입에 새로운 이름을 부여하기 위함.

 
class RBTREE{
    private : 
        NodePtr root;
        NodePtr leafNode = nullptr;

    //특정 key값 찾기 : BST property
    NodePtr IsKey(int item){
        NodePtr t = root;
        NodePtr parent = nullptr;

        while (t!=nullptr && t->key != item){
            parent = t;
            t = (item < parent->key)? parent -> left : parent -> right; // BST 속성을 이용하면서 내려가기

        }
        return t;
    }



    void Insert(int item){

        // x :삽입할 곳 pointer, y : 삽입할 곳의 parent

        NodePtr x = this-> root;
        NodePtr y = leafNode; /// T.nill;
        NodePtr z = new node(); // 동적 할당

        z->key = item;
        z->parent = nullptr; // 이제부터 이걸 찾아줄 것임.
        

        // 일단 insert는 BST와 같음.

        while(x!=leafNode){
            y = x;

            if (item < x-> key){
                x = x->left;
            }
            else{
                x =x->right;
            }
        }
        z->parent = y;

        // root인 경우.
        if(y == leafNode){
            root = z;
        }
        else if (item < y->key){
            y->left = z;
        }
        else y->right = z;

        z-> color = RED; // 일단 RED로 삽입.
        z->left = leafNode;
        z->right = leafNode;
        InsertFixUp(z);// Redblack tree로 바꾸기 위함.

    }

    void InsertFixUp(NodePtr z){
        /* 
        case 1: red uncle y 
        -> recolor : parent(black), grandparent(red), uncle(black)
        -> move z to grandparent -> fixup again
        

        // case2 & 3 모두 왼쪽 기준임. 오른쪽은 반대로 해야함.
        case2 : black uncle y & z = right child
        -> parent left rotate -> case 3

        case 3 : black uncle y & z = left child
        -> recolor : parent(black), grandparent(red), -> grandparent right rotate
        */


       // parent가 black이면 아무것도 안해도 됌. 어차피 Red로 들어갈거라.
       while(z!= root && z->parent->color == RED){
            
            NodePtr grandparent = z->parent->parent;
            NodePtr uncle = (z->parent == grandparent->left)? grandparent->right : grandparent->left; // symmetric을 동시에 처리하기 위함. 왼쪽 uncle인지 오른쪽 uncle인지
            bool side = (z->parent == grandparent->left)? true : false;


            //case1
            if (uncle && uncle-> color ==RED){
                z->parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                z = grandparent;
            }

            else{ // BLACK uncle

                //case 2
                //왼쪽 오른쪽 구별
                // 왼쪽이면 right child인지, 오른쪽이면 left child인지.
                if (z==(side? z->parent->right : z->parent->left)){
                    z = z->parent;
                    //left rotate
                    side? RotateLeft(z) : RotateRight(z);

                }

                //case 3
                z->parent->color = BLACK;
                grandparent->color = RED;
                side? RotateRight(grandparent) : RotateLeft(grandparent);

            }
       }

       root->color = BLACK; // z가 root, RED로 들어갈수도 있어서,
    }



    bool Delete(int item){

        /*
        Case1 : no child
        -> y = z
        ->simply remove it and replace with z

        Case2: just one child
        -> y = z
        ->elevate child , z 대체

        Case3 : two child
        y = right least : no left child
        -> 3-1 : y가 z의 child인 경우 -> just replace with it
        -> 3-2 : y가 z의 child가 아닌 경우 -> rightrotate(y)
        */





        NodePtr z = IsKey(item);
        //못찾으면 false
        if (!z){
            return false;
        }
        else{

            NodePtr x,y; // y : z 자리를 대체하는 노드 , x : y를 대체하는 노드
            y = z;
            Color y_original_color = y->color;

            //case 1  or case 2
            if (z->left ==leafNode){
                x = z->right;// 아무 의미는 없지만  x에 대해 명시해주는 역할임. 나중에 fix up할 때 사용할 때 사용
                Transplant(z, z->right);
            }
            else if (z->right == leafNode){
                x = z->left;// 아무 의미는 없지만  x에 대해 명시해주는 역할임. 나중에 fix up할 때 사용할 때 사용
                Transplant(z, z->left);
            }

            else{ //case 3 : two child

                y = tree_minimum(z->right);
                y_original_color = y->color;
                x = y->right;// 아무 의미는 없지만  x에 대해 명시해주는 역할임. 나중에 fix up할 때 사용할 때 사용
                
                //case 3-2
                if (y!= z->right){
                    Transplant(y, y->right); // replace y by its right child
                    y->right = z->right;
                    y->right->parent = y; // 

                }
                else{
                    // case 3-1
                    x->parent = y; // 아무 의미는 없지만  x에 대해 명시해주는 역할임. 나중에 fix up할 때 사용할 때 사용.
                }

                //이제 y 에 대해서는 완성했으니, z 빼고 교체시키기.(z가 들어가 있는 관련 정보들을 다 업데이트하는 느낌.)
                Transplant(z, y);
                y->left = z->left;
                y->left->parent = y;
                y->color = z->color; // z가 root 였을 수도 있기에.


            }
            delete z;

            if (y_original_color == BLACK){
                DeleteFixUp(x);
            }
        }
        
        return true;
    }


    void DeleteFixUp(NodePtr x)
    {
        //check x's sibiling :s
        /*
        case 1 : s(RED)
        ->recolor : x.p(RED), s(BLACK)
        -> leftrotate(x.p)
        -> s = x.p.right
        -> case2, case3, case 4


        case 2: s(BLACK) with two BLACK child and x.p(RED)
        -> recolor : x.p(BLACK), s(RED)
        -> DONE

        case 2-1 : s(BLACK) with two BALCK child & x.p(BLACK)
        ->recolor : s(RED)
        -> move x to parent -> fix again

        case 3: s(BLACK), s->left(RED), s->right(BLACK)
        ->recolor : s->left(BLACK), s(RED)
        ->rightrotate(s)
        -> Case4

        case 4: s(BLACK), s->right(RED)
        ->recolor : s(x.p.color) ,x.p(BLACK),  s->right(BLACK)
        ->leftrotate(x.p)
        */



        NodePtr s;
        

        //root이거나, double black이 깨질 떄까지.
        while(x!=root && x->color == BLACK){
            
            if(x== x->parent ->left){ // 왼쪽일 경우

                //sibling
                s = x->parent->right;

                //case 1
                if (s->color ==RED){
                    s->color = BLACK;
                    x->parent->color = RED;
                    RotateLeft(x->parent);
                    s = x->parent->right; // x는 안바뀌었는데, x->parent의 right child 정보가 바뀜.
                }
                
                //after case 1-> case2, case3, case4
                //case 2
                if (s->right->color == BLACK && s->left->color == BLACK){

                    s->color = RED;
                    x = x->parent; // fix again (if x still BLACK이라면)

                }
                else
                {
                    //case 3
                    if (s->right->color== BLACK){
                        s->left->color = BLACK;
                        s->color = RED;
                        RotateRight(s);
                        s = x->parent->right; // rotate right 하면서 바뀌었기에.
                    }

                    //after case 3->4
                    s->color = x->parent->color;
                    x->parent->color = BLACK;
                    s->right->color = BLACK;
                    RotateLeft(x->parent);
                    x = root; // Done, terminate while
                }


            }


            //symmetric 오른쪽일 경우. : 방향만 반대로.
            else{
                s = x->parent->left;

                //case 1
                if (s->color ==RED){
                    s->color = BLACK;
                    x->parent->color = RED;
                    RotateRight(x->parent);
                    s = x->parent->left;
                }
                else{
                    //case2
                    if (s->left->color == BLACK && s->right -> color ==BLACK){
                        s->color = RED;
                        x = x->parent;
                    }
                    else{

                        //case 3
                        if (s->left->color == BLACK){
                            s->right->color = BLACK;
                            s->color = RED;
                            RotateLeft(s);
                            s = x->parent->left;
                        }

                        //case 4
                        s->color = x->parent->color;
                        x->parent->color = BLACK;
                        s->left->color = BLACK;
                        RotateRight(x->parent);
                        x = root;

                    }
                }

            }

        }
        x->color = BLACK; // case 2-1에 해당되어 x.p(RED)였다면 바꿔주고 종료.
        root->color = BLACK;
    }


    // replace subtree u ->v
    void Transplant(NodePtr u, NodePtr v){
        if (!u->parent){
            root = v;
        }
        else if (u == u->parent ->left){
            u->parent->left = v;
        }
        else{
            u->parent->right = v;
        }

        v->parent = u->parent;
    }



    //find leftminimum from right subtree
    NodePtr tree_minimum(NodePtr x){ // x must be z->right
        while(x->left !=leafNode){
            x = x->left;
        }
        return x;
    }





    void RotateLeft(NodePtr x)
    {
        NodePtr y = x->right;
        x->right = y->left;

        if (y->left !=leafNode){
            y->left->parent = x;
        }
        y->parent = x->parent;
        if(x->parent!=nullptr){
            //root node
            root = y;
        }
        else if(x == x->parent->left){
            x->parent->left = y;
        }
        else{
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }



    void RotateRight(NodePtr x){
        NodePtr y = x->left;
        x->left = y->right;

        if(y->right !=leafNode){
            y->right->parent = x;
        }
        y->parent = x->parent;

        if(!x->parent){
            root = y;
        }
        else if(x == x->parent->left){
            x->parent->left = y;
        }
        else{
            x->parent->right = y;
        }
        y->right = x;
        x->parent = y;
    }

};