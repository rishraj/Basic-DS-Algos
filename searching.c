#include <stdio.h>
#include <cs50.h>

bool search(int value , int values[] , int n);
int binarysearch(int value ,int values[] , int c, int n);

int main(void)
{
    printf("Enter the size of the array: ");
    int n = get_int();
    int values[n+1];                 //declaring the main array to be searched
    for(int i=0 ; i < n ; i++)            //inputting values in the array
    {
        printf("Value %d = ", i+1);
        values[i] = get_int();
    }
    printf("Enter the value to be searched: ");
    int value = get_int();
    if(search(value , values , n))              //function to check if the value is present
        printf("Value found\n");
    else
        printf("Value not found\n");
}

bool search(int value , int values[] , int n)           //function which calls another function intended to do binary search
{
    int c=0;
    if(binarysearch(value , values , c , n))
        return 1;
    else
        return 0;
}

int binarysearch(int value ,int values[] , int c, int n)
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