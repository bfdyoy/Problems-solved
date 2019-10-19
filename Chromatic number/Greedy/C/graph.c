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

// Connect 2 nodes in a directed graph
void addEdge(struct Graph* graph, int source, int destination)
{
    // Add an edge from source to destination.  A new node is
    // added to the adjacency list of source.  The node
    // is added at the begining
    struct AdjListNode* newNode = newAdjListNode(destination);
    newNode->next = NULL;
    graph->array[source].head = newNode;
}

// Function that colors a graph using the greedy algorithm
void greedy_coloring(struct Graph *graph, int *color)
{
    // Array to keep track of the used colors
    int *used = calloc(graph->V, sizeof(int));

    // Assign the first color to the first vertex
    color[1] = 0;

    // Assign colors to the remaining V-1 vertices
    for(int iterator = 2; iterator <= graph->V; iterator++)
    {
        // If the vertex is isolated, assign him the first
        // color
        if(graph->array[iterator].head == NULL)
        {
            color[iterator] = 0;
        }
        // If the vertex has at least one connection, find
        // the first unused color
        else
        {
            // Create a new Adjacency List variable so we can
            // iterate over the vertex's neighbours
            struct AdjList *iterator_2 = malloc(sizeof(struct AdjList));
            iterator_2->head = graph->array[iterator].head;

            // Iterate over the adjacency list and change the colors
            // of adjacent vertices as used(1)
            while(1)
            {
                if(color[iterator_2->head->destination] != -1)
                {
                    used[color[iterator_2->head->destination]] = 1;
                }

                if(iterator_2->head->next == NULL)
                {
                    break;
                }

                iterator_2->head = iterator_2->head->next;
            }

            int current;

            // Find the first unused color
            for(current = 0; current < graph->V; current++)
            {
                if(used[current] == 0)
                {
                    break;
                }
            }

            // Assign the found color to the current vertex
            color[iterator] = current;

            // Initialize 'iterator_2' to point to the start of
            // the adjacency list
            iterator_2->head = graph->array[iterator].head;

            // Reset the values back to false(0) for the next iteration
            while(1)
            {
                if(color[iterator_2->head->destination] != -1)
                {
                    used[color[iterator_2->head->destination]] = 1;
                }

                if(iterator_2->head->next == NULL)
                {
                    break;
                }

                iterator_2->head = iterator_2->head->next;

            }
            // Free memory used for the adjacency list iterator
            free(iterator_2);
        }
    }
    // Free memory used for the temporary array
    free(used);
}
