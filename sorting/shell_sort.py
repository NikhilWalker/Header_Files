def shell_sort(arr: list, gap=-1):
    if gap <= 0:
        gap = len(arr) // 2

    def insertion_sort(arr, gap):
        i = gap
        while i < len(arr):
            j = i - gap
            while j >= 0:
                if arr[j + gap] > arr[j]:
                    break
                else:
                    arr[j + gap], arr[j] = arr[j], arr[j + gap]

                j = j - gap  # To check left side also
                # If the element present is greater than current element
            i += 1

    while gap > 0:
        insertion_sort(arr, gap)
        gap = gap // 2
        
