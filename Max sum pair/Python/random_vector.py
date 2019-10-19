# import all the modules we need for this module
import random
import glob


# function that will print into the test_%d.in a randomly
# generate value for vector_length and vector_length elements
# randomly generated
def build_rand_vector(max_length, max_value):

    # for each input test file generate
    for filename in glob.glob('tests/test_*.in', recursive=True):
        with open(filename, "w+") as openedfile:
            # generate a number in range 1 - max_length which
            # represents the vector_length/2
            random_length = random.randrange(1, max_length + 1, 1)

            # determine the final length of the vector which is
            # 2*n from problem's statement
            random_length = random_length * 2

            # generate "random_length" elements in range(max_value+1)
            for iterator in range(random_length):
                random_value = random.randrange(0, max_value + 1, 1)
                # write into the file the generated number
                openedfile.write("%d\n" % random_value)
            # close the opened file
            openedfile.close()
