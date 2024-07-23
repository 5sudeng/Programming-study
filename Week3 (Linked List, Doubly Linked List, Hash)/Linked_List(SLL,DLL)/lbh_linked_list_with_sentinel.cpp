#include <iostream>

class Node {
public:
    int data;
    Node* next;
    Node(int value = 0) : data(value), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;
    int size;

public:
    LinkedList() : size(0) {
        head = new Node();  // Sentinel node
    }

    ~LinkedList() {
        freeList();
    }

    // Function to insert a node at the beginning of the list
    void insertFirst(int value) {
        Node* newNode = new Node(value);
        newNode->next = head->next;
        head->next = newNode;
        size++;
    }

    // Function to insert a node at the end of the list
    void insertLast(int value) {
        Node* newNode = new Node(value);
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
        size++;
    }

    // Function to insert a node before a node with a certain value
    void insertValue(int target, int value) {
        Node* newNode = new Node(value);
        Node* temp = head;
        while (temp->next != nullptr && temp->next->data != target) {
            temp = temp->next;
        }
        if (temp->next == nullptr) {
            std::cout << "Target value not found\n";
            delete newNode;
            return;
        }
        newNode->next = temp->next;
        temp->next = newNode;
        size++;
    }

    // Function to delete a node by value
    void deleteValue(int value) {
        Node* temp = head;
        while (temp->next != nullptr && temp->next->data != value) {
            temp = temp->next;
        }
        if (temp->next == nullptr) {
            return;
        }
        Node* toDelete = temp->next;
        temp->next = temp->next->next;
        delete toDelete;
        size--;
    }

    // Function to delete the first node
    void deleteFirst() {
        if (head->next == nullptr) {
            return;
        }
        Node* toDelete = head->next;
        head->next = head->next->next;
        delete toDelete;
        size--;
    }

    // Function to delete the last node
    void deleteLast() {
        if (head->next == nullptr) {
            return;
        }
        Node* temp = head;
        while (temp->next != nullptr && temp->next->next != nullptr) {
            temp = temp->next;
        }
        if (temp->next != nullptr) {
            delete temp->next;
            temp->next = nullptr;
            size--;
        }
    }

    // Function to get the first node's value
    int getFirst() const {
        if (head->next == nullptr) {
            std::cout << "List is empty\n";
            return -1;
        }
        return head->next->data;
    }

    // Function to get the last node's value
    int getLast() const {
        if (head->next == nullptr) {
            std::cout << "List is empty\n";
            return -1;
        }
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
            }
        return temp->data;
    }

    // Function to get the size of the list
    int getSize() const {
        return size;
    }

    // Function to print the elements of the list
    void printList() const {
        Node* temp = head->next;
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
        size = 0;
    }
};

int main() {
    LinkedList list;
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