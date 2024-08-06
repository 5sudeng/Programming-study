# (Binary) Heap - CMY

Week2 `Queue` 참고 (![Queue]https://github.com/5sudeng/Programming-study/tree/a81a295d011b55bac0075cf40a25751111f54cd8/Week2%20(Queue%2C%20Stack%2C%20Array)/Queue)

- Used for implementing priority queues
- Two properties
  - **Structure property**: completeness
    - all levels full, with a possible exception being the bottom level, which is filled left to right
  - **Heap property**: priority of every node is greater than the priority of its parent
    - Min-heap: smaller numbers = higher priority
    - Max-heap: larger numbers = higher priorit
- Height: $O(logN)$ for a heap with $N$ nodes
- Insertion/Deletion: $O(logN)$

- Related notions

  - Fibonacci heap
    ![Fibonacci heap](https://media.geeksforgeeks.org/wp-content/uploads/Fibonacci-Heap.png) - A collection of trees, where each tree has a single root with its children arranged in a heap-ordered manner - Fast amortized running time for operations such as insert($O(1)$), merge($O(1)$), and extract-min($O(logN)$)
  - Heapsort: 주어진 배열로 heap을 구성한 후(내림차순 &rarr; `max-heap`, 오름차순 &rarr; `min-heap`), root를 하나씩 꺼내서 새 배열의 뒤부터 저장

- Min-heap Operations
  - `getMin()`: Returns the root element of min-heap, $O(1)$, in case of a max-heap `getMax()`
  - `extractMin()`: Removes the minimum element from min-heap, $O(logN)$ ($\because$ needs to maintain the heap property (by calling `heapify()`) after removing the root)
  - `decreaseKey()`: Decreases the value of the key, $O(logN)$
    - If the decreased key value of a node is greater than the parent of the node, do nothing
    - Otherwise, traverse up to fix the violated heap property
  - `insert()`: Inserts a new key, $O(logN)$
    - Add a new key at the end of the tree
      - If the new key is greater than its parent, do nothing
      - Otherwise, traverse up to fix the violated heap property
  - `delete()`: Deletes a key, $O(logN)$
    - Replace the key to be deleted with the minimum infinite by calling `decreaseKey()`
    - After `decreaseKey()`, the minus infinite value must reach root, so we call `extractMin()` to remove the key

```C++
// A C++ program to demonstrate common Binary Heap Operations
#include<iostream>
#include<climits>
using namespace std;

// Prototype of a utility function to swap two integers
void swap(int *x, int *y);

// A class for Min Heap
class MinHeap
{
	int *harr; // pointer to array of elements in heap
	int capacity; // maximum possible size of min heap
	int heap_size; // Current number of elements in min heap
public:
	MinHeap(int capacity);

	void MinHeapify(int i);

	int parent(int i) { return (i-1)/2; }
	int left(int i) { return (2*i + 1); }
	int right(int i) { return (2*i + 2); }

	int extractMin();
	void decreaseKey(int i, int new_val);
	int getMin() { return harr[0]; }
	void deleteKey(int i);
	void insertKey(int k);
};

MinHeap::MinHeap(int cap)
{
	heap_size = 0;
	capacity = cap;
	harr = new int[cap];
}

// Inserts a new key 'k'
void MinHeap::insertKey(int k)
{
	if (heap_size == capacity)
	{
		cout << "\nOverflow: Could not insertKey\n";
		return;
	}

	// First insert the new key at the end
	heap_size++;
	int i = heap_size - 1;
	harr[i] = k;

	// Fix the min heap property if it is violated
	while (i != 0 && harr[parent(i)] > harr[i])
	{
	swap(&harr[i], &harr[parent(i)]);
	i = parent(i);
	}
}

// Decreases value of key at index 'i' to new_val. It is assumed that
// new_val is smaller than harr[i].
void MinHeap::decreaseKey(int i, int new_val)
{
	harr[i] = new_val;
	while (i != 0 && harr[parent(i)] > harr[i])
	{
	swap(&harr[i], &harr[parent(i)]);
	i = parent(i);
	}
}

// Method to remove minimum element (or root) from min heap
int MinHeap::extractMin()
{
	if (heap_size <= 0)
		return INT_MAX;
	if (heap_size == 1)
	{
		heap_size--;
		return harr[0];
	}

	// Store the minimum value, and remove it from heap
	int root = harr[0];
	harr[0] = harr[heap_size-1];
	heap_size--;
	MinHeapify(0);

	return root;
}


// This function deletes key at index i. It first reduced value to minus infinite, then calls extractMin()
void MinHeap::deleteKey(int i)
{
	decreaseKey(i, INT_MIN);
	extractMin();
}

// A recursive method to heapify a subtree with the root at given index
// This method assumes that the subtrees are already heapified
void MinHeap::MinHeapify(int i)
{
	int l = left(i);
	int r = right(i);
	int smallest = i;
	if (l < heap_size && harr[l] < harr[i])
		smallest = l;
	if (r < heap_size && harr[r] < harr[smallest])
		smallest = r;
	if (smallest != i)
	{
		swap(&harr[i], &harr[smallest]);
		MinHeapify(smallest);
	}
}

// A utility function to swap two elements
void swap(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

int main()
{
	MinHeap h(11);
	h.insertKey(3);
	h.insertKey(2);
	h.deleteKey(1);
	h.insertKey(15);
	h.insertKey(5);
	h.insertKey(4);
	h.insertKey(45);
	cout << h.extractMin() << " ";
	cout << h.getMin() << " ";
	h.decreaseKey(2, 1);
	cout << h.getMin();
	return 0;
}
```

```Python
# Import the heap functions from python library
from heapq import heappush, heappop, heapify

# heappop - pop and return the smallest element from heap
# heappush - push the value item onto the heap, maintaining
#			 heap invarient
# heapify - transform list into heap, in place, in linear time

class MinHeap:

	def __init__(self):
		self.heap = []

	def parent(self, i):
		return (i-1)/2

	def insertKey(self, k):
		heappush(self.heap, k)

	# Decrease value of key at index 'i' to new_val
	# It is assumed that new_val is smaller than heap[i]
	def decreaseKey(self, i, new_val):
		self.heap[i] = new_val
		while(i != 0 and self.heap[self.parent(i)] > self.heap[i]):
			# Swap heap[i] with heap[parent(i)]
			self.heap[i] , self.heap[self.parent(i)] = (self.heap[self.parent(i)], self.heap[i])

	# Method to remove minimum element from min heap
	def extractMin(self):
		return heappop(self.heap)

	# This function deletes key at index i. It first reduces
	# value to minus infinite and then calls extractMin()
	def deleteKey(self, i):
		self.decreaseKey(i, float("-inf"))
		self.extractMin()

	# Get the minimum element from the heap
	def getMin(self):
		return self.heap[0]

heapObj = MinHeap()
heapObj.insertKey(3)
heapObj.insertKey(2)
heapObj.deleteKey(1)
heapObj.insertKey(15)
heapObj.insertKey(5)
heapObj.insertKey(4)
heapObj.insertKey(45)

print heapObj.extractMin(),
print heapObj.getMin(),
heapObj.decreaseKey(2, 1)
print heapObj.getMin()
```
