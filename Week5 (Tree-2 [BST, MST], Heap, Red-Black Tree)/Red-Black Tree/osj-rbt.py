class Node:
    def __init__(self, key, parent=None, left=None, right=None, color='black'):
        # 초기화 함수임. 노드의 키, 부모, 왼쪽 자식, 오른쪽 자식, 색상을 설정함.
        self.key = key
        self.parent = parent
        self.left = left
        self.right = right
        self.color = color

class RBT:
    def __init__(self):
        # 트리 초기화하고, NIL 노드 만듦.
        self.Tnil = Node(0, color='black')
        self.root = self.Tnil

    def insert(self, key):
        # 트리에 새로운 노드 삽입함.
        z = Node(key, left=self.Tnil, right=self.Tnil, color='red')

        y = None
        x = self.root

        # 트리에서 삽입 위치 찾음.
        while x != self.Tnil:
            y = x
            if z.key < x.key:
                x = x.left
            else:
                x = x.right

        z.parent = y

        # 부모 노드 설정하고 루트 노드 업데이트함.
        if y is None:
            self.root = z
        elif z.key < y.key:
            y.left = z
        else:
            y.right = z

        # 새로운 노드가 루트인 경우, 색상 검은색으로 설정함.
        if z.parent is None:
            z.color = 'black'
            return

        # 조부모 없는 경우 반환함.
        if z.parent.parent is None:
            return

        # 삽입 후 트리 균형 맞춤.
        self.insert_fix_up(z)

    def delete(self, z):
        # 트리에서 노드 삭제함.
        y = z
        y_original_color = y.color
        if z.left == self.Tnil:
            x = z.right
            self.transplant(z, z.right)
        elif z.right == self.Tnil:
            x = z.left
            self.transplant(z, z.left)
        else:
            y = self.minimum(z.right)
            y_original_color = y.color
            x = y.right
            if y.parent == z:
                x.parent = y
            else:
                self.transplant(y, y.right)
                y.right = z.right
                y.right.parent = y

            self.transplant(z, y)
            y.left = z.left
            y.left.parent = y
            y.color = z.color

        del z

        if y_original_color == 'black':
            self.delete_fix_up(x)

    def preorder(self, node):
        # 전위 순회로 트리 출력함.
        if node != self.Tnil:
            print(node.key, end=" ")
            self.preorder(node.left)
            self.preorder(node.right)

    def inorder(self, node):
        # 중위 순회로 트리 출력함.
        if node != self.Tnil:
            self.inorder(node.left)
            print(node.key, end=" ")
            self.inorder(node.right)

    def postorder(self, node):
        # 후위 순회로 트리 출력함.
        if node != self.Tnil:
            self.postorder(node.left)
            self.postorder(node.right)
            print(node.key, end=" ")

    def search(self, node, key):
        # 키를 이용해 트리에서 노드 검색함.
        if node == self.Tnil or key == node.key:
            return node

        if key < node.key:
            return self.search(node.left, key)
        else:
            return self.search(node.right, key)

    def maximum(self, node):
        # 최대값 가진 노드 찾음.
        while node.right != self.Tnil:
            node = node.right
        return node

    def minimum(self, node):
        # 최소값 가진 노드 찾음.
        while node.left != self.Tnil:
            node = node.left
        return node

    def successor(self, x):
        # 후속자 찾음.
        if x.right != self.Tnil:
            return self.minimum(x.right)

        y = x.parent
        while y != self.Tnil and x == y.right:
            x = y
            y = y.parent
        return y

    def predecessor(self, x):
        # 전임자 찾음.
        if x.left != self.Tnil:
            return self.maximum(x.left)

        y = x.parent
        while y != self.Tnil and x == y.left:
            x = y
            y = y.parent
        return y

    def insert_fix_up(self, z):
        # 삽입 후 트리 균형 맞춤.
        while z.parent.color == 'red':
            if z.parent == z.parent.parent.right:
                y = z.parent.parent.left
                if y.color == 'red':
                    y.color = 'black'
                    z.parent.color = 'black'
                    z.parent.parent.color = 'red'
                    z = z.parent.parent
                else:
                    if z == z.parent.left:
                        z = z.parent
                        self.right_rotate(z)
                    z.parent.color = 'black'
                    z.parent.parent.color = 'red'
                    self.left_rotate(z.parent.parent)
            else:
                y = z.parent.parent.right
                if y.color == 'red':
                    y.color = 'black'
                    z.parent.color = 'black'
                    z.parent.parent.color = 'red'
                    z = z.parent.parent
                else:
                    if z == z.parent.right:
                        z = z.parent
                        self.left_rotate(z)
                    z.parent.color = 'black'
                    z.parent.parent.color = 'red'
                    self.right_rotate(z.parent.parent)
            if z == self.root:
                break
        self.root.color = 'black'

    def left_rotate(self, x):
        # 왼쪽 회전 수행함.
        y = x.right
        x.right = y.left
        if y.left != self.Tnil:
            y.left.parent = x
        y.parent = x.parent
        if x.parent is None:
            self.root = y
        elif x == x.parent.left:
            x.parent.left = y
        else:
            x.parent.right = y
        y.left = x
        x.parent = y

    def right_rotate(self, x):
        # 오른쪽 회전 수행함.
        y = x.left
        x.left = y.right
        if y.right != self.Tnil:
            y.right.parent = x
        y.parent = x.parent
        if x.parent is None:
            self.root = y
        elif x == x.parent.right:
            x.parent.right = y
        else:
            x.parent.left = y
        y.right = x
        x.parent = y

    def delete_fix_up(self, x):
        # 삭제 후 트리 균형 맞춤.
        while x != self.root and x.color == 'black':
            if x == x.parent.left:
                w = x.parent.right
                if w.color == 'red':
                    w.color = 'black'
                    x.parent.color = 'red'
                    self.left_rotate(x.parent)
                    w = x.parent.right
                if w.left.color == 'black' and w.right.color == 'black':
                    w.color = 'red'
                    x = x.parent
                else:
                    if w.right.color == 'black':
                        w.left.color = 'black'
                        w.color = 'red'
                        self.right_rotate(w)
                        w = x.parent.right
                    w.color = x.parent.color
                    x.parent.color = 'black'
                    w.right.color = 'black'
                    self.left_rotate(x.parent)
                    x = self.root
            else:
                w = x.parent.left
                if w.color == 'red':
                    w.color = 'black'
                    x.parent.color = 'red'
                    self.right_rotate(x.parent)
                    w = x.parent.left
                if w.left.color == 'black' and w.right.color == 'black':
                    w.color = 'red'
                    x = x.parent
                else:
                    if w.left.color == 'black':
                        w.right.color = 'black'
                        w.color = 'red'
                        self.left_rotate(w)
                        w = x.parent.left
                    w.color = x.parent.color
                    x.parent.color = 'black'
                    w.left.color = 'black'
                    self.right_rotate(x.parent)
                    x = self.root
        x.color = 'black'

    def transplant(self, u, v):
        # 서브트리 교체함.
        if u.parent is None:
            self.root = v
        elif u == u.parent.left:
            u.parent.left = v
        else:
            u.parent.right = v
        v.parent = u.parent

    def _print(self, root, indent, last):
        # 트리 구조 출력함.
        if root != self.Tnil:
            print(indent, end='')
            if last:
                print("R----", end='')
                indent += "     "
            else:
                print("L----", end='')
                indent += "|    "

            s_color = "RED" if root.color == 'red' else "BLACK"
            print(f"{root.key} ({s_color})")
            self._print(root.left, indent, False)
            self._print(root.right, indent, True)

    def print_tree(self):
        # 트리 출력 시작함.
        if self.root is not None:
            self._print(self.root, "", True)
