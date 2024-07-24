
class DLLNode:
    def __init__(self, val):
        self.val = val
        self.next = None
        self.prev = None


class DLL:
    def __init__(self):
        self.size = 0
        self.head = None
        # self.head.next = self.tail
        # self.tail.prev = self.head.prev # 연결하면 더 헷갈림.
        self.tail = None # 맨 뒤를 가리킴.

    
    def getSize(self):
        return self.size
    
    def is_empty(self):
        return self.size ==0
    
    def clear(self):
        self.head = self.tail = None
        self.size = 0

    def get_first(self):
        return self.head.val if self.head else None
    def get_last(self):
        return self.tail.val if self.tail else None
    
    def get_at_index(self, idx)->DLLNode:

        if idx> self.size:
            print("overflow")
            return None
        
        if idx == 0:
            return self.head
        
        if idx == self.size-1:
            return self.tail
        
        if idx < self.size:

            #찾을 때, 앞에서부터 찾을 지, 뒤에서부터 찾을 지 정하면 좋다.
            # 이게 가능한 이유가 doubly linked라서.
            if idx < self.size //2 : # 앞에서부터 찾는게 빠름.
                target = self.head
                for _ in range(idx):
                    target = target.next
                return target
            
            else: # 뒤에서부터 찾는게 빠를 때
                target =self.tail
                for _ in range(self.size-1 - idx):
                    target = target.prev
                return target
            
    def find_data(self,data)->DLLNode:
        # get at index와 같지만 값을 기준으로 찾는다. : 단, O(N)
        # 사실상 앞에서부터 그냥 찾는 수밖에 없다.

        target = self.head
        while (target):
            if target.val == data:
                return target
            target = target.next
        print("do not exist")
        return None
    
    #insert
    def prepend(self, data) : #앞에서 넣기
        newnode = DLLNode(data)
        if self.is_empty():
            self.head = self.tail= newnode
            
        else:#이미 있는 경우
            temp = self.head # 바꾸는 정보 따로 저장

            #서로 이어주기
            newnode.next = temp
            temp.prev =newnode

            self.head = newnode
        self.size +=1

    
    def append(self,data): #뒤에서 넣기
        newnode = DLLNode(data)
        if self.is_empty():
            self.head = self.tail = newnode
        else:
            temp = self.tail

            temp.next = newnode #이게 먼저와야 함.
            newnode.prev = temp
        
            self.tail = newnode
        self.size +=1


    def insert_at_idx(self, data, idx):
        
        if idx> self.size:
            print("overflow")
            return
        
        if idx == 0:
            self.prepend(data)
        
        elif idx == self.size:
            self.append(data)
        else:
        
            node_idx = self.get_at_index(idx)
        
            new_node = DLLNode(data)
            prev_node_idx = node_idx.prev #외부 저장

            #새로운 거 먼저 잇기
            new_node.next = node_idx
            new_node.prev = prev_node_idx

            prev_node_idx.next = new_node
            node_idx.prev = new_node
        
            self.size +=1


    #delete
    def delete_at_idx(self, idx):
        
        if idx >= self.size:
            print("overflow")
            return
        
        elif idx == 0:
            if self.size == 1:
                    self.head = self.tail = None
            else:
                self.head =  self.head.next #or node_at_idx.next
                self.head.prev = None 
        
        elif idx == self.size -1:
                self.tail = self.tail.prev
                self.tail.next = None
            

        else: # 중간에서 빼기
            node_at_idx = self.get_at_index(idx)
            prev_idx = node_at_idx.prev # 바뀌어지는 정보, 외부 저장
            next_idx = node_at_idx.next

            prev_idx.next = next_idx
            next_idx.prev = prev_idx

        self.size -=1
    


    def delete_by_value(self, data):
        
        node_to_delete = self.find_data(data)

        if node_to_delete is None:
            return
        
        else:
        
            if node_to_delete == self.head: # if head
                if self.size == 1:
                    self.head = self.tail = None
                else:
                    self.head =  self.head.next  #or node_at_idx.next
                    self.head.prev = None 

            elif node_to_delete == self.tail: #if tail
                self.tail = self.tail.prev
                self.tail.next = None
            

            else: # 중간에서 빼기
                prev_idx = node_to_delete.prev # 바뀌어지는 정보, 외부 저장
                next_idx = node_to_delete.next

                prev_idx.next = next_idx
                next_idx.prev = prev_idx

            self.size -=1


    def delete_first(self):

        if self.is_empty():
            print("DLL is empty")
            return
        
        ## edge case 하나일 경우,
        if self.head == self.tail:
            self.head =self.tail = None
        else:
            self.head = self.head.next
            self.head.prev = None
        self.size -=1

    def delete_last(self):
        if self.is_empty():
            print("DLL is empty")
            return
        if self.head == self.tail:
            self.head =self.tail = None
        else:
            self.tail = self.tail.prev
            self.tail.next = None
        self.size -=1 


    #추가한 함수
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




    #print
    def display_forward(self):
        cur_node = self.head
        while(cur_node):
            if cur_node != self.tail:
                print("Node:", cur_node.val, "<=>", end=" ")
            else:
                print("Node:", cur_node.val)
            cur_node = cur_node.next
        

    def display_backward(self):
        cur_node = self.tail
        while(cur_node):
            if cur_node !=self.head:
                print("Node:", cur_node.val, "<=>", end=" ")
            else:
                print("Node:", cur_node.val)

            cur_node = cur_node.prev


# 테스트 케이스를 위한 코드
def run_tests():
    # 새로운 리스트 생성
    dll = DLL()

    # 빈 리스트인지 확인
    assert dll.is_empty() == True, "Test Failed: List should be empty."

    # 데이터 추가 테스트
    dll.prepend(10)
    assert dll.get_first() == 10, "Test Failed: First element should be 10."
    assert dll.get_last() == 10, "Test Failed: Last element should be 10."
    assert dll.getSize() == 1, "Test Failed: Size should be 1."

    # 앞에 추가하는 테스트
    dll.prepend(20)
    assert dll.get_first() == 20, "Test Failed: First element should be 20."
    assert dll.get_last() == 10, "Test Failed: Last element should be 10."
    assert dll.getSize() == 2, "Test Failed: Size should be 2."

    # 데이터 찾기 테스트
    node = dll.find_data(10)
    assert node is not None and node.val == 10, "Test Failed: Node with value 10 should be found."
    node = dll.find_data(30)
    assert node == None, "Test Failed: Node with value 30 should not be found."

    # 특정 인덱스 데이터 가져오기 테스트
    assert dll.get_at_index(0).val == 20, "Test Failed: Element at index 0 should be 20."
    assert dll.get_at_index(1).val == 10, "Test Failed: Element at index 1 should be 10."
    assert dll.get_at_index(2) == None, "Test Failed: Element at index 2 should not exist (overflow)."

    # 리스트 비우기 테스트
    dll.clear()
    assert dll.is_empty() == True, "Test Failed: List should be empty after clear."
    assert dll.getSize() == 0, "Test Failed: Size should be 0 after clear."

    dll.append(30)
    assert dll.get_first() == 30
    assert dll.get_last() == 30
    print(dll.getSize())
    dll.display_forward()

    dll.append(100)
    assert dll.get_first() == 30
    assert dll.get_last() == 100
    print(dll.getSize())


    dll.insert_at_idx(11, 0) #first
    dll.display_forward()
    dll.insert_at_idx(12, 4)



    dll.display_forward()
    dll.insert_at_idx(20, 3) # last

    dll.display_forward()
    dll.insert_at_idx(14, 2)
 
    dll.display_forward()



    dll.delete_at_idx(5)
    dll.display_forward()
    dll.delete_by_value(20)
    dll.display_forward()
    dll.delete_at_idx(2)
    dll.display_forward()


    # dll.delete_first()
    # dll.display_forward()

    # dll.delete_last()
    # dll.display_forward()

    dll.reverse()
    dll.display_forward()
    

    dll.reverse()
    dll.rotate(5)
    dll.display_forward()
    dll.display_backward()

    print("All tests passed!")

# 테스트 실행
run_tests()
