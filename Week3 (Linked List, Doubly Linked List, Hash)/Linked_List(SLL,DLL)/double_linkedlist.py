class Node:
    def __init__(self, data):
        self.data = data
        self.next = None
        self.prev = None

# Print the linked list
def print_list(head):
    cur = head
    while cur:
        print(cur.data, end=" ")
        cur = cur.next
    print()

# Insert node at the beginning of the list
def add_first(head, item):
    temp = Node(item)
    temp.next = head
    if head:
        head.prev = temp
    return temp  # New head node's address

# Insert node after a specific node
def add_after(prev, item):
    if prev is None:
        return
    temp = Node(item)
    temp.next = prev.next
    temp.prev = prev
    if prev.next:
        prev.next.prev = temp
    prev.next = temp

# Get the node at a specific index
def get_node(head, index):
    if index < 0:
        return None
    p = head
    for i in range(index):
        if p is None:
            return None
        p = p.next
    return p

# Insert node at a specific index
def add(head, index, item):
    if index < 0:
        return head

    if index == 0:
        return add_first(head, item)

    prev = get_node(head, index-1)
    if prev:
        add_after(prev, item)
    return head

# Insert into ordered list
def add_to_ordered_list(head, item):
    p = head
    q = None

    while p and p.data < item:
        q = p
        p = p.next

    if q is None:
        return add_first(head, item)
    else:
        add_after(q, item)
        return head

# Find node by value
def find_node(head, item):
    cur = head
    while cur:
        if cur.data == item:
            return cur
        cur = cur.next
    return None

# Remove first node
def remove_first(head):
    if head is None:
        return None
    temp = head
    head = head.next
    if head:
        head.prev = None
    return head

# Remove node after a specific node
def remove_after(prev):
    if prev is None or prev.next is None:
        return
    temp = prev.next
    prev.next = temp.next
    if temp.next:
        temp.next.prev = prev

# Remove node by index
def remove_by_index(head, index):
    if index < 0:
        return head

    if index == 0:
        return remove_first(head)

    prev = get_node(head, index-1)
    if prev and prev.next:
        remove_after(prev)
    return head

# Remove node by value
def remove_by_value(head, item):
    p = head
    q = None

    while p and p.data != item:
        q = p
        p = p.next

    if p is None:
        return head

    if q is None:
        return remove_first(head)
    else:
        remove_after(q)
        return head

# Find node by value
def find(head, word):
    p = head
    while p:
        if p.data == word:
            return p
        p = p.next
    return None

# Function to merge two sorted lists
def merge(list1, list2):
    dummy = Node(0)
    tail = dummy
    dummy.next = None

    while list1 and list2:
        if list1.data <= list2.data:
            tail.next = list1
            list1.prev = tail
            list1 = list1.next
        else:
            tail.next = list2
            list2.prev = tail
            list2 = list2.next
        tail = tail.next

    tail.next = list1 if list1 else list2

    if tail.next:
        tail.next.prev = tail

    return dummy.next

# Function to concatenate two lists
def concat(list1, list2):
    if list1 is None:
        return list2
    if list2 is None:
        return list1
    p = list1
    while p.next:
        p = p.next
    p.next = list2
    list2.prev = p
    return list1

# Function to get the middle node
def get_mid(head):
    slow = head
    fast = head.next
    while fast and fast.next:
        slow = slow.next
        fast = fast.next.next
    return slow

# Function to sort the list (ascending order)
def sort(head):
    if head is None or head.next is None:
        return head

    mid = get_mid(head)
    half = mid.next
    mid.next = None
    if half:
        half.prev = None

    return merge(sort(head), sort(half))

# Function to reverse the list
def reverse(head):
    prev = None
    cur = head
    while cur:
        next_node = cur.next
        cur.next = prev
        cur.prev = next_node
        prev = cur
        cur = next_node
    return prev

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

    # Sort the list
    head = sort(head)
    print("Sorted List:")
    print_list(head)
