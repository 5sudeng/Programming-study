#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int element;

struct node{
    element data;
    struct node* next;
};

typedef struct node Node;
//Node * head = NULL;

/*
typedef struct node {
    char *data;
    struct node* next;
} Node;
*/

//노드 찍어보기
void print_list(Node *head) {
//만약 head가 전역변수면 void print_list()    
//앞에서 Node*head = NULL 이런식으로 미리 쓰여있으니깐!
    Node *cur = head;
    while (cur != NULL) {
        printf("%d ", cur->data);
        //만약 data가 char라면 %d 대신 %s
        cur = cur->next;
    }
    printf("\n");
}


//head가 전역변수인경우
// void add_first(char *item) {
//     Node *temp = (Node*)malloc(sizeof(Node));
//     temp -> data = item;
//     temp -> next = head;
//     head = temp;
    //void가 아니라 Node면 return head;까지!

// }

// //head가 전역변수가 아닌경우
// void add_first(Node **ptr_head, char *item) {
//     Node *temp = (Node*)malloc(sizeof(Node));
//     temp -> data = item;
//     temp -> next = *ptr_head;
//     *ptr_head = temp;
// }
//이 경우 add_first(&head, item_to_store) 로 호출

//head가 전역변수가 아닌경우
Node *add_first(Node *head, element item) {
    Node * temp = (Node*)malloc(sizeof(Node));
    temp -> data = item;
    temp -> next = head;
    return temp; //새로운 head node의 주소를 return
}
//이 경우 add_first(head, item_to_store) 로 호출




//어떤 노드 뒤에 새로운 노드 삽입하기
void add_after(Node *prev, element item) {
    //head가 전역변수가 아니면 void add_after(Node *head, Node *prev, element *item)
    if (prev == NULL) return;
    Node *tmp = (Node*)malloc(sizeof(Node));
    tmp -> data = item;
    tmp -> next = prev->next;
    prev->next = tmp;
    //return head;
}

//순회하기
//index번째 노드의 주소 반환하기
Node *get_node(Node *head, int index) {
    if (index < 0) return NULL;
    Node *p = head;
    for (int i = 0; i <index && p != NULL; i++) {
        p = p->next;
    }
    return p;
}


//index번째 위치에 새로운 노드 만들어서 삽입하기
Node *add(Node *head, int index, element item) {
    if (index < 0) return head;

    if (index == 0) {
        add_first(head, item);
    }

    Node *prev = get_node(head, index-1);
    if (prev != NULL) {
        add_after(prev, item);
    }
    return head;
}


//연결리스트에 데이터들이 오름차순으로 정렬되어있을 때, 새로운 데이터 삽입
Node *add_to_ordered_list(Node *head, element item) {
    Node *p = head;
    Node *q = NULL;

    while (p != NULL && p->data != item) {
        q = p;
        p = p->next;
    }

    if (q == NULL) {
        return add_first(head, item);
    }
    else {
        add_after(q, item);
        return head;
    }
}


//첫번째 노드 삭제
//head는 전역변수로 가정. 연결리스트의 첫 번째 노드 삭제 후 그 노드의 주소 반환
Node * remove_first(Node *head) {
    if (head == NULL) return NULL;
    Node *tmp = head;
    head = head -> next;
    return tmp;
}


//어떤 노드의 다음 노드 삭제
//삭제할 노드의 바로 앞 주소가 필요함
void remove_after(Node *prev) {
    if (prev == NULL || prev->next == NULL) return;
    Node *tmp = prev->next;
    prev->next = tmp->next;
    free(tmp); // 메모리 해제
}


//index번째 노드를 삭제하고, 그 노드에 저장된 데이터 반환하기
Node *remove_by_index(Node *head, int index) {
    if (index < 0) {
        return head;
    }

    if (index == 0) {
        return remove_first(head);
    }

     Node *prev = get_node(head, index-1);
    if (prev != NULL && prev->next != NULL) {
        remove_after(prev);
    }
    return head;
}


//입력된 스트링을 저장한 노드를 찾아 삭제하고, 삭제된 노드에 저장된 데이터 반환
//삭제할 노드를 찾았는데, 삭제를 위해선 그 전 노드의 주소가 필요함.
Node *remove_by_value(Node *head, element item) {
    Node *p = head;
    Node *q = NULL; //q는 p의 한 칸 앞(prev)을 의미함
    while (p != NULL && p->data != item) {
        q = p;
        p = p->next;
    }
    if (p == NULL) {
        return head;
    }
    if (q == NULL) {
        return remove_first(head);
    }
    else {
        remove_after(q);
        return head;
    }
}



//순회하기
Node *find(Node *head, element word) {
    Node *p = head;
    while (p != NULL) {
        if ((p->data == word) == 0) return p;
        p = p->next;
    }
    return NULL;
}




// 리스트 병합
Node* merge(Node *list1, Node *list2) {
    Node dummy;
    Node *tail = &dummy;
    dummy.next = NULL;

    while (list1 != NULL && list2 != NULL) {
        if (list1->data <= list2->data) {
            tail->next = list1;
            list1 = list1->next;
        } else {
            tail->next = list2;
            list2 = list2->next;
        }
        tail = tail->next;
    }
    tail->next = (list1 != NULL) ? list1 : list2;
    return dummy.next;
}



// 리스트 연결
Node* concat(Node *list1, Node *list2) {
    Node *p;
    if (list1 == NULL) {
        return list2;
    }
    else if(list2 == NULL) {
        return list1;
    }
    else {
        p = list1;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = list2;
        return list1;
    }

}



// 리스트의 중간 노드 찾기
Node* get_mid(Node *head) {
    Node *slow = head;
    Node *fast = head->next;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}


// 리스트 정렬
Node* sort(Node *head) {
    if (head == NULL || head->next == NULL) return head;
    
    Node *mid = get_mid(head);
    Node *half = mid->next;
    mid->next = NULL;
    
    return merge(sort(head), sort(half));
}



// 리스트 역순으로 만들기
Node* reverse(Node *head) {
    Node *prev = NULL;
    Node *cur = head;
    Node *next = NULL;
    while (cur != NULL) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    return prev;
}



int main() {
    Node *head = NULL;
    // 초기 리스트 설정
    head = add_first(head, 3); // Thursday
    head = add_first(head, 2); // Tuesday
    head = add_first(head, 1); // Monday

    printf("Initial List:\n");
    print_list(head);

    // 역순으로 변경
    head = reverse(head);
    printf("Reversed List:\n");
    print_list(head);

    // 정렬된 리스트 추가
    head = add_to_ordered_list(head, 4); // Wednesday
    printf("Ordered Insertion:\n");
    print_list(head);

    // 두 리스트 병합
    Node *list1 = NULL;
    Node *list2 = NULL;

    list1 = add_first(list1, 4); // D
    list1 = add_first(list1, 2); // B
    list1 = add_first(list1, 1); // A

    list2 = add_first(list2, 5); // E
    list2 = add_first(list2, 3); // C

    Node *merged_list = merge(sort(list1), sort(list2));
    printf("Merged and Sorted List:\n");
    print_list(merged_list);

    // 두 리스트 연결
    head = concat(head, merged_list);
    printf("Concatenated List:\n");
    print_list(head);

    // 리스트 정렬
    head = sort(head);
    printf("Sorted List:\n");
    print_list(head);

    return 0;
}