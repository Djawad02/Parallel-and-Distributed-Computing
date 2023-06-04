                                    // ASSSIGNMENT 1 PDC 
                                    //TASK 1
                                    // DANIA JAWAD 20I0569 CS-B

#define _GNU_SOURCE
#define sizeeArr1 65536

#include <sys/time.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <math.h>
#include <sched.h>
// #define _GNU_SOURCE 
// #include <sched.h>


float array1[sizeeArr1]; //2^16

struct BlockInfo{
int start;
int end;
int BlkSize;
};

void* populate(void* argg){
    printf("\nCore Currently running: %d",sched_getcpu());
// printf("\n Hi from function: *Populating the array* \n");
// size_t n = sizeof(array1)/sizeof(array1[0]);
// printf("SIZEEEE: %ld \n",n);
struct BlockInfo *blockk = (struct BlockInfo *)argg;
// printf("\n Starting: %d \n",blockk->start);
// printf("\n ending: %d \n",blockk->end);
for(int i = blockk->start ;i<blockk->end;i++){
   
     array1[i] = i;
  //  printf(" %d ",array1[i]);
}

 printf(" \n ");

// free(arg);
pthread_exit(NULL);
}

void* calcSqrt(void* argg){
    // int val = *(int*)arg;
    // printf("Hi from Function: *SquareRoot of array* \n");
    //  size_t n = sizeof(array1)/sizeof(array1[0]);
    // printf("SIZEEEE: %ld \n",n);
    struct BlockInfo *blockk = (struct BlockInfo *)argg;
    for(int i = blockk->start ;i<blockk->end;i++){
         array1[i] = sqrtf((float)array1[i]);  
    }
    printf("\n");
   // free(arg);
    pthread_exit(NULL);
}

int main( int argc, char **argv ) {

double operation_count=0.0;//number of op
struct timeval start, end;

cpu_set_t cpuObj;
int i = 0;
long numCores = sysconf(_SC_NPROCESSORS_ONLN);   //returns no of cores
printf("\nThe number of cores : %ld \n",numCores);
pthread_t TID1[numCores];
int BlockfOrThreads = sizeeArr1/numCores;
// printf("size of block: %d \n",BlockfOrThreads);
 struct BlockInfo info[numCores];

for (i = 0; i < numCores; i++){
    info[i].start = i*BlockfOrThreads;
    info[i].end = (i+1)*BlockfOrThreads;
    info[i].BlkSize = BlockfOrThreads;
    printf("Block Starting: %d\n",info[i].start);
    printf("Block Ending: %d\n",info[i].end);
}

 printf("\n\n THREADS BEING CREATED NOW \n\n ");
 /*
    FOR POPULATING THE ARRAY
                             */
 gettimeofday( &start, NULL );
for (i = 0; i < numCores; i++){   //creating all threads        
     /* code */
    CPU_ZERO(&cpuObj);
    CPU_SET(i,&cpuObj);
    pthread_create(&TID1[i] , NULL ,(void*)&populate , &info[i]);
    pthread_setaffinity_np(TID1[i],sizeof(cpu_set_t),&cpuObj);
}
for ( i = 0; i < numCores; i++){ //waiting for execution
/* code */
pthread_join(TID1[i], NULL);
}
 gettimeofday( &end, NULL );

// loop for printing array
printf("\n Printing the original array \n");
for (int j = 0; j < sizeeArr1; j++){
        /* code */
        printf(" %f ",array1[j]);
}

operation_count = sizeeArr1*2;
double seconds1 = (end.tv_sec - start.tv_sec) + 1.0e-6 * (end.tv_usec - start.tv_usec);
    // printf("Seconds: %f", seconds);
double Gflops1 = 2e-9*operation_count/seconds1;




/*
    FOR SQUARE ROOT OF THE ARRAY
                                */
gettimeofday( &start, NULL );           
for (i = 0; i < numCores; i++){   //creating all threads        
        /* code */
    CPU_ZERO(&cpuObj);
    CPU_SET(i,&cpuObj);
    pthread_create(&TID1[i] , NULL ,(void*)&calcSqrt , &info[i] );
    pthread_setaffinity_np(TID1[i],sizeof(cpu_set_t),&cpuObj);
}
for ( i = 0; i < numCores; i++){    //waiting for execution
    /* code */
    pthread_join(TID1[i], NULL);
}
gettimeofday( &end, NULL );
// printf("\n Printing the sqroot array \n");
for (int j = 0; j < sizeeArr1; j++){
    /* code */
    printf(" %f ",array1[j]);
}
printf("\n");
printf( "\n\nPerformance of Populate function in Gflops %.3f Gflop/s\n\n", Gflops1 );

operation_count = sizeeArr1*2;
double seconds = (end.tv_sec - start.tv_sec) + 1.0e-6 * (end.tv_usec - start.tv_usec);
    // printf("Seconds: %f", seconds);
double Gflops = 2e-9*operation_count/seconds;
printf( " \n\nPerformance of Square root function in Gflops %.3f Gflop/s\n", Gflops );


}