#ScatterV

There are 10 processes that are participating in the communication equivalent to MPI “Scatterv”.
Out of these 10 processes one process should be randomly selected as coordinating process (who’s buffer will be scattered). 
The data-buffer to be scattered should be dynamically created [1000 min-elementsto 10000 max-elements] and initialized by each process. 
The sendcount and displacement data-structure should also be randomly generated (for 10 processes) in coordinating process.
After scattering data, every process should calculate sum of the received data values. 
All the processes should communicate their local sums to main program (host program in this case) and the main program then
should find a global sum and display the result on the screen.
