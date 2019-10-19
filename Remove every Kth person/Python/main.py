from randomGenerator import random_input
import circularLinkedList as cLL
import glob
import time

# Maximum number of children that could play the game
max_children = 10
# Maximum number to count up to
max_no_to_count = 15


def main():
    # Generate the input files
    # random_input(max_children, max_no_to_count)
    values_input = []
    # Read all the problem 1 input and store data of each file
    for filename in sorted(glob.glob('tests/test_*.in', recursive=True)):
        with open(filename, "r") as of:
            for line in of:
                values_input.append(line)
            of.close()

    # Convert values_inputs's elements to int
    values_input = list(map(int, values_input))

    # Open each output file, one by one for writing the solution
    for filename in sorted(glob.glob('tests/test_*.out', recursive=True)):
        # open one output file for writing the results
        with open(filename, "w+") as openedfile:
            # Store the values for the current file's input and pop
            # the elements from the list so we don't need to iterate
            # over the list
            no_children = values_input[0]
            values_input.pop(0)
            no_to_count = values_input[0]
            values_input.pop(0)

            # Create the linked list
            head = cLL.CircularLinkedList()

            # Add to the list 'no_children' nodes, each one's data
            # representing the number of the child in the game
            for iterator in range(1, no_children+1):
                head.append(iterator)

            # Store time before running
            start = time.time()

            # Determine the order of children that were eliminated
            # from the game
            eliminated_children = cLL.eliminate_children(head, no_to_count)

            # Store time after measured block ends
            end = time.time()

            # Convert eliminated_children's elements from 'str' to 'int'
            eliminated_children = list(map(int, eliminated_children))

            # Iterate over the list containing the results and write
            # it into the output file
            for iterator in range(len(eliminated_children)):
                openedfile.write('%d. Children no. %d\n' % (iterator+1, eliminated_children[iterator]))

            # Print the running time for the code block
            print("%s : %f" % (filename, end - start))
            
            # Close the opened file
            openedfile.close()


# Call the main function
if __name__ == '__main__':
    main()
