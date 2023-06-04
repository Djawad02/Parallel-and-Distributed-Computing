                                    // ASSSIGNMENT 1 PDC 
                                    //TASK 2
                                    // DANIA JAWAD 20I0569 CS-B

#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

#define sizeeArr1 16

int array1[sizeeArr1][sizeeArr1]; 
int sumOfArr1=0;

struct BlockInfo{
int start;
int end;
int BlkSize;
};

void* populatte(void* argg){
// printf("\n Hi from function: *Populating the array* \n");
// size_t n = sizeof(array1)/sizeof(array1[0]);
// printf("SIZEEEE: %ld \n",n);
struct BlockInfo *blockk = (struct BlockInfo *)argg;
// printf("\n Starting: %d \n",blockk->start);
// printf("\n ending: %d \n",blockk->end);
for(int i = blockk->start ;i<blockk->end;i++){
   for(int j = 0;j<blockk->BlkSize;j++){
     for (int k = 0; k < blockk->end; k++)
     {
        array1[j][k] = rand()% (16000+1-8000)+8000;   //range between 8000-16000 
      // printf(" %d ",array1[i][j]);
     }
     
   } 
}
// free(arg);
pthread_exit(NULL);
}


void* sumationArr(void* argg){
// printf("\n Hi from function: *Populating the array* \n");
// size_t n = sizeof(array1)/sizeof(array1[0]);
// printf("SIZEEEE: %ld \n",n);
struct BlockInfo *blockk = (struct BlockInfo *)argg;
printf("\n Starting: %d \n",blockk->start);
printf("\n ending: %d \n",blockk->end);
for(int i = blockk->start ;i<blockk->end;i++){
   for(int j = 0;j<blockk->BlkSize;j++){
     for (int k = 0; k < blockk->end; k++)
     {
        sumOfArr1 = sumOfArr1 + array1[i][j];   //range between 8000-16000 rand()% (16000+1-8000)+8000
      // printf(" %d ",array1[i][j]);
     }
     
   } 
}
 printf(" \n ");

// free(arg);
pthread_exit(NULL);
}


int main( int argc, char **argv ) {
 
double operation_count=0.0;//number of op
struct timeval start, end; 
int i = 0;
int blockArray[]={4,16,64};
int choice;
printf("Enter blocksize: ");
scanf("%d",&choice);
int BlockfOrThreads = choice;
int numThreads = (sizeeArr1*sizeeArr1)/BlockfOrThreads;   //returns no of cores
printf("The number of Threads : %d \n",numThreads);
pthread_t TID1[numThreads];
// printf("size of block: %d \n",BlockfOrThreads);
 struct BlockInfo info[numThreads]; 

for (i = 0; i < numThreads; i++){
    info[i].start = i*BlockfOrThreads;
    info[i].end = (i+1)*BlockfOrThreads;
    info[i].BlkSize = BlockfOrThreads;
    printf("Block Starting: %d\n",info[i].start);
    printf("Block Ending: %d\n",info[i].end);
}

 printf("\n\n THREADS CREATION \n\n");
 /*
    FOR POPULATING THE ARRAY
                             */
gettimeofday( &start, NULL );
for (i = 0; i < numThreads; i++){   //creating all threads        
     /* code */
   
    pthread_create(&TID1[i] , NULL ,(void*)&populatte , &info[i]);

}
for ( i = 0; i < numThreads; i++){ //waiting for execution
/* code */
pthread_join(TID1[i], NULL);
}
gettimeofday( &end, NULL );
//loop for printing array
printf("\n Printing the original array \n");
for (int h = 0; h < sizeeArr1; h++){
    /* code */
    for (int j = 0; j < sizeeArr1; j++){
        /* code */
        printf(" %d ",array1[h][j]);
    }
    printf("\n");
}
operation_count = sizeeArr1*2;
double seconds1 = (end.tv_sec - start.tv_sec) + 1.0e-6 * (end.tv_usec - start.tv_usec);
    // printf("Seconds: %f", seconds);
double Gflops1 = 2e-9*operation_count/seconds1;
printf( "\n\nPerformance of Populate function in Gflops %.7f Gflop/s\n\n", Gflops1 );

 /*
    FOR sum of THE ARRAY
                             */

// for (i = 0; i < numThreads; i++){   //creating all threads        
//      /* code */

//     pthread_create(&TID1[i] , NULL ,(void*)&sumationArr , &info[i]);

// }
// for ( i = 0; i < numThreads; i++){ //waiting for execution
// /* code */
// pthread_join(TID1[i], NULL);
// }

// printf("The sum is: %d \n",sumOfArr1);

}