#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generateSamples(long arraysToGenerate, long lengthOfArray, char* outputFile) {
    srand((unsigned int)time(NULL));
    FILE *fp;
    fp = fopen(outputFile, "w");
    fprintf(fp, "%ld %ld\n", arraysToGenerate, lengthOfArray);
    for (long arrayNum = 0; arrayNum < arraysToGenerate; arrayNum++) {
        for (long i = 0; i < lengthOfArray; i++) {
            int r = rand();
            fprintf(fp, "%d ", r);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
    return;
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        printf("Insufficient number of args:\n"
            "arg1: number of arrays to generate\n"
            "arg2: length of each array\n"
            "arg3: output file name\n");
        return 1;
    }
    long arraysToGenerate, lengthOfArray;
    sscanf(argv[1], "%ld", &arraysToGenerate);
    sscanf(argv[2], "%ld", &lengthOfArray);
    char* outputFile = argv[3];
    printf("Sample generator:\n"
        "\tArrays to generate: %ld\n"
        "\tLength of each array: %ld\n"
        "\tOutput file: %s\n",
        arraysToGenerate, lengthOfArray, outputFile);
    generateSamples(arraysToGenerate, lengthOfArray, outputFile);
    printf("done\n");
    return 0;
}