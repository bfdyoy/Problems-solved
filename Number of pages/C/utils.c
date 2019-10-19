#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils.h"

int number_pages (int digits_used)
{
    // iterator used for determining how many digits are used
    // for pages with the same length, e.g: 1-9, 10-99, 100-999.
    int iterator=0;
    // variable used to store the total number of pages
    int no_pages=0;
    // "9 * 10^iterator * (iterator+1)" represents the number of
    // digits used for pages with "iterator+1" length
    while (digits_used - (9*pow(10,iterator)*(iterator+1)) >= 0)
    {
        digits_used -= 9*pow(10,iterator)*(iterator+1);
        // increase the length of a page after decreasing the
        // value of total digits used
        iterator++;
    }
    // after the loop ends, in the variable "no_pages" will be
    // a value greater or equal to 0, either way, the will not be
    // a remainder because we got a valid input
    no_pages = digits_used / (iterator+1);

    // summing up the total number of pages
    while (iterator-1 >= 0)
    {
        no_pages = no_pages + 9*pow(10,iterator-1);
        iterator--;
    }

    return no_pages;
}

