#include "zeta1.h"


//Each vector in the Riemann zeta function
void processzero(int n, double *values)
{
  for (int i=1; i<=n; i++)
    {
      values[i-1] = 1.0/((double)i*(double)i);
    }
}
