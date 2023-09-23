#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// Generate an array of randomly disorderd indexes
void randomizeIndices(int *indices, int n) {
    srand(time(NULL));  // we need a seed

    // Initialize an array of indexes
    for (int i = 0; i < n; i++) {
        indices[i] = i;
    }

    // Randomly exchange elements of the array
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);  // we generate a random number between 1 and the lenght of original array
        int temp = indices[i];
        indices[i] = indices[j]; // and we swap the original with the random j index 
        indices[j] = temp;
    }
}

//In this other function we generate our ordered array of indexes and we disorder it with the previous functiuon
//And from this randomized set of numbers we take the element we are going to compare with the searched one
int random_search(int *arr, int n, int x) {
    int *indices = malloc(n * sizeof(int));
    randomizeIndices(indices, n);

    for (int i = 0; i < n; i++) {
        if (arr[indices[i]] == x) {
            return indices[i];
        }
    }

    return -1;
}