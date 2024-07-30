from typing import List

# list가 정렬되어 있을 때 list에서 target 찾는 binary search
def search(nums: List[int], target: int) -> int:
    
    start = 0
    end = len(nums)-1
    
    while start < end:
        mid = start + (end-start)//2
        
        if nums[mid] == target:
            return mid
        
        elif nums[mid] > target:
            end = mid-1
        
        else :
            start = mid+1
    
    if nums[start] == target :
        return start
    else :
        return -1

# 주어진 정렬된 리스트(nums)에서 특정 값(target)을 찾거나, 만약 리스트에 그 값이 없다면 삽입할 적절한 위치를 반환
def searchInsertIdx(nums, target):   
        start = 0
        end = len(nums)-1

        while start <= end: # start = end+1 이 되면서 끝남.
            mid = start + (end-start)//2 # start <= ~ <mid, mid<= ~ <end

            if nums[mid] == target:
                return mid
            elif nums[mid] < target:
                start = mid + 1
            else :
                end = mid - 1
        
        return start   

def selection_sort(nums):
    n = len(nums)
    for i in range(n):
        min_idx = i
        for j in range(i+1, n):
            if nums[j] < nums[min_idx]:
                min_idx = j
        nums[i], nums[min_idx] = nums[min_idx], nums[i]
    return nums

def insertion_sort(nums):
    for i in range(1, len(nums)):
        key = nums[i]
        j = i - 1
        while j >= 0 and key < nums[j]:
            nums[j + 1] = nums[j]
            j -= 1
        nums[j + 1] = key
    return nums

def merge(left, right):
    result = []
    while left and right:
        if left[0] < right[0]:
            result.append(left.pop(0))
        else:
            result.append(right.pop(0))
    if left:
        result.extend(left)
    if right:
        result.extend(right)
    return result

def merge_sort(nums):
    if len(nums) <= 1:
        return nums
    mid = len(nums) // 2
    left = merge_sort(nums[:mid])
    right = merge_sort(nums[mid:])
    return merge(left, right)

def bubble_sort(nums):
    n = len(nums)
    for i in range(n):
        for j in range(0, n-i-1):
            if nums[j] > nums[j+1]:
                nums[j], nums[j+1] = nums[j+1], nums[j]

def string_sort(s):
    s_list = list(s)
    for i in range(len(s_list)):
        for j in range(len(s_list) - 1):
            if s_list[j] > s_list[j + 1]:
                s_list[j], s_list[j + 1] = s_list[j + 1], s_list[j]
    return ''.join(s_list)


print(searchInsertIdx([7,8,10,11], 9))