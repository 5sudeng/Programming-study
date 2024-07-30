def selection_sort(arr):
    for i in range(len(arr)):
        min_idx = i
        for j in range(i+1, len(arr)):
            if arr[j] < arr[min_idx]:
                min_idx = j
        arr[i], arr[min_idx] = arr[min_idx], arr[i]

def insertion_sort(arr):
    for i in range(1, len(arr)):  # Iterate from the second element to the end of the array
        key = arr[i]  # Take the current element (element to be inserted in the sorted portion)
        j = i - 1  # Start comparing with the element just before the current element

        # Move elements of arr[0..i-1], that are greater than key, to one position ahead of their current position
        while j >= 0 and arr[j] > key:
            arr[j + 1] = arr[j]  # Shift the element one position to the right
            j -= 1  # Move to the previous element

        arr[j + 1] = key  # Insert the key in its correct position

# Driver code
arr = [64, 25, 12, 22, 11]
insertion_sort(arr)
print("Sorted array:", arr)