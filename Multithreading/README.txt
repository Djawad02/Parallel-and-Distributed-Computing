#Multithreading

Question1:
• A function to populate a 1D array of size 2^16.
• Another function to calculate square root of each item of the array, also replacing it with the original item inside the array.
• Created no.of threads equal to no.of cores using pthread affinity.
• Did block wise distribution of threads for populate() and calcSqrt() function, i.e., Assigned the array items block wise to each thread in each function.
• Printed the resultant array.

Question2:
• Populated a 2D array of size 2^16*2^16 with random integers (range 8000-16000).
• Computed the sum( ) of all the elements in the array and store it in a global variable.
• Printed the sum of all the elements in the array.

Gflops are calculated in each task to make comparison of execution time with and without cpu affinity.

*Important*
To ensure that each thread is computed on a separate core/processor, we use CPU affinity or taskset. 
Binding or unbinding a process or a thread to a specific core or CPU inside the application is ensured through CPU affinity.
However, taskset also can help you to achieve the same goal.
