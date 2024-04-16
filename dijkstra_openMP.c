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
#define NUM_THREADS 9


// Notice that we're instantiating omp to avoid race conditions
int minDistance(int shortest_dist[], bool short_path_tree[]) {
    int min = INT_MAX, min_index = -1;

    //#pragma omp parallel for shared(shortest_dist, short_path_tree) reduction(min:min) 
    #pragma omp parallel for
    for (int i = 0; i < num_verticies; i++) {
        if (!short_path_tree[i] && shortest_dist[i] <= min) {
            min = shortest_dist[i];
            min_index = i;
        }
    }

    return min_index;
}


void printSolution(int dist[], int source, double duration)
{
    #pragma omp critical
    {
        printf("Thread %d: Shortest Path for source node = %d.\n", omp_get_thread_num(), source);
        printf("Time for computation = %f\n", duration);
        printf("Vertex \t \t Distance from Source\n");
        for (int i = 0; i < num_verticies; i++){ 
            printf("%d \t\t\t\t %d\n", i, dist[i]);
        }
            
    }
}

int main() {
   /* Example graph found online */
    int graph[num_verticies][num_verticies] = { 
        { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
        { 4, 0, 8, 0, 0, 0, 0, 11, 0 },
        { 0, 8, 0, 7, 0, 4, 0, 0, 2 },
        { 0, 0, 7, 0, 9, 14, 0, 0, 0 },
        { 0, 0, 0, 9, 0, 10, 0, 0, 0 },
        { 0, 0, 4, 14, 10, 0, 2, 0, 0 },
        { 0, 0, 0, 0, 0, 2, 0, 1, 6 },
        { 8, 11, 0, 0, 0, 0, 1, 0, 7 },
        { 0, 0, 2, 0, 0, 0, 6, 7, 0 } 
    };

    int shortest_dist[num_verticies]; // Holds an arry of shortest distances from the source verticie
    bool short_path_tree[num_verticies]; 
    // Holds an array bool values. True if vertex is in short_path_tree. False if not

   // Store every node in a source_list
   int source_list[num_verticies];
   for (int vertex = 0; vertex < num_verticies; vertex++) {
      source_list[vertex] = vertex;
   }

    omp_set_nested(0); // Disable nested parallelism
    omp_set_num_threads(NUM_THREADS);

    #pragma omp parallel
    {
        //#pragma omp parallel for
        for (int source_index = 0; source_index < num_verticies; source_index++){
            // Initialize source and get start time
            int source = source_list[source_index];
            shortest_dist[source] = 0;
            double start_time = omp_get_wtime();


            // Step one in algorithm set all non-origin verticies to infinity
            //#pragma omp parallel for shared(shortest_dist, short_path_tree)
            //#pragma omp parallel for
            for (int i = 0; i < num_verticies; i++) {
                if (i != source) {
                    shortest_dist[i] = INT_MAX;
                }

                short_path_tree[i] = false;
            }

                
            for (int vert_indx = 0; vert_indx < num_verticies - 1; vert_indx++) {
                int current_vert = minDistance(shortest_dist, short_path_tree);

                short_path_tree[current_vert] = true;

                // Calculate the distance between adjacent verticies of the choosen vertex
                //#pragma omp parallel for shared(shortest_dist, short_path_tree)
                #pragma omp parallel for
                for (int adj_vertex = 0; adj_vertex < num_verticies; adj_vertex++) {

                    if (!short_path_tree[adj_vertex] && graph[current_vert][adj_vertex] && shortest_dist[current_vert] != INT_MAX 
                        && shortest_dist[current_vert] + graph[current_vert][adj_vertex] < shortest_dist[adj_vertex]) {
                            shortest_dist[adj_vertex] = shortest_dist[current_vert] + graph[current_vert][adj_vertex];
                        }
                }
            }   

        // Calculate the runtime
        double end_time = omp_get_wtime();
        double run_time = end_time - start_time;

        // Print resulting infromation
        printSolution(shortest_dist, source, run_time);
    
        }
    }
    return 0;
}