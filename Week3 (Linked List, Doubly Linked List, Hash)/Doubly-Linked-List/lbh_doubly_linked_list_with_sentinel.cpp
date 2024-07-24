#include <iostream>

class Node {
public:
    int data;
    Node* next;
    Node* prev;
    Node(int value = 0) : data(value), next(nullptr), prev(nullptr) {}
};

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;
    int size;

public:
    DoublyLinkedList() : size(0) {
        head = new Node();  // Sentinel node
        tail = new Node();  // Sentinel node
        head->next = tail;
        tail->prev = head;
    }

    ~DoublyLinkedList() {
        freeList();
    }

    // Function to insert a node at the beginning of the list
    void insertFirst(int value) {
        Node* newNode = new Node(value);
        newNode->next = head->next;
        newNode->prev = head;
        head->next->prev = newNode;
        head->next = newNode;
        size++;
    }

    // Function to insert a node at the end of the list
    void insertLast(int value) {
        Node* newNode = new Node(value);
        newNode->next = tail;
        newNode->prev = tail->prev;
        tail->prev->next = newNode;
        tail->prev = newNode;
        size++;
    }

    // Function to insert a node before a node with a certain value
    void insertValue(int target, int value) {
        Node* newNode = new Node(value);
        Node* temp = head->next;
        while (temp != tail && temp->data != target) {
            temp = temp->next;
        }
        if (temp == tail) {
            std::cout << "Target value not found\n";
            delete newNode;
            return;
        }
        newNode->next = temp;
        newNode->prev = temp->prev;
        temp->prev->next = newNode;
        temp->prev = newNode;
        size++;
    }

    // Function to delete a node by value
    void deleteValue(int value) {
        Node* temp = head->next;
        while (temp != tail && temp->data != value) {
            temp = temp->next;
        }
        if (temp == tail) {
            return;
        }
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        delete temp;
        size--;
    }

    // Function to delete the first node
    void deleteFirst() {
        if (head->next == tail) {
            return;
        }
        Node* toDelete = head->next;
        head->next = head->next->next;
        head->next->prev = head;
        delete toDelete;
        size--;
    }

    // Function to delete the last node
    void deleteLast() {
        if (tail->prev == head) {
            return;
        }
        Node* toDelete = tail->prev;
        tail->prev = tail->prev->prev;
        tail->prev->next = tail;
        delete toDelete;
        size--;
    }

    // Function to get the first node's value
    int getFirst() const {
        if (head->next == tail) {
            std::cout << "List is empty\n";
            return -1;
        }
        return head->next->data;
    }

    // Function to get the last node's value
    int getLast() const {
        if (tail->prev == head) {
            std::cout << "List is empty\n";
            return -1;
        }
        return tail->prev->data;
    }

    // Function to get the size of the list
    int getSize() const {
        return size;
    }

    // Function to print the elements of the list
    void printList() const {
        Node* temp = head->next;
        while (temp != tail) {
            std::cout << temp->data << " -> ";
            temp = temp->next;
        }
        std::cout << "NULL" << std::endl;
    }

    // Function to free all nodes in the list
    void freeList() {
        Node* temp = head;
        while (temp != nullptr) {
            Node* next = temp->next;
            delete temp;
            temp = next;
        }
        head = nullptr;
        tail = nullptr;
        size = 0;
    }
};

int main() {
    DoublyLinkedList list;
    list.insertFirst(10);
    list.insertFirst(20);
    list.insertLast(30);
    list.insertLast(40);

    std::cout << "List: ";
    list.printList();
    std::cout << "Size: " << list.getSize() << std::endl;

    std::cout << "First element: " << list.getFirst() << std::endl;
    std::cout << "Last element: " << list.getLast() << std::endl;

    list.insertValue(30, 25);
    std::cout << "After inserting 25 before 30: ";
    list.printList();

    list.deleteFirst();
    std::cout << "After deleting first element: ";
    list.printList();

    list.deleteLast();
    std::cout << "After deleting last element: ";
    list.printList();

    list.deleteValue(30);
    std::cout << "After deleting value 30: ";
    list.printList();

    std::cout << "Final size: " << list.getSize() << std::endl;

    return 0;
}