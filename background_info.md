"Graph Analysis with Parallel Computing"

- Project Description: Computational Neuroscience involves traversing neuronal connections within the brain. For this project, doing a simplified verion. Finding the shortest path between nodes. I am developing an algorithm the finds the shortest distance between nodes on  directed graph. 

- Parallellization Strategies: I will use two parallelization practices: openMI and MPI. I choose these two because I am the most familular with them in the course and believe it will provide for a sucessfull project in the next two weeks.

- Verification and Validation: Since I am finding the shortest route between nodes on a graph, I will first know how far nodes exist on the graph before inplementing the algorithm. Then, I will implement the algorithm using openMP and MPI and time how fast the algorithms take to find the shortest path for every node in relation to each other.

- Load Balancing and Memory Usage: Since I am using openMP and MPI, I will only be using CPUs. Additionally, I will need to scale how my memory usage will adapt while begin processed.

- Scaling Studies: this aspect need to be thought out more, please look into this issue.


[Dijkstra's Algorithm](https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm)

  Finds the shortest paths between nodes in a weighted graph. For a given source node in the graph, the algorithm finds the shortest path between the node and every other. Uses labels that are positive integers or real numbers, which are totally ordered.
