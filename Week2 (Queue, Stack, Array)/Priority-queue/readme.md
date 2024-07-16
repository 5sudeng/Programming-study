# Priority Queue
- One of ADT(Abstract Data Types)
- Can be implemented using binary heap

## C++

``` C++
#include <queue>

// Default: Max priority queue (descending order)
std::priority_queue<int> max_pq;

// Min priority queue (ascending order)
std::priority_queue<int, std::vector<int>, std::greater<int>> min_pq;
std::priority_queue min_pq(data.begin(), data.end(), std::greater<int>());
```

Member functions are `top`, `empty`, `size`, `push`, `pop`, etc.

## C
는 없는 것 같다,,?
아무래도 그렇겠지,,

## Python
- heapq

``` Python
import heapq # min heap
hq = []
heapq.heappush(hq, 1)
heapq.heappop(hq)
heapq.heapify(hq)
```

Methods are `heappush(heap, item)`, `heappop(heap)`, `heapify(list)`, etc.

- PriorityQueue

``` Python 
from queue import PriorityQueue
pq = PriorityQueue(maxsize = 10) # default = 무한
```

Methods are `put(item)` or `put((priority, value))`, `get`, etc.