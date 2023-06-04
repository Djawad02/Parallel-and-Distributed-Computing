__kernel void calCulatingDotProdct(__global const int* array1,  __global int* array2,__global int* outputarr,
                                     __global const int* subArr,    __global const int* offeset)
{
    int gid = get_global_id(0);
    int gid2 = get_global_id(1);
    int prd = 0;
    int* res;
    int val = offeset[gid];

    int size1 = sizeof(array1)/sizeof(array1[0]);
    int size2 = sizeof(array2)/sizeof(array2[0]);

    for(int i = offeset; i < subArr[gid]; i++){
        res[i]+=  array1[i] * array2[i];
    }

    int dot= 0;
    for(int i = 0; i < val; i++){
        dot +=res[i];
    }
    printf("\n\t\t\t\t\t\t\t***In Kernel***\n");
    printf("dot prod %d\n",dot);
    
    // Write the sum to the output buffer
    outputarr[gid] = dot;
}
