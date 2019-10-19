#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "generator.h"

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
// depending on the variables "max_towers" and "max_tunnels"
void generate_input(unsigned int max_towers, unsigned int max_tunnels)
{
    // All problem 1 input files are considered output files for this function
    // because there will be stored the randomly generated numbers;
    for (int tests_iterator = 1; tests_iterator <= TESTS_NO; tests_iterator++)
    {
        // Variables used to store the randomly generated values
        // in range (1, max_towers) and (1, max_tunnels)
        unsigned int random_no_towers;
        unsigned int random_no_tunnels;
        int iterator = 0;
        uint32_t state[1] = {rand()%1234};

        // Store the names of problem 1 input files there's no need
        // for 2 char arrays because we don't read anything
        // here we just create the input file for the problem
        char temp_name_out[FILENAME_SIZE];

        sprintf(temp_name_out, "tests\\test_%d.in", tests_iterator);

        FILE* output_file = fopen(temp_name_out, "w");

        // Making sure the fortress has more than 1 tower
        if (random_no_towers > 32767)
        {
            while (1)
            {
                // Generate a random number which represents the number of
                // towers the fortress has and
                random_no_towers = xorshift32(state);
                if (random_no_towers <= max_towers)
                {
                    break;
                }
            }

            fprintf(output_file,"%d\n", random_no_towers);

            while (1)
            {
                random_no_tunnels = xorshift32(state);
                if (random_no_tunnels <= (random_no_towers*(random_no_towers-1)/2))
                {
                    break;
                }
            }
            fprintf(output_file, "%d\n\n", random_no_tunnels);
        }
        else
        {
            random_no_towers = rand()%max_towers+2;
            random_no_tunnels = rand()%(random_no_towers * (random_no_towers-1)) / 2 + 1;
            fprintf(output_file,"%d\n", random_no_towers);
            fprintf(output_file, "%d\n\n", random_no_tunnels);
        }

        // Variables used to store the towers that have a tunnel
        // between them
        unsigned int random_tower_2;
        unsigned int random_tower_1;

        iterator = 0;

        while (iterator != random_no_tunnels)
        {
            if (random_no_towers >= 32768)
            {
                while(1)
                {
                    random_tower_1 = xorshift32(state);
                    if (random_tower_1 <= random_no_towers)
                    {
                        break;
                    }
                }

                while(1)
                {
                    random_tower_2 = xorshift32(state);
                    if (random_tower_2 <= random_no_towers)
                    {
                        break;
                    }
                }
                // Checking if the tunnel doesn't lead to the same tower
                if(random_tower_1 != random_tower_2)
                {
                    fprintf(output_file, "%u %u\n", random_tower_1, random_tower_2);
                    iterator++;
                }
            }
            else
            {
                random_tower_1 = rand()%random_no_towers+1;
                random_tower_2 = rand()%random_no_towers+1;
                if(random_tower_1 != random_tower_2)
                {
                    fprintf(output_file, "%u %u\n", random_tower_1, random_tower_2);
                    iterator++;
                }
            }
        }
        fclose(output_file);
    }
}
