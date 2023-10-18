# select the smallest element in the array and swap with the first element of
# non-sorted array
# time complexity n*2

def selection_sort(arr : list):
    n = len(arr)

    for i in range(n):
        # Find the minimum element in the remaining unsorted part of the list
        min_index = i
        for j in range(i + 1, n):
            if arr[j] < arr[min_index]:
                min_index = j

        # Swap the found minimum element with the element at the current position (i)
        arr[i], arr[min_index] = arr[min_index], arr[i]