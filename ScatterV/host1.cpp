// openCL headers							Dania jawad 20i0569 CS-B

#ifdef _APPLE_
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif


#include <stdio.h>
#include <stdlib.h>


#define MAX_SOURCE_SIZE (0x100000)



int main(int argc, char** argv) {
	
	// Define the input data array
	int numElem = rand() % (10000 - 1000 + 1) + 1000;
	int *arr1 = (int*)malloc(sizeof(int) * numElem);
	int SIZE = 10;

	for (int i = 0; i < numElem; i++) {
		arr1[i] = rand() % 5000 + 1500;	   //random nums btw 1500 and 6499;
		printf(" %d ", arr1[i]);
	}
	printf("\n");

	// Define the sendcounts and displacements arrays for scatter operation
	int* subArra = (int*)malloc(sizeof(int) * SIZE);		//sendcount
	int* nextOffset = (int*)malloc(sizeof(int) * SIZE);   //displacement

	//randomly select coordinating process
	int coOrdProc = rand() % SIZE;
	int rank = coOrdProc;
	// Initialize the sendcounts and displacements arrays
	if (coOrdProc == rank) {
		for (int i = 0; i < SIZE; i++) {

			// implementation for sendcount
			subArra[i] = rand() % (numElem / SIZE) + 1;

			//implementation for displacemnt
			nextOffset[i] = i * (numElem / SIZE);
		}
	}

	// Set up OpenCL context, command queue, and program
	// Load kernel from file kernel.cl

	FILE* kernelFile;
	char* kernel_source;
	size_t kernelSize;

	kernelFile = fopen("kernel1.cl", "r");

	if (!kernelFile) {
		fprintf(stderr, "No file named kernel1.cl was found\n");
		exit(-1);
	}
	kernel_source = (char*)malloc(MAX_SOURCE_SIZE);
	kernelSize = fread(kernel_source, 1, MAX_SOURCE_SIZE, kernelFile);
	fclose(kernelFile);

	// Getting platform and device information
	cl_platform_id platformId = NULL;
	cl_device_id deviceID = NULL;
	cl_uint retNumDevices;
	cl_uint retNumPlatforms;
	cl_int retErr = clGetPlatformIDs(1, &platformId, &retNumPlatforms);
	char* value;
	size_t valueSize;

	retErr = clGetDeviceIDs(platformId, CL_DEVICE_TYPE_DEFAULT, 1, &deviceID, &retNumDevices);
	clGetDeviceInfo(deviceID, CL_DEVICE_NAME, 0, NULL, &valueSize);
	value = (char*)malloc(valueSize);
	clGetDeviceInfo(deviceID, CL_DEVICE_NAME, valueSize, value, NULL);
	printf("\nDevice: %s\n", value);
	free(value);

	// Creating context.
	cl_context context = clCreateContext(NULL, 1, &deviceID, NULL, NULL, &retErr);


	// Creating command queue
	cl_command_queue commandQueue = clCreateCommandQueue(context, deviceID, 0, &retErr);

	// Create OpenCL buffers for the input data and output
	cl_mem original_buffer = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(int)*numElem, NULL, NULL);
	cl_mem result_nuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(int) * SIZE, NULL, NULL);
	cl_mem offsett_buffer = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(int) * SIZE, NULL, NULL);
	cl_mem subArr_buffer = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(int) * SIZE, NULL, NULL);


	// Write the sendcounts and displacements arrays to the OpenCL buffers
	clEnqueueWriteBuffer(commandQueue, original_buffer, CL_TRUE, 0, sizeof(int) * numElem, arr1, 0, NULL, NULL);
	clEnqueueWriteBuffer(commandQueue, subArr_buffer, CL_TRUE, 0, sizeof(int) * SIZE, subArra, 0, NULL, NULL);
	clEnqueueWriteBuffer(commandQueue, offsett_buffer, CL_TRUE, 0, sizeof(int) * SIZE, nextOffset, 0, NULL, NULL);


	// Create program from kernel source
	cl_program program = clCreateProgramWithSource(context, 1, (const char**)&kernel_source, (const size_t*)&kernelSize, &retErr);

	// Build program
	retErr = clBuildProgram(program, 1, &deviceID, NULL, NULL, NULL);

	// Create kernel
	cl_kernel kernel = clCreateKernel(program, "sumUsingScatterV", &retErr);
	// Set the kernel arguments

	clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&original_buffer);
	clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*)&result_nuffer);
	clSetKernelArg(kernel, 2, sizeof(cl_mem), (void*)&subArr_buffer); 
	clSetKernelArg(kernel, 3, sizeof(cl_mem), (void*)&offsett_buffer);


	// Enqueue the kernel for execution

	size_t global_size = SIZE;
	size_t local_size = 1;
	clEnqueueNDRangeKernel(commandQueue, kernel, 1, NULL, &global_size, &local_size, 0, NULL, NULL);

	// Read the output buffer into a local array
	int* local_sum = (int*)malloc(sizeof(int) * SIZE);;
	clEnqueueReadBuffer(commandQueue, result_nuffer, CL_TRUE, 0, sizeof(int) * SIZE, local_sum, 0, NULL, NULL);

	// Calculate the global sum
	int global_sum = 0;
	printf("\n\t\t\t\t\t\t\t***In Host*** \n");
	for (int i = 0; i < SIZE; i++) {
		printf("local sum: %d\n", local_sum[i]);
		global_sum += local_sum[i];
	}

	printf("\nglobal sum: %d\n", global_sum);
	printf("\n\t\t\t\t\t\t\tProgram end.\n");
	

	// Clean up, release memory.
	retErr = clFlush(commandQueue);
	retErr = clFinish(commandQueue);
	retErr = clReleaseCommandQueue(commandQueue);
	retErr = clReleaseKernel(kernel);
	retErr = clReleaseProgram(program);
	retErr = clReleaseMemObject(subArr_buffer);
	retErr = clReleaseMemObject(offsett_buffer);
	retErr = clReleaseContext(context);
	retErr = clReleaseMemObject(original_buffer);
	retErr = clReleaseMemObject(result_nuffer);
	
	//freeing memory
	free(arr1);
	free(local_sum);

	return 0;

}