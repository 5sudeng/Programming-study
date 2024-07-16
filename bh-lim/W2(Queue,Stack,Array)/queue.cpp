/*
    Method Explanations

	1.	enqueue: Adds an element to the end of the queue.
	2.	dequeue: Removes and returns the element at the front of the queue.
	3.	peek: Returns the element at the front of the queue without removing it.
	4.	is_empty: Checks if the queue is empty.
    5.	size: Returns the number of elements in the queue.
	6.	clear: Removes all elements from the queue.
*/

#include <iostream>
#include <vector>

class Queue {
private:
    std::vector<int> data;
    int front;
    int rear;
    int size;
    int capacity;

public:
    Queue(int initialCapacity) {
        data.resize(initialCapacity);
        front = 0;
        rear = -1;
        size = 0;
        capacity = initialCapacity;
    }

    bool isEmpty() const {
        return size == 0;
    }

    int getSize() const {
        return size;
    }

    void resize() {
        capacity *= 2;
        std::vector<int> newData(capacity);
        for (int i = 0; i < size; ++i) {
            newData[i] = data[(front + i) % capacity];
        }
        data = newData;
        front = 0;
        rear = size - 1;
    }

    void enqueue(int element) {
        if (size == capacity) {
            resize();
        }
        rear = (rear + 1) % capacity;
        data[rear] = element;
        size++;
    }

    int dequeue() {
        if (isEmpty()) {
            std::cout << "Queue is empty" << std::endl;
            return -1;
        }
        int element = data[front];
        front = (front + 1) % capacity;
        size--;
        return element;
    }

    int peek() const {
        if (isEmpty()) {
            std::cout << "Queue is empty" << std::endl;
            return -1;
        }
        return data[front];
    }

    void clear() {
        front = 0;
        rear = -1;
        size = 0;
    }

    void print() const {
        for (int i = 0; i < size; ++i) {
            std::cout << data[(front + i) % capacity] << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    Queue q(2);
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);

    std::cout << "Front element: " << q.peek() << std::endl;

    std::cout << "Dequeued: " << q.dequeue() << std::endl;
    std::cout << "Front element after dequeue: " << q.peek() << std::endl;

    std::cout << "Queue size: " << q.getSize() << std::endl;
    q.clear();
    std::cout << "Queue size after clearing: " << q.getSize() << std::endl;

    return 0;
}