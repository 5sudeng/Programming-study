class Node:
    def __init__(self, data, color="RED"):
        self.data = data
        self.color = color
        self.left = None
        self.right = None
        self.parent = None


class RBTree:
    def __init__(self):
        self.NIL = Node(data=None, color="BLACK")  # Sentinel node
        self.root = self.NIL

    def rotate_left(self, x):
        y = x.right
        x.right = y.left
        if y.left != self.NIL:
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

    def rotate_right(self, x):
        y = x.left
        x.left = y.right
        if y.right != self.NIL:
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

    def fix_insert(self, z):
        while z.parent.color == "RED":
            if z.parent == z.parent.parent.left:
                y = z.parent.parent.right
                if y.color == "RED":
                    z.parent.color = "BLACK"
                    y.color = "BLACK"
                    z.parent.parent.color = "RED"
                    z = z.parent.parent
                else:
                    if z == z.parent.right:
                        z = z.parent
                        self.rotate_left(z)
                    z.parent.color = "BLACK"
                    z.parent.parent.color = "RED"
                    self.rotate_right(z.parent.parent)
            else:
                y = z.parent.parent.left
                if y.color == "RED":
                    z.parent.color = "BLACK"
                    y.color = "BLACK"
                    z.parent.parent.color = "RED"
                    z = z.parent.parent
                else:
                    if z == z.parent.left:
                        z = z.parent
                        self.rotate_right(z)
                    z.parent.color = "BLACK"
                    z.parent.parent.color = "RED"
                    self.rotate_left(z.parent.parent)
        self.root.color = "BLACK"

    def insert(self, data):
        z = Node(data)
        z.left = self.NIL
        z.right = self.NIL
        y = None
        x = self.root

        while x != self.NIL:
            y = x
            if z.data < x.data:
                x = x.left
            else:
                x = x.right

        z.parent = y
        if y is None:
            self.root = z
        elif z.data < y.data:
            y.left = z
        else:
            y.right = z

        z.left = self.NIL
        z.right = self.NIL
        z.color = "RED"

        self.fix_insert(z)

    def transplant(self, u, v):
        if u.parent is None:
            self.root = v
        elif u == u.parent.left:
            u.parent.left = v
        else:
            u.parent.right = v
        v.parent = u.parent

    def tree_minimum(self, x):
        while x.left != self.NIL:
            x = x.left
        return x

    def fix_delete(self, x):
        while x != self.root and x.color == "BLACK":
            if x == x.parent.left:
                w = x.parent.right
                if w.color == "RED":
                    w.color = "BLACK"
                    x.parent.color = "RED"
                    self.rotate_left(x.parent)
                    w = x.parent.right

                if w.left.color == "BLACK" and w.right.color == "BLACK":
                    w.color = "RED"
                    x = x.parent
                else:
                    if w.right.color == "BLACK":
                        w.left.color = "BLACK"
                        w.color = "RED"
                        self.rotate_right(w)
                        w = x.parent.right

                    w.color = x.parent.color
                    x.parent.color = "BLACK"
                    w.right.color = "BLACK"
                    self.rotate_left(x.parent)
                    x = self.root
            else:
                w = x.parent.left
                if w.color == "RED":
                    w.color = "BLACK"
                    x.parent.color = "RED"
                    self.rotate_right(x.parent)
                    w = x.parent.left

                if w.right.color == "BLACK" and w.left.color == "BLACK":
                    w.color = "RED"
                    x = x.parent
                else:
                    if w.left.color == "BLACK":
                        w.right.color = "BLACK"
                        w.color = "RED"
                        self.rotate_left(w)
                        w = x.parent.left

                    w.color = x.parent.color
                    x.parent.color = "BLACK"
                    w.left.color = "BLACK"
                    self.rotate_right(x.parent)
                    x = self.root
        x.color = "BLACK"

    def delete(self, data):
        z = self.search_tree_helper(self.root, data)
        if z == self.NIL:
            print("Value not found in the tree.")
            return

        y = z
        y_original_color = y.color
        if z.left == self.NIL:
            x = z.right
            self.transplant(z, z.right)
        elif z.right == self.NIL:
            x = z.left
            self.transplant(z, z.left)
        else:
            y = self.tree_minimum(z.right)
            y_original_color = y.color
            x = y.right
            if y != z.right:
                self.transplant(y, y.right)
                y.right = z.right
                y.right.parent = y
            self.transplant(z, y)
            y.left = z.left
            y.left.parent = y
            y.color = z.color

        if y_original_color == "BLACK":
            self.fix_delete(x)

    def search_tree_helper(self, root, key):
        if root == self.NIL or root.data == key:
            return root

        if key < root.data:
            return self.search_tree_helper(root.left, key)
        else:
            return self.search_tree_helper(root.right, key)

    def search(self, key):
        current = self.search_tree_helper(self.root, key)
        if current != self.NIL:
            print(f"Found node with key: {key}")
        else:
            print(f"Node with key {key} not found")

# Example usage
if __name__ == "__main__":
    tree = RBTree()

    tree.insert(10)
    tree.insert(20)
    tree.insert(30)
    tree.insert(15)
    tree.insert(25)

    tree.search(15)
    tree.delete(15)
    tree.search(15)
