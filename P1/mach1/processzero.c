#include "mach1.h"

void processzero(int n, double *values)
{
  for (int i=0; i<n; i++)
    {
      double c = 1.0;
      if (i%2 != 0) c = -1.0;

      double x = 0.2;
      double x1 = pow(x,2*i+1);
      double x2 = 2*i+1;
      double arctan1 = (c*x1)/x2;

      double xx = (double)1/(double)239;
      double xx1 = pow(xx, 2*i+1);
      double xx2 = 2*i+1;
      double arctan2 = (c*xx1)/xx2;

      values[i] = 16*arctan1-4*arctan2;
    }
}
