#include "zeta1.h"

double compute_sum_now(double *local_values, int count)
{
  double sum = 0;
  for (int i = 0; i<count; i++)
    {
      sum += local_values[i];
    }
  return sum;
}
