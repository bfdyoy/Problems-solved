def max_sum(arr):
    # determine the first possible max sum by summing up the first
    # and last element of the vector
    sum_max = arr[0] + arr[len(arr)-1]
    # store the elements that form the pair with the maximum sum
    element_1, element_2 = arr[0], arr[len(arr)-1]

    # pop the elements already used
    arr.pop(0)
    arr.pop(len(arr)-1)

    # checking if exists another pair with a bigger sum
    while arr:
        # determine the next possible max sum
        pos_sum = arr[0] + arr[len(arr)-1]
        if sum_max < pos_sum:
            element_1, element_2 = arr[0], arr[len(arr)-1]
            sum_max = pos_sum
        # pop the elements already used
        arr.pop(0)
        arr.pop(len(arr)-1)
    # create an empty list
    result = []
    # append to the list the results : the pair with the max sum
    # and the elements that form it
    result.append(sum_max), result.append(element_1), result.append(element_2)

    # return the list with the results
    return result
