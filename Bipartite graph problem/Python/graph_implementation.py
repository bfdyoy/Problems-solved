class Queue:
    # Create an empty queue
    def __init__(self):
        self.items = []

    # Check if the queue is empty
    def is_empty(self):
        return self.items == []

    # Push an element in the queue
    def enqueue(self, data):
        self.items.append(data)

    # Pop the first element from the queue
    def dequeue(self):
        return self.items.pop(0)


class Graph:
    # Create a graph with 'n' vertices and no connected vertices
    def __init__(self, no_vertices):
        # Store the number of vertices
        self.V = no_vertices
        # Create 'n' empty lists for the adjacency list
        self.AdjList = [[] for iterator in range(no_vertices)]
        # Create the vector that will store each color of each vertex
        # initially '-1', none of the vertices are visited
        self.color_arr = [-1 for iterator in range(no_vertices)]

    # Connect 'vertex_2' to 'vertex_1'
    def connect_nodes(self, vertex_1, vertex_2):
        self.AdjList[vertex_1].append(vertex_2)

    # Check if vertex 'vertex_2' is connected to 'vertex_1'
    def is_connected(self, vertex_1, vertex_2):
        return vertex_2 in self.AdjList[vertex_1]

    # Function that returns true if the subgraph with root in 'source' is
    # bipartite, else false
    def bipartite_subgraph(self, source):
        # Create an empty queue
        queue = Queue()
        # Add the root into the queue
        queue.enqueue(source)

        # Run while there are still vertices in the queue
        while not queue.is_empty():
            # Pop the first element from the queue
            aux = queue.dequeue()

            # Return false if the vertex 'aux' has a self-loop
            if self.is_connected(aux, aux):
                return False

            # Find all uncolored adjacent vertices
            for iterator in range(self.V):
                # Check if 'aux' and 'iterator' are connected the
                # destination is not colored
                if self.is_connected(aux, iterator) and self.color_arr[iterator] == -1:
                    # Assign another color to the adjacent vertex
                    self.color_arr[iterator] = 1 - self.color_arr[aux]
                    queue.enqueue(iterator)
                # Check if 'aux' and 'iterator' are connected and have the
                # same color
                elif self.is_connected(aux, iterator) and self.color_arr[aux] == self.color_arr[iterator]:
                    return False

        return True

    # This function returns True if the graph is bipartite, else false
    def is_bipartite(self):
        # Code to handle disconnected graph
        for iterator in range(self.V):
            # Check if the vertex 'iterator' is not colored
            if self.color_arr[iterator] == -1:
                # Call the function 'bipartite_subgraph' to see if the subgraph
                # with the source node 'iterator' is bipartite or not.
                # If it is bipartite, continue to the next uncolored vertex,
                # else return False
                if not self.bipartite_subgraph(iterator):
                    return False
        return True
