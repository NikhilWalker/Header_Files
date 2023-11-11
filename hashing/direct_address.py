# Direct addressing hashing is a technique where each element of a data structure
# is directly mapped to a specific location in memory using its key as an index, 
# enabling constant-time retrieval.

class direct_address:
    def __init__(self, max_size:int) -> None:
        self.max_size = max_size
        self.address_table = [None] * self.max_size

    def search(self, key:int):
        if 0<=key<self.max_size:
            return self.address_table[key]
        else:
            raise IndexError
    
    def insert(self, key:int, data):
        if 0<=key<self.max_size:
            self.address_table[key] = data
        else:
            raise IndexError
        
    def delete(self, key:int):
        self.address_table[key] = None
    
    def resize(self, max_size):
        if max_size < self.max_size:
            self.address_table = self.address_table[:max_size]
        elif max_size > self.max_size:
            self.address_table.extend([None] * (max_size - self.max_size))
        self.max_size = max_size

    
    def find_max(self):
        index = self.max_size - 1
        while index > 0:
            if self.address_table[index] is not None:
                return self.address_table[index]
            index-=1
        else:
            return None
