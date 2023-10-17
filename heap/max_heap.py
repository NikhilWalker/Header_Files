class max_heap:
    def __init__(self, arr: list = None) -> None:
        self.heap = []
        if arr is not None:
            self.heap = arr
            self.build_max_heap()  # Build a max heap from the input array if provided

    def maximum(self):
        return self.heap[0]  # Return the maximum (root) element of the max heap

    def extract_max(self):
        if len(self.heap) == 0:
            return None  # Return None if the heap is empty
        max = self.heap[0]  # Store the current maximum (root) element
        if len(self.heap) > 1:
            self.heap[0] = self.heap.pop()  # Replace the root with the last element and remove it
        else:
            self.heap.pop()  # Remove the last element
        self.max_heapify()  # Restore the max heap property
        return max  # Return the extracted maximum element

    def build_max_heap(self):
        for index in range(len(self.heap) // 2, -1, -1):
            self.__helper(self.heap, index, len(self.heap))  # Build a max heap using the helper function

    def __helper(self, arr, parent, size):
        left = parent * 2 + 1
        right = parent * 2 + 2
        largest = parent
        if left < size and arr[left] > arr[parent]:
            largest = left
        if right < size and arr[right] > arr[largest]:
            largest = right

        if parent != largest:
            # Swap elements to maintain the max heap property
            arr[parent], arr[largest] = arr[largest], arr[parent]
            self.__helper(arr, largest, size)

    def max_heapify(self) -> None:
        self.__helper(self.heap, 0, len(self.heap))  # Max-heapify the heap starting from the root

    def increase_key(self, index, key):
        if key < self.heap[index]:
            return False  # Return False if the new key is smaller than the current value
        self.heap[index] = key
        # Define a helper function to find the parent index
        def parent(x):
            if x % 2:
                return x // 2
            else:
                return x // 2 - 1
        while index > 0:
            p = parent(index)
            if self.heap[p] < self.heap[index]:
                # Swap elements to move the larger key up the heap
                self.heap[p], self.heap[index] = self.heap[index], self.heap[p]
                index = p
            else:
                break

    def insert(self, key):
        self.heap.append(float('-inf'))  # Add a sentinel element (negative infinity)
        self.increase_key(len(self.heap) - 1, key)  # Increase the key to its correct value
