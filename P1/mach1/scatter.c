#include "mach1.h"

void scatter(double *local_values, double *values, int local_count)
{
  MPI_Scatter(values, local_count, MPI_DOUBLE, local_values, local_count, MPI_DOUBLE, 0, MPI_COMM_WORLD);
}
