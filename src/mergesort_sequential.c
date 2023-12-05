#include <mergesort.h>
#include <mergesort_sequential.h>

// merge sort alg sources: https://www.geeksforgeeks.org/merge-sort/

// 1 subarray -> arr[l..m]
// 2 subarray -> arr[m+1..r]
void merge(int *arr, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

	// temp
    int L[n1], R[n2];
 
    // fill temp
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
 
    // merge
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    // copy remaining L[]
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    // copy remaining R[]
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// sub-array from l to r index
void mergeSort(int *arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
 
        // sort both halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void mergeSortSequential(int *arr, long size) {
    mergeSort(arr, 0, size - 1);
    return;
}