# counting sort is non-comparison code
# it calculates the frequency of each element and
# sort the array
# time complexity n

def counting_sort(arr: list) -> None:
    max_value = max(arr)
    count = [0] * (max_value+1)

    for num in arr:
        count[num] += 1
    
    for i in range(1,max_value+1):
        count[i] += count[i-1]
    
    res = [0] * len(arr)

    for i in range(len(arr)-1, -1, -1):
        res[count[arr[i]]-1] = arr[i]
        count[arr[i]] -= 1
    
    for i in range(len(arr)):
        arr[i] = res[i]
