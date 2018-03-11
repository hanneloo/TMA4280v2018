#include "mach0.h"

double arctan(double x, int n)
{
  double sum = 0;
  for (int i = 0; i<= n; i++)
    {
      double x1 = pow(x, 2*i+1);
      double x2 = 2*i+1;
      double c = 1.0;
      if (i%2 != 0) c = -1.0;
      sum += (c*x1)/x2;
    }
		     
  return sum;
}
