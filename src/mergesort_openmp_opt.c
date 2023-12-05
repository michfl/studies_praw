#include <mergesort.h>
#include <omp.h>
#include <stdlib.h>
#include <string.h>

#define THREADS_N 16
#define TASK_SIZE 1000

// opt merge sort alg sources: https://en.wikipedia.org/wiki/Merge_sort#Top-down_implementation

void merge_OpenMP_opt(int *arr, int * tmp, long size) {
    long i = 0;
    long j = size / 2;
    long ti = 0;

    // merge
    while (i < size / 2 && j < size) {
        if (arr[i] < arr[j]) {
            tmp[ti] = arr[i];
            ti++; 
            i++;
        } else {
            tmp[ti] = arr[j];
            ti++; 
            j++;
        }
    }

    // copy remaining of lower half (L[])
    while (i < size / 2) {
        tmp[ti] = arr[i];
        ti++; 
        i++;
    }

    // copy remaining of upper half (R[])
    while (j < size) {
        tmp[ti] = arr[j];
        ti++; 
        j++;
    }

    memcpy(arr, tmp, size*sizeof(int));
}

void mergeSortParallel_OpenMP_opt(int *arr, int *tmp, long size) {
    if (size < 2) {
        return;
    }

    #pragma omp task shared(arr, tmp) if (size > TASK_SIZE)
    mergeSortParallel_OpenMP_opt(arr, tmp, size / 2);

    #pragma omp task shared(arr, tmp) if (size > TASK_SIZE)
    mergeSortParallel_OpenMP_opt(arr + (size / 2), tmp + (size / 2), size - (size / 2));

    #pragma omp taskwait
    merge_OpenMP_opt(arr, tmp, size);
}

void mergeSortOpenMPOpt(int *arr, long size) {
    omp_set_nested(0);
    omp_set_dynamic(0);

    int *tmp = malloc(size * sizeof(int));

    #pragma omp parallel num_threads(THREADS_N)
    {
        #pragma omp single
        mergeSortParallel_OpenMP_opt(arr, tmp, size);
    }

    free(tmp);
    return;
}