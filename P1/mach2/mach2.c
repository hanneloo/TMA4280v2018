#include "mach2.h"

double mach2(int nthreads, int n)
{
  double arctan1 = arctan(nthreads, 0.2, n);
  double x = (double)1/(double)239;
  double arctan2 = arctan(nthreads, x, n);
  return 16*arctan1 - 4*arctan2;
}
