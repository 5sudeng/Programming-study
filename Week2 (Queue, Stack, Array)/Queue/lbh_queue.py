"""
    Method Explanations

    1.	enqueue: Adds an element to the end of the queue.
    2.	dequeue: Removes and returns the element at the front of the queue.
    3.	peek: Returns the element at the front of the queue without removing it.
    4.	is_empty: Checks if the queue is empty.
    5.	size: Returns the number of elements in the queue.
    6.	clear: Removes all elements from the queue.
"""

class Queue:
    def __init__(self, initial_capacity=2):
        self.data = [None] * initial_capacity
        self.front = 0
        self.rear = -1
        self.size = 0
        self.capacity = initial_capacity

    def is_empty(self):
        return self.size == 0

    def get_size(self):
        return self.size

    def _resize(self):
        self.capacity *= 2
        new_data = [None] * self.capacity
        for i in range(self.size):
            new_data[i] = self.data[(self.front + i) % self.size]
        self.data = new_data
        self.front = 0
        self.rear = self.size - 1

    def enqueue(self, element):
        if self.size == self.capacity:
            self._resize()
        self.rear = (self.rear + 1) % self.capacity
        self.data[self.rear] = element
        self.size += 1

    def dequeue(self):
        if self.is_empty():
            print("Queue is empty")
            return None
        element = self.data[self.front]
        self.front = (self.front + 1) % self.capacity
        self.size -= 1
        return element

    def peek(self):
        if self.is_empty():
            print("Queue is empty")
            return None
        return self.data[self.front]

    def clear(self):
        self.front = 0
        self.rear = -1
        self.size = 0

    def __repr__(self):
        if self.is_empty():
            return "Queue is empty"
        return " ".join(str(self.data[(self.front + i) % self.capacity]) for i in range(self.size))

# Demonstration
q = Queue()
q.enqueue(10)
q.enqueue(20)
q.enqueue(30)

print("Queue elements:", q)

print("Front element:", q.peek())

print("Dequeued:", q.dequeue())
print("Queue after dequeue:", q)

print("Queue size:", q.get_size())
q.clear()
print("Queue size after clearing:", q.get_size())
