#include "reduc.h"

double reduczeta1(int iterations, int size, int rank)
{
  int local_count = iterations/size+1;
  double *values;
  if(rank==0)
    {
      values = calloc((local_count*size)+size, sizeof(double));
      processzero(iterations, values);
    }
  double *local_values = calloc(local_count, sizeof(double));
  scatter(local_values, values, local_count);
  double sum_now = compute_sum_now(local_values, local_count);
  double global_sum = reduc(size, rank, sum_now);
  if(rank == 0)
    {
      free(values);
    }
  free(local_values);
  double result = sqrt(global_sum*6);
  return result;
}
