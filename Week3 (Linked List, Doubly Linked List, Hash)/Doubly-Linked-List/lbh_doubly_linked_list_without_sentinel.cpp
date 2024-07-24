#include <iostream>

class Node {
public:
    int data;
    Node* next;
    Node* prev;
    Node(int value) : data(value), next(nullptr), prev(nullptr) {}
};

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;
    int size;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~DoublyLinkedList() {
        freeList();
    }

    // Function to insert a node at the beginning of the list
    void insertFirst(int value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        newNode->prev = nullptr;
        if (head != nullptr) {
            head->prev = newNode;
        } else {
            tail = newNode; // If list was empty, new node is also the tail
        }
        head = newNode;
        size++;
    }

    // Function to insert a node at the end of the list
    void insertLast(int value) {
        Node* newNode = new Node(value);
        newNode->next = nullptr;
        newNode->prev = tail;
        if (tail != nullptr) {
            tail->next = newNode;
        } else {
            head = newNode; // If list was empty, new node is also the head
        }
        tail = newNode;
        size++;
    }

    // Function to insert a node before a node with a certain value
    void insertValue(int target, int value) {
        Node* newNode = new Node(value);
        Node* temp = head;
        while (temp != nullptr && temp->data != target) {
            temp = temp->next;
        }
        if (temp == nullptr) {
            std::cout << "Target value not found\n";
            delete newNode;
            return;
        }
        newNode->next = temp;
        newNode->prev = temp->prev;
        if (temp->prev != nullptr) {
            temp->prev->next = newNode;
        } else {
            head = newNode; // Inserting before the first node
        }
        temp->prev = newNode;
        size++;
    }

    // Function to delete a node by value
    void deleteValue(int value) {
        Node* temp = head;
        while (temp != nullptr && temp->data != value) {
            temp = temp->next;
        }
        if (temp == nullptr) {
            return; // Value not found
        }
        if (temp->prev != nullptr) {
            temp->prev->next = temp->next;
        } else {
            head = temp->next; // Node to be deleted is head
        }
        if (temp->next != nullptr) {
            temp->next->prev = temp->prev;
        } else {
            tail = temp->prev; // Node to be deleted is tail
        }
        delete temp;
        size--;
    }
    
    // Function to delete the first node
    void deleteFirst() {
        if (head == nullptr) {
            return;
        }
        Node* toDelete = head;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        } else {
            tail = nullptr; // List became empty
        }
        delete toDelete;
        size--;
    }

    // Function to delete the last node
    void deleteLast() {
        if (tail == nullptr) {
            return;
        }
        Node* toDelete = tail;
        tail = tail->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        } else {
            head = nullptr; // List became empty
        }
        delete toDelete;
        size--;
    }

    // Function to get the first node's value
    int getFirst() const {
        if (head == nullptr) {
            std::cout << "List is empty\n";
            return -1;
        }
        return head->data;
    }

    // Function to get the last node's value
    int getLast() const {
        if (tail == nullptr) {
            std::cout << "List is empty\n";
            return -1;
        }
        return tail->data;
    }

    // Function to get the size of the list
    int getSize() const {
        return size;
    }

    // Function to print the elements of the list
    void printList() const {
        Node* temp = head;
        while (temp != nullptr) {
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