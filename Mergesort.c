#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define SIZE 1000000

int arr[SIZE];
int tmp[SIZE];

void printarr(int *arr, int n){
    for(int i = 0;i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void merge(int *arr, int size, int *tmp){
    int i = 0;
    int j = size/2;
    int ti = 0;

    while(i < size/2 && j < size){
        if(arr[i] < arr[j]){
            tmp[ti] = arr[i];
            i++;
        }
        else{
            tmp[ti] = arr[j];
            j++;
        }
        ti++;
    }
    while(i < size/2){
        tmp[ti] = arr[i];
        ti++; i++;
    }
    while(j < size){
        tmp[ti] = arr[j];
        ti++; j++;
    }
    memcpy(arr, tmp, size*sizeof(int));
}

void mergesort_omp_parallel(int *arr, int *tmp, int size){
    if(size <= 1)
        return;
#pragma omp task firstprivate(arr, tmp, size)
    mergesort_omp_parallel(arr, tmp, size/2);

#pragma omp task firstprivate(arr, tmp, size)
    mergesort_omp_parallel(arr + (size/2), tmp, size - size/2);

#pragma omp taskwait
    merge(arr, size, tmp);
}

void mergesort_serialize(int *arr, int *tmp, int size){
    if(size <= 1)
        return;
    mergesort_serialize(arr, tmp, size/2);
    mergesort_serialize(arr + (size/2), tmp, size - size/2);
    merge(arr, size, tmp);
}


int main(){
        int i;
        double start_time, run_time;

        /* Initialize */
        srand(time(NULL));
        for(int i=0; i < SIZE; i++)
                arr[i] = rand() % SIZE;

        start_time = omp_get_wtime();
        mergesort_omp_parallel(arr, tmp, SIZE);
        run_time = omp_get_wtime() - start_time;
        printf(" Time to sort(in parallel) Array of size %d is %f seconds \n", SIZE, run_time);

        start_time = omp_get_wtime();
        mergesort_serialize(arr, tmp, SIZE);
        run_time = omp_get_wtime() - start_time;
        printf(" Time to sort(in serial) Array of size %d is %f seconds \n", SIZE, run_time);
        /* TERMINATE PROGRAM */
        return 0;
}
