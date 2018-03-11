#include "mach2.h"

double arctan(int nthreads, double x, int n)
{
  double sum = 0;

#pragma omp parallel for num_threads(nthreads) reduction(+:sum)
  for (int i = 0; i <= n; i++)
    {
      double x1 = pow(x,2*i+1);
      double x2 = 2*i+1;
      double c = 1.0;
      if (i % 2 != 0) c = -1.0;
      sum += (c*x1)/x2;
    }
  return sum;
}
