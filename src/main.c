#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <time.h>
#include <mergesort.h>

#define METHODS_N 3

#define SEQUENTIAL  "sequential"
#define OPEN_MP     "OpenMP    "
#define OPEN_MP_OPT "OpenMP_opt"
#define CUDA        "CUDA      "

void readMetadata(FILE *fp, long* arrNumber, long* arrLength) {
    fscanf(fp, "%ld %ld", arrNumber, arrLength);
    return;
}

void readArray(FILE *fp, int* arr, long arrLength) {
    for (long i = 0; i < arrLength; i++) {
        fscanf(fp, "%d", &arr[i]);
    }
    return;
}

void copyArray(int *source, int *dest, long arrLength) {
    for (long i = 0; i < arrLength; i++) {
        dest[i] = source[i];
    }
}

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

double performTests(char *method, void (*f)(int*, long), int* arr, long arrLength) {
    int arrCopy1[arrLength], arrCopy2[arrLength];
    clock_t begin, end;
    double timeSpent;

    copyArray(arr, arrCopy1, arrLength);
    copyArray(arr, arrCopy2, arrLength);

    // warm-up
    (*f)(arrCopy1, arrLength);

    // test
    begin = clock();
    (*f)(arrCopy2, arrLength);
    end = clock();

    timeSpent = (double)(end - begin) / CLOCKS_PER_SEC;
    
    printf("- %s:\tis sorted: %d,\ttime: %fs\n", method, isSorted(arrCopy2, arrLength), timeSpent);
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

void printSummary(char *method, double mean, double meanMultiplier, double min, double minMultiplier, double max, double maxMultiplier) {
    printf("- %s:\tmean time: %fs\t%0.2fx,\tmin: %fs\t%0.2fx,\tmax: %fs\t%0.2fx,\tuncertainty: %fs\n",
        method, mean, meanMultiplier, min, minMultiplier, max, maxMultiplier, (max - min) / 2.0);
}

void showSummary(char **methods, double **times, long timesLength, int methodsLength) {
    double referenceMean, referenceMin, referenceMax;
    double mean, min, max;
    double meanMultiplier = 1, minMultiplier = 1, maxMultiplier = 1;
    
    printf("\nSummary:\n");

    summarizeTimes(times[0], timesLength, &referenceMean, &referenceMin, &referenceMax);
    printSummary(methods[0], referenceMean, meanMultiplier, referenceMin, minMultiplier, referenceMax, maxMultiplier);

    for (int i = 1; i < methodsLength; i++) {
        summarizeTimes(times[i], timesLength, &mean, &min, &max);
        meanMultiplier = referenceMean / mean;
        minMultiplier = referenceMin / min;
        maxMultiplier = referenceMax / max;
        printSummary(methods[i], mean, meanMultiplier, min, minMultiplier, max, maxMultiplier);
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Insufficient number of args:\n"
            "arg1: input file name\n");
        return 1;
    }

    // METHOD DEFINITIONS HERE
    char *methods[] = {
        SEQUENTIAL, 
        OPEN_MP,
        OPEN_MP_OPT
    };
    void (*methodAlgorithms[])(int*, long) = {
        mergeSortSequential,
        mergeSortOpenMP,
        mergeSortOpenMPOpt
    };
    // END

    char* inputFile = argv[1];
    long arrNumber, arrLength;
    FILE *fp;

    fp = fopen(inputFile, "r");
    readMetadata(fp, &arrNumber, &arrLength);

    double *times[METHODS_N];
    for (int i = 0; i < METHODS_N; i++) {
        times[i] = malloc(arrNumber * sizeof(double));
    }
    int *arr = malloc(arrLength * sizeof(int));

    for (long i = 0; i < arrNumber; i++) {
        readArray(fp, arr, arrLength);
        printf("Test %ld:\n", i + 1);

        for (int j = 0; j < METHODS_N; j++) {
            times[j][i] = performTests(methods[j], methodAlgorithms[j], arr, arrLength);
        }
    }

    showSummary(methods, times, arrNumber, METHODS_N);

    fclose(fp);
    free(arr);
    for (int i = 0; i < METHODS_N; i++) {
        free(times[i]);
    }
    return 0;
}