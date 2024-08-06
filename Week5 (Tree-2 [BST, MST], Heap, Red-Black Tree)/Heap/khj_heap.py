import sys
import math

class Heap:
    def __init__(self, capacity: int):
        self.capacity = capacity
        self.heap_size = 0
        self.harr = [-sys.maxsize - 1 for _ in range(capacity)]

    def insertKey(self, k: int):
        if self.heap_size == self.capacity:
            print('Overflow: Could not insertKey.')
            return
        self.heap_size += 1
        i = self.heap_size - 1
        self.harr[i] = k

    def parent(self, i: int):
        return (i - 1) // 2

    def left(self, i: int):
        return 2 * i + 1

    def right(self, i: int):
        return 2 * i + 2

    def maxHeapify(self, i: int):
        l = self.left(i)
        r = self.right(i)
        largest = i

        if l < self.heap_size and self.harr[l] > self.harr[i]:
            largest = l
        if r < self.heap_size and self.harr[r] > self.harr[largest]:
            largest = r

        if largest != i:
            self.harr[i], self.harr[largest] = self.harr[largest], self.harr[i]
            self.maxHeapify(largest)

    def buildMaxHeap(self):
        for i in range((self.heap_size // 2) - 1, -1, -1):
            self.maxHeapify(i)

    def heapsort(self):
        self.buildMaxHeap()
        original_size = self.heap_size

        for i in range(self.heap_size - 1, 0, -1):
            self.harr[0], self.harr[i] = self.harr[i], self.harr[0]
            self.heap_size -= 1
            self.maxHeapify(0)

        self.heap_size = original_size

    def maxHeapMaximum(self):
        if self.heap_size < 1:
            print("Error: Heap underflow")
            return -sys.maxsize - 1
        return self.harr[0]

    def maxHeapExtractMax(self):
        if self.heap_size < 1:
            print("Error: Heap underflow")
            return -sys.maxsize - 1
        maxVal = self.harr[0]
        self.harr[0] = self.harr[self.heap_size - 1]
        self.heap_size -= 1
        self.maxHeapify(0)
        return maxVal

    def maxHeapIncreaseKey(self, i: int, key: int):
        if key < self.harr[i]:
            print("Error: New key is smaller than the current key")
            return
        self.harr[i] = key
        while i > 0 and self.harr[self.parent(i)] < self.harr[i]:
            self.harr[i], self.harr[self.parent(i)] = self.harr[self.parent(i)], self.harr[i]
            i = self.parent(i)

    def maxHeapInsert(self, key: int):
        if self.heap_size == self.capacity:
            print("Error: Heap overflow")
            return
        self.heap_size += 1
        self.harr[self.heap_size - 1] = -sys.maxsize - 1
        self.maxHeapIncreaseKey(self.heap_size - 1, key)

def main():
    # [#12] p.32 example
    maxHeap = Heap(20)
    maxHeap.insertKey(4)
    maxHeap.insertKey(1)
    maxHeap.insertKey(3)
    maxHeap.insertKey(2)
    maxHeap.insertKey(16)
    maxHeap.insertKey(9)
    maxHeap.insertKey(10)
    maxHeap.insertKey(14)
    maxHeap.insertKey(8)
    maxHeap.insertKey(7)

    maxHeap.buildMaxHeap()

    # build maxheap
    print("Max Heap:", end=' ')
    for i in range(maxHeap.heap_size):
        print(maxHeap.harr[i], end=' ')
    print()

    # heapsort
    size = maxHeap.heap_size
    maxHeap.heapsort()
    print("Heapsort:", end=' ')
    for i in range(size):
        print(maxHeap.harr[i], end=' ')
    print()

    # priority queue
    # maxHeap.heap_size = size  # reset heap size
    # print("Max Heap Extract Max:", maxHeap.maxHeapExtractMax(), '/', end=' ')
    # for i in range(maxHeap.heap_size):
    #     print(maxHeap.harr[i], end=' ')
    # print()

    # maxHeap.maxHeapIncreaseKey(4, 22)
    # print("Max Heap Increase Key:", end=' ')
    # for i in range(maxHeap.heap_size):
    #     print(maxHeap.harr[i], end=' ')
    # print()

    # maxHeap.maxHeapInsert(15)
    # print("Max Heap Insert:", end=' ')
    # for i in range(maxHeap.heap_size):
    #     print(maxHeap.harr[i], end=' ')
    # print()



if __name__ == '__main__':
    main()
