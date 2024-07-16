'''
Queue by singly linked list

is_empty
enqueue
dequeue
first : return the element of the queue(do not remove)
getsize 
clear : remove all
print_queue : print status


'''

class LinkedNode():
    def __init__(self, x):
        self.val = x 
        self.next = None # singly lined list


class Queue:
    def __init__(self):
        self.front = None
        self.rear = None
        self.size = 0


    def getSize(self) -> int:
        return self.size
    

    def is_Empty(self)->bool:
        return self.size ==0

    def first(self)->int:
        if(self.is_Empty()):
            print("empty queue")
        return self.front.val

    def enqueue(self, value) ->None:
        
        
        newnode = LinkedNode(value)
        ## empty이었을 경우
        if self.is_Empty():
            self.front = self.rear = newnode

        #empty가 아니었을 경우.
        else:
            self.rear.next = newnode
        
        self.rear = newnode
        self.size +=1


    def dequeue(self)->int:
        
        if self.is_Empty():
            print("empty queue")
            return -1
        else:

            node = self.front ## 맨 처음거 불러오기

            #case 1 : 맨 마지막 꺼일 경우,
            if self.size ==1:
                self.front = self.rear = None

            #case 2 : 맨 마지막 성분이 아닐 경우
            else:   
                self.front = self.front.next

            self.size-=1 ## 전체 개수 추적
            return node.val
       

    def clear(self)->None:

        self.front = self.rear =None
        self.size = 0

    def print_queue(self)->None:

        if self.is_Empty():
            print("empty queue")
        else:
            temp = self.front
            while(temp):
                print("value : ", temp.val)
                temp = temp.next
            

# Test cases
def test_queue():
    q = Queue()

    # Test is_Empty and getSize on empty queue
    assert q.is_Empty() == True
    assert q.getSize() == 0
    print("Initial empty queue test passed.")

    # Test enqueue
    q.enqueue(10)
    q.enqueue(20)
    q.enqueue(30)
    q.print_queue()  # Expected: 10 -> 20 -> 30 -> None

    # Test first
    assert q.first() == 10
    print("First element test passed.")

    # Test is_Empty and getSize after enqueues
    assert q.is_Empty() == False
    assert q.getSize() == 3
    print("Queue size and empty check after enqueues passed.")

    # Test dequeue
    assert q.dequeue() == 10
    assert q.dequeue() == 20
    q.print_queue()  # Expected: 30 -> None

    # Test dequeue until empty
    assert q.dequeue() == 30
    assert q.dequeue() == -1  # Expected empty queue message
    q.print_queue()  # Expected: empty queue

    # Test clear
    q.enqueue(40)
    q.enqueue(50)
    q.clear()
    q.print_queue()  # Expected: empty queue
    assert q.is_Empty() == True
    assert q.getSize() == 0
    print("Queue clear test passed.")

    print("All tests passed.")

# Run test cases
if __name__ =="__main__":
    test_queue()


