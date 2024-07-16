/*
    Method Explanations

	1.	insert: Adds an element at the end of the array.
	2.	delete: Removes an element at a specific index.
	3.	get: Retrieves an element at a specific index.
	4.	size: Returns the current number of elements in the array.
	5.	is_empty: Checks if the array is empty.
	6.	clear: Removes all elements from the array.
	7.	resize: Resizes the array to accommodate more elements.
	8.	find: Searches for an element and returns its index (or -1 if not found).
	9.	contains: Checks if an element exists in the array.
*/

#include <iostream>
#include <vector>

class Array {
private:
    std::vector<int> data;
    int size;
    int capacity;

public:
    Array(int initialCapacity) {
        data.resize(initialCapacity);
        size = 0;
        capacity = initialCapacity;
    }

    void insert(int element) {
        if (size == capacity) {
            resize();
        }
        data[size++] = element;
    }

    void remove(int index) {
        if (index < 0 || index >= size) {
            std::cout << "Index out of bounds" << std::endl;
            return;
        }
        for (int i = index; i < size - 1; ++i) {
            data[i] = data[i + 1];
        }
        size--;
    }

    int get(int index) const {
        if (index < 0 || index >= size) {
            std::cout << "Index out of bounds" << std::endl;
            return -1;
        }
        return data[index];
    }

    int getSize() const {
        return size;
    }

    bool isEmpty() const {
        return size == 0;
    }

    void clear() {
        size = 0;
    }

    int find(int element) const {
        for (int i = 0; i < size; ++i) {
            if (data[i] == element) {
                return i;
            }
        }
        return -1;
    }

    bool contains(int element) const {
        return find(element) != -1;
    }

    void print() const {
        for (int i = 0; i < size; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }

private:
    void resize() {
        capacity *= 2;
        std::vector<int> newData(capacity);
        for (int i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        data = newData;
    }
};

int main() {
    Array a(2);
    a.insert(10);
    a.insert(20);
    a.insert(30);

    std::cout << "Array elements: ";
    a.print();

    a.remove(1);
    std::cout << "After deletion: ";
    a.print();

    int value = a.get(1);
    std::cout << "Element at index 1: " << value << std::endl;

    std::cout << "Array size: " << a.getSize() << std::endl;
    std::cout << "Array is empty: " << (a.isEmpty() ? "Yes" : "No") << std::endl;

    a.clear();
    std::cout << "Array size after clearing: " << a.getSize() << std::endl;

    a.insert(40);
    std::cout << "Array contains 40: " << (a.contains(40) ? "Yes" : "No") << std::endl;

    return 0;
}