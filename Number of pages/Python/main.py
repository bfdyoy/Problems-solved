# import all the modules we need for this program
from generate_sum_digits import compute_digits_used
from random_number_digits import random_sum_number_pages
from algorith_used import find_number_pages
import glob
import time

# global variable used for creating valid inputs
MAX_PAGES = 400

# call the functions that create input files
compute_digits_used(MAX_PAGES)
random_sum_number_pages(MAX_PAGES)


def main():
    value = []
    iterator = 0
    # open each input file and create an array where all the inputs
    # are stored
    for filename in glob.glob('tests/test_*.in', recursive=True):
        with open(filename, "r") as openedfile:
            for line in openedfile:
                value.append(line)
            openedfile.close()

    # convert the array to int
    value = list(map(int, value))
    # for each element of the array (input from each file) determine
    # the result and print it into the output file
    for filename in glob.glob('tests/test_*.out', recursive=True):
        with open(filename, "w+") as openedfile:
            # store in the variable result the return value of
            # of function "find_number_pages"
            start = time.time()
            result = find_number_pages(value[iterator])
            # writing in the output file the result of the function
            # for its specific input value
            end = time.time()
            openedfile.write('%d' % result)
            # increase the iterator so we can print the next result
            # of the next test
            print("%s : %f" % (filename, end - start))
            iterator += 1
            # close the opened file
            openedfile.close()


# call the main function
main()
