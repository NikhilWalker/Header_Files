def bucket_sort(arr:list)->None:

    def insertion_sort(arr):
        for i in range(1, len(arr)):
            temp = arr[i]
            j = i - 1
            while j >= 0 and arr[j] > temp:
                arr[j + 1] = arr[j]
                j -= 1
            arr[j + 1] = temp

    slots = 10
    res = [[] for _ in range(slots)]

    # put numbers in buckets
    for num in arr:
        index = int(num*slots)
        res[index].append(num)
    
    # sort individual sort
    for i in range(slots):
        insertion_sort(res[i])

    # concatenate the result
    index = 0
    for i in range(slots):
        for num in res[i]:
            arr[index] = num
            index+=1
