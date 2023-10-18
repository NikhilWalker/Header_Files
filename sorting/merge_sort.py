# divide the array in two part recursively sort the left and right array
# till the element in array becomes 1
# merge the left and right array
# worst time complexity n*lg(n)

def merge_sort(arr: list):
    if len(arr) > 1:
        # Divide the list into two halves
        mid = len(arr) // 2
        left_half = arr[:mid]
        right_half = arr[mid:]

        # Recursively sort both halves
        merge_sort(left_half)
        merge_sort(right_half)

        # Merge the two sorted halves
        i = j = k = 0  # Indices for left_half, right_half, and arr
        while i < len(left_half) and j < len(right_half):
            # Compare the elements from left_half and right_half
            if left_half[i] < right_half[j]:
                arr[k] = left_half[i]
                i += 1
            else:
                arr[k] = right_half[j]
                j += 1
            k += 1

        # Check if any elements were left in either half and append them
        while i < len(left_half):
            arr[k] = left_half[i]
            i += 1
            k += 1
        while j < len(right_half):
            arr[k] = right_half[j]
            j += 1
            k += 1
