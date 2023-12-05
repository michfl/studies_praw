#include <mergesort.h>
#include <cuda_runtime.h>
#include <stdlib.h>
#include <stdio.h>

#define BLOCKS_IN_GRID 380
#define THREADS_IN_BLOCK 256

#define min(a, b) (a < b ? a : b)

// bottom-up merge sort alg sources: https://en.wikipedia.org/wiki/Merge_sort#Bottom-up_implementation

__host__
void errorexit(const char *s) {
    printf("\n%s", s);	
    exit(EXIT_FAILURE);	 	
}

__device__ 
void merge_CUDA(int *arr, int *tmp, long left, long right, long end) {
    long i = left;
    long j = right;
    for (long k = left; k < end; k++) {
        if (i < right && (j >= end || arr[i] < arr[j])) {
            tmp[k] = arr[i];
            i++;
        } else {
            tmp[k] = arr[j];
            j++;
        }
    }
}

__global__ 
void mergeSortParallel_CUDA(int *arr, int *tmp, long size, long width, long chunksN) {
    unsigned int idx = blockIdx.x * blockDim.x + threadIdx.x;
    long start = idx * width * chunksN;

    for (long i = 0; i < chunksN; i++) {
        if (start >= size)
            break;

        merge_CUDA(arr, tmp, start, min(start + (width >> 1), size), min(start + width, size));
        start += width;
    }
}

extern "C" void mergeSortCUDA(int *arr, long size) {
	
	clock_t begin, end;
	long threadsN = BLOCKS_IN_GRID * THREADS_IN_BLOCK;

	// device memory allocation (GPU)
    int *darr = NULL;
	int *dtmp = NULL;
    if (cudaSuccess != cudaMalloc((void **) &darr, size * sizeof(int))) {
		errorexit("Error allocating memory on the GPU");
    }
	if (cudaSuccess != cudaMalloc((void **) &dtmp, size * sizeof(int))) {
		errorexit("Error allocating memory on the GPU");
    }

	// copy arr to device memory
    if (cudaSuccess != cudaMemcpy(darr, arr, size * sizeof(int), cudaMemcpyHostToDevice)) {
		errorexit("Error copying array to device");
	}

	// perform merge sort in bottom-up manner
	begin = clock();
	int* A = darr;
    int* B = dtmp;
	for (long width = 2; width < (size * 2); width *= 2) {
        long chunksN = size / ((threadsN) * width) + 1;

        mergeSortParallel_CUDA<<<BLOCKS_IN_GRID, THREADS_IN_BLOCK>>>(A, B, size, width, chunksN);
		cudaMemcpy(A, B, size * sizeof(int), cudaMemcpyDeviceToDevice);
    }
	end = clock();
	printf("| GPU actual calculations time: %fs\n", (double)(end - begin) / CLOCKS_PER_SEC);

	// copy results from device to host
    if (cudaSuccess != cudaMemcpy(arr, A, size * sizeof(int), cudaMemcpyDeviceToHost)) {
		errorexit("Error copying results to host");
	}

	//free memory
    if (cudaSuccess != cudaFree(darr)) {
		errorexit("Error when deallocating space on the GPU");
	}
	if (cudaSuccess != cudaFree(dtmp)) {
		errorexit("Error when deallocating space on the GPU");
	}

    return;
}