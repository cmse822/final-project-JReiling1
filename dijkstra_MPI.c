#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
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

int main() {
    // Initialize MPI information
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);



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

    int shortest_dist[num_verticies]; // Holds an arry of shortest distances from the source verticie
    bool short_path_tree[num_verticies]; 
    // Holds an array bool values. True if vertex is in shortest_path_tree. False if not

   // Store every node in a source_list
   int source_list[num_verticies];
   for (int vertex = 0; vertex < num_verticies; vertex++) {
      source_list[vertex] = vertex;
   }

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

   double end_time;
   get_walltime(&end_time);
   printf("Shortest Path for source node = %d \n", source);
   printSolution(shortest_dist);
   printf("Time for shortest path distance: %f seconds\n\n", end_time - start_time);


  }


   return 0;
  
}
