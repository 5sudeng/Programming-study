"""
# Definition for a Node.
class Node:
    def __init__(self, val, prev, next, child):
        self.val = val
        self.prev = prev
        self.next = next
        self.child = child
"""


# Definition for a Node.
class Node:
    def __init__(self, val, prev, next, child):
        self.val = val
        self.prev = prev
        self.next = next
        self.child = child


class Solution:



    def flatten(self, head: Node) -> Node:

        '''
        head부터 시작해서 순환하다가 child가 not None일떄
        next로 연결
        이때, 원래 next는 외부 저장을 했다가 잇기.
        '''
        if head is None:
            return None

        cur_node = head
        while(cur_node): # 마지막 노드까지 : 마지막 노드에서 child가 있을 수 있어서
            
            if cur_node.child is not None:

                '''
                child node를 잇고, 그 다음 node 반환
                (여기서 그 다음이라 함은 이어진 child node의 next가 아닌, 원래 노드의 next를 말함.
                이어서 계속 순환하다가 child를 찾는다는 느낌.
                뭔가 재귀함수 느낌이 난다.
                '''
                cur_node = self.my_function(cur_node)
            else:
                cur_node = cur_node.next # 계속 순회
        
        return head



    def my_function(self, cur_node:Node)-> Node:
        '''
        cur_node : child가 있는 parent 역할.
        '''
        if cur_node is None or cur_node.child is None:
            return cur_node.next if cur_node is not None else None

     
        child_node = cur_node.child #있어서 시행되는 함수이지만 없을 수도 있음.

        cur_node.child = None
        child_node.prev = cur_node


        #parent_node의  next를 잇는 것은 조심스럽게.
        ori_next = cur_node.next # 외부 저장 : 이거를 반환 할 것임.
        cur_node.next =child_node

        temp = child_node #이제 child node에 이어진 linked list를 순환할 것임.

        while(temp):
            
            if temp.child is not None:
                temp = self.my_function(temp) # recursively

            elif temp.next is not None:
                temp = temp.next

            else: #child도 없고 next도 None일 경우. 순회 중단.
                break

    
        #끝나고 ori_next에 이어야 할 것은 temp
        ## ori_next가 None일수도.

        if temp is not None: # 처음부터 child가 없을 수도 있음.
            temp.next =ori_next
        if ori_next is not None:
            ori_next.prev = temp

        return ori_next
     






########## test cases

def create_multilevel_doubly_linked_list(data):
    if not data:
        return None
    
    nodes = [None if val is None else Node(val, None, None, None) for val in data]
    
    head = None
    prev = None
    current = None
    child_stack = []
    
    for i, node in enumerate(nodes):
        if node is not None:
            if head is None:
                head = node
                current = head
            else:
                if current is not None:
                    current.next = node
                    node.prev = current
                current = node
        else:
            if current is not None:
                child_stack.append(current)
                current = None
        if (i + 1) < len(nodes) and nodes[i + 1] is None:
            if child_stack:
                parent = child_stack.pop()
                parent.child = nodes[i + 2]
                current = nodes[i + 2]
    
    return head



def print_flattened_list(head):
    result = []
    current = head
    while current is not None:
        result.append(current.val)
        current = current.next
    print(result)

# 주어진 리스트 데이터
data = [1,2,3,4,5,6,None,None,None,7,8,9,10,None,None,11,12]

# 다중 레벨 이중 연결 리스트 생성
head = create_multilevel_doubly_linked_list(data)
print_flattened_list(head)

# Solution 클래스의 flatten 메서드 호출
solution = Solution()
flattened_head = solution.flatten(head)

# 결과 출력
print_flattened_list(flattened_head)

