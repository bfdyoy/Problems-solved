#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <stdbool.h>
#include "generator.h"
#include "graph.h"

#define TESTS_NO 10
#define FILENAME_SIZE 20

#define ATTACK -1

int main()
{
    unsigned int no_max_towers = 10;
    unsigned int no_max_tunnels = (no_max_towers * (no_max_towers - 1)) / 2;

    // Setting the time for rand() calls
    srand(time(NULL));

    // Generate all the input files for the problem
    generate_input(no_max_towers, no_max_tunnels);

    // Read all problem 1 input and output files
    for (int tests_iterator = 1; tests_iterator <= TESTS_NO; tests_iterator++)
    {
        // Vectors used to store the name of the input and output files
        char temp_name_in[FILENAME_SIZE];
        char temp_name_out[FILENAME_SIZE];

        // Used for computing running time of a code block
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

        // Variables used to create the graph
        int no_towers;
        int no_tunnels;
        int first_elem_pair;
        int second_elem_pair;

        int iterator;

        fscanf(test_in, "%d", &no_towers);
        fscanf(test_in, "%d", &no_tunnels);

        struct Graph* graph = createGraph(no_towers);

        // Read all input from the file and build the graph
        for (iterator = 1 ; iterator <= no_tunnels ; iterator++)
        {
            fscanf(test_in, "%d", &first_elem_pair);
            fscanf(test_in, "%d", &second_elem_pair);
            // Checking if the connection was added to the adjacency
            // list before
            if ( search_by_destination(graph, first_elem_pair, second_elem_pair) == false )
            {
                addEdge(graph, first_elem_pair, second_elem_pair);
            }
            // Add an edge from source to destination and from
            // destination to source since we have an undirected
            // graph
            if ( search_by_destination(graph, second_elem_pair, first_elem_pair) == false )
            {
                addEdge(graph, second_elem_pair, first_elem_pair);
            }
        }

        // Create a color array to store the colors assigned
        // to all vertices. The value '0' means that the vertex
        // wasn't visited yet, the value '-1' is used to indicate
        // the first color and the value '2' is used to indicate
        // the second color
        int *color_arr = malloc((graph->V + 1) * sizeof(int) );
        for (iterator = 1; iterator <= graph->V; iterator++)
        {
            color_arr[iterator] = 0;
        }

        // Boolean variable which stores the result of the function
        // is_bipartite, true if the graph is bipartite, else false
        bool bipartite;

        // store time before running
        start = clock();


        bipartite = is_bipartite(graph, color_arr);

        for (iterator = 1; iterator <= graph->V; iterator++)
        {
            if(graph->array[iterator].head == NULL)
            {
                color_arr[iterator] = 2;
            }
        }

        if (bipartite == true)
        {
            fprintf(test_out,"YES !\n\n");
            // first possibility
            fprintf(test_out, "First possibility: \n\n");
            for (iterator = 1; iterator <= graph->V; iterator++)
            {
                if (graph->array[iterator].head == NULL)
                {
                    fprintf(test_out,"Tower number %d -> Defense Tower ", iterator);
                }
                else
                {
                    if(color_arr[iterator] == ATTACK)
                    {
                        fprintf(test_out, "Tower number %d -> Attack Tower", iterator);
                    }
                    else
                    {
                        fprintf(test_out, "Tower number %d -> Defense Tower", iterator);
                    }
                }
                fprintf(test_out,"\n");
            }
            fprintf(test_out, "\nSecond possibility : \n\n");
            // second possibility
            for (iterator = 1; iterator <= graph->V; iterator++)
            {
                if (graph->array[iterator].head == NULL)
                {
                    fprintf(test_out,"Tower number %d -> Attack Tower ", iterator);
                }
                else
                {
                    if(color_arr[iterator] == ATTACK)
                    {
                        fprintf(test_out, "Tower number %d -> Defense Tower", iterator);
                    }
                    else
                    {
                        fprintf(test_out, "Tower number %d -> Attack Tower", iterator);
                    }
                }
                fprintf(test_out,"\n");
            }
        }
        else
        {
            fprintf(test_out, "NO !");
        }
        // store time after measured block ends
        finish = clock();

        // determine the running time for the code block
        duration = (double)(finish - start) / CLOCKS_PER_SEC;

        printf("Test %d duration: %.3fs \n", tests_iterator, duration);
        free(color_arr);
        free(graph);

        fclose(test_in);
        fclose(test_out);
    }
    return 0;
}
