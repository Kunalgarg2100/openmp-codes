#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 100000
int arr[SIZE];
int arrcopy[SIZE];
int partition_serial(int * a, int p, int r)
{
	int lt[r-p];
	int gt[r-p];
	int i;
	int j;
	int key = a[r];
	int lt_n = 0;
	int gt_n = 0;

	for(i = p; i < r; i++){
		if(a[i] < a[r]){
			lt[lt_n++] = a[i];
		}else{
			gt[gt_n++] = a[i];
		}   
	}   

	for(i = 0; i < lt_n; i++){
		a[p + i] = lt[i];
	}   

	a[p + lt_n] = key;

	for(j = 0; j < gt_n; j++){
		a[p + lt_n + j + 1] = gt[j];
	}   

	return p + lt_n;
}

void quicksort_serial(int * a, int p, int r)
{
	int div;
	if(p < r){ 
		div = partition_serial(a, p, r); 
		quicksort_serial(a, p, div - 1); 
		quicksort_serial(a, div + 1, r); 
	}
}


int partition_parellel(int * a, int p, int r)
{
	int lt[r-p];
	int gt[r-p];
	int i;
	int j;
	int key = a[r];
	int lt_n = 0;
	int gt_n = 0;

#pragma omp parallel for
	for(i = p; i < r; i++){
		if(a[i] < a[r]){
			lt[lt_n++] = a[i];
		}else{
			gt[gt_n++] = a[i];
		}
	}

	for(i = 0; i < lt_n; i++){
		a[p + i] = lt[i];
	}

	a[p + lt_n] = key;

	for(j = 0; j < gt_n; j++){
		a[p + lt_n + j + 1] = gt[j];
	}

	return p + lt_n;
}

void quicksort_parellel(int * a, int p, int r, int threads)
{
	if(threads == 1)
		quicksort_serial(a, p, r);

	else
	{
		int div;
		//printf("ENTERED QUICKSORT!!");
		if(p < r){
			div = partition_parellel(a, p, r);
#pragma omp task
			quicksort_parellel(a, p, div - 1, threads/2);
#pragma omp task
			quicksort_parellel(a, div + 1, r, threads - threads/2);

		}
	}
}




int main(void)
{
	int i;
	int sz = SIZE;
	double start_time, run_time;
	srand(5); 
	//	printf("Initializing the arrays with random numbers...\n");
	for (i=0; i<sz; i++){
		arr[i] = 1+(rand()%sz);
		arrcopy[i] = arr[i];

	}
	//    printf("\n\nArray BEFORE sorting: \n");
	//		for( i = 0 ; i < 15; i++ ) 
	//		{
	//			printf("%d ", a[i]);
	//		}
	start_time = omp_get_wtime();
	quicksort_serial(arr, 0, sz-1);
	run_time = omp_get_wtime() - start_time;
	printf("Serial quicksort took %f seconds \n", run_time);

	int threads;
	omp_set_num_threads(omp_get_max_threads());

#pragma omp parallel
	{
#pragma omp single nowait
		{
			threads =  omp_get_num_threads();
			printf("%d\n",threads);
			start_time = omp_get_wtime();
			quicksort_parellel(arrcopy, 0, sz-1, threads);
			run_time = omp_get_wtime() - start_time;
			printf("Parellel quicksort took %f seconds \n", run_time);
		} 
	}

	//   printf("NUMBER OF THREADS : %d\n", threads);

	//    printf("\n\nArray after sorting\n");
	//    for(i = 0;i < 10; i++){
	//        printf("%d ", acopy[i]);
	//    }
	//    printf("\n");
	return 0;
}
