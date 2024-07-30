def partition(arr, low, high):
    pivot = arr[high]  # Choose the last element as the pivot
    i = low - 1  # Index of the smaller element

    for j in range(low, high):  # Traverse through the current subarray
        if arr[j] <= pivot:  # If the current element is smaller than or equal to the pivot
            i += 1  # Increment the index of the smaller element
            arr[i], arr[j] = arr[j], arr[i]  # Swap the elements

    arr[i + 1], arr[high] = arr[high], arr[i + 1]  # Place the pivot in the correct position
    return i + 1  # Return the partitioning index

def quick_sort(arr, low, high):
    if low < high:  # Base condition
        pi = partition(arr, low, high)  # Partition the array and get the partition index
        quick_sort(arr, low, pi - 1)  # Recursively sort the elements before the partition index
        quick_sort(arr, pi + 1, high)  # Recursively sort the elements after the partition index

# Driver code
arr = [10, 7, 8, 9, 1, 5]
n = len(arr)
quick_sort(arr, 0, n - 1)
print("Sorted array:", arr)