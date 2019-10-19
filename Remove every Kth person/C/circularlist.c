#include <stdlib.h>
#include <stdio.h>
#include "circularlist.h"


// Function that creates a new node of the linked list
struct node *create_new_node(int data)
{
    // Allocate memory the a new node in the list
    struct node *temp = malloc(sizeof(struct node*));
    // link the node to himself because we don't use
    // dummy pointers for head/tail, head stores the
    // first value
    temp->next = temp;
    // Store data
    temp->data = data;
    return temp;
}


// Function that builds the vector which contains the
// order in which the children are removed from the game
void get_order_children(struct node *head, int count_no, int *order)
{
    // Variable used in storing the order in which the children
    // are eliminated from the game
    int aux = 0;

    struct node *list_iterator_1 = head;
    struct node *list_iterator_2 = head;
    int count;

    // Pop nodes in the list until it has only one element
    while (list_iterator_1->next != list_iterator_1)
    {
        // Count from 1 up to 'count_no' and pop the
        // 'count_no'-th node
        count = 1;
        while (count != count_no)
        {
            list_iterator_2 = list_iterator_1;
            list_iterator_1 = list_iterator_1->next;
            count++;
        }
        // Store the number of the popped child into the array
        // to keep track of the order they were eliminated
        order[aux] = list_iterator_1->data;
        aux++;
        // Remove the 'count_no'-th node since the child from
        // that position is out of the game
        list_iterator_2->next = list_iterator_1->next;
        list_iterator_1 = list_iterator_2->next;
    }
    // Store the last child in the game, counting from 1 up to
    // 'count_no' will result in his elimination
    order[aux] = list_iterator_1->data;
}
