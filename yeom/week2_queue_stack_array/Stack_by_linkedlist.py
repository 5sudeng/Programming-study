'''
Stack by single-linked list

* push(x): Add a LinkedNode that has val x to myStack  
* pop: Remove the most recently added LinkedNode from myStack  
* top: Return val of the most recently added LinkedNode  
* getSize: Return the number of LinkedNodes in myStack  
* isEmpty: Return True if myStack is empty, or False otherwise.
* clear: Remove all LinkedNodes
* status_check: prints status of stack


top을 항상 맨 앞으로 유지. (using sentinel 어디가 앞인지 표시)
마지막에 넣은 것도, 뺄 것도 sentinel 옆에서 빼온다.

linked list의 장점은 resize를 하지 않아도 된다는 것. 메모리 크기에서 자유롭다.
'''

class LinkedNode():
    def __init__(self, x):
        self.val = x 
        self.next = None # singly lined list

class myStack(): #LIFO

    def __init__(self) -> None:
        self.sentinel = LinkedNode(0)
        self.size = 0
    
    def push(self, x:int) -> None:

        new =LinkedNode(x)
        if self.sentinel.next: ## 항상 앞으로 하기 위해서, 맨 앞인 sentinel 다음에 붙이기
            new.next = self.sentinel.next
            self.sentinel.next = new
        else:
            self.sentinel.next = new ## 아무것도 없었으므로, sentinel다음에만 바로 붙이기
        
        self.size+=1

    def pop(self)-> None:
        if self.sentinel.next : 
            self.sentinel.next = self.sentinel.next.next
            self.size -=1
    
    def top(self) -> None:
        if self.sentinel.next:
            return self.sentinel.next.val
        else:
            return None

    def getSize(self)-> int:
        return self.size
    
    def isEmpty(self)-> bool:
        return self.size == 0
    
    def clear(self)-> None:
        self.sentinel.next = None
        self.size = 0

    def status_check(self) -> None:
        #Do not modify
        if self.isEmpty():
            print("IsEmpty:",self.isEmpty(), " | Size:", self.getSize(),"| Top:", self.top())
        else:
            print("IsEmpty:",self.isEmpty(), "| Size:", self.getSize(),"| Top:", self.top())
