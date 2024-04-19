# CMSE 822: Parallel Computing Final Project

## Verification

For verification, the parallel and serial programs developed in this project were validated by comparing their results to the results of other serial implementations of Dijkstra's algorithm using a common graph. Below is an example graph used to validate the developed parallel algorithms.  

Common Graph for Validation

![Common Graph for Validation](./results/final_project_figures/graph_image.png)

Below is the result of finding the shortest path in the graph above from GeeksforGeeks

![verification image](./results/final_project_figures/verification_image.png)

Below is the result of finding the shortest path in the graph above in Jared's serial implementation

![serial graph verification](./results/final_project_figures/serial_graph_verification.png)

Below is the output for finding the shortest path in the graph when each node is a source node in serial

![serial graph output 1](./results/final_project_figures/serial_graph_output_1.png)

![serial graph output 2](./results/final_project_figures/serial_graph_output_2.png)

To verify with the serial implementation, here is Jared's openMP implementation with 2 threads when the source node equals 0

![openMP graph verification](./results/final_project_figures/openMP_graph_verification.png)

Below is the output for finding the shortest path in the graph when each node is a source node using openMP

![openMP graph output 1](./results/final_project_figures/openMP_graph_output_1.png)

![openMP graph output 2](./results/final_project_figures/openMP_graph_output_2.png)

To verify with the serial implementation, here is Jared's MPI implementation with 4 ranks when the source node equals 0

![MPI graph verification](./results/final_project_figures/MPI_graph_verification.png)

Below is the output for finding the shortest path in the graph when each node is a source node using MPI. Note that
this version is only printing the output when the process number equals 0.

![MPI graph verification](./results/final_project_figures/MPI_graph_output_1(process%200).png)