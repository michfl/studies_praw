#include <float.h>
#include <time.h>
#include <stdio.h>
#include <benchmark.h>

int isSorted(int *arr, long arrLength) {
    if (arrLength <= 1) {
        return 1;
    }
    for (long i = 1; i < arrLength; i++) {
        if (arr[i] < arr[i - 1]) {
            return 0;
        }
    }
    return 1;
}

double performTests(void (*f)(int*, long), int* arr, long arrLength) {
    int isSortedBefore, isSortedAfter;
    clock_t begin, end;
    double timeSpent;

    isSortedBefore = isSorted(arr, arrLength);

    begin = clock();
    (*f)(arr, arrLength);
    end = clock();

    isSortedAfter = isSorted(arr, arrLength);

    timeSpent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("is sorted (before|after): %d|%d, time: %fs\n", isSortedBefore, isSortedAfter, timeSpent);
    return timeSpent;
}

void summarizeTimes(double *times, long length, double *mean, double *min, double *max) {
    double sum = 0, minVal = DBL_MAX, maxVal = DBL_MIN;
    for (long i = 0; i < length; i++) {
        sum += times[i];
        if (times[i] < minVal) {
            minVal = times[i];
        }
        if (times[i] > maxVal) {
            maxVal = times[i];
        }
    }
    (*mean) = sum / length;
    (*min) = minVal;
    (*max) = maxVal;
}