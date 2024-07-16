/*
    Method Explanations

    1.	push: Adds an element to the top of the stack. If the stack is full, it calls the resize method to double the capacity.
	2.	pop: Removes and returns the top element of the stack. If the stack is empty, it prints an error message and returns -1.
	3.	peek: Returns the top element of the stack without removing it. If the stack is empty, it prints an error message and returns -1.
	4.	clear: Clears the stack by resetting top to -1.
	5.	resize: Doubles the capacity of the stack, copies the elements to the new array, and updates the capacity.
	6.	get_size: Returns the current size of the stack.
*/

#include <iostream>

class Stack {
private:
    int* data;
    int top;
    int capacity;

    // Private resize method to handle capacity doubling
    void resize() {
        capacity *= 2;
        int* newData = new int[capacity];
        for (int i = 0; i <= top; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }

public:
    Stack(int initialCapacity = 10) : top(-1), capacity(initialCapacity) {
        data = new int[initialCapacity];
    }

    ~Stack() {
        delete[] data;
    }

    // Check if the stack is empty
    bool isEmpty() const {
        return top == -1;
    }

    // Push an element onto the stack
    void push(int value) {
        if (top + 1 == capacity) {
            resize();
        }
        data[++top] = value;
    }

    // Pop an element from the stack
    int pop() {
        if (isEmpty()) {
            std::cerr << "Stack is empty\n";
            return -1;
        }
        return data[top--];
    }

    // Peek at the top element of the stack
    int peek() const {
        if (isEmpty()) {
            std::cerr << "Stack is empty\n";
            return -1;
        }
        return data[top];
    }

    // Clear the stack
    void clear() {
        top = -1;
    }

    // Get the size of the stack
    int getSize() const {
        return top + 1;
    }
};

int main() {
    Stack stack;
    stack.push(10);
    stack.push(20);
    stack.push(30);

    std::cout << "Top element: " << stack.peek() << std::endl;

    std::cout << "Popped: " << stack.pop() << std::endl;
    std::cout << "Top element after pop: " << stack.peek() << std::endl;

    stack.push(40);
    std::cout << "Top element after pushing 40: " << stack.peek() << std::endl;

    std::cout << "Stack size: " << stack.getSize() << std::endl;
    stack.clear();
    std::cout << "Stack size after clearing: " << stack.getSize() << std::endl;

    return 0;
}