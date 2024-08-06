class Node:
    def __init__(self, data):
        self.data = data
        self.children = []

# Function to add a child to a node
def add_child(parent, data):
    parent.children.append(Node(data))

# Function to delete a node (assumes parent is known)
def delete_node(parent, data):
    for i, child in enumerate(parent.children):
        if child.data == data:
            del parent.children[i]
            return
    for child in parent.children:
        delete_node(child, data)

# Function for breadth-first traversal
def bft(root):
    if not root:
        return
    queue = [root]
    while queue:
        node = queue.pop(0)
        print(node.data, end=' ')
        queue.extend(node.children)

# Function for preorder traversal
def preorder(root):
    if not root:
        return
    print(root.data, end=' ')
    for child in root.children:
        preorder(child)

# Function for postorder traversal
def postorder(root):
    if not root:
        return
    for child in root.children:
        postorder(child)
    print(root.data, end=' ')

# Function to search a node
def search(root, data):
    if not root:
        return None
    if root.data == data:
        return root
    for child in root.children:
        result = search(child, data)
        if result:
            return result
    return None

# Example usage
root = Node(1)
add_child(root, 2)
add_child(root, 3)
add_child(root, 4)

child = search(root, 2)
if child:
    add_child(child, 5)
    add_child(child, 6)

child = search(root, 3)
if child:
    add_child(child, 7)

print("Breadth-First Traversal:", end=' ')
bft(root)
print()

print("Preorder Traversal:", end=' ')
preorder(root)
print()

print("Postorder Traversal:", end=' ')
postorder(root)
print()

print("\nDeleting node 2 and its children")
delete_node(root, 2)

print("Breadth-First Traversal:", end=' ')
bft(root)
print()