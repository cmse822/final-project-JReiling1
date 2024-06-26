#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_walltime.c"

// CMSE 822: Parallel Computing
// Final Project
// Parallelization of Dijkstra: finding the shortest path between verticies on a graph
// This version is serial. See other verions of Dijkstra for parallelized
// verions in both MPI and openMP

#define num_verticies 1000


int minDistance(int shortest_dist[], bool short_path_tree[])
{
    // Initialize min value
    int min = INT_MAX, min_index;
 
    for (int vertex = 0; vertex < num_verticies; vertex++)
        if (short_path_tree[vertex] == false && shortest_dist[vertex] <= min) {
            min = shortest_dist[vertex];
            min_index = vertex;
        }
 
    return min_index;
}


void printSolution(int dist[])
{
    printf("Vertex \t\t Distance from Source\n");
    for (int i = 0; i < num_verticies; i++)
        printf("%d \t\t\t\t %d\n", i, dist[i]);
}


int** generateGraph() {
    int** graph = (int**)malloc(num_verticies * sizeof(int*));
    if (graph == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    
    for (int i = 0; i < num_verticies; i++) {
        graph[i] = (int*)malloc(num_verticies * sizeof(int));
        if (graph[i] == NULL) {
            printf("Memory allocation failed.\n");
            exit(1);
        }
    }

    // Generating random weights for the edges
    for (int i = 0; i < num_verticies; i++) {
        for (int j = 0; j < num_verticies; j++) {
            if (i == j) {
                graph[i][j] = 0;  // Diagonal elements set to 0
            } else {
                int seed = 123;
                srand(123);
                graph[i][j] = rand() % 100;  // Random weight between 0 and 19
            }
        }
    }

    return graph;
}


int main() {
   /* Example graph found online */
    // int graph[num_verticies][num_verticies] = { { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
    //                     { 4, 0, 8, 0, 0, 0, 0, 11, 0 },
    //                     { 0, 8, 0, 7, 0, 4, 0, 0, 2 },
    //                     { 0, 0, 7, 0, 9, 14, 0, 0, 0 },
    //                     { 0, 0, 0, 9, 0, 10, 0, 0, 0 },
    //                     { 0, 0, 4, 14, 10, 0, 2, 0, 0 },
    //                     { 0, 0, 0, 0, 0, 2, 0, 1, 6 },
    //                     { 8, 11, 0, 0, 0, 0, 1, 0, 7 },
    //                     { 0, 0, 2, 0, 0, 0, 6, 7, 0 } };
    int** graph = generateGraph();
   // Initialize csv 
    const char *csv_file_name="dijkstra_serial.csv";

    FILE *outputFile = fopen(csv_file_name, "a");

    // Check if the file is open
    if (outputFile == NULL) {
        // Failed to open the file
        fprintf(stderr, "Error: Failed to open file for appending.\n");
        return 1;
    }

    // Write headers if the file is newly created
    fseek(outputFile, 0, SEEK_END); // Move to the end of the file
    long fileSize = ftell(outputFile); // Get the current position (file size)
    if (fileSize == 0) { // Check if the file is empty
        fprintf(outputFile, "Num Verticies, Runtime\n");
    }


    int shortest_dist[num_verticies]; // Holds an arry of shortest distances from the source verticie
    bool short_path_tree[num_verticies]; 
    // Holds an array bool values. True if vertex is in shortest_path_tree. False if not

   // Store every node in a source_list
   int source_list[num_verticies];
   for (int vertex = 0; vertex < num_verticies; vertex++) {
      source_list[vertex] = vertex;
   }
    
    double total_start_time;
    get_walltime(&total_start_time);

    for (int source_index = 0; source_index < num_verticies; source_index++){
        double start_time;
        get_walltime(&start_time);
        int source = source_list[source_index];

        shortest_dist[source] = 0;
    
        // Step one in algorithm set all non-origin verticies to infinity
        for (int i = 0; i < num_verticies; i++) {
        if (i != source) {
            shortest_dist[i] = INT_MAX;
        }

        short_path_tree[i] = false;
        }

    // Finding the shortest path for all verticies
    // Pick the vertex with min distance from rest of verticies that are not seen
    // Mark the index as seen
    for (int vert_indx = 0; vert_indx < num_verticies - 1; vert_indx++) {
        int current_vert = minDistance(shortest_dist, short_path_tree);

        short_path_tree[current_vert] = true;

        // Calculate the distance between adjacent verticies of the choosen vertex

        for (int adj_vertex = 0; adj_vertex < num_verticies; adj_vertex++)

            if (!short_path_tree[adj_vertex] && graph[current_vert][adj_vertex] && shortest_dist[current_vert] != INT_MAX 
                && shortest_dist[current_vert] + graph[current_vert][adj_vertex] < shortest_dist[adj_vertex])

                shortest_dist[adj_vertex] = shortest_dist[current_vert] + graph[current_vert][adj_vertex];
        

    }

    // double end_time;
    // get_walltime(&end_time);
    // printf("Shortest Path for source node = %d \n", source);
    // printSolution(shortest_dist);
    // printf("Time for shortest path distance: %f seconds\n\n", end_time - start_time);
  }
    double total_end_time;
    get_walltime(&total_end_time);
    fprintf(outputFile, "%d, %f\n", num_verticies,  total_end_time - total_start_time);
    fclose(outputFile);
    return 0;
  
}
