### Python Implementation (Singly Linked List with Sentinel Node)
class Node:
    def __init__(self, data=None):
        self.data = data
        self.next = None

class LinkedList:
    def __init__(self):
        self.head = Node()  # Sentinel node
        self.size = 0

    # Function to insert a node at the beginning of the list
    def insert_first(self, value):
        new_node = Node(value)
        new_node.next = self.head.next
        self.head.next = new_node
        self.size += 1

    # Function to insert a node at the end of the list
    def insert_last(self, value):
        new_node = Node(value)
        temp = self.head
        while temp.next:
            temp = temp.next
        temp.next = new_node
        self.size += 1

    # Function to insert a node before a node with a certain value
    def insert_value(self, target, value):
        new_node = Node(value)
        temp = self.head
        while temp.next and temp.next.data != target:
            temp = temp.next

        if temp.next is None:
            print("Target value not found")
            return

        new_node.next = temp.next
        temp.next = new_node
        self.size += 1

    # Function to delete a node by value
    def delete_value(self, value):
        temp = self.head
        while temp.next and temp.next.data != value:
            temp = temp.next

        if temp.next is None:
            return

        temp.next = temp.next.next
        self.size -= 1

    # Function to delete the first node
    def delete_first(self):
        if self.head.next is None:
            return

        self.head.next = self.head.next.next
        self.size -= 1

    # Function to delete the last node
    def delete_last(self):
        if self.head.next is None:
            return

        temp = self.head
        while temp.next and temp.next.next:
            temp = temp.next

        if temp.next:
            temp.next = None
            self.size -= 1

    # Function to get the first node's value
    def get_first(self):
        if self.head.next is None:
            print("List is empty")
            return -1
        return self.head.next.data

    # Function to get the last node's value
    def get_last(self):
        if self.head.next is None:
            print("List is empty")
            return -1

        temp = self.head
        while temp.next:
            temp = temp.next

        return temp.data

    # Function to get the size of the list
    def get_size(self):
        return self.size

    # Function to print the elements of the list
    def print_list(self):
        temp = self.head.next
        while temp:
            print(temp.data, end=" -> ")
            temp = temp.next
        print("NULL")

    # Function to free all nodes in the list
    def free_list(self):
        self.head.next = None
        self.size = 0

# Demonstration
list = LinkedList()
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