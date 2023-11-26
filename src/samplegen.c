#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generateSamples(int arraysToGenerate, int lengthOfArray, char* outputFile) {
    srand((unsigned int)time(NULL));
    FILE *fp;
    fp = fopen(outputFile, "w");
    fprintf(fp, "%d %d\n", arraysToGenerate, lengthOfArray);
    for (int arrayNum = 0; arrayNum < arraysToGenerate; arrayNum++) {
        for (int i = 0; i < lengthOfArray; i++) {
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
            "arg3: output file name");
        return 1;
    }
    int arraysToGenerate = atoi(argv[1]);
    int lengthOfArray = atoi(argv[2]);
    char* outputFile = argv[3];
    printf("Sample generator:\n"
        "\tArrays to generate: %d\n"
        "\tLength of each array: %d\n"
        "\tOutput file: %s\n",
        arraysToGenerate, lengthOfArray, outputFile);
    generateSamples(arraysToGenerate, lengthOfArray, outputFile);
    printf("done");
    return 0;
}