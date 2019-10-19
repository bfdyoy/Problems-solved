#ifndef CODE_GRAPH_H
#define CODE_GRAPH_H

struct AdjListNode
{
    int destination;
    struct AdjListNode* next;
};

struct AdjList
{
    struct AdjListNode *head;
};

struct Graph
{
    int V;
    struct AdjList* array;
};

struct queue_node
{
    int key;
    struct queue_node *next;
};

struct Queue
{
    struct queue_node *front;
    struct queue_node *last;
};

int pop_queue(struct Queue *queue);
void push_queue (struct Queue *queue, int key);
struct Queue *createQueue();
bool queue_is_empty (struct Queue *queue);
struct AdjListNode* newAdjListNode(int destination);
struct Graph* createGraph(int vertices) ;
bool search_by_destination(struct Graph* graph, int source, int destination);
void addEdge(struct Graph* graph, int source, int destination);
bool bipartite_subgraph(struct Graph* graph, int source, int *color_arr);
bool is_bipartite (struct Graph* graph, int* color_arr);


#endif // CODE_GRAPH_H
