#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
#include<time.h>

void rec(int a);
void funcA(int a);
void funcB(int a);

void funcA(int a){
	int TID = omp_get_thread_num();
	if(TID != 0)
		printf("In funcA : this section is executed by thread %d\n", omp_get_thread_num());
	rec(a-1);
}

void funcB(int a){
	int TID = omp_get_thread_num();
	if(TID != 0)
	printf("In funcB : this section is executed by thread %d\n", omp_get_thread_num());
	rec(a-2);

}

void rec(int a)
{
	if(a<0)
		return;
#pragma omp parallel
	{
#pragma omp sections
		{
#pragma omp section
			funcA(a);
#pragma omp section
			funcB(a);
		}
	}
}


int main(){
        int i;
        double start_time, run_time;

        /* Initialize */
        srand(time(NULL));

        start_time = omp_get_wtime();
	rec(15);
        run_time = omp_get_wtime() - start_time;
	return 0;
}

