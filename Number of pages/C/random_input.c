#include <stdio.h>
#include <stdlib.h>
#include "random_input.h"

#define TESTS_NO 10
#define FILENAME_SIZE 20

void random_file_input(int max_pages)
{
    // all problem 1 input files are considered output files for this function
    // we'll see why
    for (int tests_iterator = 1; tests_iterator <= TESTS_NO; tests_iterator++)
    {
        // store the names of problem 1 input files
        // there's no need for 2 char arrays because we don't read anything
        // from the input, here we just create the input file for the problem
        char temp_name_in[FILENAME_SIZE];

        // allocate memory in vector for max_pages elements
        int *vector = (int*) malloc(max_pages * sizeof(int));

        // variable used to store a random valid index
        int random_index;

        sprintf(temp_name_in, "data\\test_%d.in", tests_iterator);

        FILE* write_number = fopen(temp_name_in, "w");
        FILE* input_file = fopen("sum_digits.in", "r");

        // generate a random value for random_index in range 0 .. max_pages
        // i used rand()*rand() to get a value bigger than 32768 (2 ^ 15).
        // the maxim number generated with this method is 2 ^ 30.
        random_index = (rand()*rand())%max_pages+1;

        // store all the valid inputs into an array
        for(int iterator = 0; iterator < max_pages; iterator++)
        {
            fscanf(input_file,"%d", &vector[iterator]);
        }

        // writing into the file the valid value which represents
        // the input for problem 1
        fprintf(write_number, "%d", vector[random_index]);

        // free the memory used for the array previously used
        free(vector);
        fclose(write_number);
        fclose(input_file);
    }
}

void generate_number_digits(int max_pages)
{
    // for this specific problem, a valid value represents
    // the number of digits used in a numbered book with
    // "full pages", so we won't have page 0.5 or page 0.7 etc.

    // variable used to store how many digits were used in a
    // numbered book with "iterator" pages
    int number_digits=0;
    // variable used to count how many digits are used for a page
    int digits_page=0;
    // auxiliary variable used in counting the digits of a page
    int aux;

    FILE* output_file = fopen("sum_digits.in", "w");

    // in this loop we simply determine how many digits were used
    // in a numbered book with "iterator" pages until we write
    // the digits used in a numbered book with "max_pages" pages
    for (int iterator = 1 ; iterator <= max_pages ; iterator++)
    {
        aux = iterator;
        while (aux)
            // determine how many digits are used for the page "iterator"
        {
            digits_page++;
            aux /= 10;
        }
        // the number of digits is increased with "digits_page"
        number_digits += digits_page;
        // set the number of digits for the current page to 0
        digits_page = 0;
        // writing into the file the valid value "number_digits"
        fprintf(output_file,"%d\n", number_digits);
    }

    fclose(output_file);
}
