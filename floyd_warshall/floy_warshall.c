// C Program for Floyd Warshall Algorithm
#include <stdio.h>

// Number of vertices in the graph
#define V 4

/* Define Infinite as a large enough
value. This value will be used
for vertices not connected to each other */
#define INF 99999

// A function to print the solution matrix
void printSolution(int dist[][V]);

// Solves the all-pairs shortest path
// problem using Floyd Warshall algorithm
void floydWarshall(int dist[][V])
{
	int i, j, k;
	for (k = 0; k < V; k++) {
		// Pick all vertices as source one by one
		for (i = 0; i < V; i++) {
			// Pick all vertices as destination for the
			// above picked source
			for (j = 0; j < V; j++) {
				if (dist[i][k] + dist[k][j] < dist[i][j])
					dist[i][j] = dist[i][k] + dist[k][j];
			}
		}
	}

	// Print the shortest distance matrix
	printSolution(dist);
}

/* A utility function to print solution */
void printSolution(int dist[][V])
{
	printf(
		"The following matrix shows the shortest distances"
		" between every pair of vertices \n");
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			if (dist[i][j] == INF)
				printf("%7s", "INF");
			else
				printf("%7d", dist[i][j]);
		}
		printf("\n");
	}
}

/*int main()
{
	int graph[V][V] = { { 0, 5, INF, 10 },
						{ INF, 0, 3, INF },
						{ INF, INF, 0, 1 },
						{ INF, INF, INF, 0 } };

	// Function call
	floydWarshall(graph);
	return 0;
}
*/

/*
#include <stdio.h>
#include <time.h>

#define V 4
#define INF 99999

void printSolution(int dist[][V]);
void floydWarshall(int dist[][V]);

int main()
{
    int graph[V][V] = {{0, 5, INF, 10},
                       {INF, 0, 3, INF},
                       {INF, INF, 0, 1},
                       {INF, INF, INF, 0}};

    // Number of trials to calculate average time complexity
    int trials = 10;
    clock_t start, end;
    double cpu_time_used = 0;

    for (int t = 0; t < trials; t++)
    {
        // Make a copy of the graph for each trial
        int copyGraph[V][V];
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                copyGraph[i][j] = graph[i][j];
            }
        }

        // Record the start time
        start = clock();

        // Function call
        floydWarshall(copyGraph);

        // Record the end time
        end = clock();

        // Calculate the CPU time used for this trial
        cpu_time_used += ((double)(end - start)) / CLOCKS_PER_SEC;
    }

    // Calculate the average time complexity
    double average_time = cpu_time_used / trials;

    printf("Average time complexity: %f seconds\n", average_time);

    return 0;
}
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INF 99999

void printSolution(int dist[][V]);
void floydWarshall(int dist[][V]);

int main()
{
    // Number of trials to calculate average time complexity
    int trials = 10;

    // Maximum size of the graph
    int max_size = 100;

    // Step size for increasing the graph size
    int step_size = 10;

    printf("Graph Size\tAverage Time (s)\n");

    for (int size = step_size; size <= max_size; size += step_size)
    {
        int graph[size][size];

        // Initialize the graph with random weights
        srand(time(NULL));
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (i == j)
                    graph[i][j] = 0;
                else if (rand() % 2 == 0)
                    graph[i][j] = rand() % 100;
                else
                    graph[i][j] = INF;
            }
        }

        double cpu_time_used = 0;

        for (int t = 0; t < trials; t++)
        {
            // Make a copy of the graph for each trial
            int copyGraph[size][size];
            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < size; j++)
                {
                    copyGraph[i][j] = graph[i][j];
                }
            }

            // Record the start time
            clock_t start = clock();

            // Function call
            floydWarshall(copyGraph);

            // Record the end time
            clock_t end = clock();

            // Calculate the CPU time used for this trial
            cpu_time_used += ((double)(end - start)) / CLOCKS_PER_SEC;
        }

        // Calculate the average time complexity
        double average_time = cpu_time_used / trials;

        printf("%d\t\t%f\n", size, average_time);
    }

    return 0;
}

// Rest of your code remains the same...



