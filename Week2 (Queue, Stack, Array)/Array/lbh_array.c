/*
    Method Explanations

	1.	insert: Adds an element at the end of the array.
	2.	delete: Removes an element at a specific index.
	3.	get: Retrieves an element at a specific index.
	4.	size: Returns the current number of elements in the array.
	5.	is_empty: Checks if the array is empty.
	6.	clear: Removes all elements from the array.
	7.	resize: Resizes the array to accommodate more elements.
	8.	find: Searches for an element and returns its index (or -1 if not found).
	9.	contains: Checks if an element exists in the array.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
    int capacity;
} Array;

// Function to initialize the array
void initArray(Array *a, int initialCapacity) {
    a->data = (int *)malloc(initialCapacity * sizeof(int));
    a->size = 0;
    a->capacity = initialCapacity;
}

// Function to resize the array
void resizeArray(Array *a) {
    int newCapacity = a->capacity * 2;
    int *newData = (int *)malloc(newCapacity * sizeof(int));
    for (int i = 0; i < a->size; i++) {
        newData[i] = a->data[i];
    }
    free(a->data);
    a->data = newData;
    a->capacity = newCapacity;
}

// Function to add an element to the array
void insertArray(Array *a, int element) {
    if (a->size == a->capacity) {
        resizeArray(a);
    }
    a->data[a->size++] = element;
}

// Function to remove an element from the array
void deleteArray(Array *a, int index) {
    if (index < 0 || index >= a->size) {
        printf("Index out of bounds\n");
        return;
    }
    for (int i = index; i < a->size - 1; i++) {
        a->data[i] = a->data[i + 1];
    }
    a->size--;
}

// Function to get an element at a specific index
int getArray(Array *a, int index) {
    if (index < 0 || index >= a->size) {
        printf("Index out of bounds\n");
        return -1; // Return an invalid value
    }
    return a->data[index];
}

// Function to get the current size of the array
int sizeArray(Array *a) {
    return a->size;
}

// Function to check if the array is empty
int isEmptyArray(Array *a) {
    return a->size == 0;
}

// Function to clear the array
void clearArray(Array *a) {
    a->size = 0;
}

// Function to find an element in the array
int findArray(Array *a, int element) {
    for (int i = 0; i < a->size; i++) {
        if (a->data[i] == element) {
            return i;
        }
    }
    return -1; // Return -1 if the element is not found
}

// Function to check if the array contains a specific element
int containsArray(Array *a, int element) {
    return findArray(a, element) != -1;
}

// Function to free the array
void freeArray(Array *a) {
    free(a->data);
    a->data = NULL;
    a->size = a->capacity = 0;
}

// Main function to demonstrate usage
int main() {
    Array a;
    initArray(&a, 2);
    insertArray(&a, 10);
    insertArray(&a, 20);
    insertArray(&a, 30);

    printf("Array elements: ");
    for (int i = 0; i < a.size; i++) {
        printf("%d ", a.data[i]);
    }
    printf("\n");

    deleteArray(&a, 1);
    printf("After deletion: ");
    for (int i = 0; i < a.size; i++) {
        printf("%d ", a.data[i]);
    }
    printf("\n");

    int value = getArray(&a, 1);
    printf("Element at index 1: %d\n", value);

    printf("Array size: %d\n", sizeArray(&a));
    printf("Array is empty: %s\n", isEmptyArray(&a) ? "Yes" : "No");

    clearArray(&a);
    printf("Array size after clearing: %d\n", sizeArray(&a));

    insertArray(&a, 40);
    printf("Array contains 40: %s\n", containsArray(&a, 40) ? "Yes" : "No");

    freeArray(&a);
    return 0;
}