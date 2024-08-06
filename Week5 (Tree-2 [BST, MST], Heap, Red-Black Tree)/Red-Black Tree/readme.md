# RBT : Overview

- node가 red or black color를 갖게 함으로써 어떤 path가 다른 path의 2배의 길이가 될 수 없도록 강제함
  ⇒ Approximately balanced

<aside>
💡 **Red-Black Properties**

1. 모든 노드는 red or black
2. root는 black
3. 모든 leaf(NIL)은 black
4. 만약 node가 red면 두 children은 black 이어야 함
5. 모든 node에서 simple path 상에 있는 black node의 수가 같아야 함
</aside>

### Not Completely Balanced

- 꽤 balanced 되어 있지만, completely balanced는 아님
- black node들은 balanced 되어 있음
- red node들은 spread out 되어 있어서 많은 것을 망침
- node를 insert 하거나, delete 할 때 rotation을 활용해서 property를 유지함

# RBT가 만족해야 하는 조건들

- **Order Invariant** : Tree는 ordered 되어있어야 함. (binary search tree니까)
- **Height Invariant** : leaf에서 root로 가는 모든 path에서 black node의 개수는 같아야 함.
- **Color Invariant** : red node의 부모는 black

⇒ insertrion & search 에서 O(lgn)을 보장함

- 만약 red node가 child가 있다면, 5번 조건을 만족하기 위해 자녀가 2명이어야 하고, 4번 조건에 의해 둘 다 black이어야 한다.
- 만약 black node가 하나의 child만 갖는다면, 그 child는 children으로 NIL을 갖는 red node여야함.
  → black이면 5번 조건이 안맞으니까!

# RBT : Operations

## Insertion

### **pseudo code**

```cpp
TREE-INSERT(T,z)
x = T.root // z와 compare할 node
y = NIL // z의 parent가 될 것

while x != NIL // x가 null이 아닌동안 계속
	y = x
	if z.key < x.key
		x = x.left
	else
		x = x.right

z.p = y // 새로운 node를 y의 자식에 insert
if y == NIL // y가 null인 경우. 즉, 현재 tree가 비어있는 경우
	T.root = z // z가 root가 된다.
else if z.key < y.key // 원래 tree가 비어있지 않은 경우
	y.left = z
else
	y.right = z

z.left = NIL // 삽입 후 leaf node가 되니, 양쪽 자식을 nil로 설정
z.right = NIL
z.color = RED // 삽입된 z의 색은 red로
RB-Insert_Fixup(T,z)
```

- T.nill
  - T의 nil 은 sentinel로, node x 의 NIL child를 마치 ordinary node인 것처럼 취급할 수 있게 해줌
  - 모든 leaves들은 root의 parent임
    ![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/4ddcc5c0-5be8-411b-afd8-e036e70387be/a317e950-13eb-4c51-8bd7-1cd9ce9881af/Untitled.png)
- Left rotation
  ```cpp
  LEFT-ROTATE(T,x)
  y = x.right
  x.right = y.left // y의 left subtree를 x의 right가 상속받음
  if y.left != T.nil
  	y.left.p = x // y의 left subtree들의 parent를 x로 설정해줌
  y.p = x.p // y의 parent를 x의 parent로 이어줌
  if x.p == T.nil // x가 root였다면
  	T.root = y // y가 root가 됨
  else if x == x.p.left // x가 left child 였다면
  	x.p.left = y // y는 left child가 됨
  else
  	x.p.right = y // x가 right child 였다면
  y.left = x // y는 right child가 됨
  x.p = y
  ```
  ![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/4ddcc5c0-5be8-411b-afd8-e036e70387be/785b3caa-0a5f-4774-a7f5-0f1833307cce/Untitled.png)

### **Insertion 이후 RBT의 5가지 조건을 만족하는지 확인**

1. 모든 노드는 red or black → `성립`
2. root는 black → `만약 z가 root라면 위반, 아니면 성립`
3. 모든 leaf(NIL)은 black → `성립`
4. 만약 node가 red면 두 children은 black 이어야 함 → `새로 삽입한 z의 부모 y가 black이면 상관 없는데, red면 red-red라서 조건 위반`
5. 모든 node에서 simple path 상에 있는 black node의 수가 같아야 함 → `성립`

### **RB-Insert_Fixup이 필요한 경우**

1. 조건2 위반 - z가 root이면서 red인 경우
2. 조건4 위반 - z와 그 부모 z.p가 둘 다 red인 경우

⇒ 종료 조건 : 부모노드 z.p가 black이면 종료. 조건2가 위반인 경우, z를 그냥 black으로 변경해주면 끝남

### **CASE별 설명**

**z.p가 z.p.p의 left child인 경우에 대해 설명 (right child면 좌우 바꾸면 됨)**

- **CASE1) z의 삼촌 y가 red인 경우**
  ![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/4ddcc5c0-5be8-411b-afd8-e036e70387be/3dc9eb1d-5dd2-4bc0-a4fd-6163836a3ab1/Untitled.png)
  - B노드를 새롭게 삽입 (z) → A의 오른쪽 자식일수도, 왼쪽 자식일 수도 있음
  - **A, B가 red-red 충돌이 발생하고 있고 z의 삼촌 y(D)인 red인 상황**
    - `solution` : A와 D를 black으로, 할아버지 C는 red로 변경
    - `발생 가능한 문제` : C가 red가 되면 c.p와 red-red 충돌이 발생할 수 있음
    - 다만, A,B의 문제가 2칸 위인 C와 C.p 간의 문제로 이동했음을 알 수 있음. 이렇게 쭉 root까지 이동하게 되면 결국 마지막에는 root의 색만 그냥 black으로 변경해주면 끝남
    - 조건 5인 black height도 바뀌지 않음. 색 변경 전이나 후 모두 NIL 노드까지 가는 경로의 black node의 수는 동일함. C위에서 오던 중이라고 생각하고 아래로 내려가면서 black의 수를 세어보면 똑같음
- **CASE2, 3) z의 삼촌 y가 Black인 경우**
  ![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/4ddcc5c0-5be8-411b-afd8-e036e70387be/2705e8c1-e3e1-4526-abac-95dc6d613b71/Untitled.png)
  - 삼촌 y는 NIL도 가능하기 때문에 검정 동그라미로 표현하지는 않음. 어쨋든 black이라고 생각하면 됨
  - **case2) z가 오른쪽 자식인 경우**
    - z.p에 대해 left-rotation 한 후 원래 z.p인 A를 z로 변경 → 이후 case3으로 진행
  - **case3) z가 왼쪽 자식인 경우**
    - z.p인 B를 black, z.p.p인 C를 red로 바꿈. 이후 z.p.p인 C에 대해 right-rotation을 진행 ⇒ 최종결과가 나옴

### **RB-Insert_Fixup pseudo code**

```cpp
RB-INSERT-FIXUP(T,z)
while z.p.color == RED // z의 부모가 RED라서 RED-RED 충돌
	if z.p == z.p.p.left // z가 부모의 왼쪽 자식이면
		y = z.p.p.right // y는 z의 uncle
		if y.color == RED // uncle이 red면 (case1)
			z.p.color = BLACK
			y.color = BLACK
			z.p.p.color = RED
			z = z.p.p // z를 update
		else
			if z == z.p.right // case 2
				z = z.p
				LEFT - ROTATE(T,z)
			z.p.color = BLACK
			z.p.p.color = RED // case 3
			RIGHT-ROTATE(T, z.p.p)
	else // z의 부모가 오른쪽 자식이면
		y = z.p.p.left
		if y.color == RED
			z.p.color = BLACK
			y.color = BLACK
			z.p.p.color = RED
			z = z.p.p
		else
			if z == z.p.left
				z = z.p
				RIGHT-ROTATE(T,z)
			z.p.color = BLACK
			z.p.p.color = RED
			LEFT-ROTATE(T, z.p.p)
T.root.color = BLACK
```

### **예시**

![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/4ddcc5c0-5be8-411b-afd8-e036e70387be/11e43b01-ab1d-4ee5-85b7-8ed864ad7337/Untitled.png)

### **시간복잡도**

- case1의 경우 z가 2 level만큼 상승, case2, 3는 상수시간이 걸림 ⇒ 트리의 높이에 비례하는 시간이 걸림
- 최악의 경우, case1이 계속 반복되어 root까지 red-red 충돌을 올려야 할 수도 있음. 최종적으로 root에 도달하면 root의 색만 black으로 변경해주면 됨. 따라서 최악의 경우는 높이에 해당함.
- 시간복잡도 : O(logN)

## DELETE

**pseudo code**

```python
def transplant(self, u, v):
	if u.p == None:
		self.root = v
	elif u == u.p.left :
		u.p.left = v
	else :
		u.p.right = v
	v.p = u.p
```

```cpp
RB-DELETE(T,Z)
y = z
y-original-color = y.color
if z.left == T.nil // z가 오른자식만 갖는 경우
	x = z.right
	RB-TRANSPLANT(T, z, z.right) // z를 z의 right child로 바꿈
else if z.right == T.nil // z가 왼쪽자식만 갖는 경우
	x = z.left
	RB-TRANSPLANT(T, z, z.left) // z를 z의 left child로 바꿈
else y = TREE-MINIMUM(z.right) // z가 자식이 2명인 경우
	y-original-color = y.color // y의 원래 color를 저장해두는 것이 중요
	x = y.right
	if y != z.right  // is y father down the tree?
		RB-TRANSPLANT(T, y, y.right) // replace y by its right child
		y.right = z.right // z's right child becomds
		y.right.p = y // y's right child
	else x.p = y // in case x is T.nill
		RB-TRANSPLANT(T, z, y) // replace z by its successor y
		y.left = z.left // and give z's left child to y
		y.left.p = y // which had no left child
		y.color = z.color // y의 원래 color가 red인 경우
if y-original-color == BLACK
	RB-DELETE-FIXUP(T, x) // fixup을 부를 때 x를 기준으로 부름
```

- left child가 NIL인 경우
  ![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/4ddcc5c0-5be8-411b-afd8-e036e70387be/5aef2de1-00a7-440a-9566-7991b6d54771/Untitled.png)
  ![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/4ddcc5c0-5be8-411b-afd8-e036e70387be/f0cf5a71-a74e-4321-b5bb-a88b8d0fc0dc/Untitled.png)
  ![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/4ddcc5c0-5be8-411b-afd8-e036e70387be/12c2b810-2b91-48cc-85df-40951cdc4cb5/Untitled.png)
- right child가 NIL인 경우
  ![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/4ddcc5c0-5be8-411b-afd8-e036e70387be/8c418bd3-b262-45c0-bcd9-6f3c134a3d30/Untitled.png)
  ![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/4ddcc5c0-5be8-411b-afd8-e036e70387be/3d13cf4f-0728-4ae2-9d16-f206105e9d95/Untitled.png)
  ![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/4ddcc5c0-5be8-411b-afd8-e036e70387be/e30734e6-a426-4477-be9f-228efff20274/Untitled.png)
- child가 둘 다 있는 경우
  ![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/4ddcc5c0-5be8-411b-afd8-e036e70387be/61ac019a-f0c6-4e6a-8c83-346d2df6c4e7/Untitled.png)
  ![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/4ddcc5c0-5be8-411b-afd8-e036e70387be/6fca574d-42e2-4692-ae2c-208733854dbc/Untitled.png)
  ![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/4ddcc5c0-5be8-411b-afd8-e036e70387be/7a090bec-26ff-4911-b5cb-444228083509/Untitled.png)
  ![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/4ddcc5c0-5be8-411b-afd8-e036e70387be/c84fa226-e8b1-43ff-917e-98c787336873/Untitled.png)
  ![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/4ddcc5c0-5be8-411b-afd8-e036e70387be/b3f324e2-c8de-4faa-8cea-fb6b0d1d89fc/Untitled.png)
  ![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/4ddcc5c0-5be8-411b-afd8-e036e70387be/db26373d-6a81-48af-97c8-4d7529711fe5/Untitled.png)
  ![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/4ddcc5c0-5be8-411b-afd8-e036e70387be/471f1857-d868-4d39-8fde-8ca418d0d2a7/Untitled.png)
  ![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/4ddcc5c0-5be8-411b-afd8-e036e70387be/3c047742-fcc7-432c-b5a6-3bc73f1b2c28/Untitled.png)
  ![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/4ddcc5c0-5be8-411b-afd8-e036e70387be/ba798fc1-5d95-4c5e-b06c-82f2b4169712/Untitled.png)

### **RB-DELETE-Fixup을 호출해야 하는 경우**

1. **삭제된 노드가 RED라면 그냥 종료**
   (RED는 연속할 수 없으므로, RED의 자식과 부모는 BLACK일 것이며, 따라서 중간의 RED를 지워도 BALCK-BLACK의 연속은 문제되지 않음)
2. **삭제된 노드가 BLACK이었다면 RB-DELETE-Fixup을 호출해야 함**

   ![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/4ddcc5c0-5be8-411b-afd8-e036e70387be/1e5e9842-8e75-4947-9da3-7cfcf9f6b2f2/Untitled.png)

   - 중간의 BLACK 노드를 삭제하면 RED-RED 충돌이 발생하여 조건 4를 위반
   - 중간의 BLACK 하나가 사라졌으므로 조건 5도 위반

### **Deletion 이후 RBT의 5가지 조건을 만족하는지 확인**

y : 삭제할 노드 / x : y의 자식

1. 모든 노드는 red or black → `성립`
2. root는 black → `y가 root였고, x가 red인 경우 위반`
   1. y가 삭제되면 x가 그 자리를 차지하여 root가 됨. 하지만 x의 색은 red이고, root는 red가 될 수 없음 → `새롭게 root가 된 x의 색을 black으로 변경해주면 끝남`
3. 모든 leaf(NIL)은 black → `성립`
4. 만약 node가 red면 두 children은 black 이어야 함 → `y.p와 x가 모두 red인 경우 위반`
5. 모든 node에서 simple path 상에 있는 black node의 수가 같아야 함 → `원래 y(black)을 포함했던 모든 경로는 이제 balck 노드가 하나 부족함.`

   1. `노드 x에 “extra black”을 부여해서 일단 조건 5를 억지로라도 만족시킴`

      ![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/4ddcc5c0-5be8-411b-afd8-e036e70387be/5eae7d50-2b7b-47dd-a379-d051404c91c2/Untitled.png)

      ⇒ 검정 노드가 하나 삭제되어 black height가 문제되는데, 이를 막고자 한 노드에 2개의 black 노드를 삽입했다고 우선 생각

### **RB-Delete-Fixup 구현**

`IDEA1`: extra black 을 트리의 위쪽으로 올려보낸다. 올려보내다가 해당노드 x가 red&black이 되면 그냥 black 노드로 만들고 끝낸다.

![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/4ddcc5c0-5be8-411b-afd8-e036e70387be/fff54c0d-4617-4678-be31-ef467f9a2229/Untitled.png)

`IDEA2` : 계속 올리다가 root에 도달하면 그냥 extra black을 제거한다. (그림에서 가장 사단이 root라고 가정)

![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/4ddcc5c0-5be8-411b-afd8-e036e70387be/70c2f0ca-a11e-419c-9476-c8f8d253cb54/Untitled.png)

**Loop Invariant (함수가 도는 동안의 불변의 조건)**

- x는 루트가 아닌 double-black 노드
- w는 x의 형제 노드
- w는 NIL 노드가 될 수 없음 (만약 NIL이 되면 조건 5를 위반하게 됨)

### CASE명

x가 부모가 왼쪽 자식인 경우로 설명 (오른쪽 자식인 경우, 좌우만 바꿔주면 됨)

- **CASE1) w가 red인 경우**
  ![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/4ddcc5c0-5be8-411b-afd8-e036e70387be/71093b04-eb29-4ca9-b4db-27f8c8c3a871/Untitled.png)
  - w의 자식들은 black (이들은 NIL일 수 없음. NIL인 경우 조건 5에 위배)
  - **방법**
    1. w인 D노드를 black으로 변경
    2. x.p인 B노드를 red로 변경
    3. x.p를 기준으로 left-rotation (기존 w의 자식이었던 C는 B의 자식으로 편입됨)
    4. case 2, 3, 4로 진행됨. case1은 해결책이 아니라, 해결하기 위한 form을 만드는 것
- **CASE2) w가 BLACK, w의 자식들도 BLACK**
  ![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/4ddcc5c0-5be8-411b-afd8-e036e70387be/1f7de940-4e12-444c-b887-c2d4e3c76970/Untitled.png)
  - 회색 노드는 BLACK일 수도 있고, RED일 수도 잇음
  - **방법**
    1. x의 extra-black을 x.p인 B에 전달하고, w를 RED로 바꿈.
    2. x.p인 B를 새로운 x로 지정
    3. 만약 case1에서 이 경우에 도착했다면 x.p는 red였고, 따라서 새로운 **x는 red&black이 되었음. ⇒ 그냥 BLACK으로 변경 후 끝**
- **CASE3) w는 BLACK, w의 왼쪽자식이 red, 오른자식이 black**
  ![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/4ddcc5c0-5be8-411b-afd8-e036e70387be/93ef22b8-8282-4065-94b6-053049c87b63/Untitled.png)
  - **방법**
    1. w를 red로 변경하고 w의 왼쪽자식을 black으로 변경
    2. w에 대해 right-rotation 적용
    3. x의 새로운 형제 w는 오른쪽 자식이 red이므로 CASE 4에 해당하는 상황
- **CASE4) w는 BLACK, w의 오른자식이 red**
  ![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/4ddcc5c0-5be8-411b-afd8-e036e70387be/191e39e9-5cc4-48c8-81bf-dfa798478183/Untitled.png)
  - **방법**
    1. w와 B의 색을 교환 (w의 색을 x.p인 B의 색으로 변경, B의 색을 w의 색인 black으로 변경)
    2. w의 오른쪽 자식(E)을 black으로 변경
    3. x.p에 대해 left-rotation 적용 후, x의 extra black을 제거한 후 종료 (따라서 black-height 유지 가능)

### **예시**

![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/4ddcc5c0-5be8-411b-afd8-e036e70387be/e273ae14-9f03-4734-8688-1b855f8c66c8/Untitled.png)

- 진한 회색 노드가 red, 회색은 red&black 또는 black&black임

**RB-DELETE-FIXUP(T, x) psuedo code**

```cpp
while x != T.root and x.color == BLACK
	if x == x.p.left
		w = x.p.right
			if w.color == RED // CASE1
				w.color = BLACK
				LEFT-ROTATE(T, x.p)
				w = x.p.right
			if w.left.color == BLACK and w.right.color == BLACK // CASE2
				w.color = RED
				x = x.p
			else
				if w.right.color == BLACK // CASE3
					w.left.color = BLACK
					w.color = RED
					RIGHT-ROTATE(T, w)
					w = x.p.right
				w.color = x.p.color // CASE4
				x.p.color = BLACK
				w.right.color = BLACK
				LEFT-ROTATE(T, x.p)
				x = T.root
	else // x == x.p.right
		w = w.p.left
			f w.color == RED // CASE1
				w.color = BLACK
				RIGHT-ROTATE(T, x.p)
				w = x.p.left
			if w.right.color == BLACK and w.left.color == BLACK // CASE2
				w.color = RED
				x = x.p
			else
				if w.left.color == BLACK // CASE3
					w.right.color = BLACK
					w.color = RED
					LEFT-ROTATE(T, w)
					w = x.p.left
				w.color = x.p.color // CASE4
				x.p.color = BLACK
				w.right.color = BLACK
				RIGHT-ROTATE(T, x.p)
				x = T.root
x.color = BLACK // 중요!
```

참고 : https://velog.io/@stthunderl/Red-Black-Tree-4-삭제deletion-delete-deletefixup

https://blogshine.tistory.com/102
