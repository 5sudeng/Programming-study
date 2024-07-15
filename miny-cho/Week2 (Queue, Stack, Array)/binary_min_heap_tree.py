# 지피티는 진짜 유명한 번역기임

import math

# Node class for tree-based implementation
class Node:
    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None
        self.parent = None

# MinHeap class using tree-based implementation
class MinHeap:
    def __init__(self):
        self.root = None
        self.last_node = None
        self.heap_size = 0

    def getMin(self):
        return self.root

    def printHeap(self):
        if not self.root:
            print("Empty heap")
            return

        q = [self.root]
        print("Print Heap:", end=" ")
        while q:
            node = q.pop(0)
            print(node.val, end=" ")
            if node.left:
                q.append(node.left)
            if node.right:
                q.append(node.right)
        print()

    def swap(self, a, b):
        a.val, b.val = b.val, a.val

    def enqueue(self, k):
        new_node = Node(k)

        if not self.root:
            self.root = new_node
            self.last_node = new_node
        else:
            path = self.heap_size + 1
            bit = 1 << (int(math.log2(path)))

            temp = self.root
            while bit > 1:
                bit >>= 1
                if path & bit:
                    if not temp.right:
                        break
                    temp = temp.right
                else:
                    if not temp.left:
                        break
                    temp = temp.left

            new_node.parent = temp
            if not (path & 1):
                temp.left = new_node
            else:
                temp.right = new_node
            self.last_node = new_node

            # Restore heap property
            curr_node = self.last_node
            while curr_node.parent and curr_node.parent.val > curr_node.val:
                self.swap(curr_node, curr_node.parent)
                curr_node = curr_node.parent

        self.heap_size += 1

    def dequeue(self):
        if not self.root:
            return

        if self.root == self.last_node:
            self.root = None
            self.last_node = None
            self.heap_size -= 1
            return

        self.swap(self.root, self.last_node)
        if self.last_node.parent.left == self.last_node:
            self.last_node.parent.left = None
        else:
            self.last_node.parent.right = None
        del self.last_node

        path = self.heap_size - 1
        bit = 1 << (int(math.log2(path)))

        temp = self.root
        while bit > 1:
            bit >>= 1
            if path & bit:
                if not temp.right:
                    break
                temp = temp.right
            else:
                if not temp.left:
                    break
                temp = temp.left

        self.last_node = temp
        self.heap_size -= 1

        # Restore heap property
        if not self.root:
            return

        curr_node = self.root
        while curr_node.left or curr_node.right:
            smaller = None
            if curr_node.left and curr_node.right:
                smaller = curr_node.left if curr_node.left.val < curr_node.right.val else curr_node.right
            elif curr_node.left:
                smaller = curr_node.left
            else:
                smaller = curr_node.right

            if smaller and curr_node.val > smaller.val:
                self.swap(curr_node, smaller)
                curr_node = smaller
            else:
                break
