#include <stdio.h>
#include <stdlib.h>

typedef int element;

struct node {
    element data;
    struct node *next;
    struct node *prev;
};

typedef struct node Node;

// Node *head;
// Node *tail;
int size = 0;


//리스트 찍어보기
void print_list(Node *head) {
    Node *cur = head;
    while (cur != NULL) {
        printf("%d ", cur->data);
        //만약 char라면 %s
        cur = cur->next;
    }
    printf("\n");
}


//노드 삽입
//p가 가리키는 노드 다음에 새로운 노드를 삽입하는 경우
// Node* add_after(Node *pre, element item) {
//     Node *new_node = (Node*)malloc(sizeof(Node));
//     new_node->data = item;
//     new_node->prev = NULL;
//     new_node->next = NULL;

//     if (pre == NULL && head == NULL) {  //노드가 0개인 empty list라면
//         head = new_node;    //첫번째 노드이면서 마지막 노드
//         tail = new_node;
//     }

//     else if (pre == NULL) {    //연결리스트의 맨 앞에 삽입
//         new_node->next = head;
//         head->prev = new_node;
//         head = new_node;
//     }

//     else if (pre == tail) {   //맨 마지막에 삽입
//         new_node -> prev = tail;
//         tail->next = new_node;
//         tail = new_node;
//     }

//     else {
//         new_node->prev = pre;
//         new_node->next = pre->next;
//         pre->next->prev = new_node;
//         pre->next = new_node;
//     }
//     size++;
// }
//add_after(tail, "new_tail");

//연결리스트의 맨 앞에 삽입
Node* add_first(Node *head, element item) {
    Node *temp = (Node*)malloc(sizeof(Node));
    temp->data = item;
    temp->next = head;
    temp->prev = NULL;
    if (head != NULL) {
        head->prev = temp;
    }
    return temp; // New head node's address
}


//특정 노드 앞에 삽입
void add_after(Node *prev, element item) {
    if (prev == NULL) return;
    Node *temp = (Node*)malloc(sizeof(Node));
    temp->data = item;
    temp->next = prev->next;
    temp->prev = prev;
    if (prev->next != NULL) {
        prev->next->prev = temp;
    }
    prev->next = temp;
}



// index에 해당하는 노드 찾기
Node* get_node(Node *head, int index) {
    if (index < 0) return NULL;
    Node *p = head;
    for (int i = 0; i < index && p != NULL; i++) {
        p = p->next;
    }
    return p;
}

// index에 해당하는 노드 삽입하기
Node* add(Node *head, int index, element item) {
    if (index < 0) return head;

    if (index == 0) {
        return add_first(head, item);
    }

    Node *prev = get_node(head, index-1);
    if (prev != NULL) {
        add_after(prev, item);
    }
    return head;
}

// ordered list에 add하기
Node* add_to_ordered_list(Node *head, element item) {
    Node *p = head;
    Node *q = NULL;

    while (p != NULL && p->data < item) {
        q = p;
        p = p->next;
    }

    if (q == NULL) {
        return add_first(head, item);
    } else {
        add_after(q, item);
        return head;
    }
}


//노드 찾기
Node *find_node(Node * head, element item) {
    Node *cur = head;
    while (cur != NULL) {
        if (cur->data == item){
            return cur;
        }
        cur = cur -> next;
    }
    return NULL;
}

//노드 삭제
// //p가 가리키는 노드 삭제하기
// void delete_node(char *item) {
//     Node *cur = find_node(item);
//     //만약 item말고 그냥 Node가 주어졌으면 윗줄 필요없이 그냥 cur로 넣기

//     if (cur == NULL) return;

//     if (cur == head) {
//         head = cur->next;
//         if (head != NULL) {
//             head->prev = NULL;
//         }
//         if (cur == tail) {  //리스트가 노드 하나로 이루어진 경우
//             tail = NULL;
//         }
//     }
    
//     else if (cur == tail) {
//         tail = cur -> prev;
//         if (tail != NULL) {
//             tail ->next = NULL;
//         }
//     }
//     else {
//         cur->prev->next = cur->next;
//         cur->next->prev = cur->prev;
//     }
//     free(cur);
//     size--;
// }
//delete_node("apple");


// 첫번째 노드 지우기
Node* remove_first(Node *head) {
    if (head == NULL) return NULL;
    Node *temp = head;
    head = head->next;
    if (head != NULL) {
        head->prev = NULL;
    }
    free(temp);
    return head;
}

// 해당 노드 다음 노드 지우기
void remove_after(Node *prev) {
    if (prev == NULL || prev->next == NULL) return;
    Node *temp = prev->next;
    prev->next = temp->next;
    if (temp->next != NULL) {
        temp->next->prev = prev;
    }
    free(temp);
}

// index로 노드 지우기
Node* remove_by_index(Node *head, int index) {
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

// 주어진 data에 해당하는 노드 지우기
Node* remove_by_value(Node *head, element item) {
    Node *p = head;
    Node *q = NULL; // q is the previous node

    while (p != NULL && p->data != item) {
        q = p;
        p = p->next;
    }

    if (p == NULL) {
        return head;
    }
    if (q == NULL) {
        return remove_first(head);
    } else {
        remove_after(q);
        return head;
    }
}

// data로 노드 찾기
Node* find(Node *head, element word) {
    Node *p = head;
    while (p != NULL) {
        if (p->data == word) return p;
        p = p->next;
    }
    return NULL;
}

// Function to merge two sorted lists
Node* merge(Node *list1, Node *list2) {
    Node dummy;
    Node *tail = &dummy;
    dummy.next = NULL;

    while (list1 != NULL && list2 != NULL) {
        if (list1->data <= list2->data) {
            tail->next = list1;
            list1->prev = tail;
            list1 = list1->next;
        } else {
            tail->next = list2;
            list2->prev = tail;
            list2 = list2->next;
        }
        tail = tail->next;
    }
    tail->next = (list1 != NULL) ? list1 : list2;
    if (tail->next != NULL) {
        tail->next->prev = tail;
    }
    return dummy.next;
}

// Function to concatenate two lists
Node* concat(Node *list1, Node *list2) {
    if (list1 == NULL) {
        return list2;
    }
    if (list2 == NULL) {
        return list1;
    }
    Node *p = list1;
    while (p->next != NULL) {
        p = p->next;
    }
    p->next = list2;
    list2->prev = p;
    return list1;
}

// Function to get the middle node
Node* get_mid(Node *head) {
    Node *slow = head;
    Node *fast = head->next;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

// Function to sort the list (오름차순 정렬)
Node* sort(Node *head) {
    if (head == NULL || head->next == NULL) return head;

    Node *mid = get_mid(head);
    Node *half = mid->next;
    mid->next = NULL;
    if (half != NULL) {
        half->prev = NULL;
    }

    return merge(sort(head), sort(half));
}

// Function to reverse the list
Node* reverse(Node *head) {
    Node *prev = NULL;
    Node *cur = head;
    Node *next = NULL;
    while (cur != NULL) {
        next = cur->next;
        cur->next = prev;
        cur->prev = next;
        prev = cur;
        cur = next;
    }
    return prev;
}

int main() {
    Node *head = NULL;

    // Initial list setup
    head = add_first(head, 3); // Thursday
    head = add_first(head, 2); // Tuesday
    head = add_first(head, 1); // Monday

    printf("Initial List:\n");
    print_list(head);

    // Reverse the list
    head = reverse(head);
    printf("Reversed List:\n");
    print_list(head);

    // Add to ordered list
    head = add_to_ordered_list(head, 4); // Wednesday
    printf("Ordered Insertion:\n");
    print_list(head);

    // Merge two lists
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

    // Concatenate two lists
    head = concat(head, merged_list);
    printf("Concatenated List:\n");
    print_list(head);

    // Sort the list
    head = sort(head);
    printf("Sorted List:\n");
    print_list(head);

    return 0;
}
