                                    // ASSSIGNMENT 2 PDC 
                                    //TASK 2b Merge sort
                                    // DANIA JAWAD 20I0569 CS-B
#include<mpi.h>
#include <stdio.h>
#include<stdlib.h>
#include <sys/time.h>

#define leafN1 1024 //2^10   9+1 =10
#define leafN2 128  //2^7  6+1 = 7
#define leafN3 64  //2^6  5+1 = 6

#define maxSize 131072
int array1[maxSize];// ={9,8,7,6,5,4,3,2};;

//utility function for mergesort
void Mergee(int arr[], int fir, int las,int midd){
    int firstHlf = midd-fir+1;
    int secondHlf = las-midd;

    int firHalfArr[firstHlf];
    int secHalfArr[secondHlf];

    int val1=0;
    int val3=0;
    int val2=0;

        while(firstHlf>val1){
            firHalfArr[val1] = arr[fir+val1];
            val1++;
        }

        while(secondHlf>val2){
            secHalfArr[val2] = arr[1+val2+midd];
            val2++;
        }
        val2=0;
        val3=fir;
        val1=0;

        while(secondHlf > val2 && val1 < firstHlf){    
            if(firHalfArr[val1] <= secHalfArr[val2]) {    
                arr[val3] = firHalfArr[val1];    
                val1++;    
            }    
            else{    
                arr[val3] = secHalfArr[val2];    
                val2++;    
            }    
            val3++;    
        }    
        while(firstHlf>val1){    
            arr[val3] = firHalfArr[val1];    
            val1++;    
            val3++;    
        }    
        while (secondHlf>val2){    
            arr[val3] = secHalfArr[val2];    
            val2++;    
            val3++;    
        } 
    
     
}

//recursive merge sort function
void Mergesort(int arr[], int fir, int las){
     if(las-fir <= leafN1){
        if (fir < las){
            int midd = (fir+las)/2;
            //sort first half and then second half           
            Mergesort(arr,fir,midd);
            Mergesort(arr,midd+1,las);
            Mergee(arr, fir,las,midd);
        }
     }

}

//reads the array from the input files
void ReadingFromFile(char *filName,int arr1[],int s){
    FILE *fileReader;
    fileReader = fopen(filName,"r");
    int i=0;
    if(fileReader!=NULL){
        while(fscanf(fileReader, "%d", &arr1[i]) != EOF)
         i++;  
    }
    else {
        printf("Error in opening the file.\n");
        MPI_Finalize();
    }

}

int main(int argc, char **argv){
    double operation_count=0.0;//number of op
    struct timeval start, end;

    if(argc == 2){
        int i,rank,nproc,irecv;
        int* isend;int portion;
        //printf(" %s ",argv[0]);
        int arrayS = atoi(argv[1]);
        char *Ifile;
        if(arrayS == 2048){
                Ifile = "inputFile2048.txt";
        }
        else if(arrayS == 8192){
            Ifile = "inputFile8192.txt";
        }
        else if(arrayS == 32768){
            Ifile = "inputFile32768.txt";
        }
        else if(arrayS == 131072){
            Ifile = "inputFile131072.txt";
        }
        else {
            printf("\n\t\t\t\tSORRY!\n");
            printf("\t\tKindly provide array size:  2048, 8192, 32768 or 131072\n");
            exit(1);
        }

        MPI_Init(&argc, &argv);
        MPI_Comm_size(MPI_COMM_WORLD,&nproc);
        MPI_Comm_rank(MPI_COMM_WORLD,&rank);

        //Master process reads the data
        if (rank==0) {
            
            printf("The input file is: %s",Ifile);
            printf("\n");
            ReadingFromFile(Ifile,array1,arrayS);
            portion = arrayS/nproc;
            gettimeofday( &start, NULL );
        }
        
        //equal portions broadcasted to all processes
        MPI_Bcast(&portion, 1, MPI_INT, 0, MPI_COMM_WORLD);
        
        int *partedArr = (int*)malloc(portion * sizeof(int));   //the piece of array every process has to sort

        //scattered the parts
        MPI_Scatter(array1, portion, MPI_INT, partedArr, portion, MPI_INT, 0, MPI_COMM_WORLD);
        printf("\n\n\t\t\t\t\t***Process with rank %d has received array portion %d***\n",rank,portion);
        for(int i = 0;i<portion;i++){
            printf(" %d ",partedArr[i]);
        }
        printf("\n\n");

        Mergesort(partedArr,0,portion-1);

        // now the master would merge the results together
        MPI_Gather(partedArr, portion, MPI_INT, array1, portion, MPI_INT, 0, MPI_COMM_WORLD);

        if(rank ==0){
            //master sorts the individual sorted parts together
            Mergesort(array1,0,arrayS-1);
            gettimeofday( &end, NULL );
            printf("\n\n\t\t\t\t\t***The array after sorting is given as :***\n");
            for (int i = 0; i < arrayS; i++) {
                printf("%d ", array1[i]);
            }
            printf("\n");
            operation_count = arrayS*2;
            double seconds1 = (end.tv_sec - start.tv_sec) + 1.0e-6 * (end.tv_usec - start.tv_usec);
            //  printf("Seconds: %f", seconds1);
            double Gflops1 = 2e-9*operation_count/seconds1;
            printf( "\n\nPerformance of MergeSort in Gflops %.6f Gflop/s\n\n", Gflops1 );
        }

        
        
        MPI_Finalize();
    }

    else printf("Please provide array size\n");

return 0;
}
