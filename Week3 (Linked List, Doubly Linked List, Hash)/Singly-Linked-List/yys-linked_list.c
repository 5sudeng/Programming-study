//linked list에서는 header를 알려주는 sentinel(none)의 유무가 중요했는데,
//C로 넘어오면 malloc을 통해서 heap에 dynamic memory를 할당해주어,
//크기가 동적으로 변하는 linked list를 구현할 수 있다.

#include <stdio.h>

//linkned list in C (no sentinel)
typedef struct nodeType LinkedNode;

struct nodeType{
    int val;
    LinkedNode *next; // 다음 노드를 가리키는 pointer
};


//공간 할당 및 값 할당
LinkedNode *createNode(int x) // __init__함수가 없으니 만들어줘야함. 앞에 *이 있는 이유는 newNode라는 pointer(메모리)를 return 하므로
{
    LinkedNode *newNode;
    newNode = (LinkedNode *) malloc(sizeof(LinkedNode)); //void pointer also linkednode type
    // 메모리를 할당해주고 만들어진 메모리 내 내용을 채워넣는다고 생각하면 됨.

 
    newNode ->val = x;
    newNode->next = NULL;

    return newNode;

}


// single linked list in C no sentinel


typedef struct listType SLlist;
struct listType{
    LinkedNode *first;
    int size;
};



int main(void)
{
    SLlist myLL = {NULL, 0};

    addFirst(&myLL, 10);

    printf("%d\n", getFirst(&myLL));
    getSize(&myLL);
    printSLlist(&myLL);
}


// functions

void addFirst(SLlist *LL, int x)
{
    LinkedNode *newFirst;

    newFirst = createNode(x); // 메모리 만들어서 저장

    newFirst->next = LL -> first; // NULL값
    LL -> first = newFirst;

    LL->size++;// size up

}

int getFirst(SLlist *LL)
{
    if (LL->first !=NULL)
    {
        return LL ->first ->val;

    }
    return 0;
}

int getSize(SLlist *LL)
{
    return LL -> size;
}

void printSLlist(SLlist *LL)
{
    LinkedNode *curr = LL -> first;

    printf("size : %d, firstVal : %d, allVals : ", getSize(LL) , getFirst(LL));

    while(curr !=NULL)
    {
        printf("%d ->", curr->val);
        curr = curr ->next;
    }

    print("END\n");

}


LinkedNode *searchNode(SLlist *LL, int x)
{
    LinkedNode *curr = LL->first;

    while(curr!=NULL)
    {
        if (curr->val == x)
            return curr;
        curr = curr->next;
    }
    return NULL;
}

void DeleteNode(SLlist *LL, int x)
{
    LinkedNode *curr = LL -> first;
    LinkedNode *prev = NULL;


    while(curr != NULL)
    {
        if (curr ->val == x){
            if(curr == LL ->first)
            {
                LL->first = LL->first->next; // 가장 처음에서 찾을 때

            }
        
            else{
                prev->next = curr->next; // 하다가 찾을 경우
            }

            //지우고 buffer은 지우기
            free(curr); // deallocation
            LL->size--;
            return;
        }
        else /// 못찾을 경우, 넘어가기
        {
            prev = curr;
            curr = curr -> next;
        }


    }

}