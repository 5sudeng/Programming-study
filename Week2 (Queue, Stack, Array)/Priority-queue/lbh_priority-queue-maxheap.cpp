#include <iostream>
#include <vector>

class PriorityQueue {
private:
    std::vector<int> data;

    void heapifyUp(int index) {
        while (index > 0 && data[(index - 1) / 2] < data[index]) {
            std::swap(data[index], data[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
    }

    void heapifyDown(int index) {
        int size = data.size();
        while (2 * index + 1 < size) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int largest = left;
            if (right < size && data[right] > data[left]) {
                largest = right;
            }
            if (data[index] >= data[largest]) {
                break;
            }
            std::swap(data[index], data[largest]);
            index = largest;
        }
    }

public:
    // Check if the priority queue is empty
    bool isEmpty() const {
        return data.empty();
    }

    // Push an element onto the priority queue
    void push(int value) {
        data.push_back(value);
        heapifyUp(data.size() - 1);
    }

    // Pop the top element from the priority queue
    int pop() {
        if (isEmpty()) {
            std::cerr << "Priority Queue is empty\n";
            return -1;
        }
        int topValue = data[0];
        data[0] = data.back();
        data.pop_back();
        if (!isEmpty()) {
            heapifyDown(0);
        }
        return topValue;
    }

    // Get the top element of the priority queue
    int top() const {
        if (isEmpty()) {
            std::cerr << "Priority Queue is empty\n";
            return -1;
        }
        return data[0];
    }
};

int main() {
    PriorityQueue pq;

    pq.push(10);
    pq.push(20);
    pq.push(15);

    std::cout << "Top element: " << pq.top() << std::endl;

    std::cout << "Popped: " << pq.pop() << std::endl;
    std::cout << "Top element after pop: " << pq.top() << std::endl;

    return 0;
}