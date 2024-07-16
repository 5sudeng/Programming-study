#include <iostream>
#include <cmath>
#include <climits>

using namespace std;

class Heap {
public:
    int *harr;      // pointer to array of elements in heap
    int capacity;   // maximum possible size of heap
    int heap_size;  // Current number of elements in heap

    Heap(int capacity);
    Heap(const Heap& other);    // copy constructor
    ~Heap();

    void insertKey(int k);
    int parent(int i) { return (i-1)/2; }
    int left(int i) { return (2*i + 1); }
    int right(int i) { return (2*i + 2); }

    void maxHeapify(int i);
    void buildMaxHeap();
    void heapsort();

    int maxHeapMaximum();
    int maxHeapExtractMax();
    void maxHeapIncreaseKey(int i, int key);
    void maxHeapInsert(int key);
};


// constructor
Heap::Heap(int capacity) {
    this->capacity = capacity;
    heap_size = 0;
    harr = new int[capacity];
}

// deep copy constructor
Heap::Heap(const Heap& other) {
    this->capacity = other.capacity;
    this->heap_size = other.heap_size;
    this->harr = new int[capacity];
    
    for (int i=0; i<other.capacity; i++) {
        this->harr[i] = other.harr[i];
    }
}

Heap::~Heap() {
    delete[] harr;
}

void Heap::insertKey(int k) {
    if (heap_size == capacity) {
        cout << "\nOverflow: Could not insertKey\n";
        return;
    }

    heap_size++;
    int i = heap_size - 1;
    harr[i] = k;
}


// --------------------------------
void Heap::maxHeapify(int i) {
    int l = left(i);
    int r = right(i);
    int largest = i;

    if (l < heap_size && harr[l] > harr[i]) {
        largest = l;
    }
    if (r < heap_size && harr[r] > harr[largest]) {
        largest = r;
    }

    if (largest != i) {
        swap(harr[i], harr[largest]);
        maxHeapify(largest);
    }
}

void Heap::buildMaxHeap() {
    for (int i=floor(heap_size/2)-1; i>=0; i--) {
        maxHeapify(i);
    }
}

void Heap::heapsort() {
    buildMaxHeap();

    for (int i=heap_size-1; i>=1; i--) {
        swap(harr[0], harr[i]);
        heap_size--;
        maxHeapify(0);
    }
}


// --------------------------------
int Heap::maxHeapMaximum() {
    if (heap_size < 1) {
        cerr << "Error: Heap underflow\n";
        return INT_MIN;
    }
    
    return harr[0];
}

int Heap::maxHeapExtractMax() {
    int maxVal = maxHeapMaximum();

    harr[0] = harr[heap_size - 1];
    heap_size--;
    maxHeapify(0);

    return maxVal;
}

void Heap::maxHeapIncreaseKey(int i, int key) {
    if (key < harr[i]) {
        cerr << "Error: New key is smaller than the current key\n";
        return;
    }

    harr[i] = key;
    while (i > 0 && harr[parent(i)] < harr[i]) {
        swap(harr[i], harr[parent(i)]);
        i = parent(i);
    }
}

void Heap::maxHeapInsert(int key) {
    if (heap_size == capacity) {
        cerr << "Error: Heap overflow\n";
        return;
    }

    heap_size++;
    harr[heap_size - 1] = INT_MIN;
    maxHeapIncreaseKey(heap_size - 1, key);
}




int main () {
    // [#12] p.32 example
    Heap maxHeap(20);

    maxHeap.insertKey(4);
    maxHeap.insertKey(1);
    maxHeap.insertKey(3);
    maxHeap.insertKey(2);
    maxHeap.insertKey(16);
    maxHeap.insertKey(9);
    maxHeap.insertKey(10);
    maxHeap.insertKey(14);
    maxHeap.insertKey(8);
    maxHeap.insertKey(7);

    // build maxheap
    maxHeap.buildMaxHeap();
    cout << "Max Heap: ";
    for (int i=0; i<maxHeap.heap_size; i++) {
        cout << maxHeap.harr[i] << " ";
    }
    cout << endl;
    cout << endl;

    // heapsort
    Heap heapsort = maxHeap;
    int size = heapsort.heap_size;

    heapsort.heapsort();
    cout << "Heapsort: ";
    for (int i=0; i<size; i++) {
        cout << heapsort.harr[i] << " ";
    }
    cout << endl;
    cout << endl;

    // priority queue
    Heap priorityQ1 = maxHeap;

    cout << "Max Heap Extract Max: " << priorityQ1.maxHeapExtractMax() << " / ";
    for (int i=0; i<priorityQ1.heap_size; i++) {
        cout << priorityQ1.harr[i] << " ";
    }
    cout << endl;

    Heap priorityQ2 = maxHeap;
    priorityQ2.maxHeapIncreaseKey(4, 22);
    cout << "Max Heap Increase Key: ";
    for (int i=0; i<priorityQ2.heap_size; i++) {
        cout << priorityQ2.harr[i] << " ";
    }
    cout << endl;

    priorityQ2.maxHeapInsert(15);
    cout << "Max Heap Insert: ";
    for (int i=0; i<priorityQ2.heap_size; i++) {
        cout << priorityQ2.harr[i] << " ";
    }
    cout << endl;

    return 0;
}