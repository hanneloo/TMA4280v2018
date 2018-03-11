#include "reduc.h"

double reduc(int size, int rank, double sum_now)
{

  //Reduc MPI function
  // double sum = 0;
  //MPI_Allreduce(&sum_now, &sum, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

  //Recursive doubling
  double sum = sum_now;
  int d = 1;
  while(d < size)
    {
      int exchange = rank ^ d;
      double recv = 0;
      MPI_Sendrecv(&sum, 1, MPI_DOUBLE, exchange, 0, &recv, 1, MPI_DOUBLE, exchange, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      sum += recv;
      d = d << 1;
    }
  return sum;
}
