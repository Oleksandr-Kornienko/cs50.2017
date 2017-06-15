/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    if (n<0)
    {
     return false;   
    }
    
    int firstIndex = 0;
    int lastIndex =  n;
    int searchingIndex = firstIndex + lastIndex;
    int notChanged;
    
    while (searchingIndex > 0)
    {
        notChanged = searchingIndex;
        searchingIndex = searchingIndex/2;
        if (values[searchingIndex] == value) return true;
    
       /* if (values[searchingIndex] > value)
        {
            lastIndex = searchingIndex;
            searchingIndex = searchingIndex + firstIndex;
        }
        */
        
         if (values[searchingIndex] > value) 
        { 
            lastIndex = searchingIndex; 
        }
        if (values[searchingIndex] < value) 
        { 
            firstIndex = searchingIndex; 
            searchingIndex += lastIndex; 
        }
        
        if (searchingIndex == notChanged) return false;
    }   
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    int minElement;
    for (int j=0;j<n;j++)
    {
        minElement = j;
        for (int i=j;i<n;i++) 
        {
            if (values[minElement]>values[i]) 
            {
                minElement = i;
            }
        }
        if (minElement!=j)
        {
            int changingElement = values[j];
            values[j] = values[minElement];
            values[minElement] = changingElement;
        }
    }
}
