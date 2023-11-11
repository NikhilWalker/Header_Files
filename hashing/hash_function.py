import random

def is_prime(num):
    if num <= 1:
        return False
    if num == 2:
        return True
    if num % 2 == 0:
        return False

    for i in range(3, int(num**0.5) + 1, 2):
        if num % i == 0:
            return False

    return True

def generate_random_hash_function(p, size):
    
    # get greatest prime number smaller than or equal to p
    while not is_prime(p):
        p -= 1

    a = random.randint(1, p - 1)
    b = random.randint(0, p - 1)

    def hash_function(key):
        return ((a * key + b) % p) % size

    return hash_function
