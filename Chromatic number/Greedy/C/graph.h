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

struct AdjListNode* newAdjListNode(int destination);
struct Graph* createGraph(int vertices);
int search_by_destination(struct Graph* graph, int source, int destination);
void addEdge(struct Graph* graph, int source, int destination);
void greedy_coloring(struct Graph *graph, int *color);

#endif // CODE_GRAPH_H

