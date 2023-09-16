#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

// take the A array and divide it into two arrays left and right-------------------------
void left_right(int A[], int mitad, int len,int left[],int right[]) 
{
    // copy the first half of elements to left
    for (int i = 0; i < mitad; i++) {
        left[i] = A[i];
    }

    // copy the second half of elements to right
    for (int r = mitad; r < len; r++) {
        right[r - mitad] = A[r];
    }
}

// merge the two arrays left and right into A as sorted-----------------------------------
void merge_sort(int right[],int left[],int half,int len,int sorted[])
{
    int i = 0;
    int j = 0;
    int k = 0;
    while (i <= half && j <= len - half) {
        if (left[i] < right[j]) {
            sorted[k] = left[i];
            i++;
        } else {
            sorted[k] = right[j];
            j++;
        }
        k++;
    }
}