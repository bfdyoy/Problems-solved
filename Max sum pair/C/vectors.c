#include <stdio.h>
#include <stdlib.h>
#include "vectors.h"

void merge_left_right(int *vector, int left, int middle, int right)
{
    int iterator_left, iterator_right, merge_iterator;
    int no_elements_left = middle - left + 1;
    int no_elements_right = right - middle;

    // create and allocate memory for the left and right vectors
    // they'll contain left and right elements
    int *vector_left = calloc(no_elements_left, sizeof(int));
    int *vector_right = calloc(no_elements_right, sizeof(int));

    // copy the elements from the initial vector in the left one
    for (iterator_left = 0; iterator_left < no_elements_left; iterator_left++)
        vector_left[iterator_left] = vector[left + iterator_left];
    // copy the elements from the initial vector in the right one
    for (iterator_right = 0; iterator_right < no_elements_right; iterator_right++)
        vector_right[iterator_right] = vector[middle + 1 + iterator_right];

    // merge vectors already sorted
    iterator_left = 0;
    iterator_right = 0;
    merge_iterator = left;
    // merge vectors until one vector reaches its last element
    while (iterator_left < no_elements_left && iterator_right < no_elements_right)
    {
        if ( *(vector_left + iterator_left) <= *(vector_right + iterator_right) )
        {
            *(vector + merge_iterator) = *(vector_left + iterator_left);
            iterator_left++;
        }
        else
        {
            *(vector + merge_iterator) = *(vector_right + iterator_right);
            iterator_right++;
        }
        merge_iterator++;
    }
    // case 1 : left vector has remaining elements that were not copied
    // into the merged vector
    if (iterator_left < no_elements_left)
    {
        // copy the remaining elements of the left vector if it didn't
        // reach its end
        while (iterator_left < no_elements_left)
        {
            *(vector + merge_iterator) = *(vector_left + iterator_left);
            iterator_left++;
            merge_iterator++;
        }
    }
    else
    // case 2 : right vector has remaining elements that were not copied
    // into the merged vector
    {
        // copy the remaining elements of the right vector if it didn't
        // reach its end
        while (iterator_right < no_elements_right)
        {
            *(vector + merge_iterator) = *(vector_right + iterator_right);
            iterator_right++;
            merge_iterator++;
        }
    }
    // free the memory allocated for the left and right vectors
    free(vector_left);
    free(vector_right);
}

int max_sum(int *vector, int start, int end, int *first_element, int *second_element)
{
    int max_sum;
    int next_sum;

    // determine the first potential maximum sum, this will be
    // afterwards compared to the other potential maximum sums
    max_sum = *(vector + start) + *(vector + end);

    // store the elements which has the maximum sum
    *first_element = *(vector + start);
    *second_element = *(vector + end);

    // iterators used for creating new pairs
    start++;
    end--;

    while(start < end)
    // determine the sum of the next pair and compare it
    // to the current maximum sum
    {
        next_sum = *(vector + start) + *(vector + end);
        if ( next_sum > max_sum )
        {
            max_sum = next_sum;

            *first_element = *(vector + start);
            *second_element = *(vector + end);
        }
        start++;
        end--;
    }

    return max_sum;
}
