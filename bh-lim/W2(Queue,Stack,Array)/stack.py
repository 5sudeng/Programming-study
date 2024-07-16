"""
    Method Explanations

    1.	push: Adds an element to the top of the stack. If the stack is full, it calls the resize method to double the capacity.
    2.	pop: Removes and returns the top element of the stack. If the stack is empty, it prints an error message and returns -1.
    3.	peek: Returns the top element of the stack without removing it. If the stack is empty, it prints an error message and returns -1.
    4.	clear: Clears the stack by resetting top to -1.
    5.	resize: Doubles the capacity of the stack, copies the elements to the new array, and updates the capacity.
    6.	get_size: Returns the current size of the stack.
"""

class Stack:
    def __init__(self, initial_capacity=10):
        self.data = [None] * initial_capacity
        self.top = -1
        self.capacity = initial_capacity

    def is_empty(self):
        return self.top == -1

    def push(self, value):
        if self.top + 1 == self.capacity:
            self._resize()
        self.top += 1
        self.data[self.top] = value

    def _resize(self):
        self.capacity *= 2
        new_data = [None] * self.capacity
        for i in range(self.top + 1):
            new_data[i] = self.data[i]
        self.data = new_data

    def pop(self):
        if self.is_empty():
            print("Stack is empty")
            return -1
        value = self.data[self.top]
        self.top -= 1
        return value

    def peek(self):
        if self.is_empty():
            print("Stack is empty")
            return -1
        return self.data[self.top]

    def clear(self):
        self.top = -1

    def get_size(self):
        return self.top + 1

# Demonstration
stack = Stack()
stack.push(10)
stack.push(20)
stack.push(30)

print("Top element:", stack.peek())

print("Popped:", stack.pop())
print("Top element after pop:", stack.peek())

stack.push(40)
print("Top element after pushing 40:", stack.peek())

print("Stack size:", stack.get_size())
stack.clear()
print("Stack size after clearing:", stack.get_size())