#include <iostream>
using namespace std;

// Linear Search Function
int linearSearch(int arr[], int n, int x) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == x) {
            return i; // Return the index if found
        }
    }
    return -1; // Return -1 if not found
}

// Binary Search Function
int binarySearch(int arr[], int l, int r, int x) {
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (arr[m] == x) {
            return m; // Return the index if found
        }
        if (arr[m] < x) {
            l = m + 1; // Ignore the left half
        } else {
            r = m - 1; // Ignore the right half
        }
    }
    return -1; // Return -1 if not found
}

int main() {
    int arr[] = {2, 3, 4, 10, 40};
    int x = 10;
    int n = sizeof(arr) / sizeof(arr[0]);
    // int result = linearSearch(arr, n, x);
    int result = binarySearch(arr, 0, n - 1, x);
    if (result != -1) {
        cout << "Element is present at index " << result << endl;
    } else {
        cout << "Element is not present in array" << endl;
    }
    return 0;
}