#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "rand_generator.h"

#define TESTS_NO 10
#define FILENAME_SIZE 20


uint32_t xorshift32(uint32_t state[])
{
    /* Algorithm "xor" from p. 4 of Marsaglia, "Xorshift RNGs" */
    uint32_t x = state[0];
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    state[0] = x;
    return x;
}

// Function that generates "TESTS_NO" files with random number
// depending on the variables "max_vertices"
void generate_input(unsigned int max_vertices)
{
    // All problem 1 input files are considered output files for this function
    // because there will be stored the randomly generated numbers;
    for (int tests_iterator = 1; tests_iterator <= TESTS_NO; tests_iterator++)
    {
        // Variables used to store the randomly generated values
        unsigned int random_no_vertices;
        unsigned int random_no_edges;
        int iterator = 0;
        uint32_t state[1] = {rand()%1234};

        // Store the names of problem 1 input files there's no need
        // for 2 char arrays because we don't read anything
        // here we just create the input file for the problem
        char temp_name_out[FILENAME_SIZE];

        sprintf(temp_name_out, "tests\\test_%d.in", tests_iterator);

        FILE* output_file = fopen(temp_name_out, "w");

        if (max_vertices >= 32768)
        {
            while (1)
            {
                // Generate a random number which represents the number of
                // edges the graph has
                random_no_vertices = xorshift32(state);
                if (random_no_vertices <= max_vertices)
                {
                    break;
                }
            }

            fprintf(output_file,"%d\n", random_no_vertices);

            while (1)
            {
                random_no_edges = xorshift32(state);
                if (random_no_edges <= ((random_no_vertices*(random_no_vertices-1))/2))
                {
                    break;
                }
            }
            fprintf(output_file, "%d\n\n", random_no_edges);
        }
        else
        {
            // Making sure the graph has more than 1 tower
            random_no_vertices = rand()%max_vertices+2;
            random_no_edges = rand()%((random_no_vertices * (random_no_vertices-1)) / 2) + 1;
            fprintf(output_file,"%d\n", random_no_vertices);
            fprintf(output_file, "%d\n\n", random_no_edges);
        }

        // Variables used to store the connected vertices
        unsigned int random_vertex_2;
        unsigned int random_vertex_1;

        iterator = 0;

        while (iterator != random_no_edges)
        {
            if (random_no_vertices >= 32768)
            {
                while(1)
                {
                    random_vertex_1 = xorshift32(state);
                    if (random_vertex_1 <= random_no_vertices)
                    {
                        break;
                    }
                }

                while(1)
                {
                    random_vertex_2 = xorshift32(state);
                    if (random_vertex_2 <= random_no_vertices)
                    {
                        break;
                    }
                }
                // Checking if a vertex has a self loop
                if(random_vertex_1 != random_vertex_2)
                {
                    fprintf(output_file, "%u %u\n", random_vertex_1, random_vertex_2);
                    iterator++;
                }
            }
            else
            {
                random_vertex_1 = rand()%random_no_vertices+1;
                random_vertex_2 = rand()%random_no_vertices+1;
                if(random_vertex_1 != random_vertex_2)
                {
                    fprintf(output_file, "%u %u\n", random_vertex_1, random_vertex_2);
                    iterator++;
                }
            }
        }
        fclose(output_file);
    }
}


