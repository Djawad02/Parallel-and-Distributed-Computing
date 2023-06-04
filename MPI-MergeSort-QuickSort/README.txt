MPI-MergeSort-QuickSort
The Q1.c file contains a simple serial program of Quicksort and Mergesort which takes input as array size(2^11,2^13,2^13,2^15) and reads the corresponding file to take input.
If the file is missing a new file is created and updated with random values.
The parallel part of the  code is meant to be run on master-slave cluster using mpicc and mpiexec commands for compiling and execution respectively.
The Q2a.c contains Quicksort implemented in parallel using MPI through MPI_Bcast and MPI_Scatter commands. 
The Q2b.c Mergesort implemented in parallel using MPI through MPI_Bcast and MPI_Scatter commands. 
The output is stored after sorting in output.txt file or any filename that you would specify while executing.
Each file calculates the execution time in Gflops which are printed in the end of every output.
