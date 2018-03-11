#include "mach0.h"

double mach0(int n)
{
  double arctan1 = 16*arctan(0.2, n);
  double x = (double)1/(double)239;
  double arctan2 = 4*arctan(x, n);
  return arctan1 - arctan2;
}
