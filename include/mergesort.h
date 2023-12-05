
void mergeSortSequential(int *arr, long size);

void mergeSortOpenMP(int *arr, long size);
void mergeSortOpenMPOpt(int *arr, long size);

#if __cplusplus
extern "C" {
#endif

void mergeSortCUDA(int *arr, long size);
void mergeSortCUDAOpt(int *arr, long size);

#if __cplusplus
}
#endif