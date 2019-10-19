# import all the modules we need for this program
import sort_algorithm
import random_vector as rv
import pair_algorithm as pa
import glob
import time
VECTOR_MAX_LENGTH = 1000
# vector_max_length is actually n from the problem statement
# it can be odd
VECTOR_UPPER_LIMIT_VALUE = 25000
# vector_upper_limit_value is the maximum value that an element
# can be


def main():

    # build the input files by calling the function build_rand_vector
    # from the random_vector module
    rv.build_rand_vector(VECTOR_MAX_LENGTH, VECTOR_UPPER_LIMIT_VALUE)
    array = []
    results_array = []

    # getting the name of each input file using the function glob
    # from the glob module
    for filename in glob.glob('tests/test_*.in', recursive=True):
        # open one input file for reading the vector
        with open(filename, "r") as openedfile:
            for line in openedfile:
                array.append(line)
            # close the opened file
            openedfile.close()
            # convert the array from string to integer
            array = list(map(int, array))
            # store time before running
            start = time.time()
            # sort the array using Merge Sort from the sort_algorithm module
            array = sort_algorithm.mergesort(array)
            # append to the results array the results for each file
            results_array += pa.max_sum(array)
            # store time after measured block ends
            end = time.time()
            # print running time for each test
            print("%s : %lf" % (filename, end - start))

    # setting iterator to 0 so we can print the results in the right way
    iterator = 0
    # getting the name of each output file using the function glob
    # from the glob module
    for filename in sorted(glob.glob('tests/test_*.out', recursive=True)):
        # open one output file for writing the results
        with open(filename, "w+") as openedfile:
            openedfile.write('%d <-- (%d, %d)' % (results_array[iterator], results_array[iterator+1],
                                                  results_array[iterator+2]))
            # close the opened file
            openedfile.close()
            # move to the next results
            iterator += 3


# call the main function
main()
