#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

// Function that returns the maximum values from a vector
int get_max(int *vector, int length_vector)
{
    // Initialize the maximum with the first values of the vector
    int max = vector[0];

    // Iterate over the vector and check if there is any
    // element grater than the current max, if it is, change
    // max to that value, else continue
    for (int iterator = 1; iterator <= length_vector; iterator++)
    {
        if (vector[iterator] > max)
        {
            max = vector[iterator];
        }
    }

    // Return the found maximum values
    return max;
}

