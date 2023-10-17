import random

def quick_sort_r(arr:list)->None:
    def partition(arr:list, low, high):

        # swap of the random element with pivot element
        random_index = random.randint(low, high)
        arr[low], arr[random_index] = arr[random_index], arr[low]

        pivot = arr[high]
        prev = low - 1
        for index in range(low, high):
            if pivot >= arr[index]:
                prev += 1
                arr[index], arr[prev] = arr[prev], arr[index]
        arr[prev+1], arr[high] = arr[high], arr[prev+1]
        return prev+1
    
    def sort(arr, low, high):
        if low<high:
            mid = partition(arr, low, high)
            sort(arr, low, mid-1)
            sort(arr, mid+1, high)
    
    sort(arr, 0, len(arr)-1)
    