#include "mach2.h"

int main(int argc, char **argv)
{
  if (argc != 3)
    {
      printf("Usage: %s <n_threads> <n_iterations>\n", argv[0]);
      exit(-1);
    }
  int nthreads = atoi(argv[1]);
  int n = atoi(argv[2]);
  double result = mach2(nthreads,n);
  printf("Result using mach2(threads=%i,iter=%i) is pi = %.15f \n", nthreads, n, result);
}
