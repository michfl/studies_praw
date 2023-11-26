#include <stdio.h>
#include <benchmark.h>
#include <mergesort.h>

int main() {
    printf("main\n");
    mergeSortPlain();
    mergeSortOpenMP();
    mergeSortCUDA();
    test();
    return 0;
}