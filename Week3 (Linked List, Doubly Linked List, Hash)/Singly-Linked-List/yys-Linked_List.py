'''
1. Node class 구현
2. Linked List 구현
항상 시작은 head에서 시작

내부 함수 종류
printLinkedList
addhead
addback
deletenode : 특정 값 지우기
findnode : O(N), 특정 값 찾기
addafter : 특정 노드 뒤에 추가하기
deleteafter : 특정 노드 뒤에 노드 지우기

'''

class Node:
    def __init__(self, value):
        self.val = value
        self.next = None

class LinkedList:
    def __init__(self):
        self.first = None
        self.size = 0


    def getsize(self):
        return self.size
    
    def addfront(self, val):
        newnode = Node(val)

        # first라는 것만 바로 업데이트
        newnode.next = self.first
        self.first = newnode
        self.size +=1


    def addback(self, val): # O(N)
        newnode = Node(val)

        #find last one
        temp = self.first
        if temp is None:
            self.first = newnode
            return
        
        while(temp.next): #그 다음이 있는 동안 계속 넘어가도록.
            temp = temp.next
        
        #temp는 last one, so add new one after temp
        temp.next = newnode
        self.size +=1
    
    def findNode(self, val)->Node:

        #처음부터 순회하면서 찾기 : O(N)
        curr_node = self.first
        while (curr_node): #끝에 도달 할때 까지
            if curr_node.val == val:
                print("find node : ", val)
                return curr_node
            curr_node = curr_node.next
        
        print("Do not exist in this linked list.")
        return None # 탈출이라는 것은 못찾았다는 것.


    def deleteNode(self, val):
        
        #찾으면 지우고, 못찾으면 종료.
        #지울 때를 위해 prev_node를 계속 추적한다, 지우고 전과 후를 이어 붙이도록.

        cur_node = self.first
        prev = None

        while(cur_node.next): # 찾을 동안

            if cur_node.val == val:#찾음

                #가장 처음이라면 prev가 None이기 때문에 다르게 처리
                if cur_node == self.first:
                    self.first = cur_node.next
                
                else:
                    prev.next = cur_node.next
           
                self.size -=1
                print(f"Successfully delete {val}")
                return #지웠으니 종료
            
            prev = cur_node
            cur_node= cur_node.next
            
            
        # 탈출 = 못찾은 것임.
        print("Do not exist in this linked list.")
        return None # 탈출이라는 것은 못찾았다는 것.

    def  addafter(self, prevnode, val):
        
        newnode = Node(val)
        newnode.next = prevnode.next # 이게 먼저와야 하는 이유는 다음줄에서 정보가 바뀌기 때문
        prevnode.next = newnode
        self.size +=1

    def deleteafter(self, prevnode):
        
        if prevnode.next is not None:
            prevnode.next = prevnode.next.next # 근데 next의 next가 있어야 한다. 즉 마지막 노드가 아니어야 함.
            self.size -=1
        #마지막 node라면 지울 것도 없음. 그래서 아무것도 안한다.

    def printSSL(self):
        
        cur_node = self.first
        while(cur_node.next):
            print("Current : ", cur_node.val)
            cur_node = cur_node.next
        
        #나오면서 cur_node 는 맨 마지막 꺼임
        print("Current : ", cur_node.val) #그래서 한번 더함.


def main():
    # Linked List 생성
    linked_list = LinkedList()

    linked_list.addback(100)


    # Linked List에 head 추가
    linked_list.addfront(10)
    linked_list.addfront(20)
    linked_list.addfront(30)
    print("Added 30, 20, 10 to the front")
    linked_list.printSSL()
    print()

    # Linked List에 back 추가
    linked_list.addback(40)
    linked_list.addback(50)
    print("Added 40, 50 to the back")
    linked_list.printSSL()
    print()

    # 노드 찾기
    node = linked_list.findNode(20)
    if node:
        print(f"Found node with value: {node.val}")
    else:
        print("Node with value 20 not found")
    print()

    # 특정 값 가진 노드 삭제
    linked_list.deleteNode(20)
    print("Deleted node with value 20")
    linked_list.printSSL()
    print()

    # 특정 노드 뒤에 노드 추가
    node = linked_list.findNode(10)
    if node:
        linked_list.addafter(node, 25)
        print("Added 25 after node with value 10")
        linked_list.printSSL()
        print()

    # 특정 노드 뒤에 노드 삭제
    node = linked_list.findNode(10)
    if node:
        linked_list.deleteafter(node)
        print("Deleted node after node with value 10")
        linked_list.printSSL()
        print()

if __name__ == "__main__":
    main()
