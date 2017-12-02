/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */

#include <cs50.h>
#include <stdio.h>
#include "helpers.h"
#define arrlen(x)  (sizeof(x) / sizeof((x)[0]))

/**
 * Returns true if value is in array of n values, else false.
 */
bool binarysearch(int value, int values[], int n)
{
    // Reject arrays with nonzero lengths
    if(value <= 0)
    {
        return false;
    }
    int min = 0, max = n-1;

    while (min <= max)
    {
    int guess = (min + max)/2;
    if(values[guess] == value)
        {
        return true;
        break;
        }
    else {
        if(values[guess] < value)
            {
            min = guess += 1;
            }
        if(values[guess] > value)
            {
            max = guess +-1;
            }
        }
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void selection_sort(int values[], int n)
{
    int min, temp;

    for(int i = 0; i < n-1; i++)
    {
        //Set min pointer to ith element
        min = i;
        //Check all remaining elements in array against min; assign min to lowest value
        for(int j = i+1; j < n; j++)
        {
            if(values[min] > values[j])
            {
                min = j;
            }
        }
        //If ith element is not the smallest value, swap positions with min; print out i when swap is made
        if(min != i)
        {
            temp = values[i];
            values[i] = values[min];
            values[min] = temp;
        }
    }
}
