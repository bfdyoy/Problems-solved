from random_generator import random_input
import glob
import graph_implementation as graph
import time


def main():
    # Set the number of maximum nodes in the graph
    max_no_towers = 10
    no_test_files = 10

    # Build the input by calling the function 'random_input' from
    # the random_generator module
    random_input(max_no_towers)
    result = []
    bipartite = [True for iterator in range(no_test_files)]
    test_iterator = 0

    # Get the name of each input file and open one at the time by using
    # the function 'glob' from 'glob' module
    for filename in sorted(glob.glob('tests/test_*.in', recursive=True)):
        # Open one input file at the time and store data into one list
        with open(filename, "r") as openedfile:
            # Create an empty list
            array = []
            for line in openedfile:
                array.append(line)

            # Convert the list from 'str' to 'int'
            array = list(map(int, array))
            no_towers = 0

            # Store 'no_towers' which represents the number of vertices
            # in the graph
            if len(array) > 0:
                no_towers = array[0]
                array.pop(0)
                array.pop(0)

            # Create a disconnected graph with 'no_towers' vertices
            g = graph.Graph(no_towers)

            # The list has an even number of elements, each pair of elements
            # (array[0], array[1]) represents a connection from the node represented
            # in array[0] to array[1], and a connection from array[1] to array[0] since
            # the graph is undirected
            while array:
                tunnel_1 = array[0]
                tunnel_2 = array[1]
                array.pop(0)
                array.pop(0)
                # If these two nodes aren't already connected, connect them
                if not g.is_connected(tunnel_1, tunnel_2):
                    g.connect_nodes(tunnel_1, tunnel_2)
                    g.connect_nodes(tunnel_2, tunnel_1)
            
            # Close the opened input file
            openedfile.close()
            
            # Store time before running
            start = time.time()
            
            # If the graph is not bipartite, change bipartite[test_iterator] to False, 
            # the list 'bipartite' will keep track of which input file has
            # a bipartite graph
            if not g.is_bipartite():
                bipartite[test_iterator] = False
            else:
                # If the graph is bipartite, store the coloring into the result
                # list. 'bipartite[test_iterator]' will not be changed, since it was 
                # initialised with True for every test
                result.append(g.color_arr)
            
            # Increase the value of 'test_iterator'
            test_iterator += 1
            
            # Store time after measured block ends
            end = time.time()
            
            # Print running time for each test
            print('%s : %.3lfs' % (filename, end - start))
    # Set 'iterator_1' and 'test_iterator' to 0 so we can iterate over the
    # 'bipartite' and 'result' list in the correct order
    iterator_1 = 0
    test_iterator = 0

    # getting the name of each output file using the function glob
    # from the glob module
    for filename in sorted(glob.glob('tests/test_*.out', recursive=True)):
        # open one output file at the time to write the results
        with open(filename, "w+") as openedfile:
            # Check if the graph from input is bipartite or not. If it is,
            # print how to towers can be assigned, else print 'Impossible'
            if not bipartite[test_iterator]:
                openedfile.write('NO ! \n')
                openedfile.close()
                test_iterator += 1
            else:
                openedfile.write('YES ! \n\n')
                openedfile.write('First possibility : \n\n')
                for iterator_2 in range(len(result[iterator_1])):
                    if result[iterator_1][iterator_2] == -1:
                        openedfile.write('Tower no. %d -> Attack tower\n' % (iterator_2 + 1))
                    else:
                        openedfile.write('Tower no. %d -> Defense tower\n' % (iterator_2 + 1))
                openedfile.write('\nSecond possibility : \n\n')
                for iterator_2 in range(len(result[iterator_1])):
                    if result[iterator_1][iterator_2] == -1:
                        openedfile.write('Tower no. %d -> Defense tower\n' % (iterator_2 + 1))
                    else:
                        openedfile.write('Tower no. %d -> Attack tower\n' % (iterator_2 + 1))
                iterator_1 += 1
                test_iterator += 1

            # Closes the opened file
            openedfile.close()


main()
