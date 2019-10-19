def compute_digits_used(max_pages):
    # for this specific problem, a valid value represents
    # the number of digits used in a numbered book with
    # "full pages", so we won't have page 0.5 or page 0.7 etc.

    # open the file where the valid inputs should go
    f = open("sum_digits.in", "w+")
    # variable used to store how many digits were used in a
    # numbered book with "iterator" pages
    sum_digits = 0

    # variable used to count how many digits are used for a page
    digits_page = 0

    # in this loop we simply determine how many digits were used
    # in a numbered book with "iterator" pages until we write
    # the digits used in a numbered book with "max_pages" pages
    for iterator in range(1, max_pages+1, 1):
        aux = iterator

        # determine how many digits are used for the page "iterator"
        while aux != 0:
            digits_page += 1
            aux = aux // 10

        # the number of digits is increased with "digits_page"
        sum_digits = sum_digits + digits_page
        # writing into the file the valid value "number_digits"
        f.write("%d\n" % sum_digits)
        # set the number of digits for the current page to 0
        digits_page = 0

    # close the opened file
    f.close()
