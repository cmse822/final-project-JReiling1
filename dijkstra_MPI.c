#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_walltime.c"
#include "mpi.h"

// CMSE 822: Parallel Computing
// Final Project
// Parallelization of Dijkstra: finding the shortest path between verticies on a graph
// This version is using MPI. See other verions of Dijkstra for parallelized
// verions in both serial and openMP

#define num_verticies 9


int minDistance(int dist[], bool sptSet[])
{
    // Initialize min value
    int min = INT_MAX, min_index;
 
    for (int vertex = 0; vertex < num_verticies; vertex++)
        if (sptSet[vertex] == false && dist[vertex] <= min)
            min = dist[vertex], min_index = vertex;
 
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
                srand(seed);
                graph[i][j] = rand() % 100;  // Random weight between 0 and 19
            }
        }
    }

    return graph;
}

int main(int argc, char *argv[]) 
{
    int rank, size, header_written;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Initialize csv 
    const char *csv_file_name="dijkstra_MPI.csv";

    FILE *outputFile = fopen(csv_file_name, "a");

    // Decide if the header needs to be written
    if (rank == 0) {
        fseek(outputFile, 0, SEEK_END); // Move to the end of the file
        long fileSize = ftell(outputFile); // Get the current position (file size)
        if (fileSize == 0) { // Check if the file is empty
            header_written = 0;
        } else {
            header_written = 1;
        }
    }

    // Broadcast the decision to all processes
    MPI_Bcast(&header_written, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Write the header if it hasn't been written yet
    if (!header_written) {
        if (rank == 0) {
            fprintf(outputFile, "Num Verticies, Num Ranks, Runtime\n");
        }
    }

    // // Starting information before initializing MPI
    // int** graph = generateGraph();

    /* Example graph found online */
     int graph[num_verticies][num_verticies] = { { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
                       { 4, 0, 8, 0, 0, 0, 0, 11, 0 },
                       { 0, 8, 0, 7, 0, 4, 0, 0, 2 },
                       { 0, 0, 7, 0, 9, 14, 0, 0, 0 },
                       { 0, 0, 0, 9, 0, 10, 0, 0, 0 },
                       { 0, 0, 4, 14, 10, 0, 2, 0, 0 },
                       { 0, 0, 0, 0, 0, 2, 0, 1, 6 },
                       { 8, 11, 0, 0, 0, 0, 1, 0, 7 },
                       { 0, 0, 2, 0, 0, 0, 6, 7, 0 } };

    // Check if the file is open
    if (outputFile == NULL) {
        // Failed to open the file
        fprintf(stderr, "Error: Failed to open file for appending.\n");
        return 1;
    }


    int shortest_dist[num_verticies]; // Holds an arry of shortest distances from the source verticie
    bool short_path_tree[num_verticies]; 
    // Holds an array bool values. True if vertex is in shortest_path_tree. False if not

    // Store every node in a source_list
    int source_list[num_verticies];
    for (int vertex = 0; vertex < num_verticies; vertex++) {
      source_list[vertex] = vertex;
    }

    if (size != 4) {
          if (rank == 0)
              printf("This code requires exactly 4 MPI processes.\n");
          MPI_Finalize();
          return 1;
      }

    // Divide the vertices equally among the processes
    int start_vertex = rank * num_verticies / size;
    int end_vertex = (rank + 1) * num_verticies / size;


    double total_start_time;
    MPI_Barrier(MPI_COMM_WORLD); // Ensure all processes start the timer at the same time
    if (rank == 0) {
      total_start_time = MPI_Wtime();
    }


    for (int source_index = start_vertex; source_index < end_vertex; source_index++){
      int source = source_list[source_index];

      double start_time = MPI_Wtime();

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

      if (rank == 0) {
        printf("Shortest Path for source node = %d on process %d\n", source, rank);
        printSolution(shortest_dist);
        double end_time;
        get_walltime(&end_time);
        //fprintf(outputFile, "%d, %f\n", source,  end_time - start_time);
        
      }
    }

    if (rank == 0) {
      double total_end_time = MPI_Wtime();
      printf("Time for shortest path distance: %f seconds\n\n", total_end_time - total_start_time);
      fprintf(outputFile, "%d, %d, %f\n", num_verticies, size, total_end_time - total_start_time);
    }

    MPI_Finalize();
    return 0;
  
}
