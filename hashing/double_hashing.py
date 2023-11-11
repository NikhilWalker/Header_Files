# double hashing is a method for open addressing
# the initial probe goes to hash_func1(key) and
# successive probe position are offset from previous position by the amount
# hash_func2(key) thus effectively reducing clustring 

class double_hashing:
    def __init__(self, max_size, hash_func1=None, hash_func2=None):
        if not isinstance(max_size, int) or max_size <= 0:
            raise ValueError("max_size must be a positive integer")
        self.size = max_size
        self.table = [None] * max_size
        self._hash1 = hash_func1
        self._hash2 = hash_func2

        if self._hash1 is None:
            self._hash1 = lambda key: key % self.size
        if self._hash2 is None:
            self._hash2 = lambda key: 1 + (key % (self.size - 1))

    def insert(self, key, value):
        start = index = self._hash1(key)
        step_size = self._hash2(key)
        probing_count = 0  # Track the number of probes
        while self.table[index] is not None:
            index = (index + step_size) % self.size
            probing_count += 1
            if start == index:
                raise IndexError("Table is full")
            if probing_count > self.size:
                raise IndexError("Probing limit exceeded")
        self.table[index] = (key, value)

    def search(self, key):
        start = index = self._hash1(key)
        step_size = self._hash2(key)
        probing_count = 0  # Track the number of probes
        while self.table[index] is not None:
            if self.table[index][0] == key:
                return self.table[index][1]
            index = (index + step_size) % self.size
            probing_count += 1
            if start == index:
                raise IndexError("Key not found")
            if probing_count > self.size:
                raise IndexError("Probing limit exceeded")
        return None
    
    def delete(self, key):
        start = index = self._hash1(key)
        step_size = self._hash2(key)
        probing_count = 0  # Track the number of probes
        while self.table[index] is not None:
            if self.table[index][0] == key:
                self.table[index] = None  # Delete the item
                return
            index = (index + step_size) % self.size
            probing_count += 1
            if start == index:
                raise IndexError("Key not found")
            if probing_count > self.size:
                raise IndexError("Probing limit exceeded")