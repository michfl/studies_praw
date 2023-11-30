#include <mergesort.h>
#include <mergesort_sequential.h>
#include <omp.h>
#include <stdio.h>

#define THREADS_N 10

void mergeSortParallel_OpenMP(int *arr, int l, int r, int threadsN) {
    if (threadsN == 1) {
        mergeSort(arr, l, r);
    } else if (threadsN > 1) {
        int m = l + (r - l) / 2;
        #pragma omp parallel sections num_threads(2)
        {
            #pragma omp section
            {
                mergeSortParallel_OpenMP(arr, l, m, threadsN / 2);
            }
            #pragma omp section
            {
                mergeSortParallel_OpenMP(arr, m + 1, r, threadsN - threadsN / 2);
            }
        }
        merge(arr, l, m, r);
    }
}

void mergeSortOpenMP(int *arr, long size) {
    omp_set_nested(1);
    omp_set_dynamic(0);
    mergeSortParallel_OpenMP(arr, 0, size - 1, THREADS_N);
    return;
}