class max_heap:
    def __init__(self, arr:list=None) -> None:
        self.heap = []
        if arr is not None:
            self.heap = arr
            self.build_max_heap()
    
    def maximum(self):
        return self.heap[0]
    
    def extract_max(self):
        if len(self.heap) == 0:
            return None
        max = self.heap[0]
        if len(self.heap) > 1:
            self.heap[0] = self.heap.pop()
        else:
            self.heap.pop()
        self.max_heapify()
        return max
    
    def build_max_heap(self):
        for index in range(len(self.heap)//2, -1, -1):
            self.__helper(self.heap, index, len(self.heap))

    def __helper(self, arr, parent, size):
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
            self.__helper(arr, largest, size)
    
    def max_heapify(self)->None:
        self.helper(self.heap, 0, len(self.heap))

    def increase_key(self, index, key):
        if key < self.heap[index]:
            return False
        self.heap[index] = key
        def parent(x):
            if x%2:
                return x//2
            else:
                return x//2-1
            
        while index > 0:
            p = parent(index)
            if self.heap[p] < self.heap[index]:
                self.heap[p], self.heap[index] = self.heap[index], self.heap[p]
                index = p
            else:
                break

    def insert(self, key):
        self.heap.append(float('-inf'))
        self.increase_key(len(self.heap)-1, key)

heap = max_heap([0,1,2,3,4,5,6])
print(heap.heap)
heap.insert(9)
print(heap.heap)