#include <stdio.h>
#include <stdlib.h>
#include "random_vector.h"

#define TESTS_NO 10
#define FILENAME_SIZE 20

void random_vector(int max_length, int max_value)
{
    for (int tests_iterator = 1; tests_iterator <= TESTS_NO; tests_iterator++)
    {
        // variable used to store the length of the vector that will be
        // randomly generated
        int vector_length;
        char temp_name_in[FILENAME_SIZE];

        sprintf(temp_name_in, "data\\test_%d.in", tests_iterator);

        FILE* test_in = fopen(temp_name_in, "w");

        // vector_length will be even, and respect the format "2*n"
        vector_length = 2*((rand()*rand())%max_length+1);

        fprintf(test_in, "%d\n\n", vector_length);

        for(int iterator=1; iterator <= vector_length; iterator++)
        // generate "vector_length" elements in range 0 .. max_value,
        // because I used the rand()*rand() here a value of max_value
        // bigger than 2 ^ 15 won't be a problem
        {
            fprintf(test_in,"%d\n", (rand()*rand())%max_value+1);
        }

        fclose(test_in);
    }
}


