def find_number_pages(sum_digits):
    # iterator used for determining how many digits are used
    # for pages with the same length, e.g: 1-9, 10-99, 100-999.
    iterator = 0
    while sum_digits - (9*pow(10, iterator)*(iterator + 1)) > 0:
        # "9 * 10^iterator * (iterator+1)" represents the number of
        # digits used for pages with length "iterator+1"
        sum_digits -= 9*pow(10, iterator)*(iterator + 1)
        iterator += 1
        # increase the length of a page after decreasing the
        # value of total digits used

    sum_digits /= (iterator + 1)
    # after the loop ends, in the variable "no_pages" will be
    # a value greater or equal to 0, either way, the will not be
    # a remainder because we got a valid input
    no_pages = sum_digits

    # summing up the total number of pages
    while (iterator - 1) >= 0:
        no_pages += 9 * pow(10, iterator - 1)
        iterator -= 1
    return no_pages
