def merge_sort(arr):
    if len(arr) > 1:  # Base case: if the array has more than one element
        mid = len(arr) // 2  # Find the middle point to divide the array into two halves
        L = arr[:mid]  # Copy the left half of arr
        R = arr[mid:]  # Copy the right half of arr

        merge_sort(L)  # Recursively sort the left half
        merge_sort(R)  # Recursively sort the right half

        i = j = k = 0  # Initialize three indices to track positions in L, R, and arr

        # Merge the sorted halves
        while i < len(L) and j < len(R):
            if L[i] < R[j]:  # If the element in the left half is smaller, put it in the arr
                arr[k] = L[i]
                i += 1
            else:  # If the element in the right half is smaller, put it in the arr
                arr[k] = R[j]
                j += 1
            k += 1

        # Copy any remaining elements of L, if there are any
        while i < len(L):
            arr[k] = L[i]
            i += 1
            k += 1

        # Copy any remaining elements of R, if there are any
        while j < len(R):
            arr[k] = R[j]
            j += 1
            k += 1

# Driver code
arr = [12, 11, 13, 5, 6, 7]
print("Given array is")
print(arr)
merge_sort(arr)
print("Sorted array is")
print(arr)