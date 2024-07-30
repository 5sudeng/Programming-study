class Solution(object):
    def findKthLargest(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        if len(nums) == 1 and k == 1:
            return nums[0]
        
        left, right = [], []
        for i in range(1, len(nums)):
            if nums[i] < nums[0] or (nums[i] == nums[0] and i%2==0):
                left.append(nums[i])
            else:
                right.append(nums[i])
        
        if len(right) == k-1:
            return nums[0]
        elif len(right) >= k:
            return self.findKthLargest(right, k)
        else:
            return self.findKthLargest(left, k-len(right)-1)