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
int is_safe(struct Graph *graph , int current_vertex, int *colors, int current_color);
int graph_coloring (struct Graph* graph, int no_colors, int *colors, int current_vertex);

#endif // CODE_GRAPH_H
