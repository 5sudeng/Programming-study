#include <stdio.h>
#include <stdlib.h>

int findKthLargest(int* nums, int numsSize, int k) {
    if (numsSize==1 && k==1) { return nums[0]; }

    int* left = (int*)malloc(numsSize * sizeof(int));
    int* right = (int*)malloc(numsSize * sizeof(int));
    int leftIdx = 0; int rightIdx = 0;
    for (int i=1; i<numsSize; i++) {
        if (nums[i] < nums[0] || (nums[i] == nums[0] && i%2==0)) {
            left[leftIdx++] = nums[i];
        } else {
            right[rightIdx++] = nums[i];
        }
    }

    int result;
    if (rightIdx == k-1) { result = nums[0]; }
    else if (rightIdx >= k) { result = findKthLargest(right, rightIdx, k); }
    else { result = findKthLargest(left, leftIdx, k-rightIdx-1); }
    free(left); free(right);
    return result;
}

int main() {
    int nums[5000];
    for (int i=0; i<5000; i++) { nums[i] = i; }
    int k = 1;
    printf("%d", findKthLargest(nums, 5000, 1));
}