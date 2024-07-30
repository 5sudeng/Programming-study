class TreeNode():
    def __init__(self, x: int):
        self.val = x
        self.left = None
        self.right = None

'''
BFT : Breadth First Traversal


DFT : Depth First Traversal
Preorder : visit a node before traversing : file directory listing
Inorder : Traverse -> visit in the middle : convert a binary search tree to a sorted list
Postorder : visit a node after traversing : file size calculation
'''

class Tree():

    def __init__(self, root: TreeNode = None):
        self.root = root

    def visit(self, node : TreeNode):
        print(node.val)
        '''
        사실 visit  할 때, 찾고자 하는 node인지 여부를 확인하면
        BFT-> BFS(search)
        DFT-> DFS(search)
        가 되는 것. 찾아보니 그냥 동일한 개념이랜다.
        '''
    
    #BFT
    def BFT(self):
        if self.root == None:
            return
        q = [self.root] #or q = deque([self.root])

        while q:
            curNode = q.pop(0)

            self.visit(curNode) #
            if curNode.left is not None:
                q.append(curNode.left)
            if curNode.right is not None:
                q.append(curNode.right)


    #DFT
    ## preorder
    def __DFT_preorderHelp(self, curNode):
        if curNode == None: ##  curNode가 leaf 이상으로 넘어갔을 경우, 함수 종료.
            return
        
        #먼저 방문하고, 다음 child 로 넘어가기. child 먼저.
        self.visit(curNode)
        self.__DFT_preorderHelp(curNode.left)
        self.__DFT_preorderHelp(curNode.right)

    def DFT_preorder(self):
        self.__DFT_preorderHelp(self.root) # root부터 시작

    
    ##inorder
    def __DFT_inorderHelp(self, curNode):
        if curNode == None:
            return
        
        self.__DFT_inorderHelp(curNode.left)
        self.visit(curNode)
        self.__DFT_inorderHelp(curNode.right)

    def DFT_inorder(self):
        self.__DFT_inorderHelp(self.root)
    
    ##post order
    def __DFT_postorderHelp(self, curNode):
        if curNode == None:
            return
        
        self.__DFT_postorderHelp(curNode.left)
        self.__DFT_postorderHelp(curNode.right)
        self.visit(curNode)

    def DFT_postorder(self):
        self.__DFT_postorderHelp(self.root)


def main():
    node1 = TreeNode(1)
    node2 = TreeNode(2)
    node3 = TreeNode(3)
    node4 = TreeNode(4)
    node5 = TreeNode(5)


    node1.left = node2
    node1.right = node3
    node2.left = node4
    node2.right = node5


    tree = Tree(node1)

    print("BFT")
    tree.BFT()

    print("DFT")

    print("preorder")
    tree.DFT_preorder()
    print("inorder")
    tree.DFT_inorder()
    print("postorder")
    tree.DFT_postorder()


if __name__ == "__main__":
    main()