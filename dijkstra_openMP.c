#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <omp.h>
#include <time.h>

// CMSE 822: Parallel Computing
// Final Project
// Parallelization of Dijkstra Algorithm: finding the shortest path between verticies on a graph
// This version is openMP implimentation. See other verions of Dijkstra for parallelized
// verions in both MPI and openMP

#define num_verticies 9
#define NUM_THREADS 16


// Notice that we're instantiating omp to avoid race conditions
int minDistance(int shortest_dist[], bool short_path_tree[])
{
    // Initialize min value
    int min = INT_MAX, min_index;

    #pragma omp parallel
    {
        int local_min = INT_MAX, local_min_index = -1;
        int vertex; //need to declare vertex before paralle region
        // need to create a local minimum to avoid race conditions
        // when running this for-loop

        #pragma omp for
        for (int vertex = 0; vertex < num_verticies; vertex++) {
            if (short_path_tree[vertex] == false && shortest_dist[vertex] <= local_min)
                local_min = shortest_dist[vertex];
                local_min_index = vertex;
        }
        
        // Notice we need critical to sync local and global min
        #pragma omp critical
        {
            if (local_min < min) {
                min = local_min;
                min_index = local_min_index;
            }
        }
    }
    
 
    return min_index;
}


void printSolution(int dist[])
{
    printf("Vertex \t\t Distance from Source\n");
    for (int i = 0; i < num_verticies; i++)
        printf("%d \t\t\t\t %d\n", i, dist[i]);
}

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
    bool short_path_tree[num_verticies]; 
    // Holds an array bool values. True if vertex is in shortest_path_tree. False if not

   // Store every node in a source_list
   int source_list[num_verticies];
   for (int vertex = 0; vertex < num_verticies; vertex++) {
      source_list[vertex] = vertex;
   }

    #pragma omp parallel 
    {
        for (int source_index = 0; source_index < num_verticies; source_index++){
            double start_time = omp_get_wtime();
            int source = source_list[source_index];

            shortest_dist[source] = 0;

            // Initialize OMP
            int actual_n_threads;

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

            #pragma omp for collapse(2)
            for (int thread_num = 1; thread_num < NUM_THREADS + 1; thread_num*=2) {
                omp_set_num_threads(thread_num);

                int threadnum = omp_get_thread_num();
                int numthreads = omp_get_num_threads();

                actual_n_threads = numthreads;

                
                for (int vert_indx = 0; vert_indx < num_verticies - 1; vert_indx++) {
                    int current_vert = minDistance(shortest_dist, short_path_tree);

                    short_path_tree[current_vert] = true;

                    // Calculate the distance between adjacent verticies of the choosen vertex

                    for (int adj_vertex = 0; adj_vertex < num_verticies; adj_vertex++) {

                        if (!short_path_tree[adj_vertex] && graph[current_vert][adj_vertex] && shortest_dist[current_vert] != INT_MAX 
                            && shortest_dist[current_vert] + graph[current_vert][adj_vertex] < shortest_dist[adj_vertex]) {
                                shortest_dist[adj_vertex] = shortest_dist[current_vert] + graph[current_vert][adj_vertex];
                            }
                    }
                }

            }   

        printf("Shortest Path for source node = %d \n", source);
        printSolution(shortest_dist);
        // Calculate the runtime
        double end_time = omp_get_wtime();
        double run_time = end_time - start_time;
        printf("Runtime information (num threads and runtime) %d %f\n", actual_n_threads, run_time);
    
        }
    }
    return 0;
}