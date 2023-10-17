import random

def quick_sort_r(arr: list) -> None:
    def partition(arr: list, low, high):
        # Swap a random element with the pivot element for improved performance
        random_index = random.randint(low, high)
        arr[low], arr[random_index] = arr[random_index], arr[low]

        pivot = arr[high]  # The pivot element is chosen as the last element in the subarray
        prev = low - 1  # Initialize the previous element's index

        # Iterate through the subarray
        for index in range(low, high):
            if pivot >= arr[index]:
                prev += 1
                # Swap the elements such that elements less than the pivot are on the left
                arr[index], arr[prev] = arr[prev], arr[index]

        # Move the pivot to its correct position in the sorted array
        arr[prev + 1], arr[high] = arr[high], arr[prev + 1]

        return prev + 1  # Return the index of the pivot element after partitioning

    def sort(arr, low, high):
        if low < high:
            mid = partition(arr, low, high)  # Partition the array into two subarrays
            sort(arr, low, mid - 1)  # Sort the left subarray (elements less than the pivot)
            sort(arr, mid + 1, high)  # Sort the right subarray (elements greater than the pivot)

    sort(arr, 0, len(arr) - 1)  # Initial call to the sorting function with the entire array
