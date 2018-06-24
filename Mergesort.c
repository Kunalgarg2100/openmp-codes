#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
#include<time.h>

#define SIZE 1065432

int arr[SIZE];
int tmp[SIZE];

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
        printf(" Time to sort Array of size %d is %f seconds \n", SIZE, run_time);

        /* TERMINATE PROGRAM */
        return 0;

}

void mergesort_omp_parallel(int arr[], int tmp[], int size);
{
        // Check no of threads
        // If threads = 1 use normal merge sort
        // Else use omp parallel sections
        // merge code
}

void merge(int arr[], int tmp [], int size)
{


}
