def quick_sort(arr: list) -> None:
    # The main quick_sort function
    def partition(arr: list, low, high):
        # This function partitions the array into two subarrays, with elements less than the pivot on the left
        pivot = arr[high]  # Choose the last element as the pivot
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
        # This function recursively sorts the subarray
        if low < high:
            mid = partition(arr, low, high)  # Partition the array into two subarrays
            sort(arr, low, mid - 1)  # Sort the left subarray (elements less than the pivot)
            sort(arr, mid + 1, high)  # Sort the right subarray (elements greater than the pivot)

    sort(arr, 0, len(arr) - 1)  # Initial call to the sorting function with the entire array

# The main quick_sort function is called with the input list and sorts it in ascending order.
