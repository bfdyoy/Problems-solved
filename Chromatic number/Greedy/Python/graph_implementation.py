class Graph:
    # Create a graph with 'n' vertices and no connected vertices
    def __init__(self, no_vertices):
        # Store the number of vertices
        self.V = no_vertices
        # Create 'n' empty lists for the adjacency list
        self.AdjList = [[] for iterator in range(no_vertices)]

    # Connect 'vertex_2' to 'vertex_1'
    def connect_nodes(self, vertex_1, vertex_2):
        self.AdjList[vertex_1].append(vertex_2)

    # Check if vertex 'vertex_2' is connected to 'vertex_1'
    def is_connected(self, vertex_1, vertex_2):
        return vertex_2 in self.AdjList[vertex_1]

    def greedy_coloring(self, color):
        # List to store used colors
        used = [0] * self.V

        # Assign the first color to the first vertex
        color[0] = 0

        # Assign colors to the remaining V-1 vertices
        for iterator in range(1, self.V):
            # Iterate over the adjacency list change the colors of
            # adjacent vertices as used(1 or True)
            for iterator_2 in range(len(self.AdjList[iterator])):
                used[color[self.AdjList[iterator][iterator_2]]] = True
            current = 0

            # Find the first unused color
            for current in range(self.V):
                if not used[current]:
                    break

            # Assign the found color
            color[iterator] = current

            # Reset the values back to false for the next iteration
            for iterator_2 in range(len(self.AdjList[iterator])):
                if color[self.AdjList[iterator][iterator_2]] != -1:
                    used[color[self.AdjList[iterator][iterator_2]]] = False
