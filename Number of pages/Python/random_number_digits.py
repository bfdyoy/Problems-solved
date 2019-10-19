import glob
import random


def random_sum_number_pages(max_pages):
    # store all the valid inputs into an array
    with open("sum_digits.in", "r") as file:
        array = []
        for line in file:
            # append to the vector the read value from opened file
            array.append(line)
        # close the opened file
        file.close()
    # create the input by randomly generate a index and extract the
    # value from that index which represents an input in one file
    for filename in glob.glob('tests/test_*.in', recursive=True):
        with open(filename, "w+") as openedfile:
            # generate a random value for random_index in range 0 .. max_pages
            random_index = random.randrange(0, max_pages + 1, 1)
            # storing the random value into the "value" variable
            value = array[random_index]
            # write the randomly generated value into the input file
            openedfile.write(value)
            # close the opened file
            openedfile.close()
