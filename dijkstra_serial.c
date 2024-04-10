#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

// CMSE 822: Parallel Computing
// Final Project
// Parallelization of Dijkstra: finding the shortest path between verticies on a graph
// This version is serial. See other verions of Dijkstra for parallelized
// verions in both MPI and openMP

#define num_verticies = 9





int main() {
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
    int short_path_tree[num_verticies]; 
    // Holds an array bool values. True if vertex is in shortest_path_tree. False if not

    shortest_dist[source] = 0;
  
    // Step one in algorithm set all non-origin verticies to infinity
    for (in i = 0: i < num_verticies; i++) {
      shortest_dist[i] = INT_MAX;
      short_path_tree[i] = false;
    }
  
  




}
