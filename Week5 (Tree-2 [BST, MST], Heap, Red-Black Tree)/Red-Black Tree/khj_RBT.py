'''
1. 모든 Node의 색상은 Red or Black
2. 루트 Node는 무조건 Black
3. 모든 Leaf 노드(Nil 노드라고 한다)는 무조건 Black
4. Red 노드의 자식 노드 양쪽은 언제나 Black (== 빨간색 노드가 연속으로 나올 수 없다)
5. 어떤 노드에서 Leaf 노드까지의 경로들은 모두 같은 수의 Black 노드를 포함하고 있다.
'''

#이진 트리 구현한 노드에서 color 값만 추가됨
class RBNode:
    def __init__(self, key) :
        self.key = key
        self.color = "RED"

        self.left = None
        self.right = None
        self.parent = None

    def __str__(self):
        return str(self.key)
    

# EXT 라는 멤버를 두어 RBNode 인스턴스 하나를 참조하게 함. 외부 노드이므로 black
class RedBlackTree:
    def __init__(self):
        self.__root = None  #루트 노드
        self.__EXT = RBNode(None)  # 외부 노드로 사용할 특별한 노드 생성
        self.__EXT.color = "BLACK"  # 외부 노드는 항상 black

    def get_root(self):
        return self.__root
    
    def preorder_traverse(self, cur, func, *args, **kwargs):
        if cur == self.__EXT:  #외부 노드에 도달하면 반환
            return   
        
        func(cur, *args, **kwargs)     # 현재 노드에 대한 함수 실행
        self.preorder_traverse(cur.left, func, *args, **kwargs)
        self.preorder_traverse(cur.right, func, *args, **kwargs)


    #함수 오름차순 방문
    def inorder_traverse(self, cur, func, *args, **kwargs):
        if cur == self.__EXT:
            return
        self.inorder_traverse(cur.left, func, *args, **kwargs)
        func(cur, *args, **kwargs)
        self.inorder_traverse(cur.right, func, *args, **kwargs)


    # 트리 높이 계산
    def tree_height(self, node):
        if node == self.__EXT:
            return -1  # 외부 노드는 높이에 포함되지 않음
        left_height = self.tree_height(node.left)
        right_height = self.tree_height(node.right)
        return max(left_height, right_height) + 1


    # 트리 노드 개수 계산
    def node_count(self, node):
        if node == self.__EXT:
            return 0
        return 1 + self.node_count(node.left) + self.node_count(node.right)



    # 특정 노드의 black height 계산
    def __black_height(self, node):
        if node == self.__EXT:
            return 0
        left_black_height = self.__black_height(node.left)
        right_black_height = self.__black_height(node.right)
        if node.color == "BLACK":
            return max(left_black_height, right_black_height) + 1
        else:
            return max(left_black_height, right_black_height)




    #왼쪽으로 회전
    '''
    회전 기준 노드 x의 오른쪽 자식 y가 새로운 부모 노드가 됩니다.
    x는 y의 왼쪽 자식이 됩니다.
    y의 왼쪽 자식 T2는 x의 오른쪽 자식이 됩니다.
    '''
    def __left_rotate(self, n):
            r = n.right #n의 오른쪽 자식
            l = r.left #r의 왼쪽 자식
  
            l.parent = n   #l의 부모를 n으로 설정
            n.right = l    #l은 n의 오른쪽 자식


            if n == self.__root:
                self.__root = r          #n이 루트 노드인 경우 r을 새로운 루트로 설정
            elif n.parent.left == n:
                n.parent.left = r
            else:
                n.parent.right = r
            
            r.parent = n.parent     # r의 부모를 n의 부모로 설정
            r.left = n       # r의 왼쪽 자식을 n으로 설정
            n.parent = r        




    # 오른쪽으로 회전
    '''
    회전 기준 노드 x의 왼쪽 자식 y가 새로운 부모 노드가 됩니다.
    x는 y의 오른쪽 자식이 됩니다.
    y의 오른쪽 자식 T2는 x의 왼쪽 자식이 됩니다.
    '''
    def __right_rotate(self, n):
            l = n.left
            r = l.right

            r.parent = n
            n.left = r

            if n == self.__root:
                self.__root = r
            elif n.parent.left == n:
                n.parent.left = l
            else:
                n.parent.right = l

            l.parent = n.parent
            l.right = n
            n.parent = l



    # insert 연산 : while 문 이후 insert_fix 연산 수행하여 노드의 재배치 수행
    def insert(self, key):
            new_node = RBNode(key)
            new_node.left=self.__EXT
            new_node.right=self.__EXT

            cur = self.__root

            if not cur:
                self.__root = new_node          # 트리가 비어있으면 새 노드를 루트로 설정
                self.__root.color = "BLACK"
                return

            while True:
                parent = cur
                if key < cur.key:
                    parent.left = new_node
                    new_node.parent = parent
                    break
                else:
                    cur = cur.right
                    if cur == self.__EXT:
                        parent.right = new_node
                        new_node.parent = parent
                        break

            # 삽입 후 균형을 맞추기 위해 수정
            self.__insert_fix(new_node)



    def __insert_fix(self, n):
            pn = gn = un = None
            pn = n.parent #n의 부모

            while pn != None and pn.color == "RED":  #pn의 color가 red면 반드시 조부모 존재
                gn = pn.parent  #gn은 n의 조부모

                if gn.left == pn:
                    un = gn.right  #pn의 형제

                    if un.color == "RED":   
                        gn.color = "RED"
                        pn.color = un.color = "BLACK"

                        n = gn
                        pn = n.parent

                    else:
                        if pn.right == n:
                            self.__left_rotate(pn)  # 부모를 기준으로 왼쪽 회전
                            n, pn = pn, n

                        pn.color, gn.color = gn.color, pn.color

                    self.__right_rotate(gn)
                
                
                else:
                    un = gn.left
                    if un.color == "RED":
                        gn.color = "RED"
                        pn.color = un.color = "BLACK"

                        n = gn
                        pn = n.parent

                    else:     # 부모가 조부모의 오른쪽 자식인 경우
                        # n이 부모의 왼쪽 자식인 경우
                        if pn.left == n:
                            self.__right_rotate(pn)

                        # n이 부모의 오른쪽 자식인 경우    
                        n, pn = pn, n
                        pn.color, gn.color = gn.color, pn.color
                        self.__left_rotate(gn)

            self.__root.color = "BLACK" #루트 노드는 항상 black


    def search(self, key):
        cur = self.__root
        while cur != self.__EXT and cur.key != key:
            if key < cur.key:
                cur = cur.left
            else:
                cur = cur.right
        return cur



    def delete(self, key):
        node = self.search(key)
        if node == self.__EXT:
            return  # 노드가 없으면 삭제할 것이 없음

        y = node
        y_original_color = y.color
        if node.left == self.__EXT:
            x = node.right
            self.__transplant(node, node.right)
        elif node.right == self.__EXT:
            x = node.left
            self.__transplant(node, node.left)
        else:
            y = self.__minimum(node.right)
            y_original_color = y.color
            x = y.right
            if y.parent == node:
                x.parent = y
            else:
                self.__transplant(y, y.right)
                y.right = node.right
                y.right.parent = y
            self.__transplant(node, y)
            y.left = node.left
            y.left.parent = y
            y.color = node.color
        if y_original_color == "BLACK":
            self.__delete_fix(x)



    def __delete_fix(self, x):
        while x != self.__root and x.color == "BLACK":
            if x == x.parent.left:
                w = x.parent.right
                if w.color == "RED":
                    w.color = "BLACK"
                    x.parent.color = "RED"
                    self.__left_rotate(x.parent)
                    w = x.parent.right
                if w.left.color == "BLACK" and w.right.color == "BLACK":
                    w.color = "RED"
                    x = x.parent
                else:
                    if w.right.color == "BLACK":
                        w.left.color = "BLACK"
                        w.color = "RED"
                        self.__right_rotate(w)
                        w = x.parent.right
                    w.color = x.parent.color
                    x.parent.color = "BLACK"
                    w.right.color = "BLACK"
                    self.__left_rotate(x.parent)
                    x = self.__root
            else:
                w = x.parent.left
                if w.color == "RED":
                    w.color = "BLACK"
                    x.parent.color = "RED"
                    self.__right_rotate(x.parent)
                    w = x.parent.left
                if w.right.color == "BLACK" and w.left.color == "BLACK":
                    w.color = "RED"
                    x = x.parent
                else:
                    if w.left.color == "BLACK":
                        w.right.color = "BLACK"
                        w.color = "RED"
                        self.__left_rotate(w)
                        w = x.parent.left
                    w.color = x.parent.color
                    x.parent.color = "BLACK"
                    w.left.color = "BLACK"
                    self.__right_rotate(x.parent)
                    x = self.__root
        x.color = "BLACK"



    def __transplant(self, u, v):
        if u.parent is None:
            self.__root = v
        elif u == u.parent.left:
            u.parent.left = v
        else:
            u.parent.right = v
        v.parent = u.parent


    def __minimum(self, node):
        while node.left != self.__EXT:
            node = node.left
        return node

    def minimum(self):
        return self.__minimum(self.__root)

    def __maximum(self, node):
        while node.right != self.__EXT:
            node = node.right
        return node

    def maximum(self):
        return self.__maximum(self.__root)



    def print_node(self, rbn):
        if rbn:
            print("node : {}, ".format(rbn.key), end=" ")
            if rbn.color == "RED":
                print("color : RED, ", end=" ")
            else:
                print("color : BLACK, ", end=" ")
            if rbn.left:
                print("left : {}, ".format(rbn.left.key), end=" ")
            if rbn.right:
                print("right : {}, ".format(rbn.right.key), end=" ")
            if rbn.parent:
                print("parent : {}".format(rbn.parent.key), end=" ")
            print()




if __name__ == "__main__":
    print('*'*100)
    rbt = RedBlackTree()

    for i in range(10):
        rbt.insert(i)

    rbt.preorder_traverse(rbt.get_root(), rbt.print_node)
    print('*'*100)

    # 삭제 테스트
    rbt.delete(3)
    rbt.delete(7)

    rbt.preorder_traverse(rbt.get_root(), rbt.print_node)
    print('*'*100)


