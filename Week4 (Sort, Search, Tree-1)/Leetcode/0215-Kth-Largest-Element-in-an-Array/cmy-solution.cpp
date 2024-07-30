#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Quicksort -> runtime 쓰레기
int findKthLargest(vector<int>& nums, int k) {
    if (nums.size()==1 && k==1) { return nums[0]; }

    vector<int> left, right;
    for (int i=1; i<nums.size(); i++) {
        if (nums[i] < nums[0] || (nums[i] == nums[0] && i%2==0)) { 
            left.push_back(nums[i]); 
        } else { 
            right.push_back(nums[i]); 
        }
    }

    if (right.size() == k-1) { return nums[0]; }
    else if (right.size() >= k) { return findKthLargest(right, k); }
    else { return findKthLargest(left, k-right.size()-1); }
}

// // Sort
// int findKthLargest(vector<int>& nums, int k) {
//     sort(nums.begin(), nums.end());
//     return nums[nums.size()-k];
// }

// // MinHeap
// int findKthLargest(vector<int>& nums, int k) {
//     priority_queue<int, vector<int>, greater<int>> pq;
//     for (int i=0; i<k; i++) { pq.push(nums[i]); }
//     for (int j=k; j<nums.size(); j++) {
//         if (nums[j] > pq.top()) {
//             pq.pop(); pq.push(nums[j]);
//         }
//     }
//     return pq.top();
// }

int main() {
    vector<int> nums = {-1, 2, 0};
    int k = 1;
    cout << findKthLargest(nums, k) << endl;

    return 0;
}