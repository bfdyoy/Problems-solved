#ifndef CODE_CIRCULARLIST_H
#define CODE_CIRCULARLIST_H

// structure for a node in the linked list
struct node
{
    int data; // variable to store data (number of children)
    struct node *next; // pointer to the next node in the list
};

struct node *create_new_node(int data);
void get_order_children(struct node *head, int count_no, int *order);


#endif //CODE_CIRCULARLIST_H
