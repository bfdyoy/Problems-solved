def mergesort(arr):
    # checking if the length of the vector is 1
    # the array with only one element are already sorted
    if len(arr) < 2:
        return arr
    # create an empty list where the sorted array will be stored
    result = []
    # determine the halfway point of the array
    mid = int(len(arr) // 2)
    # sort the vector that contains the left elements of the array
    left_half = mergesort(arr[:mid])
    # sort the vector that contains the right elements of the array
    right_half = mergesort(arr[mid:])

    # merge the sorted vectors
    while (len(left_half) > 0) and (len(right_half) > 0):
        # checking which element is smaller and append it to the sorted
        # array
        if left_half[0] > right_half[0]:
            result.append(right_half[0])
            # pop the element that was copied into the sorted array
            right_half.pop(0)
        else:
            result.append(left_half[0])
            # pop the element that was copied into the sorted array
            left_half.pop(0)
    # append the remaining elements of the left and right array
    # if there are any
    result += left_half
    result += right_half
    # return the sorted array
    return result
