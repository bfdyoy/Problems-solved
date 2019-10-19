#include <stdio.h>
#include <stdlib.h>
#include "sort.h"
#include "vectors.h"


void merge_sort(int *vector, int left, int right)
{
    // variable used to store the halfway point of the vector
    int middle;

    if (left != right)
    // recursively call the merge_sort function to sort
    // the vector
    {
        // determine the halfway point of the vector
        middle = (left + right) / 2;
        // sort the left elements of the vector
        merge_sort(vector, left, middle);
        // sort the right elements of the vector
        merge_sort(vector, middle + 1, right);
        // merge the two sorted vectors
        merge_left_right(vector, left, middle, right);
    }
}
