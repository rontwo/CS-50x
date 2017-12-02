#include <stdio.h>

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // Reject arrays with nonzero lengths
    if(n <= 0)
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
        return guess;
        break;
        }
    else {
        if(values[guess] < value)
            {
            min = guess += 1;
            }
        else
            {
            max = guess +-1;
            }
        }
    }
    return false;
}
