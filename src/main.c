#include <stdio.h>
#include <stdlib.h>
#include <benchmark.h>
#include <mergesort.h>

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

void printSummary(double *times, long length) {
    double mean, min, max;
    summarizeTimes(times, length, &mean, &min, &max);
    printf("mean time: %fs, min: %fs, max: %fs, uncertainty: %fs\n",
        mean, min, max, (max - min) / 2.0);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Insufficient number of args:\n"
            "arg1: input file name");
        return 1;
    }

    char* inputFile = argv[1];
    long arrNumber, arrLength;
    FILE *fp;

    fp = fopen(inputFile, "r");
    readMetadata(fp, &arrNumber, &arrLength);

    int arr[arrLength];
    double timeSpentPlain[arrNumber];

    for (long i = 0; i < arrNumber; i++) {
        readArray(fp, arr, arrLength);
        printf("Test %ld:\n", i + 1);

        printf(" - plain: ");
        timeSpentPlain[i] = performTests(mergeSortPlain, arr, arrLength);
    }

    printf("\nSummary:");
    printf("\n - plain: ");
    printSummary(timeSpentPlain, arrNumber);

    fclose(fp);
    return 0;
}