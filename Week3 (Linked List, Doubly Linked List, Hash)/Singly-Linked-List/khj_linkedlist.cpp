#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    
    Node(int d=0) : data(d), next(nullptr) {}
};

Node* add_first(Node* head, int data) {
    Node* newNode = new Node(data);
    newNode->next = head;
    return newNode;
}

void print_list(Node* head) {
    Node* p = head;
    while (p != nullptr) {
        cout << p->data << " ";
        p = p->next;
    }
    cout << "\n" << endl;
}

Node* reverse(Node* head) {
    Node* p = head;
    Node* q = nullptr;
    while (p != nullptr) {
        Node* r = q;
        q = p;
        p = p->next;
        q->next = r;
    }
    return q;
}

Node* add_to_ordered_list(Node* head, int data) {
    Node* newNode = new Node(data);
    if (head == nullptr || data <= head->data) {
        newNode->next = head;
        return newNode;
    }
    Node* p = head;
    while (p->next != nullptr && p->next->data < data) {
        p = p->next;
    }
    newNode->next = p->next;
    p->next = newNode;
    return head;
}

Node* merge(Node* list1, Node* list2) {
    if (list1 == nullptr) return list2;
    if (list2 == nullptr) return list1;
    
    Node dummy;
    Node* curr = &dummy;
    
    while (list1 != nullptr && list2 != nullptr) {
        if (list1->data <= list2->data) {
            curr->next = list1;
            list1 = list1->next;
        } else {
            curr->next = list2;
            list2 = list2->next;
        }
        curr = curr->next;
    }
    
    if (list1 != nullptr) {
        curr->next = list1;
    } else {
        curr->next = list2;
    }
    
    return dummy.next;
}

Node* sort(Node* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    
    Node* slow = head;
    Node* fast = head->next;
    
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    Node* left = head;
    Node* right = slow->next;
    slow->next = nullptr;
    
    left = sort(left);
    right = sort(right);
    
    return merge(left, right);
}

Node* concat(Node* head1, Node* head2) {
    if (head1 == nullptr) return head2;
    Node* p = head1;
    while (p->next != nullptr) {
        p = p->next;
    }
    p->next = head2;
    return head1;
}

int main() {
    Node* head = nullptr;

    // Initial list setup
    head = add_first(head, 3); // Thursday
    head = add_first(head, 2); // Tuesday
    head = add_first(head, 1); // Monday

    cout << "Initial List:" << endl;
    print_list(head);

    // Reverse the list
    head = reverse(head);
    cout << "Reversed List:" << endl;
    print_list(head);

    // Add to ordered list
    head = add_to_ordered_list(head, 4); // Wednesday
    cout << "Ordered Insertion:" << endl;
    print_list(head);

    // Merge two lists
    Node* list1 = nullptr;
    Node* list2 = nullptr;

    list1 = add_first(list1, 4); // D
    list1 = add_first(list1, 2); // B
    list1 = add_first(list1, 1); // A

    list2 = add_first(list2, 5); // E
    list2 = add_first(list2, 3); // C

    Node* merged_list = merge(sort(list1), sort(list2));
    cout << "Merged and Sorted List:" << endl;
    print_list(merged_list);

    // Concatenate two lists
    head = concat(head, merged_list);
    cout << "Concatenated List:" << endl;
    print_list(head);

    // Sort the final list
    head = sort(head);
    cout << "Sorted List:" << endl;
    print_list(head);

    return 0;
}
