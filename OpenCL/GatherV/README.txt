#GatherV

There are 10 processes that are participating in the communication equivalent to MPI “Gatherv”. Out of these 10 processes one process should be randomly selected as coordinating process (who’s buffer will be prepared by gathering data sent by others). 
The data-size to be gathered should be dynamically created by each process [20 min-elements to 200 max-elements] and initialized. 
The sendcount and displacement data-structure should also be dynamically/randomly prepared (for 10 processes) and used by the coordinating process. 
After gathering data, the coordinating process should calculate a dot product using another randomly created and prepared sparse data-array (sparse because the gathered data have been prepared using displacements thus could result in vacant data values).
The coordinating process should convey the dot product data to main program (i.e., host). 
The host program will sum all values and display the result.
