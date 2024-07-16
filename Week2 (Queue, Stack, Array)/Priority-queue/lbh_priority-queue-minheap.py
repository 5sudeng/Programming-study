class PriorityQueue:
    def __init__(self):
        self.data = []

    def is_empty(self):
        return len(self.data) == 0

    def push(self, value):
        self.data.append(value)
        self._heapify_up(len(self.data) - 1)

    def _heapify_up(self, index):
        while index > 0 and self.data[(index - 1) // 2] > self.data[index]:
            self.data[index], self.data[(index - 1) // 2] = self.data[(index - 1) // 2], self.data[index]
            index = (index - 1) // 2

    def pop(self):
        if self.is_empty():
            print("Priority Queue is empty")
            return -1
        top_value = self.data[0]
        self.data[0] = self.data.pop()
        if not self.is_empty():
            self._heapify_down(0)
        return top_value

    def _heapify_down(self, index):
        size = len(self.data)
        while 2 * index + 1 < size:
            left = 2 * index + 1
            right = 2 * index + 2
            smallest = left
            if right < size and self.data[right] < self.data[left]:
                smallest = right
            if self.data[index] <= self.data[smallest]:
                break
            self.data[index], self.data[smallest] = self.data[smallest], self.data[index]
            index = smallest

    def top(self):
        if self.is_empty():
            print("Priority Queue is empty")
            return -1
        return self.data[0]

# Demonstration
pq = PriorityQueue()

pq.push(10)
pq.push(20)
pq.push(15)

print("Top element:", pq.top())

print("Popped:", pq.pop())
print("Top element after pop:", pq.top())