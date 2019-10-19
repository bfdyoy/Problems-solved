#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include "generator.h"
#include "circularlist.h"

#define TESTS_NO 10
#define FILENAME_SIZE 20


int main()
{

    // Maximum number of children that could play the game
    static unsigned int max_children = 10;
    // Maximum number to count up to
    static unsigned int max_number = 10;

    // setting the time for rand() calls
    srand(time(NULL));

    generate_input(max_children, max_number);

    // read all problem 1 input and output files
    for (int tests_iterator = 1; tests_iterator <= TESTS_NO; tests_iterator++)
    {
        // vectors used to store the name of the input and output files
        char temp_name_in[FILENAME_SIZE];
        char temp_name_out[FILENAME_SIZE];

        // used for computing running time of a code block
        clock_t start, finish;
        double  duration;

        sprintf(temp_name_in, "tests\\test_%d.in", tests_iterator);
        sprintf(temp_name_out, "tests\\test_%d.out", tests_iterator);

        FILE* test_in = fopen(temp_name_in, "r");
        FILE* test_out = fopen(temp_name_out, "w");

        // checking if the files were opened
        if(!test_in || !test_out)
        {
            return -1;
        }

        // Variables used to store information about the
        // number of children and the number they need to
        // count up to for each game (test_1 to test_10)
        int number_children;
        int number_to_count;

        fscanf(test_in, "%d", &number_children);
        fscanf(test_in, "%d", &number_to_count);

        // No use of dummy pointers, the head will store
        // the value '1' which represents children number 1
        struct node *head = create_new_node(1);
        struct node *prev = head;

        // Create the circular linked list which will contain
        // 'number_children' nodes
        for (int iterator = 2; iterator <= number_children; iterator++)
        {
            // Add the new node to the end of the list
            prev->next = create_new_node(iterator);
            prev = prev->next;
        }

        // Link the last node to the first which is head so the
        // list is circular
        prev->next = head;

        // Vector that will keep track of the order the children
        // were eliminated
        int *eliminated_children = malloc(number_children * sizeof(int));

        // store time before running
        start = clock();

        get_order_children(head, number_to_count, eliminated_children);

        // store time after measured block ends
        finish = clock();

        // Print the order the children were eliminated
        for (int iterator = 0; iterator < number_children; iterator++)
        {
            fprintf(test_out, "%d. Children no. %d\n",
                    iterator+1, eliminated_children[iterator]);
        }

        // determine the running time for the code block
        duration = (double)(finish - start) / CLOCKS_PER_SEC;

        printf("Test %d duration: %.3fs \n", tests_iterator, duration);

        fclose(test_in);
        fclose(test_out);
        // Free memory occupied by the list and the vector
        free(head);
        free(eliminated_children);
    }

    return 0;

}
