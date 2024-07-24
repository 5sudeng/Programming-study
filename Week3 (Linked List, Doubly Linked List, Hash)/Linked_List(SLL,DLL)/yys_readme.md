# Linked List
## methods
* `getsize(self)`: 현재 `LinkedList`의 크기를 반환합니다.
* `addfront(self, val)`: 주어진 값을 리스트의 가장 앞에 추가합니다.
* `addback(self, val)`: 주어진 값을 리스트의 가장 뒤에 추가합니다.
* `findNode(self, val) -> Node`: 리스트에서 주어진 값을 갖는 노드를 찾습니다. 해당 노드를 반환하며, 존재하지 않으면 `None`을 반환합니다.
* `deleteNode(self, val)`: 리스트에서 주어진 값을 갖는 노드를 삭제합니다. 삭제에 성공하면 메시지를 출력하고, 리스트에 값이 없으면 존재하지 않는다는 메시지를 출력합니다.
* `addafter(self, prevnode, val)`: 주어진 노드 `prevnode` 다음에 값을 추가합니다.
* `deleteafter(self, prevnode)`: 주어진 노드 `prevnode` 다음의 노드를 삭제합니다. 만약 다음 노드가 없으면 아무 작업도 하지 않습니다.
* `printSSL(self)`: 리스트의 모든 요소를 출력합니다.

## 추가 methods : reverse_SSL.py
* 리스트의 모든 요소의 순서를 반대로 뒤집습니다.


# Doubly Linked List
## methods
* `__init__(self)`: `DLL` 객체를 초기화합니다. `head`와 `tail`은 `None`, `size`는 0으로 설정됩니다.
* `getSize(self)`: 현재 `DLL`의 크기를 반환합니다.
* `is_empty(self)`: `DLL`이 비어 있는지 확인합니다. 비어 있으면 `True`, 아니면 `False`를 반환합니다.
* `clear(self)`: `DLL`을 초기 상태로 만듭니다. 모든 요소를 제거하고 `size`는 0으로, `head`와 `tail`은 `None`으로 설정됩니다.
* `get_first(self)`: 리스트의 첫 번째 요소의 값을 반환합니다. 리스트가 비어 있으면 `None`을 반환합니다.
* `get_last(self)`: 리스트의 마지막 요소의 값을 반환합니다. 리스트가 비어 있으면 `None`을 반환합니다.
* `get_at_index(self, idx) -> DLLNode`: 주어진 인덱스에 있는 노드를 반환합니다. 인덱스가 범위를 벗어나면 `None`을 반환합니다.
* `find_data(self, data) -> DLLNode`: 리스트에서 주어진 값을 갖는 노드를 찾습니다. 해당 노드를 반환하며, 존재하지 않으면 `None`을 반환합니다.
* `prepend(self, data)`: 주어진 값을 리스트의 가장 앞에 추가합니다.
* `append(self, data)`: 주어진 값을 리스트의 가장 뒤에 추가합니다.
* `insert_at_idx(self, data, idx)`: 주어진 값을 리스트의 특정 인덱스에 추가합니다. 인덱스가 범위를 벗어나면 아무 작업도 하지 않습니다.
* `delete_at_idx(self, idx)`: 리스트의 특정 인덱스에 있는 노드를 삭제합니다. 인덱스가 범위를 벗어나면 아무 작업도 하지 않습니다.
* `delete_by_value(self, data)`: 리스트에서 주어진 값을 갖는 노드를 삭제합니다. 값이 존재하지 않으면 아무 작업도 하지 않습니다.
* `delete_first(self)`: 리스트의 첫 번째 노드를 삭제합니다. 리스트가 비어 있으면 아무 작업도 하지 않습니다.
* `delete_last(self)`: 리스트의 마지막 노드를 삭제합니다. 리스트가 비어 있으면 아무 작업도 하지 않습니다.
* `reverse(self)`: 리스트의 모든 요소의 순서를 반대로 뒤집습니다. `head`와 `tail`이 서로 교체됩니다.
* `rotate(self, d)`: 리스트를 오른쪽으로 `d`만큼 회전시킵니다. `d`가 음수일 경우, 왼쪽으로 회전한 효과를 냅니다. 리스트가 비어 있거나 `d`가 0일 경우, 아무 작업도 하지 않습니다.
* `display_forward(self)`: 리스트의 모든 요소를 처음부터 끝까지 출력합니다.
* `display_backward(self)`: 리스트의 모든 요소를 끝에서부터 처음까지 출력합니다.




# Deque 클래스

이 `Deque` 클래스는 이중 연결 리스트(Doubly Linked List)를 이용하여 양방향 큐(Deque)를 구현한 것입니다. 각 메서드의 기능은 다음과 같습니다.

## methods 설명
* `getSize(self)`: 현재 `Deque`의 크기를 반환합니다.
* `is_empty(self)`: `Deque`가 비어 있는지 확인합니다. 비어 있으면 `True`, 아니면 `False`를 반환합니다.
* `clear(self)`: `Deque`를 초기 상태로 만듭니다. 모든 요소를 제거하고 `size`는 0으로, `head`와 `tail`은 `None`으로 설정됩니다.
* `front(self)`: `Deque`의 가장 앞에 있는 요소의 값을 출력합니다. `Deque`가 비어 있으면 `-1`을 출력합니다.
* `back(self)`: `Deque`의 가장 뒤에 있는 요소의 값을 출력합니다. `Deque`가 비어 있으면 `-1`을 출력합니다.
* `appendleft(self, val)`: 주어진 값을 `Deque`의 가장 앞에 추가합니다. `Deque`가 비어 있을 경우, 새 노드는 `head`이자 `tail`이 됩니다. 그렇지 않으면, 새 노드는 기존의 `head` 앞에 추가됩니다.
* `append(self, val)`: 주어진 값을 `Deque`의 가장 뒤에 추가합니다. `Deque`가 비어 있을 경우, 새 노드는 `head`이자 `tail`이 됩니다. 그렇지 않으면, 새 노드는 기존의 `tail` 뒤에 추가됩니다.
* `popleft(self)`: `Deque`의 가장 앞에 있는 요소를 제거하고 그 값을 출력합니다. `Deque`가 비어 있으면 `-1`을 출력합니다. 요소가 하나만 있을 경우, `head`와 `tail`은 `None`으로 설정됩니다.
* `pop(self)`: `Deque`의 가장 뒤에 있는 요소를 제거하고 그 값을 출력합니다. `Deque`가 비어 있으면 `-1`을 출력합니다. 요소가 하나만 있을 경우, `head`와 `tail`은 `None`으로 설정됩니다.
* `reverse(self)`: `Deque`의 모든 요소의 순서를 반대로 뒤집습니다. `head`와 `tail`이 서로 교체됩니다.
* `rotate(self, d)`: `Deque`를 오른쪽으로 `d`만큼 회전시킵니다. `d`가 음수일 경우, 왼쪽으로 회전한 효과를 냅니다. `Deque`가 비어 있거나 `d`가 0일 경우, 아무 작업도 하지 않습니다. 회전은 실제 회전해야 하는 횟수만큼만 수행됩니다(`d % size`).

