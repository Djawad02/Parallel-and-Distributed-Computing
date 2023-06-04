__kernel void sumUsingScatterV(__global const int* array,  __global int* outputarr, __global const int* subArr,
                                __global const int* offeset)
{
    int gid = get_global_id(0);
    int sum = 0;

    for (int i = 0; i < subArr[gid]; i++) {
        //printf("\narray %d",array[i]);
        int jk = offeset[gid] + i;
        sum += array[jk];
    }
    printf("\n\t\t\t\t\t\t\t***In Kernel***\n");
    printf("Sum %d\n",sum);
    
    // Write the sum to the output buffer
    outputarr[gid] = sum;
}
