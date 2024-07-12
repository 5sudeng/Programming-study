# C++ 코드를 지피티에게 번역해달라 함

import math

# MinHeap class using array implementation
class MinHeap:
    def __init__(self, capacity):
        self.capacity = capacity
        self.heap_size = 0
        self.harr = [0] * capacity

    def parent(self, i):
        return (i - 1) // 2

    def left(self, i):
        return 2 * i + 1

    def right(self, i):
        return 2 * i + 2

    def insertKey(self, k):
        if self.heap_size == self.capacity:
            print("Overflow: Could not insert key")
            return

        # Insert the new key at the end
        self.heap_size += 1
        i = self.heap_size - 1
        self.harr[i] = k

        # Fix the min heap property
        while i != 0 and self.harr[self.parent(i)] > self.harr[i]:
            self.harr[i], self.harr[self.parent(i)] = self.harr[self.parent(i)], self.harr[i]
            i = self.parent(i)

    def decreaseKey(self, i, new_val):
        self.harr[i] = new_val
        while i != 0 and self.harr[self.parent(i)] > self.harr[i]:
            self.harr[i], self.harr[self.parent(i)] = self.harr[self.parent(i)], self.harr[i]
            i = self.parent(i)

    def extractMin(self):
        if self.heap_size <= 0:
            return math.inf

        if self.heap_size == 1:
            self.heap_size -= 1
            return self.harr[0]

        # Store the minimum value and remove it from heap
        root = self.harr[0]
        self.harr[0] = self.harr[self.heap_size - 1]
        self.heap_size -= 1
        self.minHeapify(0)

        return root

    def deleteKey(self, i):
        self.decreaseKey(i, -math.inf)
        self.extractMin()

    def minHeapify(self, i):
        l = self.left(i)
        r = self.right(i)
        smallest = i

        if l < self.heap_size and self.harr[l] < self.harr[i]:
            smallest = l

        if r < self.heap_size and self.harr[r] < self.harr[smallest]:
            smallest = r

        if smallest != i:
            self.harr[i], self.harr[smallest] = self.harr[smallest], self.harr[i]
            self.minHeapify(smallest)

    def getMin(self):
        return self.harr[0]
