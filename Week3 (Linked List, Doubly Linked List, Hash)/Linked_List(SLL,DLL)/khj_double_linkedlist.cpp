#include <iostream>

using namespace std;

typedef int element;

struct Node {
    element data;
    Node *next;
    Node *prev;
};

// Function prototypes
void print_list(Node *head);
Node* add_first(Node *head, element item);
void add_after(Node *prev, element item);
Node* get_node(Node *head, int index);
Node* add(Node *head, int index, element item);
Node* add_to_ordered_list(Node *head, element item);
Node* find_node(Node *head, element item);
Node* remove_first(Node *head);
void remove_after(Node *prev);
Node* remove_by_index(Node *head, int index);
Node* remove_by_value(Node *head, element item);
Node* find(Node *head, element item);
Node* merge(Node *list1, Node *list2);
Node* concat(Node *list1, Node *list2);
Node* get_mid(Node *head);
Node* sort(Node *head);
Node* reverse(Node *head);

// Print the linked list
void print_list(Node *head) {
    Node *cur = head;
    while (cur != NULL) {
        cout << cur->data << " ";
        cur = cur->next;
    }
    cout << endl;
}

// Insert node at the beginning of the list
Node* add_first(Node *head, element item) {
    Node *temp = new Node();
    temp->data = item;
    temp->next = head;
    temp->prev = NULL;
    if (head != NULL) {
        head->prev = temp;
    }
    return temp; // New head node's address
}

// Insert node after a specific node
void add_after(Node *prev, element item) {
    if (prev == NULL) return;
    Node *temp = new Node();
    temp->data = item;
    temp->next = prev->next;
    temp->prev = prev;
    if (prev->next != NULL) {
        prev->next->prev = temp;
    }
    prev->next = temp;
}

// Get the node at a specific index
Node* get_node(Node *head, int index) {
    if (index < 0) return NULL;
    Node *p = head;
    for (int i = 0; i < index && p != NULL; i++) {
        p = p->next;
    }
    return p;
}

// Insert node at a specific index
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

// Insert into ordered list
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

// Find node by value
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

// Remove first node
Node* remove_first(Node *head) {
    if (head == NULL) return NULL;
    Node *temp = head;
    head = head->next;
    if (head != NULL) {
        head->prev = NULL;
    }
    delete temp;
    return head;
}

// Remove node after a specific node
void remove_after(Node *prev) {
    if (prev == NULL || prev->next == NULL) return;
    Node *temp = prev->next;
    prev->next = temp->next;
    if (temp->next != NULL) {
        temp->next->prev = prev;
    }
    delete temp;
}

// Remove node by index
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

// Remove node by value
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

// Find node by value
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

// Function to sort the list (ascending order)
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
    Node *list1 = NULL;
    Node *list2 = NULL;

    list1 = add_first(list1, 4); // D
    list1 = add_first(list1, 2); // B
    list1 = add_first(list1, 1); // A

    list2 = add_first(list2, 5); // E
    list2 = add_first(list2, 3); // C

    Node *merged_list = merge(sort(list1), sort(list2));
    cout << "Merged and Sorted List:" << endl;
    print_list(merged_list);

    // Concatenate two lists
    head = concat(head, merged_list);
    cout << "Concatenated List:" << endl;
    print_list(head);

    // Sort the list
    head = sort(head);
    cout << "Sorted List:" << endl;
    print_list(head);

    return 0;
}
