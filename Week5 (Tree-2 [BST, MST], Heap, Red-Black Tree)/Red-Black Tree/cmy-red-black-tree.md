# Red-Black Tree

![RBT](https://www.google.com/url?sa%3Di%26url%3Dhttps%3A%2F%2Fwalkccc.me%2FCLRS%2FChap13%2F13.1%2F%26psig%3DAOvVaw2v7FOL1bnx77xcXv1sFLtM%26ust%3D1722492350332000%26source%3Dimages%26cd%3Dvfe%26opi%3D89978449%26ved%3D0CBEQjRxqFwoTCICysJfO0IcDFQAAAAAdAAAAABAI)
- BST with color bit, **RED** or **BLACK** &rarr; approximately balanced
- Red-Black properties
    1. Every node is either **red** or **black**
    2. The root is **black**
    3. Every leaf `NIL` is **black**
    4. If a node is **red**, then both its children are **black**        
    5. For each node, all simple paths from the node to descendant leaves contain the same number of **black** nodes
    &rarr; If a **red** node has any child, it must have **two** children and they must be **black**
    &rarr; If a **black** node has only one child, that child must be a **red** node with its children `NIL`

- Operations
    - `LeftRotate(T, x)`, `RightRotate(T, x)`
    - Insertion: `Insert(T, z)`, `InsertFixup(T, z)`
    - `Transplant(T, u, v)`
    - Deletion: `Delete(T, z)`, `DeleteFixup(T, x)`

## Pseudocode
### Insertion

`LEFT-ROTATE(T, x)`
```
y = x.right
x.right = y.left
if y.left != T.nil
    y.left.p = x
y.p = x.p
if x.p == T.nil
    T.root = y
else if x == x.p.left
    x.p.left = y
else
    x.p.right = y
y.left = x
x.p = y
```

`RB-INSERT(T, z)`
```
x = T.root
y = NIL
while x != NIL
    y = x
    if z.key < x.key
        x = x.left
    else
        x = x.right
z.p = y
if y == NIL
    T.root = z
else if z.key < y.key
    y.left = z
else
    y.right = z
z.left = T.nil
z.right = T.nil
z.color = RED

RB-INSERT-FIXUP(T, z)
```

`RB-INSERT-FIXUP(T, z)`
```
while z.p.color == RED
    if z.p == z.p.p.left
        y = z.p.p.left
        if y.color == RED // Case 1
            z.p.color = BLACK
            y.color = BLACK
            z.p.p.color = RED
            z = z.p.p
        else
            if z == z.p.right // Case 2
                z = z.p
                LEFT-ROTATE(T, z)
            z.p.color = BLACK // Case 3
            z.p.p.color = RED
            RIGHT-ROTATE(T, z.p.p)
    else 
        // “right” and “left” exchanged
T.root.color = BLACK
```

### Deletion

`TRNASPLANT(T, u, v)`
```
if u.p == T.NIL
    T.root = v
else if u == u.p.left
    u.p.left = v
else
    u.p.right = v
v.p = u.p
```

`RB-DELETE(T, z)`
```
y = z
y-original-color = y.color
if z.left == T.NIL
    TRANSPLANT(T, z, z.right)
else if z.right == T.NIL
    TRANSPLANT(T, z, z.left)
else
    y = TREE-MIINIMUM(z.right)
    y-original-color = y.color
    x = y.right
    if y != z.right
        TRANSPLANT(T, y, y.right)
        y.right = z.right
        y.right.p = y
    TRANSPLANT(T, z, y)
    y.left = z.left
    y.left.p = y
    y.color = z.color
if y-original-color == BLACK
    RB-DELETE-FIXUP(T, x)
```

`RB-DELETE-FIXUP(T, x)`
```
while x != T.root && x.color == BLACK
    if x == x.p.left
        w = x.p.right
        if w.color == RED // Case 1
            w.color = BLACK
            x.p.color = RED
            LEFT-ROTATE(T, x.p)
            w = x.p.right
        if w.left.color == BLACK & w.right.color == BLACK or (!w.left && !w.right) // Case 2
            w.color = RED
            x = x.p
        else
            if w.right.color == BLACK // Case 3
                w.left.color = BLACK
                w.color = RED
                RIGHT-ROTATE(T, w)
                w = x.p.right
            w.color = x.p.color // Case 4
            x.p.color = BLACK
            w.right.color = BLACK
            LEFT-ROTATE(T, x.p)
            x = T.root
    else 
        // “right” and “left” exchanged
x.color = BLACK
```

