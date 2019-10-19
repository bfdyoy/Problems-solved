#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "vectors.h"
#include "sort.h"
#include "random_vector.h"

#define TESTS_NO 10
#define FILENAME_SIZE 20

static int vector_max_length = 10;
static int upper_limit_value = 20;

int main()
{
    // setting the time for rand() calls
    srand(time(NULL));
    // generate the input file with a random even vector length
    // and the elements of the vector
    random_vector(vector_max_length/2, upper_limit_value);

    // read all the problem 1 input and output files
    for (int tests_iterator = 1; tests_iterator <= TESTS_NO; tests_iterator++)
    {
        // vectors used to store the name of input and output files
        char temp_name_in[FILENAME_SIZE];
        char temp_name_out[FILENAME_SIZE];

        // used for computing running time of a code block
        clock_t start, finish;
        double  duration;

        // variable used to store the randomly generate length of
        // the vector
        int vector_length;
        // variable used to store all the random elements of the vector
        int *vector;
        // used to store the minimum maximum sum of the partitions
        int max_found;
        // first element of the pair
        int pair_first_element;
        // second element of the pair
        int pair_second_element;

        sprintf(temp_name_in, "data\\test_%d.in", tests_iterator);
        sprintf(temp_name_out, "data\\test_%d.out", tests_iterator);

        FILE* test_in = fopen(temp_name_in, "r");
        FILE* test_out = fopen(temp_name_out, "w");

        // check if the files were opened correctly
        if(!test_in || !test_out)
        {
            return -1;
        }

        fscanf(test_in, "%d", &vector_length);
        // allocate memory for "vector_length" elements
        vector = (int*) malloc(vector_length * sizeof(int));

        for(int iterator = 0; iterator < vector_length ; iterator++)
        // read all the elements from the input file
        {
            fscanf(test_in, "%d", &vector[iterator]);
        }

        // store time before running
        start = clock();

        // sort the vector using the Merge Sort algorithm
        merge_sort(vector, 0, vector_length - 1);

        // determine the pair with the maximum sum
        max_found = max_sum(vector, 0, vector_length - 1, &pair_first_element, &pair_second_element);

        // store time after measured block ends
        finish = clock();

        fprintf(test_out, "\n\tThe elements that form the pair with the maximum sum are: (%d,%d) ->  %d\n",
                pair_first_element, pair_second_element, max_found);

        // determine the running time for the code block
        duration = (double)(finish - start) / CLOCKS_PER_SEC;
        printf("Test %d duration: %.3fs \n", tests_iterator, duration);

        fclose(test_in);
        fclose(test_out);

    }

    return 0;
}
