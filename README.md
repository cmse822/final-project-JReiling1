[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-718a45dd9cf7e7f842a935f5ebbe5719a5e09af4491e668f4dbf3b35d5cca122.svg)](https://classroom.github.com/online_ide?assignment_repo_id=14256427&assignment_repo_type=AssignmentRepo)

# CMSE 822: Parallel Computing Final Project

This will serve as the repo for your final project for the course. Complete all code development work in this repo. Commit early and often! For a detailed description of the project requirements, see [here](https://cmse822.github.io/projects).

First, give a brief description of your project topic idea and detail how you will address each of the specific project requierements given in the link above.

"Graph Analysis with Parallel Computing"

- Project Description: Computational Neuroscience involves traversing neuronal connections within the brain. Many concepts are reduced to being analyzed with TDA to understand brain dynamics. Graph analysis is a key idea for this area of research
- Parallellization Strategies: shared memory with (OpenMP) and with GPUs (CUDA) -> CUDA is widly implemented in computational neuroscience and
want to know more about openMP
- Refer to Mengsen Zhang's paper (https://direct.mit.edu/netn/article/7/2/431/114356/Temporal-Mapper-Transition-networks-in-simulated)
- Characterizing brain complex dynamics is fundamental in assessing brain functions for healthy individuals and patients with psychiatric disorders
- Brain modeling with large-scale nonlinear dynamical systems with various levels of biophysical details -> this mechanistic model utilites prior knowledge or assumptions about the biophysical and anatomical features of the brain in addition to timeseries data.
- Brain states discovered using data-driven methods often share conceptual appeal to nonlinear dynamics
- Mengsen's work develops direct link between data-driven and mechanistic modeling of brain where time series data is represented as a directed graph, whose nodes and edges could map directly to underlying attractors and phase transitions in nonlinear dynamical model of human brain.
- Morse decomposition has been used in rigorous analysis of nonlinear dynamical systems to represent a dynamical system as a directed whose nodes map to attractors (and repellers)
- Look into directed graphs
