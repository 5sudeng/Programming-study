# from collections import deque
# result = deque()

class Deque:
    rear = 0
    front = 0
    MAX_SIZE = 100
    deq = list()

    def __init__(self):
        self.rear = 0
        self.front = 0
        self.deq = [0 for i in range(self.MAX_SIZE)]

    def is_empty(self):
        if self.rear == self.front:
            return True
        return False
    
    def is_full(self):
        if (self.rear+1) % self.MAX_SIZE == self.front:
            return True
        return False

    def get_front(self):
        if self.is_empty():
            print("ERROR: EMPTY")
            return -1
        front = (self.front+1) % self.MAX_SIZE
        return self.deq[front]

    def get_rear(self):
        if self.is_empty():
            print("ERROR: EMPTY")
            return -1
        return self.deq[self.rear]
    
    def add_front(self, x):
        if self.is_full():
            print("ERROR: FULL")
            return
        self.deq[self.front] = x
        self.front = (self.front-1+self.MAX_SIZE) % self.MAX_SIZE

    def add_rear(self, x):
        if self.is_full():
            print("ERROR: FULL")
            return
        self.rear = (self.rear+1) % self.MAX_SIZE
        self.deq[self.rear] = x

    def del_front(self):
        if self.is_empty():
            print("ERROR: EMPTY")
            return
        tmp = self.get_front()
        self.front = (self.front+1) % self.MAX_SIZE
        return tmp
    
    def del_rear(self):
        if self.is_empty():
            print("ERROR: EMPTY")
            return
        tmp = self.get_rear()
        self.rear = (self.rear-1+self.MAX_SIZE) % self.MAX_SIZE
        return tmp
    
    def deque_print(self):
        i = (self.front+1) % self.MAX_SIZE
        if self.is_empty():
            print("ERROR: EMPTY")
            return
        while i != self.rear:
            print(self.deq[i], ' ')
            i = (i+1) % self.MAX_SIZE
        print(self.deq[i])


def main():
    print()

if __name__ == '__main__':
    main()