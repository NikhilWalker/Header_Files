# heap sort depends on heap data structure
# in heap the maximum element is at top of the tree
# extract the max element and again heapify the tree
# worst time complexity n*lg(n)

def max_heapify(arr, parent, size):
    # Calculate the indices of the left and right child nodes
    left = parent * 2 + 1
    right = parent * 2 + 2

    # Initialize the largest value as the current parent
    largest = parent

    # Check if the left child exists and is greater than the parent
    if left < size and arr[left] > arr[parent]:
        largest = left
        
    # Check if the right child exists and is greater than the largest (which could be the parent or left child)
    if right < size and arr[right] > arr[largest]:
        largest = right

    # If the largest value is not the parent, swap the parent and largest values
    if parent != largest:
        arr[parent], arr[largest] = arr[largest], arr[parent]
        # Recursively call max_heapify on the affected child node (largest)
        max_heapify(arr, largest, size)

def build_max_heap(arr):
    # Start from the middle of the array and work towards the beginning
    for index in range(len(arr)//2, -1, -1):
        # Call max_heapify on each index, building the Max Heap
        max_heapify(arr, index, len(arr))

def heap_sort(arr):
    # Build a Max Heap from the input array
    build_max_heap(arr)
    # Iterate from the end of the array to the beginning
    for index in range(len(arr)-1, -1, -1):
        # Swap the current root (maximum element) with the last element
        arr[index], arr[0] = arr[0], arr[index]
        # Restore the Max Heap property for the remaining elements
        max_heapify(arr, 0, index)
