#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Heap 구조체 정의
typedef struct {
    int *harr;      // 힙 요소를 저장하는 배열
    int capacity;   // 힙의 최대 크기
    int heap_size;  // 현재 힙의 요소 개수
} Heap;

// 함수 선언
void initHeap(Heap *heap, int capacity);
void insertKey(Heap *heap, int k);
int parent(int i);
int left(int i);
int right(int i);
void maxHeapify(Heap *heap, int i);
void buildMaxHeap(Heap *heap);
void heapSort(Heap *heap);
int maxHeapMaximum(Heap *heap);
int maxHeapExtractMax(Heap *heap);
void maxHeapIncreaseKey(Heap *heap, int i, int key);
void maxHeapInsert(Heap *heap, int key);
Heap copyHeap(Heap *heap);
void freeHeap(Heap *heap);

// 힙 초기화
void initHeap(Heap *heap, int capacity) {
    heap->capacity = capacity;
    heap->heap_size = 0;
    heap->harr = (int *)malloc(capacity * sizeof(int));
}

// 새로운 요소 삽입
void insertKey(Heap *heap, int k) {
    if (heap->heap_size == heap->capacity) {
        printf("\nOverflow: Could not insertKey\n");
        return;
    }

    heap->heap_size++;
    int i = heap->heap_size - 1;
    heap->harr[i] = k;
}

// 부모 인덱스 계산
int parent(int i) {
    return (i - 1) / 2;
}

// 왼쪽 자식 인덱스 계산
int left(int i) {
    return (2 * i + 1);
}

// 오른쪽 자식 인덱스 계산
int right(int i) {
    return (2 * i + 2);
}

// Max Heap 속성 유지
void maxHeapify(Heap *heap, int i) {
    int l = left(i);
    int r = right(i);
    int largest = i;

    if (l < heap->heap_size && heap->harr[l] > heap->harr[i]) {
        largest = l;
    }
    if (r < heap->heap_size && heap->harr[r] > heap->harr[largest]) {
        largest = r;
    }

    if (largest != i) {
        int temp = heap->harr[i];
        heap->harr[i] = heap->harr[largest];
        heap->harr[largest] = temp;
        maxHeapify(heap, largest);
    }
}

// Max Heap으로 변환
void buildMaxHeap(Heap *heap) {
    for (int i = (heap->heap_size / 2) - 1; i >= 0; i--) {
        maxHeapify(heap, i);
    }
}

// Heap 정렬
void heapSort(Heap *heap) {
    int original_size = heap->heap_size;
    buildMaxHeap(heap);

    for (int i = heap->heap_size - 1; i >= 1; i--) {
        int temp = heap->harr[0];
        heap->harr[0] = heap->harr[i];
        heap->harr[i] = temp;
        heap->heap_size--;
        maxHeapify(heap, 0);
    }

    heap->heap_size = original_size;
}

// 최대 값 조회
int maxHeapMaximum(Heap *heap) {
    if (heap->heap_size < 1) {
        fprintf(stderr, "Error: Heap underflow\n");
        return INT_MIN;
    }

    return heap->harr[0];
}

// 최대 값 추출
int maxHeapExtractMax(Heap *heap) {
    if (heap->heap_size < 1) {
        fprintf(stderr, "Error: Heap underflow\n");
        return INT_MIN;
    }

    int maxVal = heap->harr[0];
    heap->harr[0] = heap->harr[heap->heap_size - 1];
    heap->heap_size--;
    maxHeapify(heap, 0);

    return maxVal;
}

// 특정 요소의 키 증가
void maxHeapIncreaseKey(Heap *heap, int i, int key) {
    if (key < heap->harr[i]) {
        fprintf(stderr, "Error: New key is smaller than the current key\n");
        return;
    }

    heap->harr[i] = key;
    while (i > 0 && heap->harr[parent(i)] < heap->harr[i]) {
        int temp = heap->harr[i];
        heap->harr[i] = heap->harr[parent(i)];
        heap->harr[parent(i)] = temp;
        i = parent(i);
    }
}

// 새로운 요소 삽입
void maxHeapInsert(Heap *heap, int key) {
    if (heap->heap_size == heap->capacity) {
        fprintf(stderr, "Error: Heap overflow\n");
        return;
    }

    heap->heap_size++;
    heap->harr[heap->heap_size - 1] = INT_MIN;
    maxHeapIncreaseKey(heap, heap->heap_size - 1, key);
}

// 힙 복사
Heap copyHeap(Heap *heap) {
    Heap newHeap;
    initHeap(&newHeap, heap->capacity);
    newHeap.heap_size = heap->heap_size;
    for (int i = 0; i < heap->heap_size; i++) {
        newHeap.harr[i] = heap->harr[i];
    }
    return newHeap;
}

// 메모리 해제
void freeHeap(Heap *heap) {
    free(heap->harr);
}

int main() {
    // [#12] p.32 example
    Heap maxHeap;
    initHeap(&maxHeap, 20);

    insertKey(&maxHeap, 4);
    insertKey(&maxHeap, 1);
    insertKey(&maxHeap, 3);
    insertKey(&maxHeap, 2);
    insertKey(&maxHeap, 16);
    insertKey(&maxHeap, 9);
    insertKey(&maxHeap, 10);
    insertKey(&maxHeap, 14);
    insertKey(&maxHeap, 8);
    insertKey(&maxHeap, 7);

    /* build maxheap */ 
    buildMaxHeap(&maxHeap);
    printf("Max Heap: ");
    for (int i = 0; i < maxHeap.heap_size; i++) {
        printf("%d ", maxHeap.harr[i]);
    }
    printf("\n\n");

    /* heapsort */
    Heap heapsort = copyHeap(&maxHeap);
    int size = heapsort.heap_size;
    heapSort(&heapsort);
    printf("Heapsort: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", heapsort.harr[i]);
    }
    printf("\n\n");

    /* priority queue */
    Heap priorityQ1 = copyHeap(&maxHeap);
    printf("Max Heap Extract Max: %d / ", maxHeapExtractMax(&priorityQ1));
    for (int i = 0; i < priorityQ1.heap_size; i++) {
        printf("%d ", priorityQ1.harr[i]);
    }
    printf("\n");

    Heap priorityQ2 = copyHeap(&maxHeap);
    maxHeapIncreaseKey(&priorityQ2, 4, 22);
    printf("Max Heap Increase Key: ");
    for (int i = 0; i < priorityQ2.heap_size; i++) {
        printf("%d ", priorityQ2.harr[i]);
    }
    printf("\n");

    maxHeapInsert(&priorityQ2, 15);
    printf("Max Heap Insert: ");
    for (int i = 0; i < priorityQ2.heap_size; i++) {
        printf("%d ", priorityQ2.harr[i]);
    }
    printf("\n");

    // 메모리 해제
    freeHeap(&maxHeap);
    freeHeap(&heapsort);
    freeHeap(&priorityQ1);
    freeHeap(&priorityQ2);

    return 0;
}
