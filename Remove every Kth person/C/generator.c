#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "generator.h"

#define TESTS_NO 10
#define FILENAME_SIZE 20

uint32_t xorshift32(uint32_t state[])
{
    // Algorithm "xor" from p. 4 of Marsaglia, "Xorshift RNGs"
    uint32_t x = state[0];
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    state[0] = x;
    return x;
}

void generate_input(unsigned int max_no_children, unsigned int max_number)
{
    for (int tests_iterator = 1; tests_iterator <= TESTS_NO; tests_iterator++)
    {
        unsigned int random_number;
        uint32_t state[1] = {rand()%12345};
        // store the names of problem 1 input files
        // there's no need for 2 char arrays because we don't read anything
        // from the input, here we just create the input file for the problem
        char temp_name_out[FILENAME_SIZE];

        sprintf(temp_name_out, "tests\\test_%d.in", tests_iterator);

        FILE* output_file = fopen(temp_name_out, "w");
        if (max_no_children > 32768)
        {
            while(1)
            {
                random_number = xorshift32(state);
                if (random_number <= max_no_children)
                {
                    break;
                }
            }
        }
        else
        {
            random_number = rand()%max_no_children+1;
        }

        fprintf(output_file,"%u\n", random_number);

        if (max_number > 32768)
        {
            while(1)
            {
                random_number = xorshift32(state);
                if (random_number <= max_number)
                {
                    break;
                }
            }
        }
        else
        {
            random_number = rand()%max_number+1;
        }

        fprintf(output_file,"%u\n", random_number);

        fclose(output_file);
    }
}
