'''
from collections import deque
result = deque()

deque.append(item): item을 데크의 오른쪽 끝에 삽입한다. 
deque.appendleft(item): item을 데크의 왼쪽 끝에 삽입한다. (prepend)
deque.pop(): 데크의 오른쪽 끝 엘리먼트를 가져오는 동시에 데크에서 삭제한다.
deque.popleft(): 데크의 왼쪽 끝 엘리먼트를 가져오는 동시에 데크에서 삭제한다.
deque.remove(item): item을 데크에서 찾아 삭제한다. (제일 처음 나온 해당 string만 제거됨)
deque.clear(): 해당 deque 전체 삭제
deque.reverse(): 말그대로 역순으로 정렬한다.
deque.rotate(num): 데크를 num만큼 회전한다(양수면 오른쪽, 음수면 왼쪽).


baseline: Doubly Linked List
'''



class DLLNode:
    def __init__(self, val):
        self.val = val
        self.next = None
        self.prev = None

class Deque():

    def __init__(self):
        self.size = 0
        self.head = None
        self.tail = None

    def getSize(self):
        return self.size
    
    def is_empty(self):
        return self.size ==0
    
    def clear(self):
        self.head = self.tail = None
        self.size = 0


    def front(self):
        if self.is_empty():
            print(-1)
            return
        print(self.head.val)

    def back(self):
        if self.is_empty():
            print(-1)
            return
        print(self.tail.val)

    def appendleft(self, val):
        ## same as prepend in Doubly Linked List

        newnode = DLLNode(val)
        if self.is_empty():
            self.head = self.tail= newnode
            
        else:#이미 있는 경우
            temp = self.head # 바꾸는 정보 따로 저장

            #서로 이어주기
            newnode.next = temp
            temp.prev =newnode

            self.head = newnode
        self.size +=1

    def append(self, val):
        ## same as append in Doubly Linked List
        newnode = DLLNode(val)
        if self.is_empty():
            self.head = self.tail = newnode
        else:
            temp = self.tail

            temp.next = newnode #이게 먼저와야 함.
            newnode.prev = temp
        
            self.tail = newnode
        self.size +=1

    def popleft(self):

        #remove front value and return
       

        if self.is_empty():
            print(-1)
            return
        
        print(self.head.val)

        ## same as delete_first
        ## edge case 하나일 경우,
        if self.head == self.tail:
            self.head =self.tail = None
        else:
            self.head = self.head.next
            self.head.prev = None
        self.size -=1

    def pop(self):
        #return last value and remove it

        if self.is_empty():
            print(-1)
            return
        
        print(self.tail.val)

        #same as delete_last in doubly linked list
        if self.head == self.tail:
            self.head =self.tail = None
        else:
            self.tail = self.tail.prev
            self.tail.next = None
        self.size -=1 

    
    def reverse(self):

        '''
        SSL의 reverse를 참고. : reverse_SSL.py
        '''

        prev_node =None
        cur_node = self.head
        next_node = None

        self.tail = self.head # new tail
        while(cur_node):
            
            prev_node = cur_node.prev
            next_node = cur_node.next # 현재 시점 원래 정보 외부 저장

            #방향 바꾸기
            cur_node.prev = next_node
            cur_node.next = prev_node

            #next step
            prev_node = cur_node
            cur_node = next_node
        
        if prev_node is not None: #만약 empty라면 굳이 정보를 바꿀 이유가 없긴 함.
            self.head = prev_node



    def rotate(self, d):

        ##부트캠프 시험 문제 였음. (C array로 출제됨.)
        '''
        d%size : 실제로 회전하는 횟수(한바퀴 즉, d ==size인 경우는 제자리임으로)
        d = 0 : 아무런 작업도 하지 않음.
        d>0 : 오른쪽 회전
        d<0 : 왼쪽 회전
        '''

        if self.is_empty() or d == 0:
            return
        d %= self.size # 실제 회전 수,

        if d==0: #그냥 한바퀴인 경우
            return
        
        if d <0:
            d = self.size +d # 왼쪽으로 d만큼이라는 것은 오른쪽으로 size-d만큼이라는것
        
        ## 오른쪽 회전

        #1.새로운 tail 먼저 지정
        new_tail = self.tail
        for _ in range(d):
            new_tail = new_tail.prev

        #새로운 head : 새로운 tail 바로 옆
        new_head = new_tail.next

        new_head.prev= None
        new_tail.next = None #연결 끊기


        #원래 끊어진 부분 잇기
        self.head.prev = self.tail
        self.tail.next =self.head

        #head, tail 갱신
        self.head = new_head
        self.tail = new_tail



       