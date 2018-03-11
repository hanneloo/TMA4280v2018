#include "hybrid.h"

void vtesthybrid();

int main (int argc, char **argv) {
  vtesthybrid();
}

void vtesthybrid()
{
  int size, rank, numthreads, n;
  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (((size & (size-1)) != 0))
    {
      if(!rank)
	{
	  fprintf(stderr, "'%i' is not a power of two, try again with a different <p>\n", size);
	}
    }

  char *test_name = "hybridzeta1 vtest";
  char *log_rel_path = "vtest.txt";
  char *log_abs_path;

  FILE *log = NULL;
  if (!rank)
    log = fopen(log_rel_path, "a");

  for (int j = 1; j <= 3; j++)
    {
      int nthreads = pow(2,j);
      for (int k = 1; k <= 24; k++)
	{
	  int n = pow(2,k);
	  double t1 = MPI_Wtime();
	  double result = hybridzeta(nthreads, n, size, rank);
	  double t2 = MPI_Wtime();
	  double time = t2-t1;
	  if (rank == 0)
	    {
	      double diff = fabs(result-M_PI);
	      fprintf(log, "%s p=%i t=%i: computed = %.20f, error=%.20f, time=%.20f, n=%i\n",test_name, size, nthreads,  result, diff, time, n);
	    }
	}
      log_abs_path = realpath(log_rel_path, NULL);
      printf("%s p=%i t=%i results written to: %s\n", test_name, size, nthreads, log_abs_path);
      free(log_abs_path);
      //free(log_rel_path);
    }
  if (!rank)
    {
      fclose(log);
    }
  MPI_Finalize();
}
