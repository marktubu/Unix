def find_max_cross_subarray(array, low, high, mid):
    
    left_index = mid
    left_max = float("-inf")
    sum = 0

    for i in range(mid, low-1, -1):
        sum = sum + array[i]
        if(sum > left_max):
            left_max = sum
            left_index = i
    
    right_index = mid+1
    right_max = float("-inf")
    sum = 0

    for i in range(mid+1, high+1):
        sum = sum + array[i]
        if(sum > right_max):
            right_max = sum
            right_index = i
    
    return left_index, right_index, left_max + right_max

def find_max_subarray(array, low, high):
    if low == high:
        return low, high, array[low]
    else:
        mid = (low + high) / 2
        left_low, left_high, left_max = find_max_subarray(array, low, mid)
        right_low, right_high, right_max = find_max_subarray(array, mid + 1, high)
        cross_low, cross_high, cross_max = find_max_cross_subarray(array, low, high, mid)

        if left_max >= right_max and left_max >= cross_max:
            return left_low, left_high, left_max
        elif right_max >= left_max and right_max >= cross_max:
            return right_low, right_high, right_max
        else:
            return cross_low, cross_high, cross_max


arr = [13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7]

print find_max_subarray(arr, 0, 15)