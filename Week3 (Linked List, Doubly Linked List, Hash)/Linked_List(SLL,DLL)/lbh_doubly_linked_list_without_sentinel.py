### Python Implementation (Doubly Linked List without Sentinel Nodes)
class Node:
    def __init__(self, data):
        self.data = data
        self.next = None
        self.prev = None

class DoublyLinkedList:
    def __init__(self):
        self.head = None
        self.tail = None
        self.size = 0

    # Function to insert a node at the beginning of the list
    def insert_first(self, value):
        new_node = Node(value)
        new_node.next = self.head
        new_node.prev = None
        if self.head is not None:
            self.head.prev = new_node
        else:
            self.tail = new_node  # If list was empty, new node is also the tail
        self.head = new_node
        self.size += 1

    # Function to insert a node at the end of the list
    def insert_last(self, value):
        new_node = Node(value)
        new_node.next = None
        new_node.prev = self.tail
        if self.tail is not None:
            self.tail.next = new_node
        else:
            self.head = new_node  # If list was empty, new node is also the head
        self.tail = new_node
        self.size += 1

    # Function to insert a node before a node with a certain value
    def insert_value(self, target, value):
        new_node = Node(value)
        temp = self.head
        while temp is not None and temp.data != target:
            temp = temp.next

        if temp is None:
            print("Target value not found")
            return

        new_node.next = temp
        new_node.prev = temp.prev
        if temp.prev is not None:
            temp.prev.next = new_node
        else:
            self.head = new_node  # Inserting before the first node
        temp.prev = new_node
        self.size += 1

    # Function to delete a node by value
    def delete_value(self, value):
        temp = self.head
        while temp is not None and temp.data != value:
            temp = temp.next

        if temp is None:
            return

        if temp.prev is not None:
            temp.prev.next = temp.next
        else:
            self.head = temp.next  # Node to be deleted is head

        if temp.next is not None:
            temp.next.prev = temp.prev
        else:
            self.tail = temp.prev  # Node to be deleted is tail

        self.size -= 1

    # Function to delete the first node
    def delete_first(self):
        if self.head is None:
            return

        self.head = self.head.next
        if self.head is not None:
            self.head.prev = None
        else:
            self.tail = None  # List became empty

        self.size -= 1

    # Function to delete the last node
    def delete_last(self):
        if self.tail is None:
            return

        self.tail = self.tail.prev
        if self.tail is not None:
            self.tail.next = None
        else:
            self.head = None  # List became empty

        self.size -= 1

    # Function to get the first node's value
    def get_first(self):
        if self.head is None:
            print("List is empty")
            return -1
        return self.head.data

    # Function to get the last node's value
    def get_last(self):
        if self.tail is None:
            print("List is empty")
            return -1
        return self.tail.data

    # Function to get the size of the list
    def get_size(self):
        return self.size

    # Function to print the elements of the list
    def print_list(self):
        temp = self.head
        while temp is not None:
            print(temp.data, end=" -> ")
            temp = temp.next
        print("NULL")

    # Function to free all nodes in the list
    def free_list(self):
        self.head = None
        self.tail = None
        self.size = 0

# Demonstration
list = DoublyLinkedList()
list.insert_first(10)
list.insert_first(20)
list.insert_last(30)
list.insert_last(40)

print("List: ", end="")
list.print_list()
print("Size:", list.get_size())

print("First element:", list.get_first())
print("Last element:", list.get_last())

list.insert_value(30, 25)
print("After inserting 25 before 30: ", end="")
list.print_list()

list.delete_first()
print("After deleting first element: ", end="")
list.print_list()

list.delete_last()
print("After deleting last element: ", end="")
list.print_list()

list.delete_value(30)
print("After deleting value 30: ", end="")
list.print_list()

print("Final size:", list.get_size())