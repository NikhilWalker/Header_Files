# Radix Sort is a linear sorting algorithm
# It sorts the from least signed bit to most significant bit
# and each bit it uses counting sort as helping sort
# time complexity n

def radix_sort(arr:list)->None:

    def counting_sort(arr, exp):
        res = [0]*len(arr)
        count = [0] * 10

        for num in arr:
            index = num//exp
            count[index%10] += 1
        
        for i in range(1,10):
            count[i]+=count[i-1]
        
        for i in range(len(arr)-1, -1, -1):
            index = arr[i]//exp
            res[count[index%10]-1] = arr[i]
            count[index%10] -= 1
        
        for i in range(len(arr)):
            arr[i] = res[i]
    
    max_num = max(arr)
    exp = 1
    while max_num / exp >= 1:
        counting_sort(arr, exp)
        exp*=10
    
