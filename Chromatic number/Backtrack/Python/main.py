from random_generator import random_input
import glob
import graph_implementation as graph
import time


def main():
    no_max_vertices = 20
    results = []
    random_input(no_max_vertices)

    # Get the name of each input file and open one at the time by using
    # the function 'glob' from 'glob' module
    for filename in sorted(glob.glob('tests/test_*.in', recursive=True)):
        # Open one input file at the time and store data into one list
        with open(filename, "r") as openedfile:
            # Create an empty list
            input_list = []
            for line in openedfile:
                input_list.append(line)
            # Convert the list from 'str' to 'int'
            input_list = list(map(int, input_list))
            no_vertices = 0

            if len(input_list) > 0:
                no_vertices = input_list[0]
                input_list.pop(0)
                input_list.pop(0)
            no_max_colors = no_vertices
            colors = [0] * no_max_colors
            g = graph.Graph(no_vertices)

            while input_list:
                node_1 = input_list[0]
                input_list.pop(0)
                node_2 = input_list[0]
                input_list.pop(0)
                # If these two nodes aren't already connected, connect them
                if not g.is_connected(node_1, node_2):
                    g.connect_nodes(node_1, node_2)
                    g.connect_nodes(node_2, node_1)

            openedfile.close()

            # Store time before running
            start = time.time()

            if g.graph_coloring(no_max_colors, colors, 0):
                results.append(max(colors))

            # Store time after measured block ends
            end = time.time()

            print('%s : %.3lfs' % (filename, end - start))
            
    # Get the name of each output file and open one at the time by using
    # the function 'glob' from 'glob' module
    for filename in sorted(glob.glob('tests/test_*.out', recursive=True)):
        # open one output file at the time to write the results
        with open(filename, "w+") as openedfile:
            # Print the number of colors used to color the graph
            # from the input file
            openedfile.write('%d' % results[0])
            results.pop(0)
            openedfile.close()


main()
