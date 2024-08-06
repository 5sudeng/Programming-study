class Node:
    def __init__(self, key):
        self.key = key
        self.left = None
        self.right = None
        self.parent = None

class BST:
    def __init__(self, root):
        self.root = root

    def search(self,data):
        curr = self.root
        height = 0

        while(curr):
            if (data == curr.key):
                print(f"{data} is at height {height}")
                return
            
            #더 작으면 left subtree
            elif (data < curr.key):
                curr = curr.left
                height+=1
            #더 크면 right subtree
            else:
                curr = curr.right
                height +=1
            
        # 탈출 : 없는 경우
        print("Not exist")

    def IsKey(self, data) -> Node:
        curr = self.root
     
        
        while(curr and data !=curr.key):
            if (data < curr.key):
                curr = curr.left
            else:
                curr = curr.right

        #없다면 None, 있다면 Node 할 것.
        return curr

    def insert(self,data):
        x = self.root # node being compared with z
        y = None  ##  y will be parent of z
        
        z = Node(data) #being inserted
        z.parent = None

        # x를 순회하면서,z를 넣을 위치를 찾고, y = x 외부 저장하면서 찾게 되는 경우 이어주기
        while(x is not None): # 찾을 위치 찾기(넣을 위치의  parent찾기)
            y = x
            if(z.key < x.key):
                x = x.left
            else:
                x = x.right

        z.parent = y #찾고 나서 순회 종료.
        if (y == None): #parent가 null(leafnode)이다? 그럼 root로
            self.root = z
        elif (z.key < y.key):
            y.left = z
        else:
            y.right = z
        

    def delete(self,data):
        '''
        1. no child : just delete
        2. one child : replace with z's child
        3. two child : 
            3-1 : replace with min from left subtree
            3-2 : replace with max from right subtree
        '''

        z = self.IsKey(data) # 먼저 찾는다.
        if (z is None):
            return #없는 경우, 그냥 종료

        #case1 or case 2
        #child가 없어도 None으로 대체하는 거라 상관없음.
        if (z.left is None):
            self.Transplant(z, z.right)
        elif (z.right is None):
            self.Transplant(z, z.left)

        else:## 둘다 아닌 경우니니까, 둘다 있는 경우
            y = self.tree_minimum(z.right) # 3-2 max from right subtree

            if (y != z.right) :# 바로 direct child가 아닌 경우
                #y의 하단 내용도 바꿔야 함.
                self.Transplant(y, y.right)
                y.right = z.right
                y.right.parent = y
            
            #replace z with y
            self.Transplant(z, y)
            
            #나머지 부분 잇기
            y.left = z.left
            y.left.parent = y

        

    def tree_minimum(self, x : Node)-> Node:
        # find minimum : keep traversal left
        while (x.left):
            x =x.left
        return x
    
    def tree_maximum(self,x : Node)-> Node:
        #find maximum : keep travaersal right
        while(x.right):
            x = x.right
        return x
    
    def Transplant(self, u, v): # replace subtree from u to v(원래 u가 있던 것을 v로 바꾸는 작업)
        if (u.parent is None):
            self.root = v
        elif u == u.parent.left:
            u.parent.left = v
        else:
            u.parent.right = v
        
        if v is not None: #v가 None일수도 있으니까
            v.parent = u.parent




def main():
    # Initialize the BST with the root node
    bst = BST(Node(10))

    # Insert nodes into the BST
    bst.insert(5)
    bst.insert(15)
    bst.insert(2)
    bst.insert(7)
    bst.insert(12)
    bst.insert(17)
    bst.insert(1)
    bst.insert(3)
    bst.insert(6)
    bst.insert(8)
    bst.insert(11)
    bst.insert(13)
    bst.insert(16)
    bst.insert(18)

    # Test search function
    print("Search Test Cases:")
    bst.search(10)  # Should be at height 0
    bst.search(5)   # Should be at height 1
    bst.search(15)  # Should be at height 1
    bst.search(1)   # Should be at height 3
    bst.search(8)   # Should be at height 3
    bst.search(18)  # Should be at height 3
    bst.search(20)  # Should print "Not exist"

    # Test IsKey function
    print("\nIsKey Test Cases:")
    print(bst.IsKey(10) is not None)  # Should be True
    print(bst.IsKey(5) is not None)   # Should be True
    print(bst.IsKey(20) is None)      # Should be True

    # Test delete function
    print("\nDelete Test Cases:")
    bst.delete(1)  # No children
    bst.delete(17) # One child
    bst.delete(5)  # Two children
    bst.delete(10) # Root with two children

    # Verify delete operations by searching
    bst.search(1)  # Should print "Not exist"
    bst.search(17) # Should print "Not exist"
    bst.search(5)  # Should print "Not exist"
    bst.search(10) # Should print "Not exist"

    bst.search(3)  # Should still be in tree
    bst.search(6)  # Should still be in tree
    bst.search(15) # Should still be in tree
    bst.search(13) # Should still be in tree

if __name__ == "__main__":
    main()
