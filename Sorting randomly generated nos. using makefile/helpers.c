/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

#include "helpers.h"

int binarysearch(int value ,int values[] , int c, int n);

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)                     //function which calls another function intended to do binary search
{
    int c=0;
    if(binarysearch(value , values , c , n))
        return 1;
    else
        return 0;
}

int binarysearch(int value ,int values[] , int c, int n)            //function to perform binary search
{
    if(c > n)                           //base condition
        return 0;
    else
    {
        if(values[(c+n)/2] == value)        //if middle value is the value we are searching for , return 1
            return 1;
        else if(values[(c+n)/2] >= value)           //else if middle value is greater than the value we are searching for, search left half
            return binarysearch(value , values , c , ((c+n)/2) - 1);
        else                                        //else search right half
            return binarysearch(value , values , ((c+n)/2) + 1 , n);
    }
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    int ar[65537] , c=0;            //arbitrarily choose the counting array of size 65,536.
    for(int i=0 ; i < 65536 ; i++)
    {
        ar[i] = 0;
    }
    for(int i=0 ; i < n ; i++)             //incrementing counting array elements according to the key elements of main array
    {
        ar[values[i]]++;
    }
    for(int i=0 ; i < 65536 ; i++)
    {
        for(int j=0 ; j < ar[i] ; j++)   //loop in case there were repeated nos. in values array
        {
            values[c] = i;           // substituting the arranged values accordingly(most probable line of cause of error)
            c++;
        }
    }
    return;
}
