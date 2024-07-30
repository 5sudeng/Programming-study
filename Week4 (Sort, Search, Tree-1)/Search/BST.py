class TreeNode():
    def __init__(self, x:int):
        self.val = x
        self.left = None
        self.right = None
        self.parent = None

class BST():
    def __init__(self):
        self.root = None
    
    
    #search
    def __searchHelp(self, curNode: TreeNode, x: int) -> TreeNode:
        if not curNode:
            return None
        if x == curNode.val:
            return curNode
        elif x < curNode.val:
            return self.__searchHelp(curNode.left, x)
        else:
            return self.__searchHelp(curNode.right, x)
    
    def search(self, x: int):
        return self.__searchHelp(self.root, x)
    

    #insert
    def __insertHelp(self, curNode: TreeNode, x: int) -> TreeNode:
        if not curNode:
            return TreeNode(x)
        if x < curNode.val:
            if curNode.left is None:
                curNode.left = TreeNode(x)
                curNode.left.parent = curNode
            else:
                curNode.left = self.__insertHelp(curNode.left, x)
        elif x > curNode.val:
            if curNode.right is None:
                curNode.right = TreeNode(x)
                curNode.right.parent = curNode
            else:
                curNode.right = self.__insertHelp(curNode.right, x)
        return curNode

    def insert(self, x: int):
        if self.root is None:
            self.root = TreeNode(x)
        else:
            self.root = self.__insertHelp(self.root, x)


    #delete
    def __findMin(self, node: TreeNode) -> TreeNode:
        while node.left:
            node = node.left
        return node

    def __deleteHelp(self, node: TreeNode):
        if not node:
            return None
        
        # Node has no children
        if node.left is None and node.right is None:
            if node == self.root:
                self.root = None
            elif node == node.parent.left:
                node.parent.left = None
            else:
                node.parent.right = None
        
        # Node has one child
        elif not node.left or not node.right:
            child = node.left if node.left else node.right
            if node == self.root:
                self.root = child
            elif node == node.parent.left:
                node.parent.left = child
            else:
                node.parent.right = child
            if child:
                child.parent = node.parent

        # Node has two children    
        else:
            replace = self.__findMin(node.right)
            node.val = replace.val
            self.__deleteHelp(replace)

    def delete(self, x: int):
        node = self.search(x)
        if node:
            self.__deleteHelp(node)

# Main function to demonstrate usage
def main():
    bst = BST()
    
    # Insert nodes into the BST
    nodes_to_insert = [20, 10, 30, 5, 15, 25, 35]
    for value in nodes_to_insert:
        bst.insert(value)
        print(f"Inserted {value} into the BST.")
    
    # Search for a node in the BST
    search_value = 15
    search_result = bst.search(search_value)
    if search_result:
        print(f"Found node with value {search_value}.")
    else:
        print(f"Node with value {search_value} not found.")
    
    # Delete nodes from the BST
    nodes_to_delete = [10, 30, 20]  # Delete some nodes to demonstrate different cases
    for value in nodes_to_delete:
        bst.delete(value)
        print(f"Deleted node with value {value} from the BST.")
    
    # Final tree status (in-order traversal for visualization)
    def inorder_traversal(node):
        if node:
            inorder_traversal(node.left)
            print(node.val, end=' ')
            inorder_traversal(node.right)
    
    print("Final BST (in-order traversal):")
    inorder_traversal(bst.root)
    print()

if __name__ == "__main__":
    main()
