'''
reverse given Singly Linked List

'''

from Linked_List import *

class Node:
    def __init__(self, value):
        self.val = value
        self.next = None


# converting list form into a singly linked list
def create_linked_list(l: list) -> Node:
    if len(l) == 0:
        return None
    start = Node(l[0])
    current_node = start
    for i in range(1,len(l)):
        node_new = Node(l[i])
        current_node.next = node_new
        current_node = node_new
    return start

def create_linked_list_class(l: list)-> LinkedList:
    if len(l) == 0:
        return None
    
    linked_list = LinkedList()
    for val in l:
        linked_list.addback(val)

    return linked_list




def reverse_SSL_class(SSL: LinkedList)->LinkedList:

    #순회하면서 연결을 반대로 돌리기.
    prev = None  #새롭게 prev가 되는 친구.
    cur_node = SSL.first
    next_node = None #순회하면서 next
    while (cur_node): # 마지막의 None인 next까지 순회
        
        #일단 따로 저장
        next_node = cur_node.next
        
        #방향 바꾸기
        cur_node.next = prev

        #다음 번 넘어가기
        prev = cur_node
        cur_node = next_node
    
    SSL.first = prev #새로운 first
    return SSL



def reverse_SSL(head: Node) -> Node:
    ##### Write your Code Here #####
    
    prev , next= None, None
    current = head
    while(current is not None):
        next = current.next #save exclusively
        current.next = prev #change direction

        prev = current #update
        current = next #update
        
    return prev
    ##### End of your Code #####


def print_linked_list(n: Node, l: list) -> None:
    if n is not None:
        l.append(n.val)
        print_linked_list(n.next, l)
    else:
        print(l)


def main():



    given_list = [1,2,3,4,5,6,7]


    #class version
    
    SSL = create_linked_list_class(given_list)
    print("original")
    SSL.printSSL()


    SSL = reverse_SSL_class(SSL)
    print("reversed")
    SSL.printSSL()

    print("original")
    first_node = SSL.first # Node
    print_linked_list(first_node, l = [])

    print("reversed")
    new_first_node = reverse_SSL(first_node)
    print_linked_list(new_first_node, l = [])



if __name__ =="__main__":
    main()