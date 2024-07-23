class Node:
    def __init__(self, data=0):
        self.data = data
        self.next = None

def add_first(head, data):
    new_node = Node(data)
    new_node.next = head
    return new_node

def print_list(head):
    p = head
    while p:
        print(p.data, " ", end="")
        p = p.next
    print("\n")

def reverse(head):
    p = head
    q = None
    while p:
        r = q
        q = p
        p = p.next
        q.next = r
    return q

def add_to_ordered_list(head, data):
    new_node = Node(data)
    if not head or data <= head.data:
        new_node.next = head
        return new_node
    p = head
    while p.next and p.next.data < data:
        p = p.next
    new_node.next = p.next
    p.next = new_node
    return head

def merge(list1, list2):
    if not list1:
        return list2
    if not list2:
        return list1
    
    dummy = Node()
    curr = dummy
    
    while list1 and list2:
        if list1.data <= list2.data:
            curr.next = list1
            list1 = list1.next
        else:
            curr.next = list2
            list2 = list2.next
        curr = curr.next
    
    if list1:
        curr.next = list1
    else:
        curr.next = list2
    
    return dummy.next

def sort(head):
    if not head or not head.next:
        return head
    
    # Split the list into two halves
    slow = head
    fast = head.next
    while fast and fast.next:
        slow = slow.next
        fast = fast.next.next
    
    left = head
    right = slow.next
    slow.next = None
    
    left = sort(left)
    right = sort(right)
    
    return merge(left, right)

def concat(head1, head2):
    if not head1:
        return head2
    p = head1
    while p.next:
        p = p.next
    p.next = head2
    return head1

if __name__ == "__main__":
    head = None

    # Initial list setup
    head = add_first(head, 3) # Thursday
    head = add_first(head, 2) # Tuesday
    head = add_first(head, 1) # Monday

    print("Initial List:")
    print_list(head)

    # Reverse the list
    head = reverse(head)
    print("Reversed List:")
    print_list(head)

    # Add to ordered list
    head = add_to_ordered_list(head, 4) # Wednesday
    print("Ordered Insertion:")
    print_list(head)

    # Merge two lists
    list1 = None
    list2 = None

    list1 = add_first(list1, 4) # D
    list1 = add_first(list1, 2) # B
    list1 = add_first(list1, 1) # A

    list2 = add_first(list2, 5) # E
    list2 = add_first(list2, 3) # C

    merged_list = merge(sort(list1), sort(list2))
    print("Merged and Sorted List:")
    print_list(merged_list)

    # Concatenate two lists
    head = concat(head, merged_list)
    print("Concatenated List:")
    print_list(head)

    # Sort the final list
    head = sort(head)
    print("Sorted List:")
    print_list(head)
