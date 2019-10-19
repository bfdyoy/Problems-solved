#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "graph.h"
// Function to create a new node for the Queue
struct queue_node *new_node(int new_key)
{
    struct queue_node *newNode = (struct queue_node*) malloc(sizeof(struct queue_node));
    newNode->key = new_key;
    newNode->next = NULL;
    return newNode;
}
// Function that returns true if the Queue is empty,
// else false
bool queue_is_empty (struct Queue *queue)
{
    // If front points to NULL, the Queue is empty
    if (queue->front == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}
// Function that returns a new empty queue
struct Queue *createQueue()
{
    struct Queue *newQueue = (struct Queue*) malloc(sizeof(struct Queue));
    newQueue->front = newQueue->last;
    newQueue->last = NULL;
    return newQueue;
}
// Function that inserts an element into the Queue
void push_queue (struct Queue *queue, int key)
{
    // Create a new node
    struct queue_node* newNode = new_node(key);

    // If the queue is empty, the new node is
    // front and last
    if(queue->last == NULL)
    {
        queue->front = newNode;
        queue->last = newNode;
        return;
    }
    // Add the new node at the end of queue
    // and change last if the queue is not empty
    queue->last->next = newNode;
    queue->last = newNode;

}
// Function that returns the first element of a queue
// if it isn't empty
int pop_queue(struct Queue *queue)
{
    int key;
    // If the queue is empty, return NULL
    if (queue->front == NULL)
    {
        return NULL;
    }

    // Store the value front points to and move front
    // to the next element of the queue
    struct queue_node *poped_node = queue->front;
    queue->front = queue->front->next;

    // If front becomes NULL, then the list is empty
    // and last is also NULL
    if (queue->front == NULL)
    {
        queue->last = NULL;
    }

    key = poped_node->key;

    free(poped_node);

    return key;
}
// Function that returns true if the vertices source and
// destination are connected
bool search_by_destination(struct Graph* graph, int source, int destination)
{
    struct AdjListNode* iterator = graph->array[source].head;
    while (iterator)
    {
        if(iterator->destination == destination)
        {
            return true;
        }
        iterator = iterator->next;
    }
    return false;
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

// This function returns true if a subgraph with the root vertex
// source is bipartite, else false
bool bipartite_subgraph(struct Graph *graph, int source, int *color_arr)
{
    color_arr[source] = -1;

    // Create a queue of vertex members and add to the queue
    // the source vertex for BFS traversal
    struct Queue *queue = createQueue();
    push_queue(queue, source);

    // Run while there are still vertices in the queue
    while(!queue_is_empty(queue))
    {
        // Pop the first element from the queue
        int aux;
        aux = pop_queue(queue);

        // Return false if the vertex has a self-loop
        if (search_by_destination(graph, aux, aux) == true)
        {
            return false;
        }

        // Find all uncolored adjacent vertices
        for(int iterator = 1; iterator <= graph->V; iterator++)
        {
            // Check if an edge from aux to iterator exists and the
            // destination is not colored
            if ((search_by_destination(graph, aux, iterator) == true) &&
                (color_arr[iterator] == 0))
            {
                // Assign another color to the adjacent vertex
                color_arr[iterator] = 1- color_arr[aux];
                push_queue(queue, iterator);
            }
            // Check if there is an edge between aux and iterator
            // and if they have the same color
            else if ( (search_by_destination(graph, aux, iterator) == true) &&
                     (color_arr[aux] == color_arr[iterator]) )
            {
                return false;
            }
        }
    }
    // Return true if all adjacent vertices can be
    // colored using 2 colors
    return true;
}
// This function return true if a graph is bipartite,
// else false
bool is_bipartite(struct Graph* graph, int *color_arr)
{
    // Code to handle disconnected graph
    for (int iterator = 1; iterator <= graph->V; iterator++)
    {
        // Check if the vertex "iterator" is not colored
        if (color_arr[iterator] == 0)
        {
            if(bipartite_subgraph(graph, iterator, color_arr) == false)
            {
                return false;
            }
        }
    }
    return true;
}
