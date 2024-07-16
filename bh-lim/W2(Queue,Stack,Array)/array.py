"""
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
"""

class Array:
    def __init__(self, initial_capacity=2):
        self.data = [None] * initial_capacity
        self.size = 0
        self.capacity = initial_capacity

    def _resize(self):
        self.capacity *= 2
        new_data = [None] * self.capacity
        for i in range(self.size):
            new_data[i] = self.data[i]
        self.data = new_data

    def insert(self, element):
        if self.size == self.capacity:
            self._resize()
        self.data[self.size] = element
        self.size += 1

    def delete(self, index):
        if index < 0 or index >= self.size:
            raise IndexError("Index out of bounds")
        for i in range(index, self.size - 1):
            self.data[i] = self.data[i + 1]
        self.data[self.size - 1] = None
        self.size -= 1

    def get(self, index):
        if index < 0 or index >= self.size:
            raise IndexError("Index out of bounds")
        return self.data[index]

    def get_size(self):
        return self.size

    def is_empty(self):
        return self.size == 0

    def clear(self):
        self.size = 0

    def find(self, element):
        for i in range(self.size):
            if self.data[i] == element:
                return i
        return -1

    def contains(self, element):
        return self.find(element) != -1

    def __repr__(self):
        return " ".join(str(self.data[i]) for i in range(self.size))

# Demonstration
a = Array()
a.insert(10)
a.insert(20)
a.insert(30)

print("Array elements:", a)

a.delete(1)
print("After deletion:", a)

value = a.get(1)
print("Element at index 1:", value)

print("Array size:", a.get_size())
print("Array is empty:", "Yes" if a.is_empty() else "No")

a.clear()
print("Array size after clearing:", a.get_size())

a.insert(40)
print("Array contains 40:", "Yes" if a.contains(40) else "No")