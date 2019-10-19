#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

// Function that returns true if the vertices source and
// destination are connected
int search_by_destination(struct Graph* graph, int source, int destination)
{
    struct AdjListNode* iterator = graph->array[source].head;
    while (iterator)
    {
        if(iterator->destination == destination)
        {
            return 1;
        }
        iterator = iterator->next;
    }
    return -1;
}
// Function that return a new node in the adjacency list
struct AdjListNode* newAdjListNode(int destination)
{
    struct AdjListNode* newNode = (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->destination = destination;
    newNode->next = NULL;
    return newNode;
}
// Function that returns a new, empty graph with "vertices"
// vertices
struct Graph* createGraph(int vertices)
{
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = vertices;

    // Create an array of adjacency lists.  Size of
    // array will be V = vertices
    graph->array = (struct AdjList*) malloc((vertices + 1) * sizeof(struct AdjList));

    // Initialize each adjacency list as empty by
    // making head as NULL
    int iterator;
    for (iterator = 1; iterator <= vertices; iterator++)
    {
        graph->array[iterator].head = NULL;
    }

    return graph;
}

// Adds an edge to an undirected graph
void addEdge(struct Graph* graph, int source, int destination)
{
    // Add an edge from source to destination.  A new node is
    // added to the adjacency list of source.  The node
    // is added at the begining
    struct AdjListNode* newNode = newAdjListNode(destination);
    newNode->next = graph->array[source].head;
    graph->array[source].head = newNode;
}

int is_safe(struct Graph *graph , int current_vertex, int *colors, int current_color)
{
    // Iterate trough adjacent vertices and check if the vertex
    // color is different from the current color
    for(int iterator = 1; iterator <= graph->V; iterator++)
    {
        if(current_color == colors[iterator] && search_by_destination(graph, current_vertex,
                                                                      iterator) == 1)
        {
            return -1;
        }
    }
    return 1;
}

int graph_coloring (struct Graph* graph, int no_colors, int *colors, int current_vertex)
{
    // Check if all vertices are assigned a color
    if(current_vertex == graph->V+1)
    {
        return 1;
    }

    // Trying different color for the vertex 'current_vertex'
    for(int color_iterator = 1; color_iterator <= no_colors; color_iterator++)
    {
        // Check if assignment of color 'color_iterator' to
        // 'current_vertex' is possible
        if(is_safe(graph, current_vertex, colors, color_iterator) == 1)
        {
            // Assign the color 'color' to 'current_vertex'
            colors[current_vertex] = color_iterator;

            // Recursively assign colors to the rest of the
            // vertices
            if(graph_coloring(graph, no_colors, colors, current_vertex+1) == 1)
            {
                return 1;
            }
            // If there is no solution, remove the color and
            // go back (backtrack)
            colors[current_vertex] = 0;
        }
    }
}

