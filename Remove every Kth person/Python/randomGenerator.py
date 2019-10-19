import glob
import random


def random_input(max_no_children, max_to_count):
    # Open each input file and write the 2 randomly generated
    # values
    for filename in glob.glob('tests/test_*.in', recursive=True):
        with open(filename, "w+") as openedfile:
            random_number = random.randrange(1, max_no_children+1, 1)
            openedfile.write('%d\n' % random_number)
            random_number = random.randrange(1, max_to_count+1, 1)
            openedfile.write('%d\n' % random_number)
            openedfile.close()
