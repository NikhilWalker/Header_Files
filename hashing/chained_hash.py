# Hashing is a process that transforms input data (often of variable size) 
# into a fixed-size string of characters, typically for 
# efficient data retrieval or security purposes, using a hash function.

class chained_hash:
    def __init__(self, max_size, hash_func=lambda x: x) -> None:
        self.hash_func = hash_func
        self.table = [[] for _ in range(max_size)]
    
    def insert(self, key, data):
        arr = self.table[self.hash_func(key)]
        for i in range(len(arr)):
            if arr[i][0] == key:
                arr[i][1] = data
                return
        arr.append([key, data])
    
    def search(self, key):
        for data in self.table[self.hash_func(key)]:
            if data[0] == key:
                return data[1]
        return None
    
    def delete(self, key):
        data = self.table[self.hash_func(key)]
        for index, pair in enumerate(data):
            if pair[0] == key:
                data.pop(index)
                return
            