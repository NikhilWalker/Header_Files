def bubble_sort(arr:list):
    n = len(arr)
    
    for i in range(n):
        # Flag to check if any swaps were made in this pass
        swapped = False
        
        # Last i elements are already in place, so we don't need to compare them again
        for j in range(0, n-i-1):
            # Swap if the element found is greater than the next element
            if arr[j] > arr[j+1]:
                arr[j], arr[j+1] = arr[j+1], arr[j]
                swapped = True
                
        # If no two elements were swapped in this pass, the list is already sorted
        if not swapped:
            break