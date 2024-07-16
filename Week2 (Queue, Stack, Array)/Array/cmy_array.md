# Array
- Fixed size
- Contiguous storage

## C++

``` C++
// Simple array
int arr[4] = {10, 20, 30, 40};
arr[3] = 100;
int *newArr = new int[10];

// Multi-dim array
// 2D array with 3 rows and 4 columns
int matrix[3][4] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12}
};
matrix[1][1] = 100;

// 3D array with 2 planes, 3 rows, and 4 columns
int grid[2][3][4] = {
    {
            {1, 2, 3, 4},
            {5, 6, 7, 8},
            {9, 10, 11, 12}
    },
    {
            {13, 14, 15, 16},
            {17, 18, 19, 20},
            {21, 22, 23, 24}
    }
};
```

또는

``` C++
#include <array>
std::array<int, 3> arr;
std::array<int, 3> arr = {1, 3, 5};
```

Member functions are `at(index)`, `size`, etc.


## C

``` C
#include <stdio.h>

int main() {
    // 1D array
    int arr[5] = {10, 20, 30, 40, 50};
    int arr[] = {10, 20, 30, 40, 50};

    // 2D array
    int arr[2][3] = {10, 20, 30, 40, 50, 60}; // row-wise로 쌓임
    // 10 20 30
    // 40 50 60

    // Using pointer
    int arr[5] = {10, 20, 30, 40, 50};
    int * ptr = &arr[0];
    for (int i=0; i<5; i++) {
        printf("%d ", *ptr++);
    } // 10 20 30 40 50 

    return 0;
}
```
- No index out of bounds checking
    - arr[10]를 출력하더라도 에러 없이 컴파일 되고 실행됨

## Python
- 그냥 리스트를 쓰면 된다!