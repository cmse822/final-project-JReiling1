[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-718a45dd9cf7e7f842a935f5ebbe5719a5e09af4491e668f4dbf3b35d5cca122.svg)](https://classroom.github.com/online_ide?assignment_repo_id=14256427&assignment_repo_type=AssignmentRepo)

# CMSE 822: Parallel Computing Final Project

This will serve as the repo for your final project for the course. Complete all code development work in this repo. Commit early and often! For a detailed description of the project requirements, see [here](https://cmse822.github.io/projects).

First, give a brief description of your project topic idea and detail how you will address each of the specific project requierements given in the link above.

"Graph Analysis with Parallel Computing"

- Project Description: Computational Neuroscience involves traversing neuronal connections within the brain. For this project, doing a simplified verion. Finding the shortest path between nodes. I am developing an algorithm the finds the shortest distance between nodes on  directed graph. 

- Parallellization Strategies: I will use two parallelization practices: openMI and MPI. I choose these two because I am the most familular with them in the course and believe it will provide for a sucessfull project in the next two weeks.

- Verification and Validation: Since I am finding the shortest route between nodes on a graph, I will first know how far nodes exist on the graph before inplementing the algorithm. Then, I will implement the algorithm using openMP and MPI and time how fast the algorithms take to find the shortest path for every node in relation to each other.

- Load Balancing and Memory Usage: Since I am using openMP and MPI, I will only be using CPUs. Additionally, I will need to scale how my memory usage will adapt while begin processed.

- Scaling Studies: this aspect need to be thought out more, please look into this issue.
  


Comments from Sean Couch:
Your proposal on "Graph Analysis with Parallel Computing" for computational neuroscience is ambitious and relevant. Here are some considerations to strengthen your final report:

Clear Project Definition: Explicitly state the thesis or main question your project addresses. Clarify how graph analysis and TDA (Topological Data Analysis) contribute to understanding brain dynamics.

Parallelization Strategies: You mentioned using OpenMP and CUDA. Detail how each will be applied in your project, especially how they will handle different aspects of the computational workload. Explore how these models can complement each other to enhance performance.

Verification and Validation: Develop a clear plan for verifying the correctness of your parallel algorithms. This could involve comparing results with a serial implementation or existing benchmarks in computational neuroscience.

Load Balancing and Memory Usage: Discuss how you plan to address load balancing between CPU and GPU computations, and analyze how memory usage will scale with the size of the graph data being processed.

Scaling Studies: Elaborate on your approach to scaling studies, including both strong and weak scaling, and how they relate to the complexities of brain modeling. Include plans for thread-to-thread speedup analysis.
