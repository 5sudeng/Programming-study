# - **Search**: Find a node in the tree.
# - **Insert**: Add a new node to the tree.
# - **Delete**: Remove a node from the tree.
# - **Inorder Traversal**: Left, Root, Right.
# - **Preorder Traversal**: Root, Left, Right.
# - **Postorder Traversal**: Left, Right, Root.
# - **Breadth-First Traversal (BFT)**: Level-order traversal using a queue.
class Node:
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None

class BST:
    def __init__(self):
        self.root = None

    def insert(self, node, data):
        if node is None:
            return Node(data)
        if data < node.data:
            node.left = self.insert(node.left, data)
        else:
            node.right = self.insert(node.right, data)
        return node

    def search(self, node, data):
        if node is None or node.data == data:
            return node
        if data < node.data:
            return self.search(node.left, data)
        return self.search(node.right, data)

    def find_min(self, node):
        current = node
        while current and current.left is not None:
            current = current.left
        return current

    def delete_node(self, node, data):
        if node is None:
            return node
        if data < node.data:
            node.left = self.delete_node(node.left, data)
        elif data > node.data:
            node.right = self.delete_node(node.right, data)
        else:
            if node.left is None:
                return node.right
            elif node.right is None:
                return node.left
            temp = self.find_min(node.right)
            node.data = temp.data
            node.right = self.delete_node(node.right, temp.data)
        return node

    def inorder(self, node):
        if node:
            self.inorder(node.left)
            print(node.data, end=' ')
            self.inorder(node.right)

    def preorder(self, node):
        if node:
            print(node.data, end=' ')
            self.preorder(node.left)
            self.preorder(node.right)

    def postorder(self, node):
        if node:
            self.postorder(node.left)
            self.postorder(node.right)
            print(node.data, end=' ')

    def bft(self, node):
        if not node:
            return
        queue = [node]
        while queue:
            current = queue.pop(0)
            print(current.data, end=' ')
            if current.left:
                queue.append(current.left)
            if current.right:
                queue.append(current.right)

bst = BST()
bst.root = bst.insert(bst.root, 50)
bst.root = bst.insert(bst.root, 30)
bst.root = bst.insert(bst.root, 20)
bst.root = bst.insert(bst.root, 40)
bst.root = bst.insert(bst.root, 70)
bst.root = bst.insert(bst.root, 60)
bst.root = bst.insert(bst.root, 80)

print("Inorder traversal:", end=' ')
bst.inorder(bst.root)
print()

print("Preorder traversal:", end=' ')
bst.preorder(bst.root)
print()

print("Postorder traversal:", end=' ')
bst.postorder(bst.root)
print()

print("Breadth-First traversal:", end=' ')
bst.bft(bst.root)
print()

print("\nDelete 20")
bst.root = bst.delete_node(bst.root, 20)
print("Inorder traversal:", end=' ')
bst.inorder(bst.root)
print()