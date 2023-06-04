#Hadoop-MapReduce-Using-MPI

This project aims at implementing Hadoop's MapReduce algorithm to multiply two matrices using MPI through a cluster setup.
Firstly, Master and slave machines are powered on.
Then, matrix_generator.c file is used to create matrix of desired sizes by giving matrix size as input.
Next, the serialmatrixmul.c file is used to calculate the product of the matrices which is stored in output.txt.
Then, mpi_map_reduce.c file is executed which automatically does the load balancing depending upon the number of processes provided.
Both the results from serial and parallel execution can be compared which would turn out to be equal.
