#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"
#include "random_input.h"

#define TESTS_NO 10
#define FILENAME_SIZE 20

static int max_pages = 100;

int main()
{
    // setting the time for rand() calls
    srand(time(NULL));
    // generate the file with valid inputs for our problem
    generate_number_digits(max_pages);
    // writing in each input file a valid value
    random_file_input(max_pages);

    // read all problem 1 input and output files
    for (int tests_iterator = 1; tests_iterator <= TESTS_NO; tests_iterator++)
    {
        // vectors used to store the name of the input and output files
        char temp_name_in[FILENAME_SIZE];
        char temp_name_out[FILENAME_SIZE];

        int sum_digits_pages; // variable used to store the random valid input
        int no_pages; // variable used to store the ouput

        // used for computing running time of a code block
        clock_t start, finish;
        double  duration;

        sprintf(temp_name_in, "data\\test_%d.in", tests_iterator);
        sprintf(temp_name_out, "data\\test_%d.out", tests_iterator);

        FILE* test_in = fopen(temp_name_in, "r");
        FILE* test_out = fopen(temp_name_out, "w");

        // checking if the files were opened
        if(!test_in || !test_out)
        {
            return -1;
        }

        fscanf(test_in, "%d", &sum_digits_pages);

        // store time before running
        start = clock();

        no_pages = number_pages(sum_digits_pages);

        // store time after measured block ends
        finish = clock();

        // determine the running time for the code block
        duration = (double)(finish - start) / CLOCKS_PER_SEC;

        printf("Test %d duration: %.3fs \n", tests_iterator, duration);

        fprintf(test_out, "%d", no_pages);

        fclose(test_in);
        fclose(test_out);
    }
    return 0;
}
