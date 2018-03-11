#include "hybrid.h"

double hybridzeta(int nthreads, int iterations, int size, int rank)
{
  int local_count = iterations/size +1;
  double *values;
  if (rank == 0)
    {
      values = calloc((local_count * size)+size, sizeof(double));
      processzero(iterations, values, nthreads);
    }
  double *local_values = calloc(local_count, sizeof(double));
  scatter(local_values, values, local_count);
  double sum_now = compute_sum_now(local_values, local_count);
  double sum = 0;
  MPI_Reduce(&sum_now, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
  if(rank == 0)
    {
      free(values);
    }
  free(local_values);
  double result = sqrt(sum*6);
  return result;
}
