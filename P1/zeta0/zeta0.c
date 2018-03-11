#include "zeta0.h"

double  zeta0(int n)
{
  double sum = 0;
  for(double i = 1; i<=n; i++)
    {
      sum += 1/pow(i,2);
    }
  double result = sqrt(sum*6);
  return result;
}
