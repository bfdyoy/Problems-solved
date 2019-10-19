#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "rand_generator.h"
#include "graph.h"
#include "utils.h"

#define TESTS_NO 10
#define FILENAME_SIZE 20

int main()
{
    unsigned int no_max_vertices = 20;

    // Setting the time for rand() calls
    srand(time(NULL));

    // Generate all the input files for the problem
    generate_input(no_max_vertices);

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

        int no_vertices;
        int no_edges;
        int edge_1;
        int edge_2;
        int *colors;
        int minimum_colors;

        // Store the number of vertices and edges of the graph
        fscanf(test_in, "%d", &no_vertices);
        fscanf(test_in, "%d", &no_edges);

        // Create an isolated graph with 'no_vertices' vertices
        struct Graph* grph = createGraph(no_vertices);

        // Create a temporary array to store the color of each vertex
        colors = (int*) malloc((no_vertices+1)*sizeof(int));

        // Initialize each element of the colors array to -1
        // since 0 is the first color
        for(int iterator = 0; iterator <= grph->V; iterator++)
        {
            colors[iterator] = -1;
        }

        // Connect the vertices in the graph according to the
        // input file
        for(int iterator = 1; iterator <= no_edges; iterator++)
        {
            fscanf(test_in, "%d", &edge_1);
            fscanf(test_in, "%d", &edge_2);

            // If these two nodes aren't already connected,
            // connect them
            if(search_by_destination(grph, edge_1, edge_2) == -1)
            {
                addEdge(grph, edge_1, edge_2);
                addEdge(grph, edge_2, edge_1);
            }
        }

        // Store time before running
        start = clock();

        greedy_coloring(grph, colors);
        minimum_colors = get_max(colors, no_vertices);

        // Store time after measured block ends
        finish = clock();

        // Determine the running time for the code block
        duration = (double) (finish - start) / CLOCKS_PER_SEC;

        printf("Test %d duration: %.3fs \n", tests_iterator, duration);

        fprintf(test_out, "%d", minimum_colors+1);

        // Free the memory occupied by the graph and the colors
        // array
        free(colors);
        free(grph);

        // Close the opened files
        fclose(test_in);
        fclose(test_out);
    }
    return 0;
}
