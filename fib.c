#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
//#define NUM_THREADS 2
/* function that uses recursivity
* to compute fibonacci numbers
*/
long comp_fib_numbers(int n)
{
  // Basic algorithm: f(n) = f(n-1) + f(n-2)
  long fnm1, fnm2, fn;
  if ( n == 0 || n == 1 ) return(n);
#pragma omp task shared(fnm1)
  fnm1 = comp_fib_numbers(n-1);
#pragma omp task shared(fnm2)
  fnm2 = comp_fib_numbers(n-2);
#pragma omp taskwait
  fn = fnm1 + fnm2;
  return(fn);
}

int fibserial(int n)
{
   if (n <= 1)
      return n;
   return fibserial(n-1) + fibserial(n-2);
}


int main(int argc, char **argv)
{
  int n;
double start_time, run_time;
  long result;
  if(argc<2){
    printf("usage ./a.out <number>\n");
    exit(1);
  }
  n = atoi(argv[1]);
  //#pragma omp parallel num_threads(NUM_THREADS)
#pragma omp parallel
  {
#pragma omp single nowait
    {
      start_time = omp_get_wtime();
      result = comp_fib_numbers(n);
      run_time = omp_get_wtime() - start_time;
  printf(" Time to compute(in parallel) : %f", run_time);
    } // end of single region
  } // end of parallel region
  

  start_time = omp_get_wtime();
      result = fibserial(n);
      run_time = omp_get_wtime() - start_time;
  printf(" Time to compute(in series) : %f", run_time);

  return 0;
}
