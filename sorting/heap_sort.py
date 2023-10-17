def max_heapify(arr, parent, size):
    left = parent * 2 + 1
    right = parent * 2 + 2
    largest = parent
    if left < size and arr[left] > arr[parent]:
        largest = left
    if right < size and arr[right] > arr[largest]:
        largest = right
    
    if parent != largest:
        # swap
        arr[parent], arr[largest] = arr[largest], arr[parent]
        max_heapify(arr, largest, size)

def build_max_heap(arr):
    for index in range(len(arr)//2, -1, -1):
        max_heapify(arr, index, len(arr))

def heap_sort(arr):
    build_max_heap(arr)
    for index in range(len(arr)-1, -1, -1):
        arr[index], arr[0] = arr[0], arr[index]
        max_heapify(arr, 0, index)
