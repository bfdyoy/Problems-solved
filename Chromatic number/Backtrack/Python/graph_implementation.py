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

    # Connect 'vertex_2' to 'vertex_1'
    def connect_nodes(self, vertex_1, vertex_2):
        self.AdjList[vertex_1].append(vertex_2)

    # Check if vertex 'vertex_2' is connected to 'vertex_1'
    def is_connected(self, vertex_1, vertex_2):
        return vertex_2 in self.AdjList[vertex_1]

    def is_safe(self, current_vertex, colors, current_color):
        # Iterate trough adjacent vertices
        # and check if the vertex color is different from the
        # current color
        for iterator in range(self.V):
            if current_color == colors[iterator] and self.is_connected(current_vertex, iterator):
                return False
        return True

    def graph_coloring(self, no_colors, colors, current_vertex):
        # Check if all vertices are assigned a color
        if current_vertex == self.V:
            return True
    
        # Trying different color for the vertex 'current_vertex'
        for color in range(1, no_colors + 1):
            # Check if assignment of color 'color' to 'current_vertex'
            # is possible
            if self.is_safe(current_vertex, colors, color):
                # Assign color 'color' to 'current_vertex'
                colors[current_vertex] = color
                # Recursively assign colors to the rest of the vertices
                if self.graph_coloring(no_colors, colors, current_vertex + 1):
                    return True
                # If there is no solution, remove color and
                # go back (backtrack)
                colors[current_vertex] = 0
