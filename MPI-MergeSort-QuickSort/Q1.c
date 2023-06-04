                                    // ASSSIGNMENT 2 PDC 
                                          //TASK 1
                                    // DANIA JAWAD 20I0569 CS-B
#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define maxSize 131072
int array1[maxSize];
int firstE=0;
int lastE=0;

//function to print array
void showArray(int size, int arr[]){
    printf("\nthe array:\n");
    
    for (int i = 0; i < size; i++){
        printf(" %d ",arr[i]);
        
    }
    printf("\n");
  //printf("first %d last %d ",firstE,lastE);
}

//populates the array
void populateValues(int size){
    for (int i = 0; i < size; i++){
        array1[i] = rand()% (1000+1-200)+200;   // will generate random values in range 200-1000
        firstE = 0;
        lastE =size-1;
    }
}

//writes array data into the file
void ReturningOutputIntoFile(int arr1[],int S,char *Ofile, char *s1){
    FILE *fileWriter; 
    fileWriter = fopen(Ofile,"w");
    if(fileWriter!=NULL){
        fprintf(fileWriter, "%s\n", s1);
        for (int i = 0; i < S; i++) {
            fprintf(fileWriter, "%d\n", arr1[i]);
        }
    }

    else printf("Error in opening the file.\n");

    pclose(fileWriter);
}

//reads file data into a file
void ReadingFromFile(char *filName,int arr1[],int s){
    FILE *fileReader;
    fileReader = fopen(filName,"r");
    int i=0;
    if(fileReader!=NULL){
        while(fscanf(fileReader, "%d", &arr1[i]) != EOF)
         i++;  
    }
    //    printf("Filee read iss\n");
    //    for(int j = 0;j<s;j++){
    //      printf(" %d ",arr1[j]);
            
    //     }
    else printf("Error in opening the file.\n");

}

//for maintaining an input file
void savingInputIntoFile(int arr1[],int siz,char *filName){
    FILE *fileWriter; 
    fileWriter = fopen(filName,"w");
    if(fileWriter!=NULL){
       for (int i = 0; i < siz; i++) {
        fprintf(fileWriter, "%d\n", arr1[i]);
       }
    }

    else printf("Error in opening the file.\n");

    pclose(fileWriter);
}

//utility function for quick sort
int partitioningArr(int arr[], int fir, int las){
    int startingPt = arr[las]; 
    int val = (fir-1);
    int i = fir;
    while( i <= las - 1){  
      // current value smaller than the starting one swap them
      if (arr[i] < startingPt){  
            val++; 
            int tempp1 = arr[val];      
            arr[val] = arr[i];  
            arr[i] = tempp1;  
        }  
      i++;
    }  
    // now swap the last index element with initial
    int tempp2 = arr[val+1];  
    arr[val+1] = arr[las];  
    arr[las] = tempp2;  
    return (val + 1);  
}

//the quick sort function
void Quicksort(int arr[], int fir, int las){
//    printf("%d : %d",fir,las);
    if (fir < las){
       int div = partitioningArr(arr, fir,las);
       Quicksort(arr, fir, div-1);
       Quicksort(arr, div+1	, las);
    }
}

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
//merge sort function
void Mergesort(int arr[], int fir, int las){
      if (fir < las){
       int midd = (fir+las)/2;
       //sort first half and then second half
       
       Mergesort(arr,fir,midd);
       Mergesort(arr,midd+1,las);
       Mergee(arr, fir,las,midd);
    }
}

int main(int argc, char **argv ){
    double operation_count=0.0;//number of op
    struct timeval start, end;

    if(argc==3){ //check for the output file name and aarray size
        int arrayS = atoi(argv[1]);
        char  *Ifile;
        char  *Ofile = argv[2];
        
        printf("\n");
        printf("The array size is : %d \n", arrayS);
        printf("The output file is : %s \n", Ofile);
        printf("\n");

        switch (arrayS){
            case 2048:    //2^11
                populateValues(arrayS);  //to randomly fill the array
                Ifile = "inputFile2048.txt";
                savingInputIntoFile(array1,arrayS,Ifile);
                ReadingFromFile(Ifile,array1,arrayS);
                break;
            case 8192:    //2^13
                populateValues(arrayS); //to randomly fill the array
                Ifile = "inputFile8192.txt";
                savingInputIntoFile(array1,arrayS,Ifile);
                ReadingFromFile(Ifile,array1,arrayS);
                break;
            case 32768:   //2^15
                populateValues(arrayS); //to randomly fill the array
                Ifile = "inputFile32768.txt";
                savingInputIntoFile(array1,arrayS,Ifile);
                ReadingFromFile(Ifile,array1,arrayS);
                break;
            case 131072:   //2^17
                populateValues(arrayS); //to randomly fill the array
                Ifile = "inputFile131072.txt";
                savingInputIntoFile(array1,arrayS,Ifile);
                ReadingFromFile(Ifile,array1,arrayS);
                break;
            default:
                printf("The entered size is out of range");
                break;
        }

        printf("1. Merge Sort\n2.Quick sort\n");
        int choicee;
        printf("Enter your sorting algorithm: ");
        scanf("%d",&choicee);
        
        if(choicee==1){
            printf("\n\n\t\t\t\t\t\t\t***MERGE SORT ALGORITHM***\n");
            printf("The input was taken from the file : %s \n",Ifile);
            printf("Your sorted array is saved in : %s \n",Ofile);

            gettimeofday( &start, NULL );
            Mergesort(array1,firstE,lastE);
            gettimeofday( &end, NULL );

            char *s2 = "\t\t\t\t\t\t\t***MERGE SORT ALGORITHM***";
            ReturningOutputIntoFile(array1,arrayS,Ofile,s2);

            operation_count = arrayS*2;
            double seconds1 = (end.tv_sec - start.tv_sec) + 1.0e-6 * (end.tv_usec - start.tv_usec);
                //  printf("Seconds: %f", seconds1);
            double Gflops1 = 2e-9*operation_count/seconds1;
            printf( "\n\nPerformance of MergeSort in Gflops %.6f Gflop/s\n\n", Gflops1 );
        }
        else if(choicee==2){
            printf("\n\n\t\t\t\t\t\t\t***QUICK SORT ALGORITHM***\n");
            printf("The input was taken from the file : %s \n",Ifile);
            printf("Your sorted array is saved in : %s \n",Ofile);
            
            gettimeofday( &start, NULL );
            Quicksort(array1,firstE,lastE);
            gettimeofday( &end, NULL );

            char *s1 = "\t\t\t\t\t\t\t***QUICK SORT ALGORITHM***";
            ReturningOutputIntoFile(array1,arrayS,Ofile,s1);

            operation_count = arrayS*2;
            double seconds = (end.tv_sec - start.tv_sec) + 1.0e-6 * (end.tv_usec - start.tv_usec);
                    // printf("Seconds: %f", seconds);
            double Gflops = 2e-9*operation_count/seconds;
            printf( "\n\nPerformance of QuickSort in Gflops %.6f Gflop/s\n\n", Gflops );
        }

        
    }
    else printf("Please provide array size and output file name!\n");

    return 0;
}