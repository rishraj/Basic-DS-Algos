#include <stdio.h>
#include <cs50.h>
#include <string.h>

void sort(int values[], int n);

int main(void)
{
    printf("Enter the size of the array: ");
    int n;
    scanf("%i",&n);
    int values[n+1];                 //declaring the main array to be sorted
    for(int i=0 ; i < n ; i++)            //inputting values in the array
    {
        printf("Value %d = ", i+1);
        scanf("%i", &values[i]);
    }
    sort(values , n);                //calling sort function to sort the list
    printf(" Sorted Array : ");
    for(int i=0 ; i < n ; i++)
    {
        printf("%d " , values[i]);
    }
    printf("\n");
}


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